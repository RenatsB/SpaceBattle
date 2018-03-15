#include "ObjectManager.h"
#include <iostream>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <utility>

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
    if(findObject(_id))
    {
      m_selected.push_back(_id);
      std::cout<<"Selected: "<<_id<<std::endl;
    }
  }
}

void ObjectManager::selectObject(const std::string &_name)
{
  if(_name.empty())
  {
    for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
    {
      size_t num = it->get()->getID();
      if(!isSelected(num))
        m_selected.push_back(num);
    }
  }
  else
  {
    if(findObject(_name))
      m_selected.push_back(getObjectID(_name));
  }
}

void ObjectManager::selectObject(const std::vector<size_t> &_ids)
{
  if(_ids.empty())
  {
    selectObject("");
  }
  else
  {
    for(auto id : _ids)
      selectObject(id);
  }
}

void ObjectManager::selectObject(const std::vector<std::string> &_names)
{
  if(_names.empty())
  {
    selectObject("");
  }
  else
  {
    for(auto name : _names)
      selectObject(name);
  }
}

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

void ObjectManager::deselectObject(const std::string &_name)
{
  if(_name.empty())
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

void ObjectManager::deselectObject(const std::vector<size_t> &_ids)
{
  if(_ids.empty())
  {
    deselectObject("");
  }
  else
  {
    for(auto id : _ids)
      deselectObject(id);
  }
}

void ObjectManager::deselectObject(const std::vector<std::string> &_names)
{
  if(_names.empty())
  {
    deselectObject("");
  }
  else
  {
    for(auto name : _names)
      deselectObject(name);
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

void ObjectManager::changeMat(size_t _id)
{
  for(auto it : m_selected)
  {
    getObject(it)->setMat(_id);
  }
}

void ObjectManager::changeMat(std::string _name)
{
  for(auto it : m_selected)
  {
    getObject(it)->setMat(_name);
  }
}
void ObjectManager::changeGeo(size_t _id)
{
  for(auto it : m_selected)
  {
    getObject(it)->setGeo(_id);
  }
}

void ObjectManager::changeGeo(std::string _name)
{
  for(auto it : m_selected)
  {
    getObject(it)->setGeo(_name);
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
  for(auto it = m_sceneObjects.begin(); it<m_sceneObjects.end(); ++it)
  {
    if(_id == it->get()->getID())
    {
      return true;
    }
  }
  return false;
}

bool ObjectManager::findObject(const std::string &_name) const
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

size_t ObjectManager::getObjectID(const std::string &_name) const
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

std::string stringify(const QJsonValue _jStr)
{
  return _jStr.toString().toStdString();
}

size_t intify(const QJsonValue _jStr)
{
  return static_cast<size_t>(_jStr.toInt());
}

float floatify(const QJsonValue _jStr)
{
  return static_cast<float>(_jStr.toDouble());
}

bool boolify(const QJsonValue _jStr)
{
  return _jStr.toBool();
}

vec3 vectorize(const QJsonObject _jStr)
{
  auto arrX = _jStr["X"].toObject();
  auto arrY = _jStr["Y"].toObject();
  auto arrZ = _jStr["Z"].toObject();
  return vec3(floatify(arrX), floatify(arrY), floatify(arrZ));
}

void ObjectManager::loadRawSceneData(const std::string &_name)
{
  std::string save = "AutosavedScene";
  writeRawSceneData(save);

  m_sceneObjects.clear();
  m_sceneObjects.resize(0);
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
    auto sceneObject = obj.value().toObject();
    auto jname = sceneObject["Name"].toObject();
    auto jid = sceneObject["ID"].toObject();
    auto jactive = sceneObject["Active"].toObject();
    auto jpos = sceneObject["Position"].toObject();
    auto jrot = sceneObject["Rotation"].toObject();
    auto jscale = sceneObject["Scale"].toObject();
    auto jparent = sceneObject["Parent"].toObject();
    auto jgeoName = sceneObject["GeometryName"].toObject();
    auto jgeoID = sceneObject["GeometryID"].toObject();
    auto jmatName = sceneObject["MaterialName"].toObject();
    auto jmatID = sceneObject["MaterialID"].toObject();
    //now construct an object using retrieved info
    m_sceneObjects.emplace_back(new SceneObject(stringify(jname),
    vectorize(jpos), vectorize(jrot), vectorize(jscale),
    intify(jgeoID), intify(jmatID)));
    m_sceneObjects.back()->changeID(intify(jid));
    m_sceneObjects.back()->setActive(boolify(jactive));
    m_sceneObjects.back()->setGeo(stringify(jgeoName));
    m_sceneObjects.back()->setMat(stringify(jmatName));
    //do not assign relations at this point (not all objects constructed yet)
    //but save for later
    relations.push_back(std::pair<size_t,size_t>(intify(jparent),intify(jid)));
  }
  //here all objects should be ready for connection
  for(auto rel : relations)
  {
    getObject(rel.first)->addChild(getObject(rel.second));
  }
  file.close();
}

void ObjectManager::writeRawSceneData(const std::string &_name) const
{
  // Read in raw file
  QString fileName = QString::fromStdString("scenes/"+_name+".json");
  QFile file(fileName);
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  //write to file below

  // create document
  QJsonDocument doc;
  // Get the json object to view
  QJsonObject ObjectParts = doc.object();
  for(auto obj= m_sceneObjects.begin(); obj<m_sceneObjects.end(); ++obj)
  {
    auto sceneObject = QJsonObject();
    sceneObject["Name"] = QString::fromStdString(obj->get()->getName());
    sceneObject["ID"] = obj->get()->getID();
    auto jactive = sceneObject["Active"].toObject();
    auto jpos = sceneObject["Position"].toObject();
    auto jrot = sceneObject["Rotation"].toObject();
    auto jscale = sceneObject["Scale"].toObject();
    auto jparent = sceneObject["Parent"].toObject();
    auto jgeoName = sceneObject["GeometryName"].toObject();
    auto jgeoID = sceneObject["GeometryID"].toObject();
    auto jmatName = sceneObject["MaterialName"].toObject();
    auto jmatID = sceneObject["MaterialID"].toObject();
    ObjectParts.insert("Object", newObj);
  }
  file.write(doc.toJson());
  file.close();
}
