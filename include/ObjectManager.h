#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "SceneObject.h"
#include "DataContainer.h"

class ObjectManager
{
public:
  //static ObjectManager* instance();
  ObjectManager()=default;
  ~ObjectManager()=default;
  void createSceneObject(std::string _name="SceneObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1), size_t _geo=1, size_t _mat=0);
  void selectObject(const size_t _id);
  void selectObject(const std::string &_name);
  void deselectObject(const size_t _id);
  void deselectObject(const std::string &_name);
  void move(unsigned short _axis, float _val);
  void scale(unsigned short _axis, float _val);
  void rotate(unsigned short _axis, float _val);
  bool findObject(const size_t _id) const;
  bool findObject(const std::string &_name) const;
  size_t getObjectID(const std::string &_name) const;
private:
  bool isSelected(const size_t _id) const;
  vec3 constructTranslateVector(unsigned short _axis, float _val) const;
private:
  //static ObjectManager* s_instance;
  std::vector<std::unique_ptr<SceneObject>> m_sceneObjects;
  std::vector<size_t> m_selected;
};

#endif //OBJECTMANAGER_H
