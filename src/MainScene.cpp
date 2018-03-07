#include "MainScene.h"
#include "MaterialWireframe.h"
#include "MaterialPBR.h"
#include "MaterialPhong.h"
#include "MaterialFractal.h"
#include "MaterialEnvMap.h"

//-----------------------------------------------------------------------------------------------------
void MainScene::writeMeshAttributes(size_t _id)
{
  const auto& mesh = *m_drawData.instance()->findGeo(_id);

  using namespace MeshAttributes;
  for (const auto buff : {VERTEX, UV, NORMAL})
  {
    m_meshVBO.write(mesh.getAttribData(buff), buff);
  }
  m_meshVBO.setIndices(mesh.getIndicesData());
}
//-----------------------------------------------------------------------------------------------------
void MainScene::setAttributeBuffers()
{
  static constexpr int tupleSize[] = {3,2,3};
  auto prog = m_shaderLib->getCurrentShader();

  using namespace MeshAttributes;
  for (const auto buff : {VERTEX, UV, NORMAL})
  {
    prog->enableAttributeArray(buff);
    prog->setAttributeBuffer(buff, GL_FLOAT, m_meshVBO.offset(buff), tupleSize[buff]);
  }

}
//-----------------------------------------------------------------------------------------------------
void MainScene::initGeo()
{
  m_drawData.instance()->geoReserve(3);
  m_drawData.instance()->findGeo(0)->load("models/Grid.obj");
  m_drawData.instance()->findGeo(1)->load("models/cube.obj");
  m_drawData.instance()->findGeo(2)->load("models/Sphere.obj");
  // Create and bind our Vertex Array Object
  m_vao->create();
  m_vao->bind();
  // Create and bind our Vertex Buffer Object
  m_meshVBO.init();
  updateBuffer(0, 0);
}
//-----------------------------------------------------------------------------------------------------
void MainScene::updateBuffer(const size_t _geoID, const size_t _matID)
{
  makeCurrent();
  auto mesh = m_drawData.instance()->findGeo(_geoID);
  m_meshVBO.reset(
        sizeof(GLushort),
        mesh->getNIndicesData(),
        sizeof(GLfloat),
        mesh->getNVertData(),
        mesh->getNUVData(),
        mesh->getNNormData()
        );
  writeMeshAttributes(_geoID);
  useMaterial(_matID);
  //setAttributeBuffers();
}
//-----------------------------------------------------------------------------------------------------
void MainScene::initMaterials()
{
  m_drawData.instance()->matReserve(5);
  m_drawData.instance()->matPut(new MaterialWireframe(m_camera, m_shaderLib, &m_matrices));
  //m_drawData.instance()->matPut(new MaterialEnvMap(m_camera, m_shaderLib, &m_matrices));
  m_drawData.instance()->matPut(new MaterialPhong(m_camera, m_shaderLib, &m_matrices));
  m_drawData.instance()->matPut(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.5f, 0.0f, 0.0f}, 1.0f, 1.0f, 0.5f, 1.0f));
  m_drawData.instance()->matPut(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.1f, 0.2f, 0.5f}, 0.5f, 1.0f, 0.4f, 0.2f));
  m_drawData.instance()->matPut(new MaterialFractal(m_camera, m_shaderLib, &m_matrices));
  for (size_t i = 0; i < m_drawData.instance()->matSize(); ++i)
  {
    auto mat = m_drawData.instance()->findMat(i);
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setShaderName(name);
    mat->apply();
  }
  m_drawData.instance()->findMat(0)->apply();
}

void MainScene::useMaterial(const size_t _id)
{
  makeCurrent();
  m_drawData.instance()->findMat(_id)->apply();
  setAttributeBuffers();
}

void MainScene::init()
{
  Scene::init();

  initMaterials();
  initGeo();
  for(size_t i = 0; i<12; ++i)
    {
      createSceneObject("TEST"+std::to_string(i));
      m_sceneObjects.at(i).get()->setMat(i%3+1);
      m_sceneObjects.at(i).get()->setScale(glm::vec3(0.2f,0.5f,0.2f));
      m_sceneObjects.at(i).get()->setPosition(glm::vec3(sinf(glm::radians(static_cast<float>(i*30))),0.f,cosf(glm::radians(static_cast<float>(i*30)))));
      m_sceneObjects.at(i).get()->setRotation(vec3(0.f, 30*i, 0.f));
    }
}

//-----------------------------------------------------------------------------------------------------

void MainScene::renderScene()
{
  Scene::renderScene();
  using namespace SceneMatrices;
  mat4 t1=m_matrices[MODEL_VIEW];
  mat4 t2=m_matrices[PROJECTION];
  mat4 t3=m_matrices[NORMAL];

  m_drawData.instance()->findMat(0)->update();
  m_meshVBO.use();
  updateBuffer(0,0);
  glDrawElements(GL_TRIANGLES, m_drawData.instance()->findGeo(0)->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
  for(size_t i=0; i<m_sceneObjects.size(); ++i)
  {
    if(m_sceneObjects.at(i).get()->isActive())
    {
        m_matrices[MODEL_VIEW] = m_sceneObjects.at(i).get()->getMVmatrix();
        m_matrices[PROJECTION] = m_camera->projMatrix() * m_camera->viewMatrix() * m_matrices[MODEL_VIEW];
        m_matrices[NORMAL] = glm::inverse(glm::transpose(m_matrices[MODEL_VIEW]));

        m_drawData.instance()->findMat(m_sceneObjects.at(i).get()->findMat())->update();
        updateBuffer(m_sceneObjects.at(i).get()->getGeo(), m_sceneObjects.at(i).get()->findMat());
        //updateBuffer(m_sceneObjects.at(i).get()->getGeo(), 0);
        glDrawElements(GL_TRIANGLES, m_drawData.instance()->findGeo(1+m_sceneObjects.at(i).get()->getGeo())->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
    }
  }
  m_matrices[MODEL_VIEW] = t1;
  m_matrices[PROJECTION] = t2;
  m_matrices[NORMAL] = t3;
}
//-----------------------------------------------------------------------------------------------------

std::array<int, 4> MainScene::countAllSceneGeo() const
{
  std::array<int, 4> numData = {{0,0,0,0}};

  for(auto it = m_sceneObjects.begin(); it!=m_sceneObjects.end(); ++it)
  {
    size_t id = it.base()->get()->getGeo();
    numData[0]+=m_drawData.instance()->findGeo(id)->getNVertData();
    numData[1]+=m_drawData.instance()->findGeo(id)->getNNormData();
    numData[2]+=m_drawData.instance()->findGeo(id)->getNUVData();
    numData[3]+=m_drawData.instance()->findGeo(id)->getNIndicesData();
  }
  return numData;
}
//-----------------------------------------------------------------------------------------------------
void MainScene::createSceneObject(std::string _name, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _sc, size_t _geo, size_t _mat)
{
  m_sceneObjects.emplace_back(new SceneObject(_name, _pos, _rot, _sc, _geo, _mat));
}
