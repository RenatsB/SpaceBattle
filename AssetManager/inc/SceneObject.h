#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "BaseObject.h"

using namespace ngl;
class SceneObject : BaseObject
{
public :
  virtual void reset() override;
  virtual std::unique_ptr<BaseObject> clone() override;
  std::unique_ptr<BaseObject> instantiate();
  ~SceneObject();
private :
};

#endif
