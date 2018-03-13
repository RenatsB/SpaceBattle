#include "GenericGeo.h"

size_t GenericGeo::getGeoID() const
{
  return m_id;
}

std::string GenericGeo::getGeoName() const
{
  return m_name;
}

void GenericGeo::setGeoID(size_t _id)
{
  m_id = _id;
}

void GenericGeo::setGeoName(std::string &_name)
{
  m_name = _name;
}
