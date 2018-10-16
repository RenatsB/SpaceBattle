#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "DataContainer.h"
#include "BaseAdvObject.h"
//-------------------------------------------------------------------------------------------------------
/// @author Renats Bikmajevs
/// @note Inherited from BaseAdvObject, this class is the main scene object representation
//-------------------------------------------------------------------------------------------------------
using namespace glm;
class GameObject : public BaseAdvObject
{
public :
    //-----------------------------------------------------------------------------------------------------
    /// @brief Default constructor.
    //-----------------------------------------------------------------------------------------------------
    GameObject()=default;
    //-----------------------------------------------------------------------------------------------------
    /// @brief Custom constructor that sets most member values.
    /// @param [in]_name The name of the created object to assign
    /// @param [in]_pos The position of the created object to assign
    /// @param [in]_rot The rotation of the created object to assign
    /// @param [in]_sc The scale of the created object to assign
    /// @param [in]_geo Geometry Name
    /// @param [in]_mat Material Name
    //-----------------------------------------------------------------------------------------------------
    GameObject(std::string _name = "GameObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1),
              std::string _geo = "Default", std::string _mat="Default"):
    m_name(_name),
    m_pos(_pos),
    m_rot(_rot),
    m_scale(_sc),
    m_geometry(_geo),
    m_material(_mat)
    {}
    //-----------------------------------------------------------------------------------------------------
    /// @brief A simplified custom constructor.
    /// @param [in]_name The name of the created object to assign
    /// @param [in]_geo A pair of geometry ID and Name
    /// @param [in]_mat A pair of material ID and Name
    //-----------------------------------------------------------------------------------------------------
    GameObject(std::string _name = "GameObject", std::string _geo = "Default", std::string _mat= "Default"):
    m_name(_name),
    m_geometry(_geo),
    m_material(_mat)
    {}
    //-----------------------------------------------------------------------------------------------------
    /// @brief Default virtual destructor.
    //-----------------------------------------------------------------------------------------------------
    ~GameObject() override = default;
    //-----------------------------------------------------------------------------------------------------
    /// @brief Sets geometry ID and Name of this object to the input pair values
    //-----------------------------------------------------------------------------------------------------
    void setGeo(std::string &_new);
    //-----------------------------------------------------------------------------------------------------
    /// @brief Sets material ID and Name of this object to the input pair values
    //-----------------------------------------------------------------------------------------------------
    void setMat(std::string &_new);
    //-----------------------------------------------------------------------------------------------------
    /// @brief Returns the currently stored geometry Name of this object
    //-----------------------------------------------------------------------------------------------------
    std::string getGeoName() const;
    //-----------------------------------------------------------------------------------------------------
    /// @brief Returns the currently stored material Name of this object
    //-----------------------------------------------------------------------------------------------------
    std::string getMatName() const;
    //-----------------------------------------------------------------------------------------------------
    /// @brief A method for destroying the current object
    /// @param [in]_t time delay
    //-----------------------------------------------------------------------------------------------------
    void destroy(float _t=0.f);
private :
    //-----------------------------------------------------------------------------------------------------
    /// @brief A linked Mesh Name
    //-----------------------------------------------------------------------------------------------------
    std::string m_geometry = "Default";
    //-----------------------------------------------------------------------------------------------------
    /// @brief A linked Material Name
    //-----------------------------------------------------------------------------------------------------
    std::string m_material = "Default";
};
#endif //GAMEOBJECT_H_
