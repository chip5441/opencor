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
// CellML annotation view metadata normal view details widget
//==============================================================================

#include "cellmlannotationvieweditingwidget.h"
#include "cellmlannotationviewmetadatanormalviewdetailswidget.h"
#include "cellmlannotationviewmetadatawebviewwidget.h"
#include "filemanager.h"
#include "guiutils.h"
#include "usermessagewidget.h"

//==============================================================================

#include "ui_cellmlannotationviewmetadatanormalviewdetailswidget.h"

//==============================================================================

#include <Qt>

//==============================================================================

#include <QApplication>
#include <QClipboard>
#include <QMenu>
//#include <QPoint>
//#include <QRegularExpression>
#include <QScrollArea>
#include <QStackedWidget>

//==============================================================================

namespace OpenCOR {
namespace CellMLAnnotationView {

//==============================================================================

CellmlAnnotationViewMetadataNormalViewDetailsWidget::CellmlAnnotationViewMetadataNormalViewDetailsWidget(CellmlAnnotationViewEditingWidget *pParent) :
    Core::Widget(pParent),
    mCellmlFile(pParent->cellmlFile()),
    mGui(new Ui::CellmlAnnotationViewMetadataNormalViewDetailsWidget),
    mElement(0),
    mRdfTripleInformation(QString()),
    mType(No),
    mLookUpInformation(First),
    mVerticalScrollBarPosition(0),
    mNeighbourRow(0),
    mRdfTriplesMapping(QMap<QObject *, CellMLSupport::CellmlFileRdfTriple *>()),
    mCurrentResourceOrIdLabel(0)
{
    // Set up the GUI

    mGui->setupUi(this);

    // Create and populate our context menu

    mContextMenu = new QMenu(this);

    mContextMenu->addAction(mGui->actionCopy);

    // Create an output widget that will contain our output message and output
    // for ontological terms

    mOutput = new Core::Widget(this);

    mOutput->setLayout(new QVBoxLayout(mOutput));

    mOutput->layout()->setMargin(0);

    // Create our output message (within a scroll area, in case the label is too
    // wide)

    mOutputMessageScrollArea = new QScrollArea(mOutput);

    mOutputMessageScrollArea->setFrameShape(QFrame::NoFrame);
    mOutputMessageScrollArea->setWidgetResizable(true);

    mOutputMessage = new Core::UserMessageWidget(":/oxygen/actions/help-about.png",
                                                 mOutputMessageScrollArea);

    mOutputMessageScrollArea->setWidget(mOutputMessage);

    // Create our output for ontological terms

    Core::readTextFromFile(":/ontologicalTerms.html", mOutputOntologicalTermsTemplate);

    mOutputOntologicalTerms = new CellmlAnnotationViewMetadataWebViewWidget(mOutput);

    mOutputOntologicalTerms->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(mOutputOntologicalTerms, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showCustomContextMenu(const QPoint &)));

    mOutputOntologicalTerms->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    connect(mOutputOntologicalTerms->page(), SIGNAL(linkClicked(const QUrl &)),
            this, SLOT(linkClicked()));

    // Add our output message and output for ontological terms to our output
    // widget

    mOutput->layout()->addWidget(mOutputMessageScrollArea);
    mOutput->layout()->addWidget(mOutputOntologicalTerms);

    // Add our output widget to our main layout

    mGui->layout->addWidget(mOutput);
}

//==============================================================================

CellmlAnnotationViewMetadataNormalViewDetailsWidget::~CellmlAnnotationViewMetadataNormalViewDetailsWidget()
{
    // Delete the GUI

    delete mGui;
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::retranslateUi()
{
    // Retranslate our GUI

    mGui->retranslateUi(this);

    // For the rest of our GUI, it's easier to just update it, so...

//    updateGui(mElement, mRdfTripleInformation, mType, mLookUpInformation, true);

    // Retranslate our output message

    mOutputMessage->setMessage(tr("There is no metadata associated with the current CellML element..."));
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::updateGui(iface::cellml_api::CellMLElement *pElement,
                                                                    const QString &pRdfTripleInformation,
                                                                    const Type &pType,
                                                                    const Information &pLookUpInformation,
                                                                    const bool &pRetranslate)
{
    if (!pElement)
        return;

    // Keep track of the CellML element

    mElement = pElement;

    // Reset various properties
    // Note: we might only do that before adding new items, but then again there
    //       is no need to waste memory, so...

    mOutputOntologicalTerms->setHtml(QString());

    // Populate mOutputOntologicalTerms, but only if there is at least one RDF
    // triple

    CellMLSupport::CellmlFileRdfTriples rdfTriples = mCellmlFile->rdfTriples(pElement);
    QString firstRdfTripleInformation = QString();
    QString lastRdfTripleInformation = QString();

    if (rdfTriples.count()) {
        // Create labels to act as headers

//        newGridLayout->addWidget(Core::newLabel(tr("Qualifier"),
//                                                1.25, true, false,
//                                                Qt::AlignCenter,
//                                                newGridWidget),
//                                 0, 0);
//        newGridLayout->addWidget(Core::newLabel(tr("Resource"),
//                                                1.25, true, false,
//                                                Qt::AlignCenter,
//                                                newGridWidget),
//                                 0, 1);
//        newGridLayout->addWidget(Core::newLabel(tr("Id"),
//                                                1.25, true, false,
//                                                Qt::AlignCenter,
//                                                newGridWidget),
//                                 0, 2);

        // Number of terms

//        newGridLayout->addWidget(Core::newLabel((rdfTriples.count() == 1)?
//                                                    tr("(1 term)"):
//                                                    tr("(%1 terms)").arg(QString::number(rdfTriples.count())),
//                                                1.0, false, true,
//                                                Qt::AlignCenter,
//                                                newGridWidget),
//                                 0, 3);

        // Add the RDF triples information to our layout
        // Note: for the RDF triple's subject, we try to remove the CellML
        //       file's URI base, thus only leaving the equivalent of a CellML
        //       element cmeta:id which will speak more to the user than a
        //       possibly long URI reference...

//        int row = 0;

//        foreach (CellMLSupport::CellmlFileRdfTriple *rdfTriple, rdfTriples) {
//            // Qualifier

//            QString qualifierAsString = (rdfTriple->modelQualifier() != CellMLSupport::CellmlFileRdfTriple::ModelUnknown)?
//                                            rdfTriple->modelQualifierAsString():
//                                            rdfTriple->bioQualifierAsString();
//            QString rdfTripleInformation = qualifierAsString+"|"+rdfTriple->resource()+"|"+rdfTriple->id()+"|"+QString::number(++row);

//            QLabel *qualifierLabel = Core::newLabel("<a href=\""+rdfTripleInformation+"\">"+qualifierAsString+"</a>",
//                                                    1.0, false, false,
//                                                    Qt::AlignCenter,
//                                                    newGridWidget);

//            connect(qualifierLabel, SIGNAL(linkActivated(const QString &)),
//                    this, SLOT(lookUpQualifier(const QString &)));

//            newGridLayout->addWidget(qualifierLabel, row, 0);

//            // Resource

//            QLabel *resourceLabel = Core::newLabel("<a href=\""+rdfTripleInformation+"\">"+rdfTriple->resource()+"</a>",
//                                                   1.0, false, false,
//                                                   Qt::AlignCenter,
//                                                   newGridWidget);

//            resourceLabel->setAccessibleDescription("http://identifiers.org/"+rdfTriple->resource()+"/?redirect=true");
//            resourceLabel->setContextMenuPolicy(Qt::CustomContextMenu);

//            connect(resourceLabel, SIGNAL(customContextMenuRequested(const QPoint &)),
//                    this, SLOT(showCustomContextMenu(const QPoint &)));
//            connect(resourceLabel, SIGNAL(linkActivated(const QString &)),
//                    this, SLOT(lookUpResource(const QString &)));

//            newGridLayout->addWidget(resourceLabel, row, 1);

//            // Id

//            QLabel *idLabel = Core::newLabel("<a href=\""+rdfTripleInformation+"\">"+rdfTriple->id()+"</a>",
//                                             1.0, false, false,
//                                             Qt::AlignCenter,
//                                             newGridWidget);

//            connect(idLabel, SIGNAL(customContextMenuRequested(const QPoint &)),
//                    this, SLOT(showCustomContextMenu(const QPoint &)));
//            connect(idLabel, SIGNAL(linkActivated(const QString &)),
//                    this, SLOT(lookUpId(const QString &)));

//            idLabel->setAccessibleDescription("http://identifiers.org/"+rdfTriple->resource()+"/"+rdfTriple->id()+"/?profile=most_reliable&redirect=true");
//            idLabel->setContextMenuPolicy(Qt::CustomContextMenu);

//            newGridLayout->addWidget(idLabel, row, 2);

//            // Remove button

//            QPushButton *removeButton = new QPushButton(newGridWidget);
//            // Note #1: ideally, we could assign a QAction to our
//            //          QPushButton, but this cannot be done, so... we
//            //          assign a few properties by hand...
//            // Note #2: to use a QToolButton would allow us to assign a
//            //          QAction to it, but a QToolButton doesn't look quite
//            //          the same as a QPushButton on some platforms, so...

//            removeButton->setEnabled(Core::FileManager::instance()->isReadableAndWritable(mCellmlFile->fileName()));
//            removeButton->setIcon(QIcon(":/oxygen/actions/list-remove.png"));
//            removeButton->setStatusTip(tr("Remove the term"));
//            removeButton->setToolTip(tr("Remove"));
//            removeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

//            mRdfTriplesMapping.insert(removeButton, rdfTriple);

//            connect(removeButton, SIGNAL(clicked(bool)),
//                    this, SLOT(removeRdfTriple()));

//            newGridLayout->addWidget(removeButton, row, 3, Qt::AlignCenter);

//            // Keep track of the very first resource id and update the last one

//            if (row == 1)
//                firstRdfTripleInformation = rdfTripleInformation;

//            lastRdfTripleInformation = rdfTripleInformation;
//        }

        // Have the remove buttons column take as little horizontal space as
        // possible compared to the other columns

//        newGridLayout->setColumnStretch(0, 1);
//        newGridLayout->setColumnStretch(1, 1);
//        newGridLayout->setColumnStretch(2, 1);

        // Have all the rows take a minimum of vertical space

//        newGridLayout->setRowStretch(++row, 1);
    }

    // Hide our old output widget and show our new one

    mOutputMessageScrollArea->setVisible(!rdfTriples.count());
    mOutputOntologicalTerms->setVisible(rdfTriples.count());

    // Request for something to be looked up, if needed

    if (pLookUpInformation != None) {
        if (rdfTriples.count()) {
            // Request for the first resource id, the last resource id or an
            // 'old' qualifier, resource or resource id to be looked up

            if (pLookUpInformation == First)
                // Look up the first resource id

                genericLookUp(firstRdfTripleInformation, Id, pRetranslate);
            else if (pLookUpInformation == Last)
                // Look up the last resource id

                genericLookUp(lastRdfTripleInformation, Id, pRetranslate);
            else
                // Look up any 'old' qualifier, resource or resource id

                genericLookUp(pRdfTripleInformation, pType, pRetranslate);
        } else {
            // No RDF triple left, so ask for 'nothing' to be looked up
            // Note: we do this to let people know that there is nothing to look
            //       up and that they can 'clean' whatever they use to show a
            //       look up to the user...

            genericLookUp();
        }
    }
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::addRdfTriple(CellMLSupport::CellmlFileRdfTriple *pRdfTriple)
{
    if (!pRdfTriple)
        return;

    // Make sure that the given RDF triple will be visible, this by handling the
    // change in the range of our vertical scroll bar which will result in
    // showLastRdfTriple() being called

//    connect(verticalScrollBar(), SIGNAL(rangeChanged(int, int)),
//            this, SLOT(showLastRdfTriple()));

    // Enable the looking up of the last information

    mLookUpInformation = Last;

    // Update the GUI to reflect the addition of the given RDF triple

    updateGui(mElement, QString(), No, mLookUpInformation);
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::genericLookUp(const QString &pRdfTripleInformation,
                                                                        const Type &pType,
                                                                        const bool &pRetranslate)
{
    // Retrieve the RDF triple information

    QStringList rdfTripleInformationAsStringList = pRdfTripleInformation.split("|");
    QString qualifierAsString = pRdfTripleInformation.isEmpty()?QString():rdfTripleInformationAsStringList[0];
    QString resourceAsString = pRdfTripleInformation.isEmpty()?QString():rdfTripleInformationAsStringList[1];
    QString idAsString = pRdfTripleInformation.isEmpty()?QString():rdfTripleInformationAsStringList[2];
//    int rowAsInt = pRdfTripleInformation.isEmpty()?0:rdfTripleInformationAsStringList[3].toInt();

    // Keep track of the RDF triple information and type

    mRdfTripleInformation = pRdfTripleInformation;
    mType = pType;

    // Make the row corresponding to the qualifier, resource or id bold (and
    // italic in some cases)
    // Note: to use mGridLayout->rowCount() to determine the number of rows
    //       isn't an option since no matter whether we remove rows (in
    //       updateGui()), the returned value will be the maximum number of rows
    //       that there has ever been, so...

//    for (int row = 0; mGridLayout->itemAtPosition(++row, 0);) {
//        QLabel *qualifierLabel = qobject_cast<QLabel *>(mGridLayout->itemAtPosition(row, 0)->widget());
//        QLabel *resourceLabel = qobject_cast<QLabel *>(mGridLayout->itemAtPosition(row, 1)->widget());
//        QLabel *idLabel = qobject_cast<QLabel *>(mGridLayout->itemAtPosition(row, 2)->widget());

//        QFont font = idLabel->font();

//        font.setBold((mLookUpInformation != None) && (row == rowAsInt));
//        font.setItalic(false);

//        QFont italicFont = idLabel->font();

//        italicFont.setBold(font.bold());
//        italicFont.setItalic(font.bold());

//        qualifierLabel->setFont((pType == Qualifier)?italicFont:font);
//        resourceLabel->setFont((pType == Resource)?italicFont:font);
//        idLabel->setFont((pType == Id)?italicFont:font);
//    }

    // Check whether we have something to look up

    if (mLookUpInformation == None)
        // Nothing to look up, so...

        return;

    // Let people know that we want to look something up

    switch (pType) {
    case Qualifier:
        emit qualifierLookUpRequested(qualifierAsString, pRetranslate);

        break;
    case Resource:
        emit resourceLookUpRequested(resourceAsString, pRetranslate);

        break;
    case Id:
        emit idLookUpRequested(resourceAsString, idAsString, pRetranslate);

        break;
    default:
        // No

        emit noLookUpRequested();
    }
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::disableLookUpInformation()
{
    // Disable the looking up of information

    mLookUpInformation = None;

    // Update the GUI by pretending to be interested in looking something up

    genericLookUp();
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::lookUpQualifier(const QString &pRdfTripleInformation)
{
    // Enable the looking up of any information

    mLookUpInformation = Any;

    // Call our generic look up function

    genericLookUp(pRdfTripleInformation, Qualifier);
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::lookUpResource(const QString &pRdfTripleInformation)
{
    // Enable the looking up of any information

    mLookUpInformation = Any;

    // Call our generic look up function

    genericLookUp(pRdfTripleInformation, Resource);
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::lookUpId(const QString &pRdfTripleInformation)
{
    // Enable the looking up of any information

    mLookUpInformation = Any;

    // Call our generic look up function

    genericLookUp(pRdfTripleInformation, Id);
}

//==============================================================================

QString CellmlAnnotationViewMetadataNormalViewDetailsWidget::rdfTripleInformation(const int &pRow) const
{
Q_UNUSED(pRow);
    // Return the RDF triple information for the given row

    QString res = QString();

//    // Retrieve the item for the first label link from the given row

//    QLayoutItem *item = mGridLayout->itemAtPosition(pRow, 0);

//    if (!item)
//        // No item could be retrieved, so...

//        return res;

//    // Retrieve the text from the item's widget which is a QLabel

//    res = static_cast<QLabel *>(item->widget())->text();

//    // Extract the RDF triple information from the text

//    res.remove(QRegularExpression("^[^\"]*\""));
//    res.remove(QRegularExpression("\"[^\"]*$"));

    // We are done with retrieving the RDF triple information for the given row,
    // so...

    return res;
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::removeRdfTriple()
{
    // Retrieve the RDF triple associated with the remove button

    CellMLSupport::CellmlFileRdfTriple *rdfTriple = mRdfTriplesMapping.value(sender());

    mRdfTriplesMapping.remove(sender());

    // Remove the RDF triple from the CellML file and from our set of RDF
    // triples this widget uses

    mCellmlFile->rdfTriples().remove(rdfTriple);

    // Retrieve the number of the row we want to delete, as well as the total
    // number of rows
    // Note: should some RDF triples have been removed, then to call
    //       mGridLayout->rowCount() won't give us the correct number of rows,
    //       so...

//    int row = 0;
//    int rowMax = mGridLayout->rowCount();

//    for (int i = 1; i < rowMax; ++i) {
//        QLayoutItem *item = mGridLayout->itemAtPosition(i, 3);

//        if (!item) {
//            // The row doesn't exist anymore, so...

//            rowMax = i;

//            break;
//        }

//        if (item->widget() == sender())
//            // This is the row we want to remove

//            row = i;
//    }

    // Make sure that row and rowMax have meaningful values

//    Q_ASSERT(row > 0);
//    Q_ASSERT(rowMax > row);

    // Determine the neighbour row which we want to be visible

//    mNeighbourRow = (rowMax-1 > row)?row:row-1;

//    // Determine the 'new' RDF triple information to look up, depending on
//    // whether there is any RDF triple left

//    if (mRdfTriplesMapping.isEmpty()) {
//        // There are no RDF triples left, so...

//        mRdfTripleInformation = QString();
//        mType = No;
//    } else if (!rdfTripleInformation(row).compare(mRdfTripleInformation)) {
//        // The RDF triple information is related to the row we want to delete,
//        // so we need to find a new one

//        mRdfTripleInformation = rdfTripleInformation((rowMax-1 > row)?row+1:row-1);
//    }

    // Make sure that the neighbour of our removed RDF triple will be made
    // visible and we do this by handling the change in the range of our
    // vertical scroll bar which will result in showNeighbourRdfTriple() being
    // called

//    connect(verticalScrollBar(), SIGNAL(rangeChanged(int, int)),
//            this, SLOT(showNeighbourRdfTriple()));

    // Update the GUI to reflect the removal of the RDF triple

    updateGui(mElement, mRdfTripleInformation, mType, mLookUpInformation);

    // Let people know that an RDF triple has been removed

    emit rdfTripleRemoved(rdfTriple);
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::showNeighbourRdfTriple()
{
//    // No need to show our neighbour RDF triple, so...

//    disconnect(verticalScrollBar(), SIGNAL(rangeChanged(int, int)),
//               this, SLOT(showNeighbourRdfTriple()));

//    // Make sure that the neighbour RDF triple is visible

//    ensureWidgetVisible(mGridLayout->itemAtPosition(mNeighbourRow, 0)->widget());
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::showLastRdfTriple()
{
//    // No need to show our last RDF triple, so...

//    disconnect(verticalScrollBar(), SIGNAL(rangeChanged(int, int)),
//               this, SLOT(showLastRdfTriple()));

//    // Determine the number of rows in our grid layout
//    // Note: to use mGridLayout->rowCount() isn't an option since no matter
//    //       whether we remove rows (in updateGui()), the returned value will be
//    //       the maximum number of rows that there has ever been, so...

//    int row = 0;

//    while (mGridLayout->itemAtPosition(++row, 0))
//        ;

//    // Make sure that the last RDF triple is visible

//    ensureWidgetVisible(mGridLayout->itemAtPosition(row-1, 0)->widget());
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::linkClicked()
{
//---GRY--- TO BE DONE...
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::showCustomContextMenu(const QPoint &pPosition)
{
    Q_UNUSED(pPosition);

    // Keep track of the resource or id

    mCurrentResourceOrIdLabel = qobject_cast<QLabel *>(qApp->widgetAt(QCursor::pos()));

    // Should our context menu to allow the copying of the URL of the resource
    // or id

    mContextMenu->exec(QCursor::pos());
}

//==============================================================================

void CellmlAnnotationViewMetadataNormalViewDetailsWidget::on_actionCopy_triggered()
{
    // Copy the URL of the resource or id to the clipboard

    QApplication::clipboard()->setText(mCurrentResourceOrIdLabel->accessibleDescription());
}

//==============================================================================

}   // namespace CellMLAnnotationView
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
