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
  //DataContainer();
  static DataContainer* instance();
  bool loadGeometry(const std::string _path);
  void removeGeo(const unsigned _id);
 // void removeGeo(const std::string _name);
  void updateMaterial(unsigned _id);
  Mesh* findGeo(unsigned _id);
private :
  static DataContainer* s_instance;
  //std::unordered_map<std::unique_ptr<Mesh>> m_geoUnordered;
  std::vector<std::unique_ptr<Mesh>> m_geo;
  //std::unordered_map<std::unique_ptr<Material>> m_matUnordered;
  std::vector<std::unique_ptr<Material>> m_mat;

};

#endif
