#ifndef LIGHT_H
#define LIGHT_H
#include "BaseAdvObject.h"
enum class LightType {POINT, SPOT, DIRECTIONAL};
using namespace glm;
class Light : BaseAdvObject
{
public:
    Light()=default;
    Light(LightType _t=LightType::POINT):
    m_LType(_t)
    {}
    void setLType(LightType _t=LightType::POINT);
    LightType getLType() const;
    void setIntensity(float _i);
    float getIntensity() const;
    void setFaloff(float _i);
    float getFaloff() const;
private:
    LightType m_LType = LightType::POINT;
    float m_intensity;
    float m_faloff;
    vec3 m_colour = vec3(1.f,1.f,1.f);
}

#endif // LIGHT_H
