#include <qtest.h>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
using namespace glm;
class mockSceneObject : public QObject
{
  Q_OBJECT
public :
  mockSceneObject(std::string _name = "SceneObject", glm::vec3 _pos=glm::vec3(0,0,0), glm::vec3 _rot=glm::vec3(0,0,0), glm::vec3 _sc=glm::vec3(1,1,1),
              std::pair<size_t, std::string>_geo = {1, "Mesh1"}, std::pair<size_t, std::string>_mat={0, "Material1"}):
    m_pos(_pos),
    m_rot(_rot),
    m_scale(_sc),
    m_name(_name),
    m_MVmatrix(1),
    m_geometry(_geo.first, _geo.second),
    m_material(_mat.first, _mat.second)
  {}
  mockSceneObject(std::string _name = "SceneObject", std::pair<size_t, std::string>_geo = {1, "Mesh1"}, std::pair<size_t, std::string>_mat={0, "Material1"}):
    m_pos(glm::vec3(0,0,0)),
    m_rot(glm::vec3(0,0,0)),
    m_scale(glm::vec3(1,1,1)),
    m_name(_name),
    m_MVmatrix(1),
    m_geometry(_geo.first, _geo.second),
    m_material(_mat.first, _mat.second)
  {}
  ~mockSceneObject()=default;
  void reset();
  void changeID (const size_t _newID);
  void setName(const std::string _new);
  std::string getName() const;
  void setParent(mockSceneObject* _new);
  mockSceneObject* getParent() const;
  void addChild(mockSceneObject* _new);
  void setChildren(std::vector<mockSceneObject*> _new);
  std::vector<mockSceneObject*> getChildren() const;
  void moveObject (const vec3 _tr);
  void setPosition (const vec3 _tr);
  void rotateObject (const vec3 _rot);
  void setRotation (const vec3 _rot);
  void scaleObject (const vec3 _sc);
  void setScale (const vec3 _sc);
  vec3 getPosition () const;
  vec3 getRotation () const;
  vec3 getScale () const;
  size_t getID () const;
  void setActive(bool _new);
  bool isActive();
  void updateMatrix();
  mat4 getMVmatrix() const;
  void setGeo(std::pair<size_t, std::string> &_new);
  void setMat(std::pair<size_t, std::string> &_new);
  size_t getGeoID() const;
  std::string getGeoName() const;
  size_t getMatID() const;
  std::string getMatName() const;
protected :
  vec3 m_pos = glm::vec3(0,0,0);
  vec3 m_rot = glm::vec3(0,0,0);
  vec3 m_scale = glm::vec3(1,1,1);
  size_t m_id=0;
  mockSceneObject* m_parent = nullptr;
  std::vector<mockSceneObject*> m_children;
  std::string m_name = "SceneObject";
  bool m_isActive = true;
  mat4 m_MVmatrix {1};
  std::pair<size_t, std::string> m_geometry = {1, "Mesh1"};
  std::pair<size_t, std::string> m_material = {1, "Material1"};
};
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::changeID(const size_t _newID)
{
  m_id = _newID;
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::setName(const std::string _new)
{
  m_name = _new;
}
//-----------------------------------------------------------------------------------------------------
std::string mockSceneObject::getName() const
{
  return m_name;
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::setParent(mockSceneObject* _new)
{
  if(m_parent!=nullptr)
    m_parent->addChild(this); //remove this from current parent
  m_parent = _new;
  if(m_parent!=nullptr)
    m_parent->addChild(this); //add this to new parent
}
//-----------------------------------------------------------------------------------------------------
mockSceneObject* mockSceneObject::getParent() const
{
  return m_parent;
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::addChild(mockSceneObject* _new)
{
  if(!m_children.empty())
  {
    for(auto it= m_children.begin(); it<m_children.end(); ++it)
    {
      if(*it.base() == _new) //check if newly added object is already a child
        m_children.erase(it);
    }
  }
  else
  {
    m_children.emplace_back(_new);
    m_children.back()->updateMatrix();
  }
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::setChildren(std::vector<mockSceneObject*> _new)
{
  while(!m_children.empty())
    m_children.at(0)->setParent(nullptr); //since this will remove current child from the vector, use while loop
  m_children = _new;
  for(size_t i = 0; i<m_children.size(); ++i)
    m_children.at(i)->updateMatrix();
}
//-----------------------------------------------------------------------------------------------------
std::vector<mockSceneObject*> mockSceneObject::getChildren() const
{
  return m_children;
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::moveObject (const vec3 _tr)
{
  m_pos += _tr;
  updateMatrix();
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::setPosition(const vec3 _tr)
{
  m_pos=_tr;
  updateMatrix();
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::rotateObject (const vec3 _rot)
{
  m_rot += _rot;
  updateMatrix();
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::setRotation (const vec3 _rot)
{
  m_rot=_rot;
  updateMatrix();
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::scaleObject (const vec3 _sc)
{
  m_scale += _sc;
  updateMatrix();
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::setScale (const vec3 _sc)
{
  m_scale=_sc;
  updateMatrix();
}
//-----------------------------------------------------------------------------------------------------
vec3 mockSceneObject::getPosition () const
{
  return m_pos;
}
//-----------------------------------------------------------------------------------------------------
vec3 mockSceneObject::getRotation () const
{
  return m_rot;
}
//-----------------------------------------------------------------------------------------------------
vec3 mockSceneObject::getScale () const
{
  return m_scale;
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::setActive(bool _new)
{
  m_isActive = _new;
}
//-----------------------------------------------------------------------------------------------------
bool mockSceneObject::isActive()
{
  return m_isActive;
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::updateMatrix()
{
  m_MVmatrix = glm::mat4();
    if(m_parent==nullptr)
    {
      m_MVmatrix = glm::translate(m_MVmatrix, m_pos);
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
      m_MVmatrix = glm::scale(m_MVmatrix, m_scale);
    }
    else
    {
      m_MVmatrix=m_parent->getMVmatrix();
      m_MVmatrix = glm::translate(m_MVmatrix, m_pos);
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
      m_MVmatrix = glm::rotate(m_MVmatrix, glm::radians(m_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
      m_MVmatrix = glm::scale(m_MVmatrix, m_scale);
    }

    if(!m_children.empty()) //make sure to update children as they have no way of knowing of the parent matrix changes
    {
      for(auto child : m_children)
        child->updateMatrix();
    }
}
//-----------------------------------------------------------------------------------------------------
mat4 mockSceneObject::getMVmatrix() const
{
  return m_MVmatrix;
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::reset()
{
  m_pos=vec3(0,0,0);
  m_rot=vec3(0,0,0);
  m_scale=vec3(1,1,1);
  if(m_parent != nullptr)
    setParent(nullptr);
  if(!m_children.empty())
    setChildren(std::vector<mockSceneObject*>{});
  setActive(true);
  std::pair<size_t, std::string> geo{1, "Mesh1"};
  std::pair<size_t, std::string> mat{1, "Material1"};
  setGeo(geo);
  setMat(mat);
}
//-----------------------------------------------------------------------------------------------------
size_t mockSceneObject::getID () const
{
  return m_id;
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::setGeo(std::pair<size_t, std::string> &_new)
{
  m_geometry = _new;
}
//-----------------------------------------------------------------------------------------------------
void mockSceneObject::setMat(std::pair<size_t, std::string> &_new)
{
  m_material = _new;
}
//-----------------------------------------------------------------------------------------------------
size_t mockSceneObject::getGeoID() const
{
  return m_geometry.first;
}
//-----------------------------------------------------------------------------------------------------
std::string mockSceneObject::getGeoName() const
{
  return m_geometry.second;
}
//-----------------------------------------------------------------------------------------------------
size_t mockSceneObject::getMatID() const
{
  return m_material.first;
}
//-----------------------------------------------------------------------------------------------------
std::string mockSceneObject::getMatName() const
{
  return m_material.second;
}
//-----------------------------------------------------------------------------------------------------
