/*******************************************************************************

Licensed to the OpenCOR team under one or more contributor license agreements.
See the NOTICE.txt file distributed with this work for additional information
regarding copyright ownership. The OpenCOR team licenses this file to you under
the Apache License, Version 2.0 (the "License"); you may not use this file
except in compliance with the License. You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.

*******************************************************************************/

//==============================================================================
// Single cell view information graphs widget
//==============================================================================

#include "cellmlfileruntime.h"
#include "singlecellviewgraphpanelwidget.h"
#include "singlecellviewinformationgraphswidget.h"
#include "singlecellviewplugin.h"
#include "singlecellviewsimulation.h"
#include "singlecellviewsimulationwidget.h"
#include "singlecellviewwidget.h"

//==============================================================================

#include <QFileInfo>
#include <QMenu>
#include <QScrollBar>
#include <QSettings>

//==============================================================================

#include "ui_singlecellviewinformationgraphswidget.h"

//==============================================================================

namespace OpenCOR {
namespace SingleCellView {

//==============================================================================

SingleCellViewInformationGraphsWidget::SingleCellViewInformationGraphsWidget(SingleCellViewPlugin *pPlugin,
                                                                             QWidget *pParent) :
    QStackedWidget(pParent),
    Core::CommonWidget(pParent),
    mGui(new Ui::SingleCellViewInformationGraphsWidget),
    mViewWidget(pPlugin->viewWidget()),
    mGraphPanels(QMap<Core::PropertyEditorWidget *, SingleCellViewGraphPanelWidget *>()),
    mPropertyEditors(QMap<SingleCellViewGraphPanelWidget *, Core::PropertyEditorWidget *>()),
    mPropertyEditor(0),
    mGraphs(QMap<Core::Property *, SingleCellViewGraphPanelPlotGraph *>()),
    mGraphProperties(QMap<SingleCellViewGraphPanelPlotGraph *, Core::Property *>()),
    mParameterActions(QMap<QAction *, CellMLSupport::CellmlFileRuntimeParameter *>()),
    mFileName(QString()),
    mHorizontalScrollBarValue(0)
{
    // Set up the GUI

    mGui->setupUi(this);

    // Create our context menus and populate our main context menu

    mContextMenu = new QMenu(this);
    mParametersContextMenu = new QMenu(this);

    mContextMenu->addAction(mGui->actionAddGraph);
    mContextMenu->addSeparator();
    mContextMenu->addAction(mGui->actionRemoveCurrentGraph);
    mContextMenu->addAction(mGui->actionRemoveAllGraphs);
    mContextMenu->addSeparator();
    mContextMenu->addAction(mGui->actionSelectAllGraphs);
    mContextMenu->addAction(mGui->actionUnselectAllGraphs);
}

//==============================================================================

SingleCellViewInformationGraphsWidget::~SingleCellViewInformationGraphsWidget()
{
    // Delete the GUI

    delete mGui;
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::retranslateUi()
{
    // Retranslate our GUI

    mGui->retranslateUi(this);

    // Retranslate all our property editors

    foreach (Core::PropertyEditorWidget *propertyEditor, mPropertyEditors)
        propertyEditor->retranslateUi();

    // Retranslate the information about our graphs properties
    // Note: no need to do this for all our property editors (i.e. call
    //       updateAllGraphsInfo()) since this will automatically be done when
    //       selecting another graph panel. So, instead, we just do this for our
    //       current graph panel...

    updateGraphsInfo();
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::initialize(SingleCellViewSimulation *pSimulation)
{
    // Populate our parameters context menu

    populateParametersContextMenu(pSimulation->runtime());

    // Update our graphs information

    updateAllGraphsInfo();
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::finalize()
{
    // Clear our parameters context menu

    mParametersContextMenu->clear();
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::initialize(SingleCellViewGraphPanelWidget *pGraphPanel)
{
    // Retrieve the property editor for the given file name or create one, if
    // none exists

    Core::PropertyEditorWidget *oldPropertyEditor = mPropertyEditor;

    mPropertyEditor = mPropertyEditors.value(pGraphPanel);

    if (!mPropertyEditor) {
        // No property editor exists for the given graph panel, so create one

        mPropertyEditor = new Core::PropertyEditorWidget(false, false, this);

        // We want our own context menu for our property editor

        mPropertyEditor->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(mPropertyEditor, SIGNAL(customContextMenuRequested(const QPoint &)),
                this, SLOT(propertyEditorContextMenu(const QPoint &)));

        // Keep track of changes to the horizontal bar's value

        connect(mPropertyEditor->horizontalScrollBar(), SIGNAL(valueChanged(int)),
                this, SLOT(propertyEditorHorizontalScrollBarValueChanged(const int &)));

        // Keep track of changes to columns' width

        connect(mPropertyEditor->header(), SIGNAL(sectionResized(int, int, int)),
                this, SLOT(propertyEditorSectionResized(const int &, const int &, const int &)));

        // Keep track of when the user changes a property value

        connect(mPropertyEditor, SIGNAL(propertyChanged(Core::Property *)),
                this, SLOT(graphChanged(Core::Property *)));

        // Add our new property editor to ourselves

        addWidget(mPropertyEditor);

        // Keep track of the link between our existing graph panel and our new
        // property editor

        mGraphPanels.insert(mPropertyEditor, pGraphPanel);
        mPropertyEditors.insert(pGraphPanel, mPropertyEditor);
    }

    // Set the value of the property editor's horizontal scroll bar

    mPropertyEditor->horizontalScrollBar()->setValue(mHorizontalScrollBarValue);

    // Set our property editor's columns' width

    if (oldPropertyEditor) {
        for (int i = 0, iMax = oldPropertyEditor->header()->count(); i < iMax; ++i)
            mPropertyEditor->setColumnWidth(i, oldPropertyEditor->columnWidth(i));
    }

    // Set our retrieved property editor as our current widget

    setCurrentWidget(mPropertyEditor);

    // Update our graphs information
    // Note: this is in case the user changed the locale and then switched to a
    //       different graph panel...

    updateAllGraphsInfo();
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::finalize(SingleCellViewGraphPanelWidget *pGraphPanel)
{
    // Remove track of the link betwen our graph panel and our property editor

    mGraphPanels.remove(mPropertyEditors.value(pGraphPanel));
    mPropertyEditors.remove(pGraphPanel);
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::addGraph(SingleCellViewGraphPanelPlotWidget *pPlot,
                                                     SingleCellViewGraphPanelPlotGraph *pGraph)
{
    Q_UNUSED(pPlot);

    // Make sure that we have a property editor

    if (!mPropertyEditor)
        return;

    // Prevent ourselves from being updated (to avoid flickering)

    mPropertyEditor->setUpdatesEnabled(false);

    // Create a section for our newly added graph

    Core::Property *graphProperty = mPropertyEditor->addSectionProperty();

    graphProperty->setCheckable(true);
    graphProperty->setChecked(true);

    // Keep track of the link between our given graph and our graph property

    mGraphs.insert(graphProperty, pGraph);
    mGraphProperties.insert(pGraph, graphProperty);

    // Create some properties for our graph
    // Note: to add properties will result in the propertyChanged() signal being
    //       emitted, but we don't want to handle that signal (at least, not
    //       when creating a graph since not everyting may be set yet so this
    //       might cause more problems than anything), so we must disconnect
    //       ourselves from it before adding the properties (and then reconnect
    //       ourselves to it once we are done)...

    disconnect(mPropertyEditor, SIGNAL(propertyChanged(Core::Property *)),
               this, SLOT(graphChanged(Core::Property *)));

    mPropertyEditor->addListProperty(graphProperty);

    Core::Property *xProperty = mPropertyEditor->addStringProperty(pGraph->parameterX()?pGraph->parameterX()->fullyFormattedName():Core::UnknownValue, graphProperty);
    Core::Property *yProperty = mPropertyEditor->addStringProperty(pGraph->parameterY()?pGraph->parameterY()->fullyFormattedName():Core::UnknownValue, graphProperty);

    xProperty->setEditable(true);
    yProperty->setEditable(true);

    connect(mPropertyEditor, SIGNAL(propertyChanged(Core::Property *)),
            this, SLOT(graphChanged(Core::Property *)));

    // Update the information about our new graph

    updateGraphsInfo(graphProperty);

    // Allow ourselves to be updated again

    mPropertyEditor->setUpdatesEnabled(true);

    // Make sure that our property editor is our current widget

    setCurrentWidget(mPropertyEditor);
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::removeGraphs(SingleCellViewGraphPanelPlotWidget *pPlot,
                                                         const SingleCellViewGraphPanelPlotGraphs &pGraphs)
{
    Q_UNUSED(pPlot);

    // Make sure that we have a property editor

    if (!mPropertyEditor)
        return;

    // Prevent ourselves from being updated (to avoid flickering)

    mPropertyEditor->setUpdatesEnabled(false);

    // Remove the graph properties associated with the given graphs, as well as
    // their trace

    foreach (SingleCellViewGraphPanelPlotGraph *graph, pGraphs) {
        Core::Property *property = mGraphProperties.value(graph);

        mPropertyEditor->removeProperty(property);

        mGraphs.remove(property);
        mGraphProperties.remove(graph);
    }

    // Allow ourselves to be updated again

    mPropertyEditor->setUpdatesEnabled(true);
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::on_actionAddGraph_triggered()
{
    // Ask the graph panel associated with our current property editor to add an
    // 'empty' graph

    mGraphPanels.value(mPropertyEditor)->addGraph(new SingleCellViewGraphPanelPlotGraph());
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::on_actionRemoveCurrentGraph_triggered()
{
    // Ask the graph panel associated with our current property editor to remove
    // the current graph

    mGraphPanels.value(mPropertyEditor)->removeGraphs(SingleCellViewGraphPanelPlotGraphs() << mGraphs.value(mPropertyEditor->currentProperty()));
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::on_actionRemoveAllGraphs_triggered()
{
    // Ask the graph panel associated with our current property editor to remove
    // all the graphs

    mGraphPanels.value(mPropertyEditor)->removeGraphs(mGraphs.values());
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::selectAllGraphs(const bool &pSelect)
{
    // (Un)select all the graphs
    // Note: normally, we would only update the checked state of our graph
    //       properties, which would in turn update the selected state of our
    //       graphs and let people know that they have been updated. Now, the
    //       problem with this is that every single graph is going to be shown/
    //       hidden indivdually. So, if we have loads of graphs with many data
    //       points, then it's going to be slow. So, instead, we disconnect the
    //       propertyChanged() signal, update the checked state of our graph
    //       properties as well as the selected state of our graphs, and then
    //       let people know that all the graphs have been updated...

    disconnect(mPropertyEditor, SIGNAL(propertyChanged(Core::Property *)),
               this, SLOT(graphChanged(Core::Property *)));

    foreach (Core::Property *property, mGraphProperties)
        property->setChecked(pSelect);

    foreach (SingleCellViewGraphPanelPlotGraph *graph, mGraphs)
        graph->setSelected(pSelect);

    if (mGraphs.count()) {
        emit graphsUpdated(qobject_cast<SingleCellViewGraphPanelPlotWidget *>(mGraphs.values().first()->plot()),
                           mGraphs.values());
    }

    connect(mPropertyEditor, SIGNAL(propertyChanged(Core::Property *)),
            this, SLOT(graphChanged(Core::Property *)));
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::on_actionSelectAllGraphs_triggered()
{
    // Select all the graphs

    selectAllGraphs(true);
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::on_actionUnselectAllGraphs_triggered()
{
    // Unselect all the graphs

    selectAllGraphs(false);
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::updateGui()
{
    // Update our graphs information
    // Note: this is useful, for example, if we created a graph for a file that
    //       has not yet been selected, in which case the graph will initially
    //       be invalid, but it should become valid after we have switched to
    //       that file and back...

    updateAllGraphsInfo();
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::finishEditing()
{
    // Make sure that we have a property editor

    if (!mPropertyEditor)
        return;

    // Ask our property editor to finish editing

    mPropertyEditor->finishEditing();
}

//==============================================================================

static const auto PropertySeparator = QStringLiteral(" | ");

//==============================================================================

Core::Properties SingleCellViewInformationGraphsWidget::graphProperties(SingleCellViewGraphPanelWidget *pGraphPanel,
                                                                        const QString &pFileName) const
{
    // Retrieve and return all the graph properties associated with the given
    // graph and file name, if any

    Core::Properties res = Core::Properties();
    Core::PropertyEditorWidget *propertyEditor = mPropertyEditors.value(pGraphPanel);

    if (propertyEditor) {
        foreach (Core::Property *property, propertyEditor->properties()) {
            // The property should be returned if it is a section (i.e. a graph
            // property), is checked (i.e. a selected graph) and have its first
            // sub-property (i.e. to which model the graph applies) has either a
            // value of "Current" or that of the given file name

            if (   (property->type() == Core::Property::Section)
                && property->isChecked()) {
                QString modelPropertyValue = property->properties().first()->value();

                if (   !modelPropertyValue.compare(tr("Current"))
                    || !modelPropertyValue.split(PropertySeparator).last().compare(pFileName)) {
                    res << property;
                }
            }
        }
    }

    return res;
}

//==============================================================================

int SingleCellViewInformationGraphsWidget::headerCount() const
{
    // Return the number of headers in our property editors

    return mPropertyEditor?mPropertyEditor->header()->count():0;
}

//==============================================================================

int SingleCellViewInformationGraphsWidget::columnWidth(const int &pIndex) const
{
    // Return the width of the given column

    return mPropertyEditor?mPropertyEditor->columnWidth(pIndex):0;
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::setColumnWidth(const int &pIndex,
                                                           const int &pColumnWidth)
{
    // Return the width of the given column

    if (mPropertyEditor)
        mPropertyEditor->setColumnWidth(pIndex, pColumnWidth);
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::propertyEditorContextMenu(const QPoint &pPosition) const
{
    Q_UNUSED(pPosition);

    // Make sure that we have a property editor

    if (!mPropertyEditor)
        return;

    // Retrieve our current property, if any

    Core::Property *crtProperty = mPropertyEditor->currentProperty();

    // Update the enabled state of some of our actions

    mGui->actionRemoveCurrentGraph->setEnabled(crtProperty);
    mGui->actionRemoveAllGraphs->setEnabled(!mPropertyEditor->properties().isEmpty());

    bool canSelectAllGraphs = false;
    bool canUnselectAllGraphs = false;

    foreach (Core::Property *property, mGraphProperties) {
        bool graphSelected = property->isChecked();

        canSelectAllGraphs   = canSelectAllGraphs   || !graphSelected;
        canUnselectAllGraphs = canUnselectAllGraphs ||  graphSelected;
    }

    mGui->actionSelectAllGraphs->setEnabled(canSelectAllGraphs);
    mGui->actionUnselectAllGraphs->setEnabled(canUnselectAllGraphs);

    // Show the context menu, or not, depending on the type of property we are
    // dealing with, if any

    if (   !crtProperty
        || (crtProperty->type() == Core::Property::Section)
        || (!crtProperty->name().compare(tr("Model")))) {
        mContextMenu->exec(QCursor::pos());
    } else {
        mParametersContextMenu->exec(QCursor::pos());
    }
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::propertyEditorHorizontalScrollBarValueChanged(const int &pValue)
{
    // Keep track of the property editor's horizontal scroll bar value

    mHorizontalScrollBarValue = pValue;
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::propertyEditorSectionResized(const int &pIndex,
                                                                         const int &pOldSize,
                                                                         const int &pNewSize)
{
    Q_UNUSED(pOldSize);

    // Let people know that a header section has been resized

    emit headerSectionResized(pIndex, pOldSize, pNewSize);
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::populateParametersContextMenu(CellMLSupport::CellmlFileRuntime *pRuntime)
{
    // Populate our parameters context menu with the contents of our main
    // context menu

    mParametersContextMenu->addActions(mContextMenu->actions());
    mParametersContextMenu->addSeparator();

    // Now, add our model parameters to it

    QString componentHierarchy = QString();
    QMenu *componentMenu = 0;

    foreach (CellMLSupport::CellmlFileRuntimeParameter *parameter, pRuntime->parameters()) {
        // Check whether the current parameter is in the same component
        // hierarchy as the previous one

        QString crtComponentHierarchy = parameter->formattedComponentHierarchy();

        if (crtComponentHierarchy.compare(componentHierarchy)) {
            // The current parameter is in a different component hierarchy, so
            // create a new menu hierarchy for our 'new' component, reusing
            // existing menus, whenever possible

            QMenu *menu = mParametersContextMenu;

            foreach (const QString &component, parameter->componentHierarchy()) {
                // Check whether we already have a menu for our current
                // component

                componentMenu = 0;

                foreach (QObject *object, menu->children()) {
                    QMenu *subMenu = qobject_cast<QMenu *>(object);

                    if (subMenu && !subMenu->menuAction()->text().compare(component)) {
                        componentMenu = subMenu;

                        break;
                    }
                }

                // Create a new menu for our current component, if none could be
                // found

                if (!componentMenu) {
                    componentMenu = new QMenu(component, menu);

                    menu->addMenu(componentMenu);
                }

                // Get ready for the next component in our component hierarchy

                menu = componentMenu;
            }

            // Keep track of the new component hierarchy

            componentHierarchy = crtComponentHierarchy;
        }

        // Make sure that we have a 'current' component menu
        // Note: this should never happen, but we never know...

        if (!componentMenu)
            continue;

        // Add the current parameter to the 'current' component menu

        QAction *parameterAction = componentMenu->addAction(SingleCellViewSimulationWidget::parameterIcon(parameter->type()),
                                                            parameter->formattedName());

        // Create a connection to handle the parameter value update

        connect(parameterAction, SIGNAL(triggered(bool)),
                this, SLOT(updateParameterValue()));

        // Keep track of the parameter associated with our model parameter
        // action

        mParameterActions.insert(parameterAction, parameter);
    }
}

//==============================================================================

bool SingleCellViewInformationGraphsWidget::checkParameter(CellMLSupport::CellmlFileRuntime *pRuntime,
                                                           SingleCellViewGraphPanelPlotGraph *pGraph,
                                                           Core::Property *pParameterProperty,
                                                           const bool &pParameterX) const
{
    // Check that the information held by the given property corresponds to
    // an existing parameter in our runtime

    CellMLSupport::CellmlFileRuntimeParameter *res = 0;

    if (pRuntime) {
        // Retrieve the component and parameter of the property

        QStringList info = pParameterProperty->value().split(".");
        QStringList componentHierarchy = info;
        QString parameterName = info.last();
        int parameterDegree = parameterName.size();

        componentHierarchy.removeLast();

        // Determine the degree of our parameter, if any

        parameterName.replace("'", QString());

        parameterDegree -= parameterName.size();

        // Check whether we can find our property among our runtime's parameters

        foreach (CellMLSupport::CellmlFileRuntimeParameter *parameter, pRuntime->parameters()) {
            if (   (parameter->componentHierarchy() == componentHierarchy)
                && !parameter->name().compare(parameterName)
                && (parameter->degree() == parameterDegree)) {
                res = parameter;

                break;
            }
        }
    }

    // Update our parameter property based on whether it corresponds to an
    // existing parameter in our runtime

    static const QIcon BlankIcon   = QIcon(":/blank.png");
    static const QIcon WarningIcon = QIcon(":/oxygen/status/task-attention.png");

    pParameterProperty->setIcon(res?BlankIcon:WarningIcon);
    pParameterProperty->setExtraInfo(res?
                                         QString():
                                         pRuntime?
                                             tr("does not exist"):
                                             tr("no runtime"));

    // Keep track of the existing parameter, if any, to which our property
    // corresponds

    if (pParameterX)
        pGraph->setParameterX(res);
    else
        pGraph->setParameterY(res);

    return res;
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::updateGraphInfo(Core::Property *pProperty,
                                                            const QString &pFileName)
{
    // Make sure that we have a property

    if (!pProperty)
        return;

    // Update the graph information by checking the new value of the given
    // section property

    // Update the model property's icon and graph colour, based on the value of
    // the model property, and determine the file name from which we will have
    // to check our X and Y properties

    static const QIcon LockedIcon   = QIcon(":/oxygen/status/object-locked.png");
    static const QIcon UnlockedIcon = QIcon(":/oxygen/status/object-unlocked.png");

    SingleCellViewGraphPanelPlotGraph *graph = mGraphs.value(pProperty);
    QString fileName = mFileName;
    QPen oldPen = graph->pen();
    QPen newPen = oldPen;

    if (!pFileName.compare(tr("Current"))) {
        pProperty->properties()[0]->setIcon(UnlockedIcon);

        newPen.setColor(Qt::darkBlue);
    } else {
        pProperty->properties()[0]->setIcon(LockedIcon);

        newPen.setColor(Qt::darkRed);

        fileName = pFileName.split(PropertySeparator).last();
    }

    graph->setPen(newPen);

    // Check that the parameters represented by the value of the X and Y
    // properties exist for the current/selected model
    // Note: we absolutely want to check the parameter (so that an icon can be
    //       assigned to its corresponding property) , hence the order of our &&
    //       assignment...

    bool graphOk = true;
    CellMLSupport::CellmlFileRuntime *runtime = mViewWidget->runtime(fileName);
    CellMLSupport::CellmlFileRuntimeParameter *oldParameterX = graph->parameterX();
    CellMLSupport::CellmlFileRuntimeParameter *oldParameterY = graph->parameterY();

    graphOk = checkParameter(runtime, graph, pProperty->properties()[1], true) && graphOk;
    graphOk = checkParameter(runtime, graph, pProperty->properties()[2], false) && graphOk;

    // Update our section's name, if possible
    // Note: indeed, when populating ourselves, updateGraphInfo() gets called
    //       (through graphChanged()), yet we don't want to (and can't) do what
    //       follows if not all the properties are available...

    pProperty->setName( pProperty->properties()[1]->value()
                       +PropertySeparator
                       +pProperty->properties()[2]->value());

    // Update the status (i.e. icon) of our (section) property

    static const QIcon BlankIcon   = QIcon(":/blank.png");
    static const QIcon WarningIcon = QIcon(":/oxygen/status/task-attention.png");

    pProperty->setIcon(graphOk?BlankIcon:WarningIcon);

    // Update the file name with which the graph is associated

    graph->setFileName(fileName);

    // Let people know if we consider that the graph has been updated

    if (   (oldParameterX != graph->parameterX())
        || (oldParameterY != graph->parameterY())
        || (oldPen != newPen)) {
        emit graphsUpdated(qobject_cast<SingleCellViewGraphPanelPlotWidget *>(graph->plot()),
                           SingleCellViewGraphPanelPlotGraphs() << graph);
    }
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::graphChanged(Core::Property *pProperty)
{
    // The graph has changed, which means that either it has been un/selected or
    // that the value of its model, X or Y parameter property has changed

    if (pProperty->type() == Core::Property::Section) {
        // The property associated with the graph is a section, which means that
        // the graph has been un/selected, so update its selected state and let
        // people know that our graph has been updated

        SingleCellViewGraphPanelPlotGraph *graph = mGraphs.value(pProperty);

        if (graph) {
            graph->setSelected(pProperty->isChecked());

            emit graphsUpdated(qobject_cast<SingleCellViewGraphPanelPlotWidget *>(graph->plot()),
                               SingleCellViewGraphPanelPlotGraphs() << graph);
        }
    } else {
        // Either the model, X or Y parameter property of the graph has changed,
        // so update its information
        // Note: updateGraphInfo() will emit the graphsUpdated() signal, if
        //       needed...

        updateGraphInfo(pProperty->parentProperty(),
                        pProperty->parentProperty()->properties()[0]->value());
    }
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::updateGraphsInfo(Core::Property *pSectionProperty)
{
    // Make sure that we have a property editor

    if (!mPropertyEditor)
        return;

    // Make sure that no editing is in progress

    finishEditing();

    // Use the given section property or retrieve the ones for our current
    // property editor

    QList<Core::Property *> graphProperties = QList<Core::Property *>();

    if (pSectionProperty) {
        graphProperties << pSectionProperty;
    } else {
        foreach (Core::Property *property, mPropertyEditor->properties()) {
            if (property->type() == Core::Property::Section)
                graphProperties << property;
        }
    }

    // Determine the model list values

    QStringList modelListValues = QStringList();

    foreach (const QString &fileName, mViewWidget->fileNames())
        modelListValues << QFileInfo(fileName).fileName()+PropertySeparator+fileName;

    modelListValues.sort();

    modelListValues.prepend(QString());
    modelListValues.prepend(tr("Current"));

    // Go through our graph properties and update (incl. retranslate) their
    // information

    foreach (Core::Property *graphProperty, graphProperties) {
        graphProperty->properties()[0]->setName(tr("Model"));
        graphProperty->properties()[1]->setName(tr("X"));
        graphProperty->properties()[2]->setName(tr("Y"));

        // Keep track of the current model value, so that we can safely update
        // its list values and then select the correct model value back

        QString oldModelValue = graphProperty->properties()[0]->value();
        QString newModelValue = oldModelValue;

        graphProperty->properties()[0]->setListValues(modelListValues, false);
        // Note: we don't want setListValues() to emit a signal since one will
        //       be emitted as a result of our call to setValue() below...

        if (newModelValue.isEmpty()) {
            // newModelValue is empty, which means that this is the first time
            // we come here, so update our graph info using the current value of
            // our model property

            newModelValue = graphProperty->properties()[0]->value();
        } else if (!modelListValues.contains(oldModelValue)) {
            // Our old model value is not in our new model list values, which
            // means that either the value of the model property was "Current"
            // (and the locale got changed) or the current file got renamed, so
            // we use that instead

            if (oldModelValue.contains(PropertySeparator)) {
                // The current file got renamed

                newModelValue = QFileInfo(mFileName).fileName()+PropertySeparator+mFileName;
            } else {
                // The value of the model property was "Current" (and the locale
                // got changed)

                newModelValue = tr("Current");
            }
        }

        // Set the value of our model property to newModelValue (which will
        // result in updateGraphInfo() being called, so we are all fine)

        graphProperty->properties()[0]->setValue(newModelValue, true);
        // Note: we must force the setting of the value since it may very well
        //       be that it's the same as before, yet we want the signal
        //       associated with setValue() to be emitted (so that
        //       updateGraphInfo() can then be called)...
    }
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::updateAllGraphsInfo()
{
    // Update the information about our graphs properties and this for all our
    // property editors, so first keep track of our active property editor

    Core::PropertyEditorWidget *oldPropertyEditor = mPropertyEditor;

    // Go through our property editors and update the information about the
    // graph properties they hold

    foreach (Core::PropertyEditorWidget *propertyEditor, mPropertyEditors) {
        mPropertyEditor = propertyEditor;

        updateGraphsInfo();
    }

    // Retrieve our originally active property editor

    mPropertyEditor = oldPropertyEditor;
}

//==============================================================================

void SingleCellViewInformationGraphsWidget::updateParameterValue()
{
    // Update the current property's value

    mPropertyEditor->currentProperty()->setValue(mParameterActions.value(qobject_cast<QAction *>(sender()))->fullyFormattedName());
}

//==============================================================================

}   // namespace SingleCellView
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
