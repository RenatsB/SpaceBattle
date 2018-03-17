#include "BaseMesh.h"

class TestGeo : public BaseMesh
{
  TestGeo()=default;
  TestGeo(const TestGeo&) = default;
  TestGeo& operator=(const TestGeo&) = default;
  TestGeo(TestGeo&&) = default;
  TestGeo& operator=(TestGeo&&) = default;
  virtual ~TestGeo();
  virtual void load(const std::string &_fname) override;
  virtual void reset() override;
};
