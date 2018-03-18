#include <QtTest/QtTest>
#include "mockSceneObject.cpp"
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <utility>
class mockObjectManager
{
public:
  mockObjectManager()=default;
  ~mockObjectManager()=default;
  void createSceneObject(std::string _name="SceneObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1), std::pair<size_t, std::string> _geo={1, "Mesh1"}, std::pair<size_t, std::string> _mat={1, "Material1"});
  void createSceneObject(std::string _name="SceneObject", std::pair<size_t, std::string> _geo={1, "Mesh1"}, std::pair<size_t, std::string> _mat={1, "Material1"});
  void selectObject(const size_t _id);
  void selectObject(const std::string &_name);
  void selectObject(const std::vector<size_t> &_ids);
  void selectObject(const std::vector<std::string> &_names);
  void deselectObject(const size_t _id);
  void deselectObject(const std::string &_name);
  void deselectObject(const std::vector<size_t> &_ids);
  void deselectObject(const std::vector<std::string> &_names);
  bool isSelected(const size_t _id) const;
  bool isSelected(const std::string _name) const;
  void move(unsigned short _axis, float _val);
  void scale(unsigned short _axis, float _val);
  void rotate(unsigned short _axis, float _val);
  vec3 constructTranslateVector(unsigned short _axis, float _val) const;
  void changeGeo(std::pair<size_t, std::string> _geo);
  void changeMat(std::pair<size_t, std::string> _mat);
  mockSceneObject* objectAt(size_t _pos) const;
  bool findObject(const size_t _id) const;
  bool findObject(const std::string &_name) const;
  mockSceneObject* getObject(size_t _id) const;
  mockSceneObject* getObject(std::string _name) const;
  size_t getObjectID(const std::string &_name) const;
  size_t getObjectCount() const;
  void loadRawSceneData(const std::string &_name);
  void writeRawSceneData(const std::string &_name) const;
  void checkObjectIDs();
  size_t getFreeID() const;
  std::vector<size_t> getCurrentIDs()const;
private:
  std::vector<std::unique_ptr<mockSceneObject>> m_sceneObjects;
  std::vector<size_t> m_selected;
};
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::createSceneObject(std::string _name, vec3 _pos, vec3 _rot, vec3 _sc, std::pair<size_t, std::string> _geo, std::pair<size_t, std::string> _mat)
{
  m_sceneObjects.emplace_back(new mockSceneObject(_name, _pos, _rot, _sc, _geo, _mat));
  checkObjectIDs();
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::createSceneObject(std::string _name, std::pair<size_t, std::string> _geo, std::pair<size_t, std::string> _mat)
{
  m_sceneObjects.emplace_back(new mockSceneObject(_name, _geo, _mat));
  checkObjectIDs();
}
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
vec3 mockObjectManager::constructTranslateVector(unsigned short _axis, float _val) const
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
vec3 vectorize(const QJsonArray _jStr)
{
  auto arrX = _jStr[0];
  auto arrY = _jStr[1];
  auto arrZ = _jStr[2];
  return vec3(floatify(arrX), floatify(arrY), floatify(arrZ));
}
//-----------------------------------------------------------------------------------------------------
void mockObjectManager::loadRawSceneData(const std::string &_name)
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
    m_sceneObjects.emplace_back(new mockSceneObject(stringify(jname),
    vectorize(jpos), vectorize(jrot), vectorize(jscale),
    std::pair<size_t, std::string>{intify(jgeoID), stringify(jgeoName)}, std::pair<size_t, std::string>{intify(jmatID), stringify(jmatName)}));
    m_sceneObjects.back()->changeID(intify(jid));
    m_sceneObjects.back()->setActive(jactive);
    //do not assign relations at this point (not all objects constructed yet)
    //but save for later
    if(jparent != QJsonValue::Null)
    {
      relations.push_back(std::pair<size_t,size_t>(intify(jparent),intify(jid)));
    }
    //make sure to update matrix at this point ot else all objects will have default matrix
    m_sceneObjects.back()->updateMatrix();
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
void mockObjectManager::writeRawSceneData(const std::string &_name) const
{
  // Read in raw file
  QString fileName = QString::fromStdString("scenes/"+_name+".json");
  QFile file(fileName);
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  //write to file below

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
      sceneObject["Parent"] = static_cast<qint32>(obj->get()->getParent()->getID());
    }
    else
    {
      sceneObject["Parent"] = QJsonValue::Null;
    }
    sceneObject["GeometryName"] = QString::fromStdString(obj->get()->getGeoName());
    sceneObject["GeometryID"] = static_cast<qint32>(obj->get()->getGeoID());
    sceneObject["MaterialName"] = QString::fromStdString(obj->get()->getMatName());
    sceneObject["MaterialID"] = static_cast<qint32>(obj->get()->getMatID());
    ObjectParts["Object"+QString::fromStdString(std::to_string(i))] = sceneObject;
    ++i;
  }
  QJsonDocument doc(ObjectParts);
  file.write(doc.toJson());
  file.close();
}
//-----------------------------------------------------------------------------------------------------
