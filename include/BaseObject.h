#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include <vec3.hpp>
#include <memory>

using namespace glm;

class BaseObject
{
public :
  virtual void reset() = 0;
  virtual void changeID (const unsigned _newID) = 0;
  void moveObject (const vec3 _tr);
  void setPosition (const vec3 _tr);
  void rotateObject (const vec3 _rot);
  void setRotation (const vec3 _rot);
  void scaleObject (const vec3 _sc);
  void setScale (const vec3 _sc);
  vec3 getPosition () const;
  vec3 getRotation () const;
  vec3 getScale () const;
  virtual unsigned getID () const = 0;
  void setActive(bool _new) { m_isActive = _new; }
  bool isActive() { return m_isActive; }
  virtual ~BaseObject();
protected :
  vec3 m_pos;
  vec3 m_rot;
  vec3 m_scale;
  unsigned m_id;
  BaseObject* m_parent;
  std::string m_tag;
  bool m_isActive = true;
};

#endif
