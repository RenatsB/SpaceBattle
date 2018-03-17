#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include "SceneObject.h"
#include "DataContainer.h"
//-------------------------------------------------------------------------------------------------------
/// @author Renats Bikmajevs
/// Modified from : --
/// @note A container for Scene Objects that also manages them and can save or load the current scene setup
//-------------------------------------------------------------------------------------------------------
class ObjectManager
{
public:
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default constructor
  //-----------------------------------------------------------------------------------------------------
  ObjectManager()=default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default destructor.
  //-----------------------------------------------------------------------------------------------------
  ~ObjectManager()=default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief A full object Instantiation method using all constructor parameters
  /// @param [in]_name Name of the instantiated object
  /// @param [in]_pos Position of the instantiated object
  /// @param [in]_rot Rotation of the instantiated object
  /// @param [in]_sc Scale of the instantiated object
  /// @param [in]_geo A pair of linked geometry ID and Name
  /// @param [in]_mat A pair of linked material ID and Name
  //-----------------------------------------------------------------------------------------------------
  void createSceneObject(std::string _name="SceneObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1), std::pair<size_t, std::string> _geo={1, "Mesh1"}, std::pair<size_t, std::string> _mat={1, "Material1"});
  //-----------------------------------------------------------------------------------------------------
  /// @brief A simplified object Instantiation method
  /// @param [in]_name Name of the instantiated object
  /// @param [in]_geo A pair of linked geometry ID and Name
  /// @param [in]_mat A pair of linked material ID and Name
  //-----------------------------------------------------------------------------------------------------
  void createSceneObject(std::string _name="SceneObject", std::pair<size_t, std::string> _geo={1, "Mesh1"}, std::pair<size_t, std::string> _mat={1, "Material1"});
  //-----------------------------------------------------------------------------------------------------
  /// @brief Adds a scene object with the specified ID to the selection vector
  //-----------------------------------------------------------------------------------------------------
  void selectObject(const size_t _id);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Adds a scene object with the specified Name to the selection vector, if none specified selects all
  //-----------------------------------------------------------------------------------------------------
  void selectObject(const std::string &_name);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Adds scene objects with the specified IDs to the selection vector
  //-----------------------------------------------------------------------------------------------------
  void selectObject(const std::vector<size_t> &_ids);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Adds scene objects with the specified Names to the selection vector
  //-----------------------------------------------------------------------------------------------------
  void selectObject(const std::vector<std::string> &_names);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Removes a scene object with the specified ID from the selection vector
  //-----------------------------------------------------------------------------------------------------
  void deselectObject(const size_t _id);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Removes a scene object with the specified name from the selection vector, if none specified deselects all
  //-----------------------------------------------------------------------------------------------------
  void deselectObject(const std::string &_name);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Removes scene objects with the specified IDs from the selection vector
  //-----------------------------------------------------------------------------------------------------
  void deselectObject(const std::vector<size_t> &_ids);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Removes scene objects with the specified Names from the selection vector
  //-----------------------------------------------------------------------------------------------------
  void deselectObject(const std::vector<std::string> &_names);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Checks if scene object with specified ID is selected
  //-----------------------------------------------------------------------------------------------------
  bool isSelected(const size_t _id) const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Checks if scene object with specified Name is selected
  //-----------------------------------------------------------------------------------------------------
  bool isSelected(const std::string _name) const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Moves all currently selected objects based on input axis and amount
  //-----------------------------------------------------------------------------------------------------
  void move(unsigned short _axis, float _val);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Scales all currently selected objects based on input axis and amount
  //-----------------------------------------------------------------------------------------------------
  void scale(unsigned short _axis, float _val);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Rotates all currently selected objects based on input axis and amount
  //-----------------------------------------------------------------------------------------------------
  void rotate(unsigned short _axis, float _val);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Converts axis-value representaion into a proper vector
  //-----------------------------------------------------------------------------------------------------
  vec3 constructTranslateVector(unsigned short _axis, float _val) const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Changes geometry values of all currently selected objects based on input
  //-----------------------------------------------------------------------------------------------------
  void changeGeo(std::pair<size_t, std::string> _geo);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Changes material values of all currently selected objects based on input
  //-----------------------------------------------------------------------------------------------------
  void changeMat(std::pair<size_t, std::string> _mat);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns a pointer to the scene object at the specified position in the stored vector, for easy lookup when ID and Name are irrelevant
  /// @brief If object is not found returns nullptr
  //-----------------------------------------------------------------------------------------------------
  SceneObject* objectAt(size_t _pos) const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Checks if a scene object with specified ID exists
  //-----------------------------------------------------------------------------------------------------
  bool findObject(const size_t _id) const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Checks if a scene object with specified Name exists
  //-----------------------------------------------------------------------------------------------------
  bool findObject(const std::string &_name) const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns a pointer to the scene object with the specified ID
  /// @brief If object is not found returns nullptr
  //-----------------------------------------------------------------------------------------------------
  SceneObject* getObject(size_t _id) const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns a pointer to the scene object with the specified Name
  /// @brief If object is not found returns nullptr
  //-----------------------------------------------------------------------------------------------------
  SceneObject* getObject(std::string _name) const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns the ID of the scene object with the specified Name
  /// @brief If object is not found returns 0
  //-----------------------------------------------------------------------------------------------------
  size_t getObjectID(const std::string &_name) const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns the current size of the scene object vector
  //-----------------------------------------------------------------------------------------------------
  size_t getObjectCount() const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Reads a json file with the specified name and loads all data into the scene
  /// @brief In the beginning autosaves using AutosavedScene.json name and resets the scene
  /// @brief Warning: this excludes mesh and material data
  //-----------------------------------------------------------------------------------------------------
  void loadRawSceneData(const std::string &_name);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Writes all current scene data to json using the specified file name
  /// @brief Warning: this excludes mesh and material data
  //-----------------------------------------------------------------------------------------------------
  void writeRawSceneData(const std::string &_name) const;
private:
  //-----------------------------------------------------------------------------------------------------
  /// @brief Checks if there are scene objects that share the same ID and replaces them with new IDs if found
  //-----------------------------------------------------------------------------------------------------
  void checkObjectIDs();
  //-----------------------------------------------------------------------------------------------------
  /// @brief Scans the current objects and returns an ID that is not in use
  //-----------------------------------------------------------------------------------------------------
  size_t getFreeID() const;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Returns a vector of all currently used IDs of scene objects
  //-----------------------------------------------------------------------------------------------------
  std::vector<size_t> getCurrentIDs()const;
private:
  //-----------------------------------------------------------------------------------------------------
  /// @brief A vector of pointers to all currently stored scene objects
  //-----------------------------------------------------------------------------------------------------
  std::vector<std::unique_ptr<SceneObject>> m_sceneObjects;
  //-----------------------------------------------------------------------------------------------------
  /// @brief A vector of selected object IDs
  //-----------------------------------------------------------------------------------------------------
  std::vector<size_t> m_selected;
};
#endif //OBJECTMANAGER_H_
