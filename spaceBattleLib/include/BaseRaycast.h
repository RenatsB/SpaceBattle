#ifndef DATACONTAINER_H_
#define DATACONTAINER_H_
#include <glm/vec3.hpp>
#include <glm/common.hpp>
class GameObject; //forward declaration
using namespace glm;
class BaseRaycast
{
public:
  BaseRaycast()
  {
    m_origin = vec3(0);
    m_direction = vec3(0,0,1);
  }
  virtual GameObject* Cast(vec3 _o, vec3 _d, float _l)=0;
protected:
  float m_distance = 1.f;
  vec3 m_origin;
  vec3 m_direction;
};
#endif //DATACONTAINER_H_
