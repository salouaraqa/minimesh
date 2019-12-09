#include <vtkSmartPointer.h>
#include <vtkXMLUnstructuredGridReader.h>

#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkNamedColors.h>

#pragma once


class Viewer
{
public:
  Viewer(void) {}
  ~Viewer(void) {}

  // TODO
  void view(vtkSmartPointer<vtkXMLUnstructuredGridReader> reader)

  {
    auto colors = vtkSmartPointer<vtkNamedColors>::New();

    auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->ScalarVisibilityOff();

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->EdgeVisibilityOn();
    actor->GetProperty()->SetLineWidth(2.0);

    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    auto renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("Wheat").GetData());

    renderWindow->SetSize(640, 480);

    renderWindow->Render();
    renderWindowInteractor->Start();



  }

};
