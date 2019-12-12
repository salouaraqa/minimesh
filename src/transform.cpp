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
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTransformFilter.h>
#include <vtkDataSetMapper.h>

#include "transform.hpp"
#include "cpptoml.h"
#include "viewer.hpp"
#include "options.hpp"
#include "quality.hpp"

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

  /*
    if(mp->compute_quality){
      auto qual = new QualityChecker();
      qual->check_quality(appendFilter->GetOutput());
    }
    */
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

  std::string input = tp->input;
  std::string output = tp->output;

  auto reader1 =vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader1->SetFileName(input.c_str());
  reader1->Update();

  auto originalMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  originalMapper->SetInputConnection(reader1->GetOutputPort());

  auto originalActor = vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);

  auto translation = vtkSmartPointer<vtkTransform>::New();
  translation->Translate(tp->coords[0],tp->coords[1],tp->coords[2]);

  auto reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
  reader->SetFileName(output.c_str());
  reader->Update();

  auto transformFilter = vtkSmartPointer<vtkTransformFilter>::New();
  transformFilter->SetInputConnection(reader->GetOutputPort());
  transformFilter->SetTransform(translation);
  transformFilter->Update();


   auto transformedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
   transformedMapper->SetInputConnection(transformFilter->GetOutputPort());

  auto transformedActor = vtkSmartPointer<vtkActor>::New();
  transformedActor->SetMapper(transformedMapper);


  auto renderer =  vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(transformedActor);
  renderer->SetBackground(.4, .5, .4); // Set renderer's background color to green

  auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  auto renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();
  renderWindowInteractor->Start();

}
