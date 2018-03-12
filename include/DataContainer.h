#ifndef DATACONTAINER_H_
#define DATACONTAINER_H_

#include <vector>
#include <memory>
#include <unordered_map>
#include "GenericGeo.h"
#include "GenericMat.h"

class DataContainer
{
public :
  static DataContainer* instance();
  void matUpdate(const size_t _id);
  size_t matSize() const;
  size_t geosize() const;
  GenericGeo* geoFind(const size_t _id) const;
  GenericGeo* geoFind(const std::string _name) const;
  GenericMat* matFind(const size_t _id) const;
  GenericMat* matFind(const std::string _name) const;
  void matReserve(const size_t _amount);
  void geoReserve(const size_t _amount);
  void matPut(GenericMat* _new);
  void geoPut(GenericGeo* _new);
  void matRemove(const std::string _name);
  void matRemove(const size_t _id);
  void geoRemove(const std::string _name);
  void geoRemove(const size_t _id);
  std::vector<std::string> getGeoNames() const;
  std::vector<std::string> getMatNames() const;

private :
  static DataContainer* s_instance;
  std::vector<std::unique_ptr<GenericGeo>> m_geo;
  std::vector<std::unique_ptr<GenericMat>> m_mat;

};

#endif
