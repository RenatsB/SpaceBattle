#include "SceneObject.h"

void SceneObject::reset()
{
  m_pos=vec3(0,0,0);
  m_rot=vec3(0,0,0);
  m_scale=vec3(1,1,1);
}

void SceneObject::setGeometry(unsigned _new)
{
  m_geometry = _new;
}
