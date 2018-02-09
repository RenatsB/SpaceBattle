#ifndef SCENE_H_
#define SCENE_H_

#include "SceneObject.h"
#include <ngl/Camera.h>
#include <ngl/Colour.h>
#include <ngl/Light.h>
#include <ngl/Transformation.h>
#include <ngl/Text.h>
#include <memory>
#include <QOpenGLWidget>
#include <QResizeEvent>
#include <QEvent>

class Scene : QOpenGLWidget
{
  Q_OBJECT

public:
  Scene(Camera* io_camera, QWidget *io_parent);
  Scene(const Scene&) = default;
  Scene& operator=(const Scene&) = default;
  Scene(Scene&&) = default;
  Scene& operator=(Scene&&) = default;
  virtual ~Scene() = default;

  void addObject(std::unique_ptr<SceneObject> _in);
  void instantiate(Vec3 _pos, Vec3 _rot=Vec3(0,0,0), Vec3 _sc=Vec3(1,1,1));
  void cloneObject(const unsigned _id);
  void removeObject(const unsigned _id);
  void changeRelationship(const unsigned _ref, const unsigned _parent);
private:
  std::vector<std::unique_ptr<SceneObject>> m_objects;
  ngl::Mat4 m_mouseGlobalTX;
  std::unique_ptr<ngl::Camera> m_cam;
  ngl::Transformation m_transform;
  ngl::Vec3 m_targetPos;
  std::unique_ptr<ngl::Light> m_light;
  int m_lightTimer;
  bool m_animate;
  ngl::Real m_lightAngle;
  void loadMatricesToShader();

  void keyPress(QKeyEvent* _event);
  void mouseMove(QMouseEvent * _event);
  void mouseClick(QMouseEvent * _event);
protected :
  void initializeGL();
  void resizeGL(int _w , int _h);
  void paintGL();
  virtual void renderScene();
  std::array<glm::mat4, 3> m_matrices;
};

#endif
