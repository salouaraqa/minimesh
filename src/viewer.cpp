#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>

#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>

#include "viewer.hpp"


void Viewer::view(vtkSmartPointer<vtkDataSet> DataSet)
    {

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(DataSet);
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
