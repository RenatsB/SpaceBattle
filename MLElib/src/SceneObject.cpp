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

void SceneObject::setGeo(std::pair<size_t, std::string> &_new)
{
  m_geometry = _new;
}

void SceneObject::setMat(std::pair<size_t, std::string> &_new)
{
  m_material = _new;
}

size_t SceneObject::getGeoID() const
{
  return m_geometry.first;
}

size_t SceneObject::getMatID() const
{
  return m_material.first;
}

std::string SceneObject::getGeoName() const
{
  return m_geometry.second;
}

std::string SceneObject::getMatName() const
{
  return m_material.second;
}
