#include "MainScene.h"
#include "MaterialWireframe.h"
#include "MaterialPBR.h"
#include "MaterialPhong.h"
#include "MaterialBump.h"
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
  m_drawData.instance()->geoReserve(7);
  m_drawData.instance()->findGeo(0)->load("models/Grid.obj");
  m_drawData.instance()->findGeo(1)->load("models/cube.obj");
  m_drawData.instance()->findGeo(2)->load("models/Asteroid.obj");
  m_drawData.instance()->findGeo(3)->load("models/mandarin.obj");
  m_drawData.instance()->findGeo(4)->load("models/Suzanne.obj");
  m_drawData.instance()->findGeo(5)->load("models/test2.obj");
  m_drawData.instance()->findGeo(6)->load("models/Sphere.obj");
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
  m_drawData.instance()->matReserve(7);
  m_drawData.instance()->matPut(new MaterialWireframe(m_camera, m_shaderLib, &m_matrices));
  m_drawData.instance()->matPut(new MaterialPhong(m_camera, m_shaderLib, &m_matrices));
  m_drawData.instance()->matPut(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.5f, 0.0f, 0.0f}, 1.0f, 1.0f, 0.5f, 1.0f));
  m_drawData.instance()->matPut(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.1f, 0.2f, 0.5f}, 0.5f, 1.0f, 0.4f, 0.2f));
  m_drawData.instance()->matPut(new MaterialBump(m_camera, m_shaderLib, &m_matrices));
  m_drawData.instance()->matPut(new MaterialFractal(m_camera, m_shaderLib, &m_matrices));
  m_drawData.instance()->matPut(new MaterialEnvMap(m_camera, m_shaderLib, &m_matrices));
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
      m_sceneObjects.at(i).get()->setGeometry(i%6+1);
      m_sceneObjects.at(i).get()->setMat(i%3+1);
      m_sceneObjects.at(i).get()->setScale(glm::vec3(0.2f,0.2f,0.2f));
      m_sceneObjects.at(i).get()->setPosition(glm::vec3(sinf(glm::radians(static_cast<float>(i*0.5))),0.f,cosf(glm::radians(static_cast<float>(i*0.5)))));
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
        glDrawElements(GL_TRIANGLES, m_drawData.instance()->findGeo(m_sceneObjects.at(i).get()->getGeo())->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);

        if(isSelected(i))
        {
            m_drawData.instance()->findMat(m_sceneObjects.at(i).get()->findMat())->update();
            updateBuffer(m_sceneObjects.at(i).get()->getGeo(), 0);
            glDrawElements(GL_TRIANGLES, m_drawData.instance()->findGeo(m_sceneObjects.at(i).get()->getGeo())->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
        }
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
//-----------------------------------------------------------------------------------------------------
void MainScene::selectObject(const size_t _id)
{
  if(m_selected.empty())
  {
    m_selected.push_back(_id);
  }
  else
  {
    bool check = false;
    for(auto it = m_selected.begin(); it<m_selected.end(); ++it)
    {
      if(_id == *it.base())
      {
        check = true;
        break;
      }
    }
    if(!check)
      m_selected.push_back(_id);
  }
}
void MainScene::deselectObject(const size_t _id)
{
  for(auto it = m_selected.begin(); it<m_selected.end(); ++it)
  {
    if(*it.base() == _id)
    {
      m_selected.erase(it);
      break;
    }
  }
}

void MainScene::select()
{
  if(m_selected.size() < m_sceneObjects.size())
  {
    if(!m_selected.empty())
    {
      selectObject(m_selected.at(m_selected.size()-1) + 1);
    }
    else
    {
      selectObject(0);
    }
  }
}

void MainScene::deselect()
{
  if(!m_selected.empty())
  {
    deselectObject(m_selected.at(m_selected.size()-1));
  }
}

bool MainScene::isSelected(const size_t _id) const
{
  for(auto s : m_selected)
  {
    if(s == _id)
      return true;
  }
  return false;
}

void MainScene::move(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->moveObject(constructTranslateVector(_axis, _val));
  }
}

void MainScene::scale(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->scaleObject(constructTranslateVector(_axis, _val));
  }
}

void MainScene::rotate(unsigned short _axis, float _val)
{

  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->rotateObject(constructTranslateVector(_axis, _val));
  }
}

vec3 MainScene::constructTranslateVector(unsigned short _axis, float _val) const
{
  vec3 ret(0,0,0);
  switch(_axis)
  {
    case 0 : {ret.x = _val; break;}
    case 1 : {ret.y = _val; break;}
    case 2 : {ret.z = _val; break;}
    case 3 : {ret.x = _val; ret.y = _val; break;}
    case 4 : {ret.y = _val; ret.z = _val;break;}
    case 6 : {ret.x = _val; ret.z = _val;break;}
    default : {ret.x = _val; ret.y = _val; ret.z = _val;break;}
  }
  return ret;
}

void MainScene::changeMat(size_t _new)
{
  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->setMat(_new);
  }
}

void MainScene::loadMat(std::string _path)
{
  //std::cout<<"loading material from: "<<_path<<std::endl;
  std::cout<<"Warning: function not implemented"<<std::endl;
}

void MainScene::changeGeo(size_t _new)
{
  for(auto obj : m_selected)
  {
    m_sceneObjects.at(obj)->setGeometry(_new);
  }
}

void MainScene::receiveGeoPath(QString _current)
{
  m_geoPathCmd = _current.toStdString();
}

void MainScene::loadGeo()
{
  std::string normal = m_geoPathCmd;

  if(normal.size() > 7)
  {
    if(normal.substr(normal.size()-4, 4) == ".obj")
    {
      if(normal.substr(0, 7) == "models/")
      {
        std::cout<<"Loading geometry from: "<<normal<<" ..."<<std::endl;
        m_drawData.instance()->geoReserve(1);
        m_drawData.instance()->findGeo(m_drawData.instance()->geosize()-1)->load(normal);
        std::cout<<"Geometry successfully loaded from: "<<normal<<std::endl;
      }
      else
      {
        std::cout<<"File is not in models folder. Aborting..."<<std::endl;
      }
    }
    else
    {
      std::cout<<"Not an .obj extension. Aborting..."<<std::endl;
    }
  }
  else
  {
    std::cout<<normal;
  }

}

void MainScene::receiveTableInfo(QTableWidgetItem* _ref)
{
  unsigned short ax = static_cast<unsigned short>(_ref->column());
  float val = static_cast<float>(_ref->data(0).toFloat());
  unsigned short type = static_cast<unsigned short>(_ref->row());
  switch(type)
  {
    case 0 : {move(ax, val); break;}
    case 1 : {rotate(ax, val); break;}
    case 2 : {scale(ax, val); break;}
    default : {break;}
  }
}


































