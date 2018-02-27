#include "SceneObject.h"

void SceneObject::reset()
{
  m_pos=vec3(0,0,0);
  m_rot=vec3(0,0,0);
  m_scale=vec3(1,1,1);
}

void SceneObject::changeID(const unsigned _newID)
{
  m_id = _newID;
}

unsigned SceneObject::getID () const
{
  return m_id;
}

void SceneObject::setGeometry(unsigned _new)
{
  m_geometry = _new;
}

unsigned SceneObject::getGeo() const
{
  return m_geometry;
}
