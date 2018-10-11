#include "ObjectManager.h"
#include <iostream>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <utility>
//-----------------------------------------------------------------------------------------------------
void ObjectManager::createGameObject(std::string _name, vec3 _pos, vec3 _rot, vec3 _sc, std::pair<size_t, std::string> _geo, std::pair<size_t, std::string> _mat)
{
  m_gameObjects.emplace_back(new GameObject(_name, _pos, _rot, _sc, _geo, _mat));
  checkObjectIDs();
}
//-----------------------------------------------------------------------------------------------------
void ObjectManager::createGameObject(std::string _name, std::pair<size_t, std::string> _geo, std::pair<size_t, std::string> _mat)
{
  m_gameObjects.emplace_back(new GameObject(_name, _geo, _mat));
  checkObjectIDs();
}
//-----------------------------------------------------------------------------------------------------
void ObjectManager::removeObject(const std::string _name)
{
  if(!_name.empty())
  {
    for(auto it = m_gameObjects.begin(); it<m_gameObjects.end(); ++it)
    {
      if(it->get()->getName() == _name)
        m_gameObjects.erase(it);
    }
  }
}
//-----------------------------------------------------------------------------------------------------
void ObjectManager::removeObject(const size_t _id)
{
  for(auto it = m_gameObjects.begin(); it<m_gameObjects.end(); ++it)
  {
    if(it->get()->getID() == _id)
      m_gameObjects.erase(it);
  }
}
//-----------------------------------------------------------------------------------------------------
void ObjectManager::selectObject(const size_t _id)
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
void ObjectManager::selectObject(const std::string &_name)
{
  if(_name.empty()) //no name specified => select all
  {
    for(auto it = m_gameObjects.begin(); it<m_gameObjects.end(); ++it)
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
void ObjectManager::selectObject(const std::vector<size_t> &_ids)
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
void ObjectManager::selectObject(const std::vector<std::string> &_names)
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
void ObjectManager::deselectObject(const size_t _id)
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
void ObjectManager::deselectObject(const std::string &_name)
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
void ObjectManager::deselectObject(const std::vector<size_t> &_ids)
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
void ObjectManager::deselectObject(const std::vector<std::string> &_names)
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
//-----------------------------------------------------------------------------------------------------
bool ObjectManager::isSelected(const std::string _name)const
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
void ObjectManager::move(unsigned short _axis, float _val)
{
  for(auto obj : m_selected)
  {
    m_gameObjects.at(obj)->moveObject(constructTranslateVector(_axis, _val));
  }
}
//-----------------------------------------------------------------------------------------------------
void ObjectManager::scale(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_gameObjects.at(obj)->scaleObject(constructTranslateVector(_axis, _val));
  }
}
//-----------------------------------------------------------------------------------------------------
void ObjectManager::rotate(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_gameObjects.at(obj)->rotateObject(constructTranslateVector(_axis, _val));
  }
}
//-----------------------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------------------
void ObjectManager::changeGeo(std::pair<size_t, std::string> _geo)
{
  for(auto it : m_selected)
  {
    getObject(it)->setGeo(_geo);
  }
}
//-----------------------------------------------------------------------------------------------------
void ObjectManager::changeMat(std::pair<size_t, std::string> _mat)
{
  for(auto it : m_selected)
  {
    getObject(it)->setMat(_mat);
  }
}
//-----------------------------------------------------------------------------------------------------
GameObject* ObjectManager::objectAt(size_t _pos) const
{
  return m_gameObjects.at(_pos).get();
}
//-----------------------------------------------------------------------------------------------------
bool ObjectManager::findObject(const size_t _id) const
{
  for(auto it = m_gameObjects.begin(); it<m_gameObjects.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      return true;
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------
bool ObjectManager::findObject(const std::string &_name) const
{
  for(auto it = m_gameObjects.begin(); it<m_gameObjects.end(); ++it)
  {
    if(_name == it->get()->getName())
    {
      return true;
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------
GameObject* ObjectManager::getObject(size_t _id) const
{
  for(auto it = m_gameObjects.begin(); it<m_gameObjects.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      return it->get();
    }
  }
  return nullptr;
}
//-----------------------------------------------------------------------------------------------------
GameObject* ObjectManager::getObject(std::string _name) const
{
  for(auto it = m_gameObjects.begin(); it<m_gameObjects.end(); ++it)
  {
    if(_name == it.base()->get()->getName())
    {
      return it.base()->get();
    }
  }
  return nullptr;
}
//-----------------------------------------------------------------------------------------------------
size_t ObjectManager::getObjectID(const std::string &_name) const
{
  size_t id=0;
  for(auto it = m_gameObjects.begin(); it<m_gameObjects.end(); ++it)
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
size_t ObjectManager::getObjectCount() const
{
  return m_gameObjects.size();
}
//-----------------------------------------------------------------------------------------------------
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
        m_gameObjects[n]->changeID(tmp);
      }
    }
  }
}
//-----------------------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------------------
std::vector<size_t> ObjectManager::getCurrentIDs()const
{
  std::vector<size_t> ret;
  ret.clear();
  ret.reserve(m_gameObjects.size());
  for(size_t i=0; i<m_gameObjects.size(); ++i)
  {
    ret.push_back(m_gameObjects.at(i)->getID());
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
vec3 vectorize(const QJsonArray _jStr)
{
  auto arrX = _jStr[0];
  auto arrY = _jStr[1];
  auto arrZ = _jStr[2];
  return vec3(floatify(arrX), floatify(arrY), floatify(arrZ));
}
//-----------------------------------------------------------------------------------------------------
void ObjectManager::loadRawSceneData(const std::string &_name)
{
  std::string save = "AutosavedScene";
  writeRawSceneData(save);

  m_gameObjects.clear();
  m_gameObjects.resize(0);
  m_selected.clear();
  m_selected.resize(0);

  // Read in raw file
  QString fileName = QString::fromStdString("scenes/"+_name+".json");
  QFile file(fileName);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QByteArray rawData = file.readAll();
  // Parse document
  QJsonDocument doc(QJsonDocument::fromJson(rawData));
  // Get the json object to view
  QJsonObject ObjectParts = doc.object();
  std::vector<std::pair<size_t, size_t>> relations;

  for(auto obj= ObjectParts.begin(); obj!=ObjectParts.end(); ++obj)
  {
    auto gameObject = obj.value().toObject();
    auto jname = gameObject["Name"].toString();
    auto jid = gameObject["ID"].toInt();
    bool jactive = gameObject["Active"].toBool();
    auto jpos = gameObject["Position"].toArray();
    auto jrot = gameObject["Rotation"].toArray();
    auto jscale = gameObject["Scale"].toArray();
    auto jparent = gameObject["Parent"].toInt();
    auto jgeoName = gameObject["GeometryName"].toString();
    auto jgeoID = gameObject["GeometryID"].toInt();
    std::cout<<jgeoID<<std::endl;
    auto jmatName = gameObject["MaterialName"].toString();
    auto jmatID = gameObject["MaterialID"].toInt();
    //now construct an object using retrieved info
    std::cout<<intify(jmatID)<<stringify(jmatName)<<std::endl;
    m_gameObjects.emplace_back(new GameObject(stringify(jname),
    vectorize(jpos), vectorize(jrot), vectorize(jscale),
    std::pair<size_t, std::string>{intify(jgeoID), stringify(jgeoName)}, std::pair<size_t, std::string>{intify(jmatID), stringify(jmatName)}));
    m_gameObjects.back()->changeID(intify(jid));
    m_gameObjects.back()->setActive(jactive);
    //do not assign relations at this point (not all objects constructed yet)
    //but save for later
    if(jparent != QJsonValue::Null)
    {
      relations.push_back(std::pair<size_t,size_t>(intify(jparent),intify(jid)));
    }
    //make sure to update matrix at this point ot else all objects will have default matrix
    m_gameObjects.back()->updateMatrix();
  }
  //here all objects should be ready for connection
  for(auto rel : relations)
  {
    //calling addChild also calls add parent in the child, so no need for extra code here
    getObject(rel.first)->addChild(getObject(rel.second));
  }
  file.close();
}
//-----------------------------------------------------------------------------------------------------
void ObjectManager::writeRawSceneData(const std::string &_name) const
{
  // Read in raw file
  QString fileName = QString::fromStdString("scenes/"+_name+".json");
  QFile file(fileName);
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  //write to file below

  // Get the json object to view
  QJsonObject ObjectParts;
  size_t i=0;
  for(auto obj= m_gameObjects.begin(); obj<m_gameObjects.end(); ++obj)
  {
    auto gameObject = QJsonObject();
    gameObject["Name"] = QString::fromStdString(obj->get()->getName());
    gameObject["ID"] = static_cast<qint32>(obj->get()->getID());
    bool boolText = obj->get()->isActive() ? true : false;
    gameObject["Active"] = boolText;
    QJsonArray pos;
    pos.append(static_cast<double>(obj->get()->getPosition().x));
    pos.append(static_cast<double>(obj->get()->getPosition().y));
    pos.append(static_cast<double>(obj->get()->getPosition().z));
    gameObject["Position"] = pos;
    QJsonArray rot;
    rot.append(static_cast<double>(obj->get()->getRotation().x));
    rot.append(static_cast<double>(obj->get()->getRotation().y));
    rot.append(static_cast<double>(obj->get()->getRotation().z));
    gameObject["Rotation"] = rot;
    QJsonArray scale;
    scale.append(static_cast<double>(obj->get()->getScale().x));
    scale.append(static_cast<double>(obj->get()->getScale().y));
    scale.append(static_cast<double>(obj->get()->getScale().z));
    gameObject["Scale"] = scale;
    if(obj->get()->getParent() != nullptr)
    {
      gameObject["Parent"] = static_cast<qint32>(obj->get()->getParent()->getID());
    }
    else
    {
      gameObject["Parent"] = QJsonValue::Null;
    }
    gameObject["GeometryName"] = QString::fromStdString(obj->get()->getGeoName());
    gameObject["GeometryID"] = static_cast<qint32>(obj->get()->getGeoID());
    gameObject["MaterialName"] = QString::fromStdString(obj->get()->getMatName());
    gameObject["MaterialID"] = static_cast<qint32>(obj->get()->getMatID());
    ObjectParts["Object"+QString::fromStdString(std::to_string(i))] = gameObject;
    ++i;
  }
  QJsonDocument doc(ObjectParts);
  file.write(doc.toJson());
  file.close();
}
//-----------------------------------------------------------------------------------------------------