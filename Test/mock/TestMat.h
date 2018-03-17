#include "BaseMaterial.h"

class TestMat : public BaseMaterial
{
public:
  TestMat()=default;
  TestMat(const TestMat&) = default;
  TestMat& operator=(const TestMat&) = default;
  TestMat(TestMat&&) = default;
  TestMat& operator=(TestMat&&) = default;
  ~TestMat()override=default;
  virtual void init() override;
  virtual void update() override;
  virtual void apply() override;
  virtual const char* shaderFileName() const override;
  virtual void setShaderName(const std::string &_name) override;
};
