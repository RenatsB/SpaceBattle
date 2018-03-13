#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include <ext.hpp>
#include <glm.hpp>
#include <memory>
#include <vector>

using namespace glm;

class BaseObject
{
public :
  BaseObject(std::string _name = "SceneObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1)):
    m_pos(_pos),
    m_rot(_rot),
    m_scale(_sc),
    m_tag(_name),
    m_MVmatrix(1)
  {}
  virtual ~BaseObject()=default;
  virtual void reset() = 0;
  virtual void changeID (const size_t _newID);
  void setName(std::string _new);
  std::string getName() const;
  void setParent(BaseObject* _new);
  BaseObject* getParent() const;
  void setChildren(std::vector<BaseObject*> _new);
  void addChild(BaseObject* _new);
  std::vector<BaseObject*> getChildren() const;
  void moveObject (const vec3 _tr);
  void setPosition (const vec3 _tr);
  void rotateObject (const vec3 _rot);
  void setRotation (const vec3 _rot);
  void scaleObject (const vec3 _sc);
  void setScale (const vec3 _sc);
  vec3 getPosition () const;
  vec3 getRotation () const;
  vec3 getScale () const;
  virtual size_t getID () const = 0;
  void setActive(bool _new);
  bool isActive();
  void updateMatrix();
  mat4 getMVmatrix() const;
protected :
  vec3 m_pos = glm::vec3(0,0,0);
  vec3 m_rot = glm::vec3(0,0,0);
  vec3 m_scale = glm::vec3(1,1,1);
  size_t m_id;
  BaseObject* m_parent = nullptr;
  std::vector<BaseObject*> m_children;
  std::string m_tag = "SceneObject";
  bool m_isActive = true;
  mat4 m_MVmatrix {1};
};

#endif
