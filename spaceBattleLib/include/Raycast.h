#include <glm/vec3.hpp>
using namespace glm;
class GameObject; //forward declaration
class Raycast
{
public:
  Raycast()
  {
    m_origin = vec3(0);
    m_direction = vec3(0,0,1);
  }
  void Cast(GameObject* _ref, vec3 _d, float _l);
  void Cast(GameObject* _ref, vec3 _o, vec3 _d, float _l);
  GameObject* Cast(vec3 _o, vec3 _d, float _l);
private:
  GameObject* CastInternal(GameObject* _ref, vec3 _o, vec3 _d, float _l);
  float m_distance = 1.f;
  vec3 m_origin;
  vec3 m_direction;

};
