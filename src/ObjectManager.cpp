#include "ObjectManager.h"
#include <iostream>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
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

vec3 vectorize(const QJsonArray _jStr)
{
  auto arrX = _jStr[0];
  auto arrY = _jStr[1];
  auto arrZ = _jStr[2];
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
    auto jname = sceneObject["Name"].toString();
    auto jid = sceneObject["ID"].toInt();
    bool jactive = sceneObject["Active"].toBool();
    auto jpos = sceneObject["Position"].toArray();
    auto jrot = sceneObject["Rotation"].toArray();
    auto jscale = sceneObject["Scale"].toArray();
    auto jparent = sceneObject["Parent"].toInt();
    auto jgeoName = sceneObject["GeometryName"].toString();
    auto jgeoID = sceneObject["GeometryID"].toInt();
    auto jmatName = sceneObject["MaterialName"].toString();
    auto jmatID = sceneObject["MaterialID"].toInt();
    //now construct an object using retrieved info
    m_sceneObjects.emplace_back(new SceneObject(stringify(jname),
    vectorize(jpos), vectorize(jrot), vectorize(jscale),
    intify(jgeoID), intify(jmatID)));
    m_sceneObjects.back()->changeID(intify(jid));
    m_sceneObjects.back()->setActive(jactive);
    m_sceneObjects.back()->setGeo(stringify(jgeoName));
    m_sceneObjects.back()->setMat(stringify(jmatName));
    //do not assign relations at this point (not all objects constructed yet)
    //but save for later
    if(jparent != QJsonValue::Null)
    {
      relations.push_back(std::pair<size_t,size_t>(intify(jparent),intify(jid)));
    }
    m_sceneObjects.back()->updateMatrix();
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

  // Get the json object to view
  QJsonObject ObjectParts;
  size_t i=0;
  for(auto obj= m_sceneObjects.begin(); obj<m_sceneObjects.end(); ++obj)
  {
    auto sceneObject = QJsonObject();
    sceneObject["Name"] = QString::fromStdString(obj->get()->getName());
    sceneObject["ID"] = static_cast<qint32>(obj->get()->getID());
    bool boolText = obj->get()->isActive() ? true : false;
    sceneObject["Active"] = boolText;
    QJsonArray pos;
    pos.append(static_cast<double>(obj->get()->getPosition().x));
    pos.append(static_cast<double>(obj->get()->getPosition().y));
    pos.append(static_cast<double>(obj->get()->getPosition().z));
    sceneObject["Position"] = pos;
    QJsonArray rot;
    rot.append(static_cast<double>(obj->get()->getRotation().x));
    rot.append(static_cast<double>(obj->get()->getRotation().y));
    rot.append(static_cast<double>(obj->get()->getRotation().z));
    sceneObject["Rotation"] = rot;
    QJsonArray scale;
    scale.append(static_cast<double>(obj->get()->getScale().x));
    scale.append(static_cast<double>(obj->get()->getScale().y));
    scale.append(static_cast<double>(obj->get()->getScale().z));
    sceneObject["Scale"] = scale;
    if(obj->get()->getParent() != nullptr)
    {
      sceneObject["Parent"] = QString::fromStdString(std::to_string(obj->get()->getParent()->getID()));
    }
    else
    {
      sceneObject["Parent"] = QJsonValue::Null;
    }
    sceneObject["GeometryName"] = QString::fromStdString(obj->get()->getGeoName());
    sceneObject["GeometryID"] = QString::fromStdString(std::to_string(obj->get()->getGeo()));
    sceneObject["MaterialName"] = QString::fromStdString(obj->get()->getMatName());
    sceneObject["MaterialID"] = QString::fromStdString(std::to_string(obj->get()->getMat()));
    //ObjectParts.append(sceneObject);
    ObjectParts["Object"+QString::fromStdString(std::to_string(i))] = sceneObject;
    ++i;
  }
  QJsonDocument doc(ObjectParts);
  file.write(doc.toJson());
  file.close();
}
