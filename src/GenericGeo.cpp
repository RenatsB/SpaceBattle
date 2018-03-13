#include "GenericGeo.h"

size_t GenericGeo::getGeoID() const
{
  return m_id;
}

std::string GenericGeo::getGeoName() const
{
  return m_name;
}

/*void load(const std::string &_fname, const size_t _meshNum = 0)
{
  return;
}*/
