#include "SceneObject.h"

void SceneObject::reset()
{
  m_pos.null();
  m_rot.null();
  m_scale.set(1,1,1);
}
