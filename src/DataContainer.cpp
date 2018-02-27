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

/*bool DataContainer::loadGeometry(const std::string _path)
{
  unsigned newID = 0;
  for(auto it = m_geoUnordered.begin(); it != m_geoUnordered.end(); ++it)
  {
    if(it->second == newID)
    {
      ++newID;
    }
  }
  Mesh temp;
  temp.load(_path);
  //catch exception

  m_geoUnordered.push_back(temp, newID);
  //catch exception

  return true;
}

void DataContainer::removeGeo(const unsigned _id)
{
  for(auto it = m_geoUnordered.begin(); it != m_geoUnordered.end(); ++it)
  {
    if(it->second == _id)
    {
      m_geoUnordered.erase(it);
    }
  }
}

void DataContainer::updateMaterial(unsigned _id)
{
  for(auto it = m_matUnordered.begin(); it != m_matUnordered.end(); ++it)
  {
    if(it->second == _id)
    {
      it->first->update();
    }
  }
}
*/

bool DataContainer::loadGeometry(const std::string _path)
{
  std::unique_ptr<Mesh> temp;
  temp.get()->load(_path);
  //catch exception

  m_geo.emplace_back(std::move(temp));
  //catch exception

  return true;
}

void DataContainer::removeGeo(const unsigned _id)
{
  auto it = m_geo.begin()+_id;
  m_geo.erase(it);
}

void DataContainer::updateMaterial(unsigned _id)
{
  m_mat.at(_id).get()->update();
}

Mesh* DataContainer::findGeo(unsigned _id)
{
  return m_geo.at(_id).get();
}
