#ifndef GEOMETRYPOOL_H_
#define GEOMETRYPOOL_H_

#include <vector>
#include <unordered_map>
#include "MeshData.h"

class GeometryPool
{
public :
  static GeometryPool* instance();
  bool loadGeometry(const std::string _path);
  void removeGeo(const unsigned _id);
  void removeGeo(const std::string _name);
private :
  static GeometryPool* pInstance;
  bool checkValidity(const unsigned _id);
  void sortGeometry();
  //std::unordered_map<Geometry*,unsigned> m_geo;
  std::vector<MeshData*> m_geo;
};

#endif
