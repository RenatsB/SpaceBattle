#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "Scene.h"
#include "MaterialPBR.h"
#include "MaterialPhong.h"
#include "ShaderLib.h"
#include "DataContainer.h"
#include <vector>
#include "SceneObject.h"
#include <QTableWidget>

class MainScene : public Scene
{
  Q_OBJECT
public:
  //-----------------------------------------------------------------------------------------------------
  /// @brief Constructor for DemoScene.
  /// @param [io] io_camera the camera used to view the scene.
  /// @param [io] io_shaderLib the shader library to store and retrieve our shaders.
  /// @param [io] io_parent the parent window to create the GL context in.
  //-----------------------------------------------------------------------------------------------------
  MainScene(
     const std::shared_ptr<Camera> &io_camera,
     const std::shared_ptr<ShaderLib> &io_shaderLib,
     QWidget *_parent
     ) :
   Scene(io_camera, _parent),
   m_shaderLib(io_shaderLib)
  {}
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default copy constructor.
  //-----------------------------------------------------------------------------------------------------
  MainScene(const MainScene&) = default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default copy assignment operator.
  //-----------------------------------------------------------------------------------------------------
  MainScene& operator=(const MainScene&) = default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default move constructor.
  //-----------------------------------------------------------------------------------------------------
  MainScene(MainScene&&) = default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default move assignment operator.
  //-----------------------------------------------------------------------------------------------------
  MainScene& operator=(MainScene&&) = default;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Default destructor.
  //-----------------------------------------------------------------------------------------------------
  ~MainScene() override = default;
  virtual void init() override;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Used to intialise the models, vbo and vao.
  //-----------------------------------------------------------------------------------------------------
  void initGeo();
  //-----------------------------------------------------------------------------------------------------
  /// @brief Used to create our shader programs, or use exisiting ones if they have been loaded.
  //-----------------------------------------------------------------------------------------------------
  void initMaterials();
  //-----------------------------------------------------------------------------------------------------
  /// @brief Receives and acts on a key event.
  /// @param [io] io_event is the key event that was received.
  //-----------------------------------------------------------------------------------------------------
  //virtual void keyPress(QKeyEvent* io_event) override;
  void selectObject(const size_t _id);
  void deselectObject(const size_t _id);

public slots:
  void select();
  void deselect();
  void move(unsigned short _axis, float _val);
  void scale(unsigned short _axis, float _val);
  void rotate(unsigned short _axis, float _val);
  void changeMat(size_t _new);
  void loadMat(std::string _path);
  void changeGeo(size_t _new);
  void receiveGeoPath(QString _current);
  void loadGeo();
  void receiveTableInfo(QTableWidgetItem* _ref);

private:
  void createSceneObject(std::string _name="SceneObject", vec3 _pos=vec3(0,0,0), vec3 _rot=vec3(0,0,0), vec3 _sc=vec3(1,1,1), size_t _geo=1, size_t _mat=0);
  void loadMesh(size_t _id);
  void loadMesh(size_t _meshID, size_t _shaderID);
  void loadMesh(Mesh _raw, size_t _shaderID);
  void loadAllMeshData();
  void updateBuffer(const size_t _geoID, const size_t _matID);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Used to write our mesh data into the vbo.
  //-----------------------------------------------------------------------------------------------------
  void writeMeshAttributes(size_t _id);
  //-----------------------------------------------------------------------------------------------------
  /// @brief Used to pass attribute pointers to the current shader program.
  //-----------------------------------------------------------------------------------------------------
  void setAttributeBuffers();
  void useMaterial(const size_t _id);
  std::array<int, 4> countAllSceneGeo() const;
  virtual void renderScene() override;
  bool isSelected(const size_t _id) const;
  vec3 constructTranslateVector(unsigned short _axis, float _val) const;

private:
  //-----------------------------------------------------------------------------------------------------
  /// @brief Wraps up our OpenGL buffers and VAO.
  //-----------------------------------------------------------------------------------------------------
  MeshVBO m_meshVBO;
  //-----------------------------------------------------------------------------------------------------
  /// @brief Vertex array object, default constructed with a pointer to this OpenGL widget,
  /// a dynamic_cast is used due to Scene's multiple inheritence.
  //-----------------------------------------------------------------------------------------------------
  std::unique_ptr<QOpenGLVertexArrayObject> m_vao {
    new QOpenGLVertexArrayObject(dynamic_cast<QObject*>(this))
  };
  std::shared_ptr<ShaderLib> m_shaderLib;
  DataContainer m_drawData;
  Mesh m_grid;

  std::vector<std::unique_ptr<SceneObject>> m_sceneObjects;
  std::vector<size_t> m_selected;

  std::string m_geoPathCmd;

};

#endif // MAINSCENE_H
