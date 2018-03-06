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
  void removeGeo(const size_t _id);
 // void removeGeo(const std::string _name);
  void updateMaterial(size_t _id);
  bool loadMaterial(size_t _id);
  Material* findMat(size_t _id);
  size_t matSize() const;
  size_t geosize() const;
  Mesh* findGeo(size_t _id);
  void matReserve(size_t _amount);
  void geoReserve(size_t _amount);
  void matPut(Material* _new);
  void geoPut(Mesh* _new);
private :
  static DataContainer* s_instance;
  //std::unordered_map<std::unique_ptr<Mesh>> m_geoUnordered;
  std::vector<std::unique_ptr<Mesh>> m_geo;
  //std::unordered_map<std::unique_ptr<Material>> m_matUnordered;
  std::vector<std::unique_ptr<Material>> m_mat;

};

#endif
