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

bool DataContainer::loadGeometry(const std::string _path)
{
  std::unique_ptr<Mesh> temp;
  temp.get()->load(_path);
  //catch exception

  m_geo.emplace_back(std::move(temp));
  //catch exception

  return true;
}

void DataContainer::removeGeo(const size_t _id)
{
  auto it = m_geo.begin()+static_cast<long>(_id);
  m_geo.erase(it);
}

void DataContainer::updateMaterial(size_t _id)
{
  m_mat.at(_id).get()->update();
}

Mesh* DataContainer::findGeo(size_t _id)
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

void DataContainer::matReserve(size_t _amount)
{
  m_mat.reserve(_amount);
}

void DataContainer::geoReserve(size_t _amount)
{
  for(size_t i = 0; i < _amount; ++i)
  {
    m_geo.emplace_back(new Mesh);
  }
}

void DataContainer::matPut(Material* _new)
{
  m_mat.emplace_back(_new);
}

void DataContainer::geoPut(Mesh* _new)
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

Material* DataContainer::findMat(size_t _id)
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
