#ifndef BASEMESH_H_
#define BASEMESH_H_
#include <string>

class BaseMesh
{
public:
  BaseMesh()=default;
  BaseMesh(const BaseMesh&) = default;
  BaseMesh& operator=(const BaseMesh&) = default;
  BaseMesh(BaseMesh&&) = default;
  BaseMesh& operator=(BaseMesh&&) = default;
  virtual ~BaseMesh()=default;
  virtual void load(const std::string &_fname)=0;
  virtual void reset()=0;
};

#endif //BASEMESH_H_
