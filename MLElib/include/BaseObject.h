#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_
#include <vec3.hpp>
#include <gtc/matrix_transform.hpp>
#include <ext.hpp>
#include <glm.hpp>
#include <memory>
#include <vector>
//-------------------------------------------------------------------------------------------------------
/// @author Renats Bikmajevs
/// Modified from : --
/// @note This is a base pure virtual class for scene objects. Mainly used to hide all transformation methods from the child class.
//-------------------------------------------------------------------------------------------------------
using namespace glm;
class BaseObject
{
public :
  //-----------------------------------------------------------------------------------------------------
  /// @brief Custom constructor that sets most member values.
  /// @param [in]_name The name of the created object to assign
  /// @param [in]_pos The position of the created object to assign
  /// @param [in]_rot The rotation of the created object to assign
  /// @param [in]_sc The scale of the created object to assign
  /// @note also resets the stored transformation matrix to identity
  //-----------------------------------------------------------------------------------------------------
  BaseObject(std::string _name = "SceneObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1)):
    m_pos(_pos),
    m_rot(_rot),
    m_scale(_sc),
    m_name(_name),
    m_MVmatrix(1)
  {}
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default virtual destructor.
  //-----------------------------------------------------------------------------------------------------
  virtual ~BaseObject()=default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Resets the object to defaults
  //-----------------------------------------------------------------------------------------------------
  virtual void reset() = 0;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Changes the ID of the current object
  /// @param [in]_newID New ID
  //-----------------------------------------------------------------------------------------------------
  virtual void changeID (const size_t _newID);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Changes the name of the current object
  /// @param [in]_new New name
  //-----------------------------------------------------------------------------------------------------
  void setName(const std::string _new);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns the name of the current object
  //-----------------------------------------------------------------------------------------------------
  std::string getName() const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Sets the parent of the current object
  /// @param [io]_new New parent
  //-----------------------------------------------------------------------------------------------------
  void setParent(BaseObject* _new);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns the parent of the current object
  //-----------------------------------------------------------------------------------------------------
  BaseObject* getParent() const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Changes the children of the current object
  /// @param [io]_new New children
  //-----------------------------------------------------------------------------------------------------
  void setChildren(std::vector<BaseObject*> _new);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Adds a child to the current object
  /// @param [io]_new New child
  //-----------------------------------------------------------------------------------------------------
  void addChild(BaseObject* _new);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns all children of the current object
  //-----------------------------------------------------------------------------------------------------
  std::vector<BaseObject*> getChildren() const;
  void moveObject (const vec3 _tr);
  void setPosition (const vec3 _tr);
  void rotateObject (const vec3 _rot);
  void setRotation (const vec3 _rot);
  void scaleObject (const vec3 _sc);
  void setScale (const vec3 _sc);
  vec3 getPosition () const;
  vec3 getRotation () const;
  vec3 getScale () const;
  virtual size_t getID () const = 0;
  void setActive(bool _new);
  bool isActive();
  void updateMatrix();
  mat4 getMVmatrix() const;
protected :
  vec3 m_pos = glm::vec3(0,0,0);
  vec3 m_rot = glm::vec3(0,0,0);
  vec3 m_scale = glm::vec3(1,1,1);
  size_t m_id=0;
  BaseObject* m_parent = nullptr;
  std::vector<BaseObject*> m_children;
  std::string m_name = "SceneObject";
  bool m_isActive = true;
  mat4 m_MVmatrix {1};
};

#endif
