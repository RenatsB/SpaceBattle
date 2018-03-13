#include "DataContainer.h"

void DataContainer::geoRemove(const size_t _id)
{
  auto it = m_geo.begin()+static_cast<long>(_id);
  m_geo.erase(it);
}
/*void DataContainer::geoRemove(const std::string _name)
{
  for(auto it = m_geo.begin(); it < m_geo.end(); ++it)
  {
    if(it.base()->get()->getName() == _name)
      m_geo.erase(it);
  }
}*/

void DataContainer::matUpdate(const size_t _id)
{
  m_mat.at(_id).get()->update();
}

BaseMesh* DataContainer::geoFind(const size_t _id) const
{
  if(_id < m_geo.size())
  {
    return m_geo.at(_id).get();
  }
  else
  {
    return nullptr;
  }
}

void DataContainer::matPut(BaseMaterial* _new)
{
  m_mat.emplace_back(_new);
}

void DataContainer::geoPut(BaseMesh* _new)
{
  m_geo.emplace_back(_new);
}

size_t DataContainer::matSize() const
{
  return m_mat.size();
}

size_t DataContainer::geosize() const
{
  return m_geo.size();
}

BaseMaterial* DataContainer::matFind(const size_t _id) const
{
  if(_id < m_mat.size())
  {
     return m_mat.at(_id).get();
  }
  else
  {
    return nullptr;
  }
}

