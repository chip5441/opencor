/*******************************************************************************

Copyright (C) The University of Auckland

OpenCOR is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenCOR is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

//==============================================================================
// Simulation support Python wrapper
//==============================================================================

#include "corecliutils.h"
#include "cellmlfileruntime.h"
#include "datastoreinterface.h"
#include "datastorepythonwrapper.h"
#include "filemanager.h"
#include "interfaces.h"
#include "pythonqtsupport.h"
#include "simulation.h"
#include "simulationmanager.h"
#include "simulationsupportplugin.h"
#include "simulationsupportpythonwrapper.h"
#include "solverinterface.h"

//==============================================================================

#include <QApplication>
#include <QEventLoop>
#include <QFileInfo>
#include <QMap>
#include <QWidget>

//==============================================================================

#include <array>

//==============================================================================

namespace OpenCOR {
namespace SimulationSupport {

//==============================================================================

static void doSetOdeSolver(SimulationData *pSimulationData, const QString &pOdeSolverName)
{
    for (auto solverInterface : Core::solverInterfaces()) {
        if (pOdeSolverName == solverInterface->solverName()) {
            // Set the ODE solver's name

            pSimulationData->setOdeSolverName(pOdeSolverName);

            for (const auto &solverInterfaceProperty : solverInterface->solverProperties()) {
                // Set each ODE solver property's default value

                pSimulationData->addOdeSolverProperty(solverInterfaceProperty.id(), solverInterfaceProperty.defaultValue());
            }

            return;
        }
    }

    throw std::runtime_error(QObject::tr("Unknown ODE solver.").toStdString());
}

//==============================================================================

static void doSetNlaSolver(SimulationData *pSimulationData, const QString &pNlaSolverName)
{
    for (auto solverInterface : Core::solverInterfaces()) {
        if (pNlaSolverName == solverInterface->solverName()) {
            // Set the NLA solver's name

            pSimulationData->setNlaSolverName(pNlaSolverName);

            for (const auto &solverInterfaceProperty : solverInterface->solverProperties()) {
                // Set each NLA solver property's default value

                pSimulationData->addNlaSolverProperty(solverInterfaceProperty.id(), solverInterfaceProperty.defaultValue());
            }

            return;
        }
    }

    throw std::runtime_error(QObject::tr("Unknown NLA solver.").toStdString());
}

//==============================================================================

static PyObject *initializeSimulation(const QString &pFileName)
{
    // Ask our simulation manager to manage our file and then retrieve the
    // corresponding simulation from it

    SimulationManager *simulationManager = SimulationManager::instance();

    simulationManager->manage(pFileName);

    Simulation *simulation = simulationManager->simulation(pFileName);

    if (simulation != nullptr) {
        // Check for issues with the simulation

        if (simulation->hasBlockingIssues()) {
            // We return the simulation to allow the user to view its issues

            return PythonQt::priv()->wrapQObject(simulation);
        }

        // Get our runtime

        CellMLSupport::CellmlFileRuntime *runtime = simulation->runtime();

        // Find the solver whose name is first in alphabetical order, as this
        // is the simulation's solver

        QString odeSolverName = QString();
        QString nlaSolverName = QString();

        for (auto solverInterface : Core::solverInterfaces()) {
            QString solverName = solverInterface->solverName();

            if (solverInterface->solverType() == Solver::Type::Ode) {
                if (odeSolverName.isEmpty()
                 || odeSolverName.compare(solverName, Qt::CaseInsensitive) > 0) {
                    odeSolverName = solverName;
                }
            } else if (solverInterface->solverType() == Solver::Type::Nla) {
                if (nlaSolverName.isEmpty()
                 || nlaSolverName.compare(solverName, Qt::CaseInsensitive) > 0) {
                    nlaSolverName = solverName;
                }
            }
        }

        // Set our solver and its default properties

        doSetOdeSolver(simulation->data(), odeSolverName);

        // Set our NLA solver if we need one

        if ((runtime != nullptr) && runtime->needNlaSolver()) {
            doSetNlaSolver(simulation->data(), nlaSolverName);
        }

        // Complete initialisation by loading any SED-ML properties

        if (simulation->fileType() == SimulationSupport::Simulation::FileType::SedmlFile
         || simulation->fileType() == SimulationSupport::Simulation::FileType::CombineArchive) {

            QString initializationError = simulation->furtherInitialize();

            if (!initializationError.isEmpty()) {
                // We couldn't complete initialisation so no longer manage the simulation

                simulationManager->unmanage(pFileName);

                // And raise a Python exception

                PyErr_SetString(PyExc_ValueError, qPrintable(initializationError));

                return nullptr;
            }
        }

        // Do we have a valid simulation?

        if ((runtime != nullptr) && runtime->isValid()) {
            // Reset both the simulation's data and results (well, initialise in the
            // case of its data)

            simulation->data()->reset();
            simulation->results()->reset();
        }

        // Return the simulation as a Python object

        return PythonQt::priv()->wrapQObject(simulation);
    }

#include "pythonbegin.h"
    Py_RETURN_NONE;
#include "pythonend.h"
}

//==============================================================================

static PyObject *openSimulation(PyObject *self, PyObject *args)
{
    Q_UNUSED(self)

    PyObject *bytes;
    char *name;
    Py_ssize_t len;
    if (PyArg_ParseTuple(args, "O&", PyUnicode_FSConverter, &bytes) == 0) { // NOLINT(cppcoreguidelines-pro-type-vararg)
#include "pythonbegin.h"
        Py_RETURN_NONE;
#include "pythonend.h"
    }
    PyBytes_AsStringAndSize(bytes, &name, &len);
    QString fileName = QString::fromUtf8(name, int(len));
#include "pythonbegin.h"
    Py_DECREF(bytes);
#include "pythonend.h"

    QString error = Core::openFile(fileName);

    if (!error.isEmpty()) {
        PyErr_SetString(PyExc_IOError, qPrintable(error));

        return nullptr;
    }

    return initializeSimulation(QFileInfo(fileName).canonicalFilePath());
}

//==============================================================================

static PyObject *openRemoteSimulation(PyObject *self, PyObject *args)
{
    Q_UNUSED(self)

    PyObject *bytes;
    char *name;
    Py_ssize_t len;
    if (PyArg_ParseTuple(args, "O&", PyUnicode_FSConverter, &bytes) == 0) { // NOLINT(cppcoreguidelines-pro-type-vararg)
#include "pythonbegin.h"
        Py_RETURN_NONE;
#include "pythonend.h"
    }
    PyBytes_AsStringAndSize(bytes, &name, &len);
    QString url = QString::fromUtf8(name, int(len));
#include "pythonbegin.h"
    Py_DECREF(bytes);
#include "pythonend.h"

    QString error = Core::openRemoteFile(url);

    if (!error.isEmpty()) {
        PyErr_SetString(PyExc_IOError, qPrintable(error));

        return nullptr;
    }

    return initializeSimulation(Core::localFileName(url));
}

//==============================================================================

static PyObject *closeSimulation(PyObject *self, PyObject *args)
{
    Q_UNUSED(self)

    if (PyTuple_Size(args) > 0) {
#include "pythonbegin.h"
        PythonQtInstanceWrapper *wrappedSimulation = PythonQtSupport::getInstanceWrapper(PyTuple_GET_ITEM(args, 0)); // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
#include "pythonend.h"

        if (wrappedSimulation != nullptr) {
            auto simulation = static_cast<SimulationSupport::Simulation *>(wrappedSimulation->_objPointerCopy);

            QString fileName = simulation->fileName();

            // Close the simulation by asking our manager to no longer manage it

            SimulationManager::instance()->unmanage(simulation->fileName());

            // And tell the file manager that we no longer are using the file

            Core::FileManager::instance()->unmanage(fileName);
        }
    }

#include "pythonbegin.h"
    Py_RETURN_NONE;
#include "pythonend.h"
}

//==============================================================================

SimulationSupportPythonWrapper::SimulationSupportPythonWrapper(PyObject *pModule,
                                                               QObject *pParent) :
    QObject(pParent)
{
    Q_UNUSED(pModule)

    // Register some OpenCOR classes with Python and decorators to our ourselves

    PythonQtSupport::registerClass(&Simulation::staticMetaObject);
    PythonQtSupport::registerClass(&SimulationData::staticMetaObject);
    PythonQtSupport::registerClass(&SimulationResults::staticMetaObject);

    PythonQtSupport::addInstanceDecorators(this);

    // Add some Python wrappers

    static std::array<PyMethodDef, 4> PythonSimulationSupportMethods = {{
                                                                           { "openSimulation", openSimulation, METH_VARARGS, "Open a simulation." },
                                                                           { "openRemoteSimulation", openRemoteSimulation, METH_VARARGS, "Open a remote simulation." },
                                                                           { "closeSimulation", closeSimulation, METH_VARARGS, "Close a simulation." },
                                                                           { nullptr, nullptr, 0, nullptr }
                                                                       }};

    PyModule_AddFunctions(pModule, PythonSimulationSupportMethods.data());
}

//==============================================================================

void SimulationSupportPythonWrapper::error(const QString &pErrorMessage)
{
    mErrorMessage = pErrorMessage;
}

//==============================================================================

void SimulationSupportPythonWrapper::clearResults(Simulation *pSimulation)
{
    // Ask our widget to clear our results
    // Note: we get the widget to do this as it needs to clear all associated
    //       graphs...

    emit pSimulation->clearResults(pSimulation->fileName());
}

//==============================================================================

void SimulationSupportPythonWrapper::resetParameters(Simulation *pSimulation)
{
    // Reset our model parameters

    pSimulation->reset();
}

//==============================================================================

void SimulationSupportPythonWrapper::simulationFinished(qint64 pElapsedTime)
{
    // Save the elapsed time of the simulation

    mElapsedTime = pElapsedTime;

    emit gotElapsedTime();
}

//==============================================================================

bool SimulationSupportPythonWrapper::valid(Simulation *pSimulation)
{
    // Is the simulation's model valid?

    if (!pSimulation->hasBlockingIssues()) {
        CellMLSupport::CellmlFileRuntime *runtime = pSimulation->runtime();
        return (runtime != nullptr) && runtime->isValid();
    }

    return false;
}

//==============================================================================

PyObject *SimulationSupportPythonWrapper::issues(Simulation *pSimulation) const
{
    // Return a list of any issues the simulation has

    PyObject *issuesList = PyList_New(0);

    auto simulationIssues = pSimulation->issues();

    for (const auto &simulationIssue : simulationIssues) {
        QString issueType;
        QString information;

        switch (simulationIssue.type()) {
        case SimulationSupport::SimulationIssue::Type::Information:
            issueType = tr("Information");

            break;
        case SimulationSupport::SimulationIssue::Type::Error:
            issueType = tr("Error");

            break;
        case SimulationSupport::SimulationIssue::Type::Warning:
            issueType = tr("Warning");

            break;
        case SimulationSupport::SimulationIssue::Type::Fatal:
            issueType = tr("Fatal");

            break;
        }

        if ((simulationIssue.line() != 0) && (simulationIssue.column() != 0)) {
            information = QString("[%1:%2] %3: %4.").arg(simulationIssue.line())
                                                     .arg(simulationIssue.column())
                                                     .arg(issueType,
                                                          Core::formatMessage(simulationIssue.message()));
        } else {
            information = QString("%1: %2.").arg(issueType,
                                                 Core::formatMessage(simulationIssue.message()));
        }

        PyList_Append(issuesList, PyUnicode_FromString(information.toUtf8().constData()));
    }

    return issuesList;
}

//==============================================================================

bool SimulationSupportPythonWrapper::run(Simulation *pSimulation)
{
    if (pSimulation->hasBlockingIssues()) {
        throw std::runtime_error(tr("Cannot run because simulation has blocking issues.").toStdString());
    }

    if (!valid(pSimulation)) {
        throw std::runtime_error(tr("Cannot run because simulation has an invalid runtime.").toStdString());
    }

    QWidget *focusWidget = nullptr;

    // A successful run will set elapsed time

    mElapsedTime = -1;

    // Clear error message

    mErrorMessage = QString();

    // Try to allocate all the memory we need by adding a run to our simulation
    // and, if successful, run our simulation

    if (pSimulation->addRun()) {
        // Save the keyboard focus, which will be to our IPython console

        focusWidget = QApplication::focusWidget();

        // Let people know that we are starting our run

        emit pSimulation->runStarting(pSimulation->fileName());

        // Get the elapsed time when the simulation has finished

        connect(pSimulation, &Simulation::done,
                this, &SimulationSupportPythonWrapper::simulationFinished);

        // Get error messages from the simulation

        connect(pSimulation, &Simulation::error,
                this, &SimulationSupportPythonWrapper::error);

        // Use an event loop so we don't busy wait

        QEventLoop waitForCompletion;

        // We use a queued connection because the event is in our thread

        connect(this, &SimulationSupportPythonWrapper::gotElapsedTime,
                &waitForCompletion, &QEventLoop::quit, Qt::QueuedConnection);

        // Start the simulation and wait for it to complete

        pSimulation->run();

        waitForCompletion.exec();

        // Disconnect our signal handlers now that the simulation has finished

        disconnect(pSimulation, nullptr, this, nullptr);

        if (!mErrorMessage.isEmpty()) {
            throw std::runtime_error(mErrorMessage.toStdString());
        }
    } else {
        throw std::runtime_error(tr("We could not allocate the memory required for the simulation.").toStdString());
    }

    // Restore the keyboard focus back to IPython

    if (focusWidget != nullptr) {
        focusWidget->setFocus();
    }

    return mElapsedTime >= 0;
}

//==============================================================================

void SimulationSupportPythonWrapper::setStartingPoint(SimulationData *pSimulationData,
                                                      double pStartingPoint,
                                                      bool pRecompute)
{
    pSimulationData->setStartingPoint(pStartingPoint, pRecompute);
}

//==============================================================================

void SimulationSupportPythonWrapper::setEndingPoint(SimulationData *pSimulationData,
                                                    double pEndingPoint)
{
    pSimulationData->setEndingPoint(pEndingPoint);
}

//==============================================================================

void SimulationSupportPythonWrapper::setPointInterval(SimulationData *pSimulationData,
                                                      double pPointInterval)
{
    pSimulationData->setPointInterval(pPointInterval);
}


//==============================================================================

void SimulationSupportPythonWrapper::setOdeSolver(SimulationData *pSimulationData,
                                                  const QString &pOdeSolverName)
{
    doSetOdeSolver(pSimulationData, pOdeSolverName);
}

//==============================================================================

void SimulationSupportPythonWrapper::setNlaSolver(SimulationData *pSimulationData,
                                                  const QString &pNlaSolverName)
{
    doSetNlaSolver(pSimulationData, pNlaSolverName);
}

//==============================================================================

PyObject * SimulationSupportPythonWrapper::algebraic(SimulationData *pSimulationData) const
{
    return DataStore::DataStorePythonWrapper::dataStoreValuesDict(pSimulationData->algebraicValues(),
                                                                  &(pSimulationData->simulationDataUpdatedFunction()));
}

//==============================================================================

PyObject * SimulationSupportPythonWrapper::constants(SimulationData *pSimulationData) const
{
    return DataStore::DataStorePythonWrapper::dataStoreValuesDict(pSimulationData->constantsValues(),
                                                                  &(pSimulationData->simulationDataUpdatedFunction()));
}

//==============================================================================

PyObject * SimulationSupportPythonWrapper::rates(SimulationData *pSimulationData) const
{
    return DataStore::DataStorePythonWrapper::dataStoreValuesDict(pSimulationData->ratesValues(),
                                                                  &(pSimulationData->simulationDataUpdatedFunction()));
}

//==============================================================================

PyObject * SimulationSupportPythonWrapper::states(SimulationData *pSimulationData) const
{
    return DataStore::DataStorePythonWrapper::dataStoreValuesDict(pSimulationData->statesValues(),
                                                                  &(pSimulationData->simulationDataUpdatedFunction()));
}

//==============================================================================

const OpenCOR::DataStore::DataStoreVariable * SimulationSupportPythonWrapper::points(SimulationResults *pSimulationResults) const
{
    return pSimulationResults->pointsVariable();
}

//==============================================================================

PyObject * SimulationSupportPythonWrapper::algebraic(SimulationResults *pSimulationResults) const
{
    return DataStore::DataStorePythonWrapper::dataStoreVariablesDict(pSimulationResults->algebraicVariables());
}

//==============================================================================

PyObject * SimulationSupportPythonWrapper::constants(SimulationResults *pSimulationResults) const
{
    return DataStore::DataStorePythonWrapper::dataStoreVariablesDict(pSimulationResults->constantsVariables());
}

//==============================================================================

PyObject * SimulationSupportPythonWrapper::rates(SimulationResults *pSimulationResults) const
{
    return DataStore::DataStorePythonWrapper::dataStoreVariablesDict(pSimulationResults->ratesVariables());
}

//==============================================================================

PyObject * SimulationSupportPythonWrapper::states(SimulationResults *pSimulationResults) const
{
    return DataStore::DataStorePythonWrapper::dataStoreVariablesDict(pSimulationResults->statesVariables());
}

//==============================================================================

} // namespace SimulationSupport
} // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
