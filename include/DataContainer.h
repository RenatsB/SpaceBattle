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
  bool geoLoad(const std::string _path);
  void matUpdate(const size_t _id);
  bool matLoad(const size_t _id);
  size_t matSize() const;
  size_t geosize() const;
  Mesh* geoFind(const size_t _id) const;
  Mesh* geoFind(const std::string _name) const;
  Material* matFind(const size_t _id) const;
  Material* matFind(const std::string _name) const;
  void matReserve(const size_t _amount);
  void geoReserve(const size_t _amount);
  void matPut(Material* _new);
  void geoPut(Mesh* _new);
  void matRemove(const std::string _name);
  void matRemove(const size_t _id);
  void geoRemove(const std::string _name);
  void geoRemove(const size_t _id);
  std::vector<std::string> getGeoNames() const;
  std::vector<std::string> getMatNames() const;
private :
  static DataContainer* s_instance;
  std::vector<std::unique_ptr<Mesh>> m_geo;
  std::vector<std::unique_ptr<Material>> m_mat;

};

#endif
