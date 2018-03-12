#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "SceneObject.h"
#include "DataContainer.h"

class ObjectManager
{
public:
  static ObjectManager* instance();
  void selectObject(const size_t _id);
  void deselectObject(const size_t _id);
  void move(unsigned short _axis, float _val);
  void scale(unsigned short _axis, float _val);
  void rotate(unsigned short _axis, float _val);
private:
  bool isSelected(const size_t _id) const;
  vec3 constructTranslateVector(unsigned short _axis, float _val) const;
private:
  static ObjectManager* s_instance;
  std::vector<std::unique_ptr<SceneObject>> m_sceneObjects;
  std::vector<size_t> m_selected;
};

#endif //OBJECTMANAGER_H
