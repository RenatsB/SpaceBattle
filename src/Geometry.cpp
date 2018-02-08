#include "Geometry.h"

void Geometry::clear()
{
  //TODO
}

bool Geometry::reload()
{
  //TODO
  return true;
}

bool Geometry::load(std::string _path)
{
  //TODO
  return true;
}

unsigned Geometry::getID() const
{
  return m_id;
}

std::string Geometry::getName() const
{
  return m_name;
}

void Geometry::setName(const std::string _name)
{
  m_name = _name;
}
