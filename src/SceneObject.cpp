#include "SceneObject.h"

void SceneObject::reset()
{
  m_pos=vec3(0,0,0);
  m_rot=vec3(0,0,0);
  m_scale=vec3(1,1,1);
}

void SceneObject::changeID(const size_t _newID)
{
  m_id = _newID;
}

size_t SceneObject::getID () const
{
  return m_id;
}

void SceneObject::setGeo(size_t _new)
{
  m_geometry->setGeoID(_new);
}

void SceneObject::setGeo(std::string _name)
{
  m_geometry->setGeoName(_name);
}

void SceneObject::setMat(size_t _new)
{
  m_material->setMatID(_new);
}

void SceneObject::setMat(std::string _name)
{
  m_material->setMatName(_name);
}

size_t SceneObject::getGeo() const
{
  return m_geometry->getGeoID();
}

size_t SceneObject::matFind() const
{
  return m_material->getMatID();
}
