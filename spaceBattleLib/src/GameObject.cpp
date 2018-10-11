#include "GameObject.h"
//-----------------------------------------------------------------------------------------------------
void GameObject::reset()
{
  m_pos=vec3(0,0,0);
  m_rot=vec3(0,0,0);
  m_scale=vec3(1,1,1);
  if(m_parent != nullptr)
    setParent(nullptr);
  if(!m_children.empty())
    setChildren(std::vector<BaseObject*>{});
  setActive(true);
  std::pair<size_t, std::string> geo{1, "Mesh1"};
  std::pair<size_t, std::string> mat{1, "Material1"};
  setGeo(geo);
  setMat(mat);
}
//-----------------------------------------------------------------------------------------------------
void GameObject::changeID(const size_t _newID)
{
  m_id = _newID;
}
//-----------------------------------------------------------------------------------------------------
size_t GameObject::getID () const
{
  return m_id;
}
//-----------------------------------------------------------------------------------------------------
void GameObject::setGeo(std::pair<size_t, std::string> &_new)
{
  m_geometry = _new;
}
//-----------------------------------------------------------------------------------------------------
void GameObject::setMat(std::pair<size_t, std::string> &_new)
{
  m_material = _new;
}
//-----------------------------------------------------------------------------------------------------
size_t GameObject::getGeoID() const
{
  return m_geometry.first;
}
//-----------------------------------------------------------------------------------------------------
std::string GameObject::getGeoName() const
{
  return m_geometry.second;
}
//-----------------------------------------------------------------------------------------------------
size_t GameObject::getMatID() const
{
  return m_material.first;
}
//-----------------------------------------------------------------------------------------------------
std::string GameObject::getMatName() const
{
  return m_material.second;
}
//-----------------------------------------------------------------------------------------------------
void GameObject::destroy()
{
  this->~GameObject();
}
//-----------------------------------------------------------------------------------------------------
