#ifndef DATACONTAINER_H_
#define DATACONTAINER_H_

#include <vector>
#include <memory>
#include <unordered_map>
#include "BaseMesh.h"
#include "BaseMaterial.h"

class DataContainer
{
public :
  DataContainer()=default;
  ~DataContainer()=default;
  void matUpdate(const size_t _id);
  size_t matSize() const;
  size_t geosize() const;
  BaseMesh* geoFind(const size_t _id) const;
  BaseMesh* geoFind(const std::string _name) const;
  BaseMaterial* matFind(const size_t _id) const;
  BaseMaterial* matFind(const std::string _name) const;
  void matPut(BaseMaterial* _new);
  void matPut(BaseMaterial* _new, const std::string _name);
  void geoPut(BaseMesh* _new);
  void geoPut(BaseMesh* _new, const std::string _name);
  void matRemove(const std::string _name);
  void matRemove(const size_t _id);
  void geoRemove(const std::string _name);
  void geoRemove(const size_t _id);
  void setGeoName(const size_t _id, const std::string _new);
  void setMatName(const size_t _id, const std::string _new);
  std::vector<std::string> getGeoNames() const;
  std::vector<std::string> getMatNames() const;
  size_t getMatID(const std::string &_name) const;
  size_t getGeoID(const std::string &_name) const;
  std::string getMatName(const size_t _id) const;
  std::string getGeoName(const size_t _id) const;
private:
  void checkIDs();
  void checkGeoIDs();
  void checkMatIDs();
  size_t getFreeGeoID() const;
  size_t getFreeMatID() const;
  void checkNames();
  void checkMatNames();
  void checkGeoNames();
  std::vector<size_t> getCurrentGeoIDs()const;
  std::vector<size_t> getCurrentMatIDs()const;

private :
  std::vector<std::unique_ptr<BaseMesh>> m_geo;
  std::vector<std::unique_ptr<BaseMaterial>> m_mat;

};

#endif
