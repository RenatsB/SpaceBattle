#include "ObjectManager.h"

void ObjectManager::createSceneObject(std::string _name, vec3 _pos, vec3 _rot, vec3 _sc, size_t _geo, size_t _mat)
{
  m_sceneObjects.emplace_back(new SceneObject(_name, _pos, _rot, _sc, _geo, _mat));
  checkObjectIDs();
}

void ObjectManager::selectObject(const size_t _id)
{
  if(m_selected.empty())
  {
    m_selected.push_back(_id);
  }
  else
  {
    if(!findObject(_id))
      m_selected.push_back(_id);
  }
}

void ObjectManager::selectObject(const std::string &_name)
{
  if(_name.empty())
  {
    for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
    {
      if(!isSelected(it.base()->get()->getID()))
        m_selected.push_back(getObjectID(_name));
    }
  }
  else
  {
    if(findObject(_name))
      m_selected.push_back(getObjectID(_name));
  }
}

void ObjectManager::deselectObject(const size_t _id)
{
  for(auto it = m_selected.begin(); it<m_selected.end(); ++it)
  {
    if(*it.base() == _id)
    {
      m_selected.erase(it);
      break;
    }
  }
}

void ObjectManager::deselectObject(const std::string &_name)
{
  if(_name.empty())
  {
    m_selected.clear();
    m_selected.resize(0);
  }
  else
  {
    size_t id = getObjectID(_name);
    for(auto it = m_selected.begin(); it<m_selected.end(); ++it)
    {
      if(*it.base() == id)
      {
        m_selected.erase(it);
        break;
      }
    }
  }
}

void ObjectManager::move(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->moveObject(constructTranslateVector(_axis, _val));
  }
}

void ObjectManager::scale(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->scaleObject(constructTranslateVector(_axis, _val));
  }
}

void ObjectManager::rotate(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->rotateObject(constructTranslateVector(_axis, _val));
  }
}

vec3 ObjectManager::constructTranslateVector(unsigned short _axis, float _val) const
{
  vec3 ret(0,0,0);
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

SceneObject* ObjectManager::objectAt(size_t _pos) const
{
  return m_sceneObjects.at(_pos).get();
}

bool ObjectManager::findObject(const size_t _id) const
{
  bool check = false;
  for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
  {
    if(_id == it.base()->get()->getID())
    {
      check = true;
      break;
    }
  }
  return check;
}

bool ObjectManager::findObject(const std::string &_name) const
{
  bool check = false;
  for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
  {
    if(_name == it.base()->get()->getName())
    {
      check = true;
      break;
    }
  }
  return check;
}

size_t ObjectManager::getObjectID(const std::string &_name) const
{
  size_t id=0;
  for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
  {
    if(_name == it.base()->get()->getName())
    {
      id=it.base()->get()->getID();
      break;
    }
  }
  return id;
}

std::vector<size_t> ObjectManager::getCurrentIDs()const
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

void ObjectManager::checkObjectIDs()
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

size_t ObjectManager::getFreeID() const
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

SceneObject* ObjectManager::getObject(size_t _id) const
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

SceneObject* ObjectManager::getObject(std::string _name) const
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

size_t ObjectManager::getObjectCount() const
{
  return m_sceneObjects.size();
}

bool ObjectManager::isSelected(const size_t _id)const
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
