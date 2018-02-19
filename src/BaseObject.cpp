#include "BaseObject.h"

void BaseObject::changeID(const unsigned _newID)
{
  m_id = _newID;
}

void BaseObject::moveObject (const vec3 _tr)
{
  m_pos += _tr;
}

void BaseObject::setPosition(const vec3 _tr)
{
  m_pos=_tr;
}

void BaseObject::rotateObject (const vec3 _rot)
{
  m_rot += _rot;
}

void BaseObject::setRotation (const vec3 _rot)
{
  m_rot=_rot;
}

void BaseObject::scaleObject (const vec3 _sc)
{
  m_scale += _sc;
}

void BaseObject::setScale (const vec3 _sc)
{
  m_scale=_sc;
}

vec3 BaseObject::getPosition () const
{
  return m_pos;
}

vec3 BaseObject::getRotation () const
{
  return m_rot;
}

vec3 BaseObject::getScale () const
{
  return m_scale;
}

unsigned BaseObject::getID () const
{
  return m_id;
}
