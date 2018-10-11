#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "DataContainer.h"
#include "BaseObject.h"
//-------------------------------------------------------------------------------------------------------
/// @author Renats Bikmajevs
/// Modified from : --
/// @note Inherited from BaseObject, this class is the main scene object representation
//-------------------------------------------------------------------------------------------------------
using namespace glm;
class GameObject : public BaseObject
{
public :
  //-----------------------------------------------------------------------------------------------------
  /// @brief Custom constructor that sets most member values.
  /// @param [in]_name The name of the created object to assign
  /// @param [in]_pos The position of the created object to assign
  /// @param [in]_rot The rotation of the created object to assign
  /// @param [in]_sc The scale of the created object to assign
  /// @param [in]_geo A pair of geometry ID and Name
  /// @param [in]_mat A pair of material ID and Name
  //-----------------------------------------------------------------------------------------------------
  GameObject(std::string _name = "GameObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1),
              std::pair<size_t, std::string>_geo = {1, "Mesh1"}, std::pair<size_t, std::string>_mat={0, "Material1"}):
    BaseObject(_name, _pos, _rot, _sc),
    m_geometry(_geo.first, _geo.second),
    m_material(_mat.first, _mat.second)
  {}
  //-----------------------------------------------------------------------------------------------------
  /// @brief A simplified custom constructor.
  /// @param [in]_name The name of the created object to assign
  /// @param [in]_geo A pair of geometry ID and Name
  /// @param [in]_mat A pair of material ID and Name
  //-----------------------------------------------------------------------------------------------------
  GameObject(std::string _name = "GameObject", std::pair<size_t, std::string>_geo = {1, "Mesh1"}, std::pair<size_t, std::string>_mat={0, "Material1"}):
    BaseObject(_name),
    m_geometry(_geo.first, _geo.second),
    m_material(_mat.first, _mat.second)
  {}
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default virtual destructor.
  //-----------------------------------------------------------------------------------------------------
  ~GameObject() override = default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Resets all members of this object to their default values
  //-----------------------------------------------------------------------------------------------------
  virtual void reset() override;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Sets the ID of this object to the input value
  //-----------------------------------------------------------------------------------------------------
  virtual void changeID(const size_t _newID) override;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns the currently stored ID of this object
  //-----------------------------------------------------------------------------------------------------
  virtual size_t getID() const override;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Sets geometry ID and Name of this object to the input pair values
  //-----------------------------------------------------------------------------------------------------
  void setGeo(std::pair<size_t, std::string> &_new);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Sets material ID and Name of this object to the input pair values
  //-----------------------------------------------------------------------------------------------------
  void setMat(std::pair<size_t, std::string> &_new);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns the currently stored geometry ID of this object
  //-----------------------------------------------------------------------------------------------------
  size_t getGeoID() const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns the currently stored geometry Name of this object
  //-----------------------------------------------------------------------------------------------------
  std::string getGeoName() const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns the currently stored material ID of this object
  //-----------------------------------------------------------------------------------------------------
  size_t getMatID() const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns the currently stored material Name of this object
  //-----------------------------------------------------------------------------------------------------
  std::string getMatName() const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief A method for destroying the current object
  //-----------------------------------------------------------------------------------------------------
  void destroy();
private :
  //-----------------------------------------------------------------------------------------------------
  /// @brief A pair of linked Mesh ID and Name
  //-----------------------------------------------------------------------------------------------------
  std::pair<size_t, std::string> m_geometry = {1, "Mesh1"};
  //-----------------------------------------------------------------------------------------------------
  /// @brief A pair of linked Material ID and Name
  //-----------------------------------------------------------------------------------------------------
  std::pair<size_t, std::string> m_material = {1, "Material1"};
};
#endif //GAMEOBJECT_H_
