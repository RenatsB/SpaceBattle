#include <QApplication>
#include "MainWindow.h"
#include <TrackballCamera.h>
#include <ShaderLib.h>
#include <random>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ext.hpp>
#include "MainScene.h"
#include "DataContainer.h"
#include "ObjectManager.h"

int main(int argc, char *argv[])
{
  // create an OpenGL format specifier
  QSurfaceFormat format;
  // set the number of samples for multisampling
  // will need to enable glEnable(GL_MULTISAMPLE); once we have a context
  format.setSamples(4);
#if defined(DARWIN)
  // at present mac osx Mountain Lion only supports GL3.2
  // the new mavericks will have GL 4.x so can change
  format.setMajorVersion(4);
  format.setMinorVersion(2);
#else
  // with luck we have the latest GL version so set to this
  format.setMajorVersion(4);
  format.setMinorVersion(3);
#endif
  // now we are going to set to CoreProfile OpenGL so we can't use and old Immediate mode GL
  format.setProfile(QSurfaceFormat::CoreProfile);
  // now set the depth buffer to 24 bits
  format.setDepthBufferSize(24);

  // this will set the format for all widgets
  QSurfaceFormat::setDefaultFormat(format);
  // make an instance of the QApplication
  QApplication app(argc, argv);
  // Create a new MainWindow
  MainWindow window;
  // Create a camera
  std::shared_ptr<Camera> cam(new TrackballCamera);
  // Create a shader library
  std::shared_ptr<ShaderLib> lib(new ShaderLib);
  std::shared_ptr<DataContainer> drawData(new DataContainer);
  std::shared_ptr<ObjectManager> objManager(new ObjectManager);
  // Create a scene to place inside the window
  //std::shared_ptr<Scene> scene(new DemoScene(cam, lib, &window));
  std::shared_ptr<Scene> scene(new MainScene(cam, lib, drawData, objManager, &window));
  // Initialise the window using our scene
  window.init(scene);
  // show it
  window.show();
  // hand control over to Qt framework
  return app.exec();
}
