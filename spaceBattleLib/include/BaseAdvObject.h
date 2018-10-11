#ifndef BASEADVOBJECT_H
#define BASEADVOBJECT_H
#include "BaseObject.h"
using namespace glm;
class BaseAdvObject
{
    //-----------------------------------------------------------------------------------------------------
    /// @brief Custom constructor that sets most member values.
    /// @param [in]_name The name of the created object to assign
    /// @param [in]_pos The position of the created object to assign
    /// @param [in]_rot The rotation of the created object to assign
    /// @param [in]_sc The scale of the created object to assign
    /// @note also resets the stored transformation matrix to identity
    //-----------------------------------------------------------------------------------------------------
    BaseAdvObject(std::string _name = "GameObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1)):
      m_pos(_pos),
      m_rot(_rot),
      m_scale(_sc),
      m_name(_name),
      m_MVmatrix(1)
    {}
}

#endif // BASEADVOBJECT_H
