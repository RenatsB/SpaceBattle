#include "DataContainer.h"

void DataContainer::matUpdate(const size_t _id)
{
  m_mat.at(_id).get()->update();
}

void DataContainer::matPut(BaseMaterial* _new)
{
  m_mat.emplace_back(_new);
  checkMatIDs();
  checkMatNames();
}

void DataContainer::matPut(BaseMaterial* _new, std::string _name)
{
  if(!_name.empty())
  {
    _new->setName(_name);
    m_mat.emplace_back(_new);
    checkMatIDs();
  }
  else
  {
    m_mat.emplace_back(_new);
    checkMatIDs();
    checkMatNames();
  }
}

void DataContainer::geoPut(BaseMesh* _new)
{
  m_geo.emplace_back(_new);
  checkGeoIDs();
  checkGeoNames();
}

void DataContainer::geoPut(BaseMesh* _new, std::string _name)
{
  if(!_name.empty())
  {
    _new->setName(_name);
    m_geo.emplace_back(_new);
    checkGeoIDs();
  }
  else
  {
    m_geo.emplace_back(_new);
    checkGeoIDs();
    checkGeoNames();
  }
}

size_t DataContainer::matSize() const
{
  return m_mat.size();
}

size_t DataContainer::geosize() const
{
  return m_geo.size();
}

BaseMesh* DataContainer::geoFind(const size_t _id) const
{
  for(auto it = m_geo.begin(); it<m_geo.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      return it->get();
    }
  }
  return nullptr;
}

BaseMesh* DataContainer::geoFind(const std::string _name) const
{
  for(auto it = m_geo.begin(); it<m_geo.end(); ++it)
  {
    if(_name == it->get()->getName())
    {
      return it->get();
    }
  }
  return nullptr;
}

BaseMaterial* DataContainer::matFind(const size_t _id) const
{
  for(auto it = m_mat.begin(); it<m_mat.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      return it->get();
    }
  }
  return nullptr;
}

BaseMaterial* DataContainer::matFind(const std::string _name) const
{
  for(auto it = m_mat.begin(); it<m_mat.end(); ++it)
  {
    if(_name == it->get()->getName())
    {
      return it->get();
    }
  }
  return nullptr;
}

void DataContainer::matRemove(const std::string _name)
{
  for(auto it = m_mat.begin(); it<m_mat.end(); ++it)
  {
    if(_name == it->get()->getName())
    {
      m_mat.erase(it);
      break;
    }
  }
}

void DataContainer::matRemove(const size_t _id)
{
  for(auto it = m_mat.begin(); it<m_mat.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      m_mat.erase(it);
      break;
    }
  }
}

void DataContainer::geoRemove(const std::string _name)
{
  for(auto it = m_geo.begin(); it<m_geo.end(); ++it)
  {
    if(_name == it->get()->getName())
    {
      m_geo.erase(it);
      break;
    }
  }
}

void DataContainer::geoRemove(const size_t _id)
{
  for(auto it = m_geo.begin(); it<m_geo.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      m_geo.erase(it);
      break;
    }
  }
}

std::vector<std::string> DataContainer::getGeoNames() const
{
  std::vector<std::string> ret;
  for(auto it = m_geo.begin(); it<m_geo.end(); ++it)
  {
    ret.emplace_back(it->get()->getName());
  }
  return ret;
}

std::vector<std::string> DataContainer::getMatNames() const
{
  std::vector<std::string> ret;
  for(auto it = m_mat.begin(); it<m_mat.end(); ++it)
  {
    ret.emplace_back(it->get()->getName());
  }
  return ret;
}

size_t DataContainer::getMatID(const std::string &_name) const
{
  for(auto it = m_mat.begin(); it<m_mat.end(); ++it)
  {
    if(_name == it->get()->getName())
    {
      return it->get()->getID();
    }
  }
  return 0;
}

size_t DataContainer::getGeoID(const std::string &_name) const
{
  for(auto it = m_geo.begin(); it<m_geo.end(); ++it)
  {
    if(_name == it->get()->getName())
    {
      return it->get()->getID();
    }
  }
  return 0;
}

void DataContainer::checkIDs()
{
  checkGeoIDs();
  checkMatIDs();
}

void DataContainer::checkGeoIDs()
{
  std::vector<size_t> currentUsed = getCurrentGeoIDs();
  for(size_t m =0; m<currentUsed.size(); ++m)
  {
    if(m==0&&m_geo[m]->getName()=="")
      m_geo[m]->setName("Mesh");

    for(size_t n=m+1; n<currentUsed.size(); ++n)
    {
      if(currentUsed[m] == currentUsed[n])
      {
        size_t tmp = getFreeGeoID();
        currentUsed[n] = tmp;
        m_geo[n]->setID(tmp);
        if(m_geo[n]->getName() == "")
          m_geo[n]->setName("Mesh"+std::to_string(tmp));
      }
    }
  }
}

void DataContainer::checkMatIDs()
{
  std::vector<size_t> currentUsed = getCurrentMatIDs();
  for(size_t m =0; m<currentUsed.size(); ++m)
  {
    if(m==0&&m_mat[m]->getName()=="")
      m_mat[m]->setName("Material");

    for(size_t n=m+1; n<currentUsed.size(); ++n)
    {
      if(currentUsed[m] == currentUsed[n])
      {
        size_t tmp = getFreeMatID();
        currentUsed[n] = tmp;
        m_mat[n]->setID(tmp);
        if(m_mat[m]->getName()=="")
          m_mat[m]->setName("Material"+std::to_string(tmp));
      }
    }
  }
}

size_t DataContainer::getFreeGeoID() const
{
  size_t newID=0;
  std::vector<size_t> currentUsed = getCurrentGeoIDs();
  for(auto n : currentUsed)
  {
    if(n==newID) //match, need a different id
    {
      ++newID;
      if(n+1>newID)
        break;
    }
  }
  return newID;
}

size_t DataContainer::getFreeMatID() const
{
  size_t newID=0;
  std::vector<size_t> currentUsed = getCurrentMatIDs();
  for(auto n : currentUsed)
  {
    if(n==newID) //match, need a different id
    {
      ++newID;
      if(n+1>newID)
        break;
    }
  }
  return newID;
}

std::vector<size_t> DataContainer::getCurrentGeoIDs() const
{
  std::vector<size_t> ret;
  ret.clear();
  ret.reserve(m_geo.size());
  for(size_t i=0; i<m_geo.size(); ++i)
  {
    ret.push_back(m_geo.at(i)->getID());
  }
  return ret;
}

std::vector<size_t> DataContainer::getCurrentMatIDs() const
{
  std::vector<size_t> ret;
  ret.clear();
  ret.reserve(m_mat.size());
  for(size_t i=0; i<m_mat.size(); ++i)
  {
    ret.push_back(m_mat.at(i)->getID());
  }
  return ret;
}

void DataContainer::checkNames()
{
  checkMatNames();
  checkGeoNames();
}

void DataContainer::checkMatNames()
{
  std::vector<std::string> current = getMatNames();
  std::vector<size_t> currentIDs = getCurrentMatIDs();
  for(size_t m =0; m<current.size(); ++m)
  {
    if(m==0&&m_mat[m]->getName()=="")
      m_mat[m]->setName("Material");

    for(size_t n=m+1; n<current.size(); ++n)
    {
      if(current[m] == current[n])
      {
        std::string tmp = current[m]+std::to_string(currentIDs[n]);
        m_mat[n]->setName(tmp);
      }
    }
  }
}

void DataContainer::checkGeoNames()
{
  std::vector<std::string> current = getGeoNames();
  std::vector<size_t> currentIDs = getCurrentGeoIDs();
  for(size_t m =0; m<current.size(); ++m)
  {
    if(m==0&&m_geo[m]->getName()=="")
      m_geo[m]->setName("Mesh");

    for(size_t n=m+1; n<current.size(); ++n)
    {
      if(current[m] == current[n])
      {
        std::string tmp = current[m]+std::to_string(currentIDs[n]);
        m_geo[n]->setName(tmp);
      }
    }
  }
}
