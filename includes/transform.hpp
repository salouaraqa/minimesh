#pragma once

#include<memory>
#include "cpptoml.h"
enum TransformType
{ MERGE, TRANSLATE };

struct Params
{
  virtual ~Params(void) = default;
  TransformType transform_type;
  bool compute_quality;
  // TODO
};

struct MergeParams : public Params
{
  // TODO
  std::vector<std::string> input;
  std::string output;
};

struct TranslationParams : public Params
{
  std::string input;
  std::string output;
  std::vector<double> coords;
  // TODO
};

class Transform
{
public:
  Transform(void) {}
  ~Transform(void) {}

  // TODO
  void mymerge(MergeParams*);
  void mytranslate(TranslationParams*);
};
