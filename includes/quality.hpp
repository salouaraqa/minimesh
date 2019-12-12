#pragma once

class QualityChecker
{
public:
  QualityChecker() {}
  ~QualityChecker(void) {}

  // TODO


  // TODO
  int evaluateMeshCell(vtkSmartPointer<vtkUnstructuredGrid>);
  void check_quality(vtkSmartPointer<vtkAppendFilter> filter);

};
