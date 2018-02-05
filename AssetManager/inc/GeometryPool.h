#ifndef GEOMETRYPOOL_H_
#define GEOMETRYPOOL_H_

#include <vector>
#include "Geometry.h"

class GeometryPool
{
public :
  bool loadGeometry(const std::string _path);
  void removeGeo(const unsigned _id);
  void removeGeo(const std::string _name);
private :
  bool checkValidity(const unsigned _id);
  std::vector<Geometry> m_geo;
};

#endif
