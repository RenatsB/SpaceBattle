#ifndef GUIMODULE_H_
#define GUIMODULE_H_

#include <ngl/Camera.h>
#include <ngl/Colour.h>
#include <ngl/Light.h>
#include <ngl/Transformation.h>
#include <ngl/Text.h>
#include "WinParams.h"
#include <QOpenGLWindow>
#include <memory>

class GUIModule : public QOpenGLWindow
{
public:
  GUIModule();
  ~GUIModule();
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int _w, int _h) override;
  //void draw() const;

private:
  WinParams m_win;
  ngl::Mat4 m_mouseGlobalTX;
  ngl::Camera m_cam;
  ngl::Transformation m_transform;
  ngl::Vec3 m_targetPos;
  std::unique_ptr<ngl::Light> m_light;
  int m_lightTimer;
  bool m_animate;
  ngl::Real m_lightAngle;
  void loadMatricesToShader();
  void keyPressEvent(QKeyEvent *_event) override;
  void mouseMoveEvent (QMouseEvent * _event ) override;
  void mousePressEvent ( QMouseEvent *_event) override;
  void mouseReleaseEvent ( QMouseEvent *_event ) override;
  void wheelEvent( QWheelEvent *_event) override;
  void timerEvent(QTimerEvent *_event) override;
  void updateLight();
  void drawScene(const std::string &_shader);
};

#endif
