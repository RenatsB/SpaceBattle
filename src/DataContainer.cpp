#include "DataContainer.h"

DataContainer *DataContainer::s_instance = 0;

DataContainer* DataContainer::instance()
{
  if(!s_instance)
    {
      s_instance = new DataContainer;
    }
  return s_instance;
}

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

GenericGeo* DataContainer::geoFind(const size_t _id) const
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

void DataContainer::matReserve(const size_t _amount)
{
  m_mat.reserve(_amount);
}

void DataContainer::geoReserve(const size_t _amount)
{
  for(size_t i = 0; i < _amount; ++i)
  {
    m_geo.emplace_back(new GenericGeo);
  }
}

void DataContainer::matPut(GenericMat* _new)
{
  m_mat.emplace_back(_new);
}

void DataContainer::geoPut(GenericGeo* _new)
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

GenericMat* DataContainer::matFind(const size_t _id) const
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

