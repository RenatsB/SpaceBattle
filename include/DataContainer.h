#ifndef DATACONTAINER_H_
#define DATACONTAINER_H_

#include <vector>
#include <memory>
#include <unordered_map>
#include "Mesh.h"
#include "MaterialPhong.h"
#include "MaterialPBR.h"

class DataContainer
{
public :
  static DataContainer* instance();
  bool loadGeometry(const std::string _path);
  void removeGeo(const unsigned _id);
  void removeGeo(const std::string _name);
private :
  static DataContainer* pInstance;
  std::unordered_map<Mesh*,unsigned> m_geoUnordered;
  std::vector<std::unique_ptr<Mesh>> m_geo;
  std::unordered_map<Material*,unsigned> m_matUnordered;
  std::vector<std::unique_ptr<Material>> m_mat;

};

#endif
