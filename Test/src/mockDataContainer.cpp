#include <QtTest/QtTest>
#include <vector>
#include <memory>
#include <unordered_map>
#include "mockMatGeo.cpp"
class mockDataContainer : public QObject
{
  Q_OBJECT
public :
  mockDataContainer()=default;
  ~mockDataContainer()=default;
  //void matUpdate(const size_t _id); <- this is virtual originally and does nothing at BaseMaterial level
  size_t matSize() const;
  size_t geosize() const;
  mockMatGeo* geoFind(const size_t _id) const;
  mockMatGeo* geoFind(const std::string _name) const;
  mockMatGeo* matFind(const size_t _id) const;
  mockMatGeo* matFind(const std::string _name) const;
  void matPut(mockMatGeo* _new);
  void matPut(mockMatGeo* _new, const std::string _name);
  void geoPut(mockMatGeo* _new);
  void geoPut(mockMatGeo* _new, const std::string _name);
  void matRemove(const std::string _name);
  void matRemove(const size_t _id);
  void geoRemove(const std::string _name);
  void geoRemove(const size_t _id);
  void setGeoName(const size_t _id, const std::string _new);
  void setMatName(const size_t _id, const std::string _new);
  std::string getMatName(const size_t _id) const;
  std::string getGeoName(const size_t _id) const;
  std::vector<std::string> getGeoNames() const;
  std::vector<std::string> getMatNames() const;
  size_t getMatID(const std::string &_name) const;
  size_t getGeoID(const std::string &_name) const;
  void checkIDs();
  void checkGeoIDs();
  void checkMatIDs();
  size_t getFreeGeoID() const;
  size_t getFreeMatID() const;
  std::vector<size_t> getCurrentGeoIDs()const;
  std::vector<size_t> getCurrentMatIDs()const;
  void checkNames();
  void checkMatNames();
  void checkGeoNames();
protected :
  std::vector<std::unique_ptr<mockMatGeo>> m_geo;
  std::vector<std::unique_ptr<mockMatGeo>> m_mat;
};
//-----------------------------------------------------------------------------------------------------
size_t mockDataContainer::matSize() const
{
  return m_mat.size();
}
//-----------------------------------------------------------------------------------------------------
size_t mockDataContainer::geosize() const
{
  return m_geo.size();
}
//-----------------------------------------------------------------------------------------------------
mockMatGeo* mockDataContainer::geoFind(const size_t _id) const
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
//-----------------------------------------------------------------------------------------------------
mockMatGeo* mockDataContainer::geoFind(const std::string _name) const
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
//-----------------------------------------------------------------------------------------------------
mockMatGeo* mockDataContainer::matFind(const size_t _id) const
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
//-----------------------------------------------------------------------------------------------------
mockMatGeo* mockDataContainer::matFind(const std::string _name) const
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::matPut(mockMatGeo* _new)
{
  m_mat.emplace_back(_new);
  checkMatIDs();
  checkMatNames();
}
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::matPut(mockMatGeo* _new, std::string _name)
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::geoPut(mockMatGeo* _new)
{
  m_geo.emplace_back(_new);
  checkGeoIDs();
  checkGeoNames();
}
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::geoPut(mockMatGeo* _new, std::string _name)
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::matRemove(const std::string _name)
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::matRemove(const size_t _id)
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::geoRemove(const std::string _name)
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::geoRemove(const size_t _id)
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::setGeoName(const size_t _id, const std::string _new)
{
  for(auto it = m_geo.begin(); it<m_geo.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      it->get()->setName(_new);
      break;
    }
  }
}
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::setMatName(const size_t _id, const std::string _new)
{
  for(auto it = m_mat.begin(); it<m_mat.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      it->get()->setName(_new);
      break;
    }
  }
}
//-----------------------------------------------------------------------------------------------------
std::string mockDataContainer::getMatName(const size_t _id) const
{
  for(auto it = m_mat.begin(); it<m_mat.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      return it->get()->getName();
    }
  }
  return "Material1";
}
//-----------------------------------------------------------------------------------------------------
std::string mockDataContainer::getGeoName(const size_t _id) const
{
  for(auto it = m_geo.begin(); it<m_geo.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      return it->get()->getName();
    }
  }
  return "Mesh1";
}
//-----------------------------------------------------------------------------------------------------
std::vector<std::string> mockDataContainer::getGeoNames() const
{
  std::vector<std::string> ret;
  for(auto it = m_geo.begin(); it<m_geo.end(); ++it)
  {
    ret.emplace_back(it->get()->getName());
  }
  return ret;
}
//-----------------------------------------------------------------------------------------------------
std::vector<std::string> mockDataContainer::getMatNames() const
{
  std::vector<std::string> ret;
  for(auto it = m_mat.begin(); it<m_mat.end(); ++it)
  {
    ret.emplace_back(it->get()->getName());
  }
  return ret;
}
//-----------------------------------------------------------------------------------------------------
size_t mockDataContainer::getMatID(const std::string &_name) const
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
//-----------------------------------------------------------------------------------------------------
size_t mockDataContainer::getGeoID(const std::string &_name) const
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::checkIDs()
{
  checkGeoIDs();
  checkMatIDs();
}
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::checkGeoIDs()
{
  std::vector<size_t> currentUsed = getCurrentGeoIDs();
  for(size_t m =0; m<currentUsed.size(); ++m)
  {
    for(size_t n=m+1; n<currentUsed.size(); ++n) //start from 1
    {
      if(currentUsed[m] == currentUsed[n]) //if we have a match
      {
        size_t tmp = getFreeGeoID();
        currentUsed[n] = tmp; //update for further loop iterations
        m_geo[n]->setID(tmp);
      }
    }
  }
}
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::checkMatIDs()
{
  std::vector<size_t> currentUsed = getCurrentMatIDs();
  for(size_t m =0; m<currentUsed.size(); ++m)
  {
    for(size_t n=m+1; n<currentUsed.size(); ++n) //start from 1
    {
      if(currentUsed[m] == currentUsed[n]) //if we have a match
      {
        size_t tmp = getFreeMatID();
        currentUsed[n] = tmp; //update for further loop iterations
        m_mat[n]->setID(tmp);
      }
    }
  }
}
//-----------------------------------------------------------------------------------------------------
size_t mockDataContainer::getFreeGeoID() const
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
//-----------------------------------------------------------------------------------------------------
size_t mockDataContainer::getFreeMatID() const
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
//-----------------------------------------------------------------------------------------------------
std::vector<size_t> mockDataContainer::getCurrentGeoIDs() const
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
//-----------------------------------------------------------------------------------------------------
std::vector<size_t> mockDataContainer::getCurrentMatIDs() const
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::checkNames()
{
  checkMatNames();
  checkGeoNames();
}
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::checkMatNames()
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
//-----------------------------------------------------------------------------------------------------
void mockDataContainer::checkGeoNames()
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
//-----------------------------------------------------------------------------------------------------
