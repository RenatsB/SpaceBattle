#include "BaseObject.h"

void BaseObject::changeID(const unsigned _newID)
{
  m_id = _newID;
}

void BaseObject::moveObject (const Vec3 _tr)
{
  m_pos += _tr;
}

void BaseObject::setPosition(const Vec3 _tr)
{
  m_pos.set(_tr);
}

void BaseObject::rotateObject (const Vec3 _rot)
{
  m_rot += _rot;
}

void BaseObject::setRotation (const Vec3 _rot)
{
  m_rot.set(_rot);
}

void BaseObject::scaleObject (const Vec3 _sc)
{
  m_scale += _sc;
}

void BaseObject::setScale (const Vec3 _sc)
{
  m_scale.set(_sc);
}

Vec3 BaseObject::getPosition () const
{
  return m_pos;
}

Vec3 BaseObject::getRotation () const
{
  return m_rot;
}

Vec3 BaseObject::getScale () const
{
  return m_scale;
}

unsigned BaseObject::getID () const
{
  return m_id;
}
