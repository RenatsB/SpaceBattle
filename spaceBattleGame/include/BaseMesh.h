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

  virtual void setName(std::string _new);
  virtual std::string getName() const;
  virtual void setID(size_t _new);
  virtual size_t getID() const;
protected:
  size_t m_id=0;
  std::string m_name="";
};

#endif //BASEMESH_H_
