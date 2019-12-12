#pragma once
#include <vtkSmartPointer.h>
#include<vtkXMLImageDataReader.h>


class Viewer
{
public:
  Viewer(void) {}
  ~Viewer(void) {}

  // TODO
  void view(vtkSmartPointer<vtkDataSet>);

};
