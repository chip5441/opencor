/* This file is automatically generated from SProS.idl
 * DO NOT EDIT DIRECTLY OR CHANGES WILL BE LOST!
 */
#ifndef _GUARD_IFACE_SProS
#define _GUARD_IFACE_SProS
#include "cda_compiler_support.h"
#ifdef MODULE_CONTAINS_SProS
#define PUBLIC_SProS_PRE CDA_EXPORT_PRE
#define PUBLIC_SProS_POST CDA_EXPORT_POST
#else
#define PUBLIC_SProS_PRE CDA_IMPORT_PRE
#define PUBLIC_SProS_POST CDA_IMPORT_POST
#endif
#include "Ifacexpcom.hxx"
#include "IfaceDOM_APISPEC.hxx"
#include "IfaceMathML_content_APISPEC.hxx"
#include "IfaceCellML_APISPEC.hxx"
namespace iface
{
  namespace SProS
  {
    class Base;
    class BaseSet;
    class BaseIterator;
    class SEDMLElement;
    class NamedElement;
    class NamedElementSet;
    class NamedElementIterator;
    class NamedIdentifiedElement;
    class NamedIdentifiedElementSet;
    class NamedIdentifiedElementIterator;
    class Model;
    class ModelSet;
    class ModelIterator;
    class Simulation;
    class SimulationSet;
    class SimulationIterator;
    class UniformTimeCourse;
    class Task;
    class TaskSet;
    class TaskIterator;
    class DataGenerator;
    class DataGeneratorSet;
    class DataGeneratorIterator;
    class Output;
    class OutputSet;
    class OutputIterator;
    class Plot2D;
    class Plot3D;
    class Report;
    class Change;
    class ChangeSet;
    class ChangeIterator;
    class ComputeChange;
    class ChangeAttribute;
    class AddXML;
    class ChangeXML;
    class RemoveXML;
    class Variable;
    class VariableSet;
    class VariableIterator;
    class Parameter;
    class ParameterSet;
    class ParameterIterator;
    class Curve;
    class CurveSet;
    class CurveIterator;
    class Surface;
    class SurfaceSet;
    class SurfaceIterator;
    class DataSet;
    class DataSetSet;
    class DataSetIterator;
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Bootstrap
     : public virtual iface::XPCOM::IObject
    {
    public:
      virtual ~Bootstrap() {}
      virtual iface::SProS::SEDMLElement* createEmptySEDML() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::SEDMLElement* parseSEDMLFromURI(const wchar_t* uri, const wchar_t* relativeTo) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::SEDMLElement* parseSEDMLFromText(const wchar_t* txt, const wchar_t* baseURI) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::SEDMLElement* makeSEDMLFromElement(iface::dom::Element* el) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual wchar_t* sedmlToText(iface::SProS::SEDMLElement* el) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Base
     : public virtual iface::XPCOM::IObject
    {
    public:
      virtual ~Base() {}
      virtual iface::dom::Element* domElement() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual iface::dom::NodeList* notes() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual iface::dom::NodeList* annotations() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST SProSException : public std::exception
    {
    public:
      SProSException(){}
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST BaseSet
     : public virtual iface::XPCOM::IObject
    {
    public:
      virtual ~BaseSet() {}
      virtual iface::SProS::BaseIterator* iterateElements() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual void insert(iface::SProS::Base* b) throw(std::exception&) = 0;
      virtual void remove(iface::SProS::Base* b) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST BaseIterator
     : public virtual iface::XPCOM::IObject
    {
    public:
      virtual ~BaseIterator() {}
      virtual iface::SProS::Base* nextElement() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST SEDMLElement
     : public virtual iface::SProS::Base
    {
    public:
      virtual ~SEDMLElement() {}
      virtual uint32_t level() throw(std::exception&)  = 0;
      virtual void level(uint32_t attr) throw(std::exception&) = 0;
      virtual uint32_t version() throw(std::exception&)  = 0;
      virtual void version(uint32_t attr) throw(std::exception&) = 0;
      virtual iface::SProS::ModelSet* models() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::TaskSet* tasks() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::SimulationSet* simulations() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::DataGeneratorSet* generators() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::OutputSet* outputs() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Model* createModel() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::UniformTimeCourse* createUniformTimeCourse() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Task* createTask() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::DataGenerator* createDataGenerator() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Plot2D* createPlot2D() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Plot3D* createPlot3D() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Report* createReport() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::ComputeChange* createComputeChange() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::ChangeAttribute* createChangeAttribute() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::AddXML* createAddXML() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::RemoveXML* createRemoveXML() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::ChangeXML* createChangeXML() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Variable* createVariable() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Parameter* createParameter() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Curve* createCurve() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Surface* createSurface() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::DataSet* createDataSet() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST NamedElement
     : public virtual iface::SProS::Base
    {
    public:
      virtual ~NamedElement() {}
      virtual wchar_t* name() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void name(const wchar_t* attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST NamedElementSet
     : public virtual iface::SProS::BaseSet
    {
    public:
      virtual ~NamedElementSet() {}
      virtual iface::SProS::NamedElementIterator* iterateNamedElement() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST NamedElementIterator
     : public virtual iface::SProS::BaseIterator
    {
    public:
      virtual ~NamedElementIterator() {}
      virtual iface::SProS::NamedElement* nextNamedElement() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST NamedIdentifiedElement
     : public virtual iface::SProS::NamedElement
    {
    public:
      virtual ~NamedIdentifiedElement() {}
      virtual wchar_t* id() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void id(const wchar_t* attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST NamedIdentifiedElementSet
     : public virtual iface::SProS::NamedElementSet
    {
    public:
      virtual ~NamedIdentifiedElementSet() {}
      virtual iface::SProS::NamedIdentifiedElementIterator* iterateNamedIdentifiedElements() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::NamedIdentifiedElement* getNamedIdentifiedElementByIdentifier(const wchar_t* idMatch) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST NamedIdentifiedElementIterator
     : public virtual iface::SProS::NamedElementIterator
    {
    public:
      virtual ~NamedIdentifiedElementIterator() {}
      virtual iface::SProS::NamedIdentifiedElement* nextNamedIdentifiedElement() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Model
     : public virtual iface::SProS::NamedIdentifiedElement
    {
    public:
      virtual ~Model() {}
      virtual wchar_t* language() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void language(const wchar_t* attr) throw(std::exception&) = 0;
      virtual wchar_t* source() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void source(const wchar_t* attr) throw(std::exception&) = 0;
      virtual iface::SProS::ChangeSet* changes() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST ModelSet
     : public virtual iface::SProS::NamedIdentifiedElementSet
    {
    public:
      virtual ~ModelSet() {}
      virtual iface::SProS::ModelIterator* iterateModels() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Model* getModelByIdentifier(const wchar_t* idMatch) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST ModelIterator
     : public virtual iface::SProS::NamedIdentifiedElementIterator
    {
    public:
      virtual ~ModelIterator() {}
      virtual iface::SProS::Model* nextModel() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Simulation
     : public virtual iface::SProS::NamedIdentifiedElement
    {
    public:
      virtual ~Simulation() {}
      virtual wchar_t* algorithmKisaoID() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void algorithmKisaoID(const wchar_t* attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST SimulationSet
     : public virtual iface::SProS::NamedIdentifiedElementSet
    {
    public:
      virtual ~SimulationSet() {}
      virtual iface::SProS::SimulationIterator* iterateSimulations() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Simulation* getSimulationByIdentifier(const wchar_t* idMatch) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST SimulationIterator
     : public virtual iface::SProS::NamedIdentifiedElementIterator
    {
    public:
      virtual ~SimulationIterator() {}
      virtual iface::SProS::Simulation* nextSimulation() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST UniformTimeCourse
     : public virtual iface::SProS::Simulation
    {
    public:
      virtual ~UniformTimeCourse() {}
      virtual double initialTime() throw(std::exception&)  = 0;
      virtual void initialTime(double attr) throw(std::exception&) = 0;
      virtual double outputStartTime() throw(std::exception&)  = 0;
      virtual void outputStartTime(double attr) throw(std::exception&) = 0;
      virtual double outputEndTime() throw(std::exception&)  = 0;
      virtual void outputEndTime(double attr) throw(std::exception&) = 0;
      virtual uint32_t numberOfPoints() throw(std::exception&)  = 0;
      virtual void numberOfPoints(uint32_t attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Task
     : public virtual iface::SProS::NamedIdentifiedElement
    {
    public:
      virtual ~Task() {}
      virtual wchar_t* simulationReferenceIdentifier() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void simulationReferenceIdentifier(const wchar_t* attr) throw(std::exception&) = 0;
      virtual iface::SProS::Simulation* simulationReference() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void simulationReference(iface::SProS::Simulation* attr) throw(std::exception&) = 0;
      virtual wchar_t* modelReferenceIdentifier() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void modelReferenceIdentifier(const wchar_t* attr) throw(std::exception&) = 0;
      virtual iface::SProS::Model* modelReference() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void modelReference(iface::SProS::Model* attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST TaskSet
     : public virtual iface::SProS::NamedIdentifiedElementSet
    {
    public:
      virtual ~TaskSet() {}
      virtual iface::SProS::TaskIterator* iterateTasks() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Task* getTaskByIdentifier(const wchar_t* idMatch) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST TaskIterator
     : public virtual iface::SProS::NamedIdentifiedElementIterator
    {
    public:
      virtual ~TaskIterator() {}
      virtual iface::SProS::Task* nextTask() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST DataGenerator
     : public virtual iface::SProS::NamedIdentifiedElement , public virtual iface::cellml_api::MathContainer
    {
    public:
      virtual ~DataGenerator() {}
      virtual iface::SProS::ParameterSet* parameters() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::VariableSet* variables() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST DataGeneratorSet
     : public virtual iface::SProS::NamedIdentifiedElementSet
    {
    public:
      virtual ~DataGeneratorSet() {}
      virtual iface::SProS::DataGeneratorIterator* iterateDataGenerators() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::DataGenerator* getDataGeneratorByIdentifier(const wchar_t* idMatch) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST DataGeneratorIterator
     : public virtual iface::SProS::NamedIdentifiedElementIterator
    {
    public:
      virtual ~DataGeneratorIterator() {}
      virtual iface::SProS::DataGenerator* nextDataGenerator() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Output
     : public virtual iface::SProS::NamedIdentifiedElement
    {
    public:
      virtual ~Output() {}
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST OutputSet
     : public virtual iface::SProS::NamedIdentifiedElementSet
    {
    public:
      virtual ~OutputSet() {}
      virtual iface::SProS::OutputIterator* iterateOutputs() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Output* getOutputByIdentifier(const wchar_t* idMatch) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST OutputIterator
     : public virtual iface::SProS::NamedIdentifiedElementIterator
    {
    public:
      virtual ~OutputIterator() {}
      virtual iface::SProS::Output* nextOutput() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Plot2D
     : public virtual iface::SProS::Output
    {
    public:
      virtual ~Plot2D() {}
      virtual iface::SProS::CurveSet* curves() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Plot3D
     : public virtual iface::SProS::Output
    {
    public:
      virtual ~Plot3D() {}
      virtual iface::SProS::SurfaceSet* surfaces() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Report
     : public virtual iface::SProS::Output
    {
    public:
      virtual ~Report() {}
      virtual iface::SProS::DataSetSet* datasets() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Change
     : public virtual iface::SProS::Base
    {
    public:
      virtual ~Change() {}
      virtual wchar_t* target() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void target(const wchar_t* attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST ChangeSet
     : public virtual iface::SProS::BaseSet
    {
    public:
      virtual ~ChangeSet() {}
      virtual iface::SProS::ChangeIterator* iterateChanges() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST ChangeIterator
     : public virtual iface::SProS::BaseIterator
    {
    public:
      virtual ~ChangeIterator() {}
      virtual iface::SProS::Change* nextChange() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST ComputeChange
     : public virtual iface::SProS::Change , public virtual iface::cellml_api::MathContainer
    {
    public:
      virtual ~ComputeChange() {}
      virtual iface::SProS::VariableSet* variables() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::ParameterSet* parameters() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST ChangeAttribute
     : public virtual iface::SProS::Change
    {
    public:
      virtual ~ChangeAttribute() {}
      virtual wchar_t* newValue() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST AddXML
     : public virtual iface::SProS::Change
    {
    public:
      virtual ~AddXML() {}
      virtual iface::dom::NodeList* anyXML() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST ChangeXML
     : public virtual iface::SProS::AddXML
    {
    public:
      virtual ~ChangeXML() {}
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST RemoveXML
     : public virtual iface::SProS::Change
    {
    public:
      virtual ~RemoveXML() {}
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Variable
     : public virtual iface::SProS::NamedIdentifiedElement
    {
    public:
      virtual ~Variable() {}
      virtual wchar_t* target() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void target(const wchar_t* attr) throw(std::exception&) = 0;
      virtual wchar_t* symbol() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void symbol(const wchar_t* attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST VariableSet
     : public virtual iface::SProS::NamedIdentifiedElementSet
    {
    public:
      virtual ~VariableSet() {}
      virtual iface::SProS::VariableIterator* iterateVariables() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Variable* getVariableByIdentifier(const wchar_t* idMatch) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST VariableIterator
     : public virtual iface::SProS::NamedIdentifiedElementIterator
    {
    public:
      virtual ~VariableIterator() {}
      virtual iface::SProS::Variable* nextVariable() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Parameter
     : public virtual iface::SProS::NamedIdentifiedElement
    {
    public:
      virtual ~Parameter() {}
      virtual double value() throw(std::exception&)  = 0;
      virtual void value(double attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST ParameterSet
     : public virtual iface::SProS::NamedIdentifiedElementSet
    {
    public:
      virtual ~ParameterSet() {}
      virtual iface::SProS::ParameterIterator* iterateParameters() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual iface::SProS::Parameter* getParameterByIdentifier(const wchar_t* idMatch) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST ParameterIterator
     : public virtual iface::SProS::NamedIdentifiedElementIterator
    {
    public:
      virtual ~ParameterIterator() {}
      virtual iface::SProS::Parameter* nextParameter() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Curve
     : public virtual iface::SProS::NamedElement
    {
    public:
      virtual ~Curve() {}
      virtual bool logX() throw(std::exception&)  = 0;
      virtual void logX(bool attr) throw(std::exception&) = 0;
      virtual bool logY() throw(std::exception&)  = 0;
      virtual void logY(bool attr) throw(std::exception&) = 0;
      virtual wchar_t* xDataGeneratorID() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void xDataGeneratorID(const wchar_t* attr) throw(std::exception&) = 0;
      virtual wchar_t* yDataGeneratorID() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void yDataGeneratorID(const wchar_t* attr) throw(std::exception&) = 0;
      virtual iface::SProS::DataGenerator* xDataGenerator() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void xDataGenerator(iface::SProS::DataGenerator* attr) throw(std::exception&) = 0;
      virtual iface::SProS::DataGenerator* yDataGenerator() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void yDataGenerator(iface::SProS::DataGenerator* attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST CurveSet
     : public virtual iface::SProS::NamedElementSet
    {
    public:
      virtual ~CurveSet() {}
      virtual iface::SProS::CurveIterator* iterateCurves() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST CurveIterator
     : public virtual iface::SProS::NamedElementIterator
    {
    public:
      virtual ~CurveIterator() {}
      virtual iface::SProS::Curve* nextCurve() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST Surface
     : public virtual iface::SProS::Curve
    {
    public:
      virtual ~Surface() {}
      virtual bool logZ() throw(std::exception&)  = 0;
      virtual void logZ(bool attr) throw(std::exception&) = 0;
      virtual wchar_t* zDataGeneratorID() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void zDataGeneratorID(const wchar_t* attr) throw(std::exception&) = 0;
      virtual iface::SProS::DataGenerator* zDataGenerator() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void zDataGenerator(iface::SProS::DataGenerator* attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST SurfaceSet
     : public virtual iface::SProS::CurveSet
    {
    public:
      virtual ~SurfaceSet() {}
      virtual iface::SProS::SurfaceIterator* iterateSurfaces() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST SurfaceIterator
     : public virtual iface::SProS::CurveIterator
    {
    public:
      virtual ~SurfaceIterator() {}
      virtual iface::SProS::Surface* nextSurface() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST DataSet
     : public virtual iface::SProS::NamedElement
    {
    public:
      virtual ~DataSet() {}
      virtual wchar_t* dataGeneratorID() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void dataGeneratorID(const wchar_t* attr) throw(std::exception&) = 0;
      virtual iface::SProS::DataGenerator* dataGen() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
      virtual void dataGen(iface::SProS::DataGenerator* attr) throw(std::exception&) = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST DataSetSet
     : public virtual iface::SProS::NamedElementSet
    {
    public:
      virtual ~DataSetSet() {}
      virtual iface::SProS::DataSetIterator* iterateDataSets() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_SProS_PRE 
    class  PUBLIC_SProS_POST DataSetIterator
     : public virtual iface::SProS::NamedElementIterator
    {
    public:
      virtual ~DataSetIterator() {}
      virtual iface::SProS::DataSet* nextDataSet() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
  };
};
#undef PUBLIC_SProS_PRE
#undef PUBLIC_SProS_POST
#endif // guard
