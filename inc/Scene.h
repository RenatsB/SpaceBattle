#ifndef SCENE_H_
#define SCENE_H_

#include "SceneObject.h"

class Scene
{
public:
  void addObject(std::unique_ptr<SceneObject> _in);
  void instantiate(Vec3 _pos, Vec3 _rot=Vec3(0,0,0), Vec3 _sc=Vec3(1,1,1));
  void cloneObject(const unsigned _id);
  void removeObject(const unsigned _id);
  void changeRelationship(const unsigned _ref, const unsigned _parent);
private:
  std::vector<std::unique_ptr<SceneObject>> m_objects;
};

#endif
