#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include <ngl/Vec3.h>
#include <memory>

using namespace ngl;
class BaseObject
{
public :
  virtual void reset() = 0;
  virtual std::unique_ptr<BaseObject> clone() = 0;
  void changeID (const unsigned _newID);
  void moveObject (const Vec3 _tr);
  void setPosition (const Vec3 _tr);
  void rotateObject (const Vec3 _rot);
  void setRotation (const Vec3 _rot);
  void scaleObject (const Vec3 _sc);
  void setScale (const Vec3 _sc);
  Vec3 getPosition () const;
  Vec3 getRotation () const;
  Vec3 getScale () const;
  unsigned getID () const;
  virtual ~BaseObject();
protected :
  Vec3 m_pos;
  Vec3 m_rot;
  Vec3 m_scale;
  unsigned m_id;
};

#endif
