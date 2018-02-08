#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <memory>
#include <ngl/Obj.h>

class Geometry
{
public :
  Geometry()=default;
  ~Geometry();
  void clear();
  bool reload();
  bool load(std::string _path);
  unsigned getID() const;
  std::string getName() const;
  void setName(const std::string _name);
private :
  ngl::Obj m_data;
  unsigned m_id;
  std::string m_name;
};

#endif
