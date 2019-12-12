#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>


#include <vtkSmartPointer.h>
#include <vtkAppendFilter.h>

#include <vtkXMLUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>

#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>
#include <vtkVersion.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkGeometryFilter.h>
#include <vtkAppendPoints.h>

#include "transform.hpp"
#include "cpptoml.h"
#include "viewer.hpp"
#include "options.hpp"

void Transform::mymerge(MergeParams *mp)
{

  auto input1 = vtkSmartPointer<vtkUnstructuredGrid>::New();
  auto input2 = vtkSmartPointer<vtkUnstructuredGrid>::New();

  std::string inputFilename1 = mp->input[0];
  std::string inputFilename2 = mp->input[1];
  std::string output = mp->output;

  auto reader1 =vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader1->SetFileName(inputFilename1.c_str());
  reader1->Update();
  input1->ShallowCopy(reader1->GetOutput());

  auto reader2 = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader2->SetFileName(inputFilename2.c_str());
  reader2->Update();
  input2->ShallowCopy(reader2->GetOutput());


//Append the two meshes
  auto appendFilter = vtkSmartPointer<vtkAppendPoints>::New();
  appendFilter->AddInputData(input1);
  appendFilter->AddInputData(input2);


 //Remove any duplicate points.
  auto cleanFilter =  vtkSmartPointer<vtkCleanPolyData>::New();
  cleanFilter->SetInputConnection(appendFilter->GetOutputPort());
  cleanFilter->Update();

  auto writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName(output.c_str());
  writer->SetInputData(cleanFilter->GetOutput());


  auto reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader->SetFileName(output.c_str());
  reader->Update();

  auto viewer = new Viewer();
  viewer->view(reader->GetOutput());

}

void Transform::mytranslate(TranslationParams *tp){

}