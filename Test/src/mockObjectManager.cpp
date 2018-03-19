#include "mockObjectManager.h"
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::selectObject(const size_t _id)
{
  if(m_selected.empty()) //none selected yet
  {
    m_selected.push_back(_id);
  }
  else
  {
    if(findObject(_id)) //if object exists
    {
      m_selected.push_back(_id);
    }
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::selectObject(const std::string &_name)
{
  if(_name.empty()) //no name specified => select all
  {
    for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
    {
      size_t num = it->get()->getID();
      if(!isSelected(num))
        m_selected.push_back(num);
    }
  }
  else //otherwise select a single object
  {
    if(findObject(_name)) //if object exists
      m_selected.push_back(getObjectID(_name));
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::selectObject(const std::vector<size_t> &_ids)
{
  if(_ids.empty()) //no ids specified
  {
    selectObject(""); //select all
  }
  else
  {
    for(auto id : _ids)
      selectObject(id);
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::selectObject(const std::vector<std::string> &_names)
{
  if(_names.empty()) //no names specified
  {
    selectObject(""); //select all
  }
  else
  {
    for(auto name : _names)
      selectObject(name);
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::deselectObject(const size_t _id)
{
  for(auto it = m_selected.begin(); it<m_selected.end(); ++it)
  {
    if(*it == _id)
    {
      m_selected.erase(it);
      break;
    }
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::deselectObject(const std::string &_name)
{
  if(_name.empty()) //no name => deselect all
  {
    m_selected.clear();
    m_selected.resize(0);
  }
  else
  {
    if(findObject(_name))
    {
      size_t id = getObjectID(_name);
      for(auto it = m_selected.begin(); it<m_selected.end(); ++it)
      {
        if(*it == id)
        {
          m_selected.erase(it);
          break;
        }
      }
    }
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::deselectObject(const std::vector<size_t> &_ids)
{
  if(_ids.empty()) //no ids => deselect all
  {
    deselectObject("");
  }
  else
  {
    for(auto id : _ids)
      deselectObject(id);
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::deselectObject(const std::vector<std::string> &_names)
{
  if(_names.empty()) //no names => deselect all
  {
    deselectObject("");
  }
  else
  {
    for(auto name : _names)
      deselectObject(name);
  }
}
//-----------------------------------------------------------------------------------------------------
bool mockObjectManager::isSelected(const size_t _id)const
{
  for(auto it = m_selected.begin(); it<m_selected.end(); ++it)
  {
    if(*it.base() == _id)
    {
      return true;
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------
bool mockObjectManager::isSelected(const std::string _name)const
{
  for(auto it = m_selected.begin(); it<m_selected.end(); ++it)
  {
    if(*it.base() == getObjectID(_name))
    {
      return true;
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::move(unsigned short _axis, float _val)
{
  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->moveObject(constructTranslateVector(_axis, _val));
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::scale(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->scaleObject(constructTranslateVector(_axis, _val));
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::rotate(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->rotateObject(constructTranslateVector(_axis, _val));
  }
}
//-----------------------------------------------------------------------------------------------------
glm::vec3 mockObjectManager::constructTranslateVector(unsigned short _axis, float _val) const
{
  glm::vec3 ret(0,0,0);
  switch(_axis)
  {
    case 0 : {ret.x = _val; break;}
    case 1 : {ret.y = _val; break;}
    case 2 : {ret.z = _val; break;}
    case 3 : {ret.x = _val; ret.y = _val; break;}
    case 4 : {ret.y = _val; ret.z = _val;break;}
    case 6 : {ret.x = _val; ret.z = _val;break;}
    default : {ret.x = _val; ret.y = _val; ret.z = _val;break;}
  }
  return ret;
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::changeGeo(std::pair<size_t, std::string> _geo)
{
  for(auto it : m_selected)
  {
    getObject(it)->setGeo(_geo);
  }
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::changeMat(std::pair<size_t, std::string> _mat)
{
  for(auto it : m_selected)
  {
    getObject(it)->setMat(_mat);
  }
}
//-----------------------------------------------------------------------------------------------------
mockSceneObject* mockObjectManager::objectAt(size_t _pos) const
{
  return m_sceneObjects.at(_pos).get();
}
//-----------------------------------------------------------------------------------------------------
bool mockObjectManager::findObject(const size_t _id) const
{
  for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      return true;
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------
bool mockObjectManager::findObject(const std::string &_name) const
{
  for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
  {
    if(_name == it->get()->getName())
    {
      return true;
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------
mockSceneObject* mockObjectManager::getObject(size_t _id) const
{
  for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      return it->get();
    }
  }
  return nullptr;
}
//-----------------------------------------------------------------------------------------------------
mockSceneObject* mockObjectManager::getObject(std::string _name) const
{
  for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
  {
    if(_name == it.base()->get()->getName())
    {
      return it.base()->get();
    }
  }
  return nullptr;
}
//-----------------------------------------------------------------------------------------------------
size_t mockObjectManager::getObjectID(const std::string &_name) const
{
  size_t id=0;
  for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
  {
    if(_name == it->get()->getName())
    {
      id=it.base()->get()->getID();
      break;
    }
  }
  return id;
}
//-----------------------------------------------------------------------------------------------------
size_t mockObjectManager::getObjectCount() const
{
  return m_sceneObjects.size();
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::checkObjectIDs()
{
  std::vector<size_t> currentUsed = getCurrentIDs();
  for(size_t m =0; m<currentUsed.size(); ++m)
  {
    for(size_t n=m+1; n<currentUsed.size(); ++n)
    {
      if(currentUsed[m] == currentUsed[n])
      {
        size_t tmp = getFreeID();
        currentUsed[n] = tmp;
        m_sceneObjects[n]->changeID(tmp);
      }
    }
  }
}
//-----------------------------------------------------------------------------------------------------
size_t mockObjectManager::getFreeID() const
{
  size_t newID=0;
  std::vector<size_t> currentUsed = getCurrentIDs();
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
std::vector<size_t> mockObjectManager::getCurrentIDs()const
{
  std::vector<size_t> ret;
  ret.clear();
  ret.reserve(m_sceneObjects.size());
  for(size_t i=0; i<m_sceneObjects.size(); ++i)
  {
    ret.push_back(m_sceneObjects.at(i)->getID());
  }
  return ret;
}
//-----------------------------------------------------------------------------------------------------
inline std::string stringify(const QJsonValue _jStr)
{
  return _jStr.toString().toStdString();
}
//-----------------------------------------------------------------------------------------------------
inline size_t intify(int _jStr)
{
  return static_cast<size_t>(_jStr);
}
//-----------------------------------------------------------------------------------------------------
inline float floatify(const QJsonValue _jStr)
{
  return static_cast<float>(_jStr.toDouble());
}
//-----------------------------------------------------------------------------------------------------
glm::vec3 vectorize(const QJsonArray _jStr)
{
  auto arrX = _jStr[0];
  auto arrY = _jStr[1];
  auto arrZ = _jStr[2];
  return glm::vec3(floatify(arrX), floatify(arrY), floatify(arrZ));
}
//-----------------------------------------------------------------------------------------------------
