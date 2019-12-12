#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>

#include<vtkUnstructuredGrid.h>
#include <vtkVersion.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkDataSet.h>
#include <vtkMeshQuality.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include<vtkAppendFilter.h>

#include"quality.hpp"
#include"viewer.hpp"
#define 	VTK_QUALITY_SHAPE_AND_SIZE   14



int QualityChecker::evaluateMeshCell(vtkSmartPointer<vtkUnstructuredGrid> mesh)
{
    vtkSmartPointer<vtkMeshQuality> qual = vtkSmartPointer<vtkMeshQuality>::New();
    qual->SetInputData(mesh);
    qual->SetHexQualityMeasureToVolume();
    qual->Update();
    vtkSmartPointer<vtkDoubleArray> quality = vtkDoubleArray::SafeDownCast(qual->GetOutput()->GetCellData()->GetArray("Quality"));
    int nNeg = 0;
    for (vtkIdType i = 0; i < quality->GetNumberOfTuples(); i++)
    {

        if (quality->GetValue(i) < 0)
            nNeg++;
    }
    return nNeg;
}

void QualityChecker::check_quality(vtkSmartPointer<vtkAppendFilter> filter){
    vtkSmartPointer<vtkMeshQuality> qualityFilter = vtkSmartPointer<vtkMeshQuality>::New();
    qualityFilter->SetInputConnection(filter->GetOutputPort());
    qualityFilter->SetTriangleQualityMeasure(VTK_QUALITY_SHAPE_AND_SIZE);
    qualityFilter->Update();
    auto viewer = new Viewer();
    viewer->view(qualityFilter->GetOutput());
  }
