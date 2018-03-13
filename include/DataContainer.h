#ifndef DATACONTAINER_H_
#define DATACONTAINER_H_

#include <vector>
#include <memory>
#include <unordered_map>
#include "GenericGeo.h"
#include "GenericMat.h"
#include "BaseMesh.h"
#include "BaseMaterial.h"

class DataContainer
{
public :
  DataContainer()=default;
  ~DataContainer()=default;
  //static DataContainer* instance();
  void matUpdate(const size_t _id);
  size_t matSize() const;
  size_t geosize() const;
  BaseMesh* geoFind(const size_t _id) const;
  BaseMesh* geoFind(const std::string _name) const;
  BaseMaterial* matFind(const size_t _id) const;
  BaseMaterial* matFind(const std::string _name) const;
  void matReserve(const size_t _amount);
  void geoReserve(const size_t _amount);
  void matPut(BaseMaterial* _new);
  void geoPut(BaseMesh* _new);
  void matRemove(const std::string _name);
  void matRemove(const size_t _id);
  void geoRemove(const std::string _name);
  void geoRemove(const size_t _id);
  std::vector<std::string> getGeoNames() const;
  std::vector<std::string> getMatNames() const;

private :
  //static DataContainer* s_instance;
  std::vector<std::unique_ptr<BaseMesh>> m_geo;
  std::vector<std::unique_ptr<BaseMaterial>> m_mat;

};

#endif
