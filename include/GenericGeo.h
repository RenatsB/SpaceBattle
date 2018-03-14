#ifndef GEOMETRYDATA_H
#define GEOMETRYDATA_H
#include <memory>

class GenericGeo
{
public:
  GenericGeo()=default;
  GenericGeo(size_t _id):
    m_id(_id),
    m_name("mesh"+std::to_string(_id))
  {}
  GenericGeo(size_t _id, std::string _name):
    m_id(_id),
    m_name(_name)
  {}
  GenericGeo(const GenericGeo&) = default;
  GenericGeo& operator=(const GenericGeo&) = default;
  GenericGeo(GenericGeo&&) = default;
  GenericGeo& operator=(GenericGeo&&) = default;
  virtual ~GenericGeo()=default;
  size_t getGeoID() const;
  std::string getGeoName() const;
  void setGeoID(size_t _id);
  void setGeoName(std::string &_name);
protected:
  size_t m_id = 0;
  std::string m_name = "mesh";
};

#endif //GEOMETRYDATA_H
