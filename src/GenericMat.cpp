#include "GenericMat.h"

size_t GenericMat::getMatID() const
{
  return m_id;
}
std::string GenericMat::getMatName() const
{
  return m_name;
}

void GenericMat::setMatID(size_t _id)
{
  m_id = _id;
}

void GenericMat::setMatName(std::string &_name)
{
  m_name = _name;
}
