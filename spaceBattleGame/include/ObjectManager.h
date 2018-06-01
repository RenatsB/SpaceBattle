#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "SceneObject.h"
#include "DataContainer.h"

class ObjectManager
{
public:
  ObjectManager()=default;
  ~ObjectManager()=default;
  void createSceneObject(std::string _name="SceneObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1), std::pair<size_t, std::string> _geo={1, "Mesh1"}, std::pair<size_t, std::string> _mat={1, "Material1"});
  void createSceneObject(std::string _name="SceneObject", std::pair<size_t, std::string> _geo={1, "Mesh1"}, std::pair<size_t, std::string> _mat={1, "Material1"});
  void selectObject(const size_t _id);
  void selectObject(const std::string &_name);
  void selectObject(const std::vector<size_t> &_ids);
  void selectObject(const std::vector<std::string> &_names);
  void deselectObject(const size_t _id);
  void deselectObject(const std::string &_name);
  void deselectObject(const std::vector<size_t> &_ids);
  void deselectObject(const std::vector<std::string> &_names);
  bool isSelected(const size_t _id) const;
  void move(unsigned short _axis, float _val);
  void scale(unsigned short _axis, float _val);
  void rotate(unsigned short _axis, float _val);
  /*void changeMat(size_t _id);
  void changeMat(std::string _name);
  void changeGeo(size_t _id);
  void changeGeo(std::string _name);*/
  void changeGeo(std::pair<size_t, std::string> _geo);
  void changeMat(std::pair<size_t, std::string> _mat);
  SceneObject* objectAt(size_t _pos) const;
  bool findObject(const size_t _id) const;
  bool findObject(const std::string &_name) const;
  SceneObject* getObject(size_t _id) const;
  SceneObject* getObject(std::string _name) const;
  size_t getObjectID(const std::string &_name) const;
  size_t getObjectCount() const;
  void loadRawSceneData(const std::string &_name);
  void writeRawSceneData(const std::string &_name) const;
private:
  void checkObjectIDs();
  size_t getFreeID() const;
  std::vector<size_t> getCurrentIDs()const;
  vec3 constructTranslateVector(unsigned short _axis, float _val) const;
private:
  std::vector<std::unique_ptr<SceneObject>> m_sceneObjects;
  std::vector<size_t> m_selected;
};

#endif //OBJECTMANAGER_H
