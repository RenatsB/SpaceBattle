#ifndef BASEMATERIAL_H_
#define BASEMATERIAL_H_
#include <string>

class BaseMaterial
{
public:
  BaseMaterial()=default;
  BaseMaterial(const BaseMaterial&) = default;
  BaseMaterial& operator=(const BaseMaterial&) = default;
  BaseMaterial(BaseMaterial&&) = default;
  BaseMaterial& operator=(BaseMaterial&&) = default;
  virtual ~BaseMaterial();
  virtual void init()=0;
  virtual void update()=0;
  virtual void apply();
  virtual const char* shaderFileName() const = 0;
  virtual void setShaderName(const std::string &_name);
};

#endif //BASEMATERIAL_H_
