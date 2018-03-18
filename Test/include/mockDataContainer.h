#include <vector>
#include <memory>
#include <unordered_map>
#include "mockMatGeo.cpp"
class mockDataContainer
{
public :
  mockDataContainer()=default;
  ~mockDataContainer()=default;
  size_t matSize() const;
  size_t geosize() const;
  mockMatGeo* geoFind(const size_t _id) const;
  mockMatGeo* geoFind(const std::string _name) const;
  mockMatGeo* matFind(const size_t _id) const;
  mockMatGeo* matFind(const std::string _name) const;
  void matPut(mockMatGeo* _new);
  void matPut(mockMatGeo* _new, const std::string _name);
  void geoPut(mockMatGeo* _new);
  void geoPut(mockMatGeo* _new, const std::string _name);
  void matRemove(const std::string _name);
  void matRemove(const size_t _id);
  void geoRemove(const std::string _name);
  void geoRemove(const size_t _id);
  void setGeoName(const size_t _id, const std::string _new);
  void setMatName(const size_t _id, const std::string _new);
  std::string getMatName(const size_t _id) const;
  std::string getGeoName(const size_t _id) const;
  std::vector<std::string> getGeoNames() const;
  std::vector<std::string> getMatNames() const;
  size_t getMatID(const std::string &_name) const;
  size_t getGeoID(const std::string &_name) const;
  void checkIDs();
  void checkGeoIDs();
  void checkMatIDs();
  size_t getFreeGeoID() const;
  size_t getFreeMatID() const;
  std::vector<size_t> getCurrentGeoIDs()const;
  std::vector<size_t> getCurrentMatIDs()const;
  void checkNames();
  void checkMatNames();
  void checkGeoNames();
protected :
  std::vector<std::unique_ptr<mockMatGeo>> m_geo;
  std::vector<std::unique_ptr<mockMatGeo>> m_mat;
};
