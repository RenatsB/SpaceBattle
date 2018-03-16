#include "MainScene.h"
#include <MaterialWireframe.h>
#include <MaterialPBR.h>
#include <MaterialPhong.h>
#include <MaterialBump.h>
#include <MaterialFractal.h>
#include <MaterialEnvMap.h>
#include <sys/stat.h>

//-----------------------------------------------------------------------------------------------------
void MainScene::writeMeshAttributes(size_t _id)
{
  const auto& mesh = static_cast<Mesh*>(m_drawData->geoFind(_id));

  using namespace MeshAttributes;
  for (const auto buff : {VERTEX, UV, NORMAL})
  {
    m_meshVBO.write(mesh->getAttribData(buff), buff);
  }
  m_meshVBO.setIndices(mesh->getIndicesData());
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
  Mesh* temp1= new Mesh;
  Mesh* temp2= new Mesh;
  Mesh* temp3= new Mesh;
  Mesh* temp4= new Mesh;
  Mesh* temp5= new Mesh;
  Mesh* temp6= new Mesh;
  temp1->load("models/Grid.obj");
  temp2->load("models/cube.obj");
  temp3->load("models/Sphere.obj");
  temp4->load("models/Suzanne.obj");
  temp5->load("models/mandarin.obj");
  temp6->load("models/test2.obj");
  m_drawData->geoPut(temp1, "Grid");
  m_drawData->geoPut(temp2, "Cube");
  m_drawData->geoPut(temp3, "Sphere");
  m_drawData->geoPut(temp4, "Chimp");
  m_drawData->geoPut(temp5, "Fruit");
  m_drawData->geoPut(temp6, "Thing");
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
  auto mesh = static_cast<Mesh*>(m_drawData->geoFind(_geoID));
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
}
//-----------------------------------------------------------------------------------------------------
void MainScene::initMaterials()
{
  Material* temp1 = new MaterialWireframe(m_camera, m_shaderLib, &m_matrices);
  Material* temp2 = new MaterialPhong(m_camera, m_shaderLib, &m_matrices);
  Material* temp3 = new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {0.0f, 0.0f, 1.0f}, 1.0f, 1.0f, 0.5f, 1.0f);
  Material* temp4 = new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {1.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 0.9f, 0.4f);
  Material* temp5 = new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {1.0f, 1.0f, 0.0f}, 1.0f, 0.5f, 0.4f, 0.0f);
  m_drawData->matPut(temp1);
  m_drawData->matPut(temp2);
  m_drawData->matPut(temp3);
  m_drawData->matPut(temp4);
  m_drawData->matPut(temp5);
  for (size_t i = 0; i < m_drawData->matSize(); ++i)
  {
    auto mat = m_drawData->matFind(i);
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setName(name);
    mat->setShaderName(name);
    mat->apply();
  }
  m_drawData->setMatName(2, "BluePBR");
  m_drawData->setMatName(3, "RedPBR");
  m_drawData->setMatName(4, "YellowPBR");
  m_drawData->matFind(0)->apply();
}

void MainScene::useMaterial(const size_t _id)
{
  makeCurrent();
  m_drawData->matFind(_id)->apply();
  setAttributeBuffers();
}

void MainScene::init()
{
  Scene::init();

  initMaterials();
  initGeo();
  std::vector<std::pair<size_t, std::string>> geo = {{1, "Cube"}, {2, "Sphere"}, {3, "Chimp"}, {4, "Fruit"}, {5, "Thing"}};
  std::vector<std::pair<size_t, std::string>> mat = {{1, "Phong"}, {2, "BluePBR"}, {3, "RedPBR"}, {4, "YellowPBR"}};
  for(size_t i = 0; i<1000; ++i)
    {
      createSceneObject("TEST"+std::to_string(i), geo.at(i%5), mat.at(i%4));
      //m_objects->getObject(i)->setGeo(mat);
      //m_objects->getObject(i)->setMat(mat);
      m_objects->getObject(i)->setScale(glm::vec3(0.2f,0.2f,0.2f));
      m_objects->getObject(i)->setPosition(glm::vec3(sinf(glm::radians(static_cast<float>(i*30))),static_cast<float>(i/32.0f),cosf(glm::radians(static_cast<float>(i*30)))));
      m_objects->getObject(i)->setRotation(vec3(0.f, 30*i, 0.f));
      //m_objects->getObject(i)->setActive(false);
    }
  m_objects->writeRawSceneData("TestScene");
  m_objects->loadRawSceneData("TestScene");
}

//-----------------------------------------------------------------------------------------------------

void MainScene::renderScene()
{
  Scene::renderScene();
  using namespace SceneMatrices;
  mat4 t1=m_matrices[MODEL_VIEW];
  mat4 t2=m_matrices[PROJECTION];
  mat4 t3=m_matrices[NORMAL];

  m_drawData->matFind(0)->update();
  m_meshVBO.use();
  updateBuffer(0,0);
  glDrawElements(GL_TRIANGLES, static_cast<Mesh*>(m_drawData->geoFind(0))->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
  for(size_t i=0; i<m_objects->getObjectCount(); ++i)
  {
    if(m_objects->objectAt(i)->isActive())
    {
      //m_objects->objectAt(i)->setGeo(i%(m_drawData->geosize()-1)+1);
      //m_objects->objectAt(i)->setMat(i%(m_drawData->matSize()-1)+1);
      m_matrices[MODEL_VIEW] = m_objects->objectAt(i)->getMVmatrix();
      m_matrices[PROJECTION] = m_camera->projMatrix() * m_camera->viewMatrix() * m_matrices[MODEL_VIEW];
      m_matrices[NORMAL] = glm::inverse(glm::transpose(m_matrices[MODEL_VIEW]));
      if(m_wireframe)
      {
        m_drawData->matFind(m_objects->objectAt(i)->getMatID())->update();
        updateBuffer(m_objects->objectAt(i)->getGeoID(), 0);
        glDrawElements(GL_TRIANGLES, static_cast<Mesh*>(m_drawData->geoFind(m_objects->objectAt(i)->getGeoID()))->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
      }
      else
      {
        m_drawData->matFind(m_objects->objectAt(i)->getMatID())->update();
        updateBuffer(m_objects->objectAt(i)->getGeoID(), m_objects->objectAt(i)->getMatID());
        glDrawElements(GL_TRIANGLES, static_cast<Mesh*>(m_drawData->geoFind(m_objects->objectAt(i)->getGeoID()))->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);

        if(m_objects->isSelected(i))
        {
          m_drawData->matFind(m_objects->objectAt(i)->getMatID())->update();
          updateBuffer(m_objects->objectAt(i)->getGeoID(), 0);
          glDrawElements(GL_TRIANGLES, static_cast<Mesh*>(m_drawData->geoFind(m_objects->objectAt(i)->getGeoID()))->getNIndicesData(), GL_UNSIGNED_SHORT, nullptr);
        }
      }
    }
  }
  m_matrices[MODEL_VIEW] = t1;
  m_matrices[PROJECTION] = t2;
  m_matrices[NORMAL] = t3;
}
//-----------------------------------------------------------------------------------------------------
void MainScene::createSceneObjectFull(std::string _name, vec3 _pos, vec3 _rot, vec3 _sc, std::pair<size_t, std::string> _geo, std::pair<size_t, std::string> _mat)
{
  m_objects->createSceneObject(_name, _pos, _rot, _sc, _geo, _mat);
}
void MainScene::createSceneObject(std::string _name, std::pair<size_t, std::string> _geo, std::pair<size_t, std::string> _mat)
{
  m_objects->createSceneObject(_name, _geo, _mat);
}
//-----------------------------------------------------------------------------------------------------
void MainScene::select()
{
  m_objects->selectObject(deduceSelectCmd(m_selectCmd));
}

void MainScene::deselect()
{
  m_objects->deselectObject(deduceSelectCmd(m_selectCmd));
}

void MainScene::changeMat(QString _cmd)
{
  std::string normal = _cmd.toStdString();
  bool check = false; //assuming a numeric value
  for(size_t i=0; i< static_cast<size_t>(_cmd.size()); ++i)
  {
    if(!check)
      switch(normal.at(i))
      {
      case '0':{break;}
      case '1':{break;}
      case '2':{break;}
      case '3':{break;}
      case '4':{break;}
      case '5':{break;}
      case '6':{break;}
      case '7':{break;}
      case '8':{break;}
      case '9':{break;}
      default:{check=true;break;} //character is not a number => we have a name
      }
  }
  if(check)
  {
    m_objects->changeMat(std::pair<size_t, std::string>{m_drawData->getMatID(normal), normal});
  }
  else
  {
    if(_cmd.toUInt() < m_drawData->matSize())
    {
      m_objects->changeMat(std::pair<size_t, std::string>{_cmd.toUInt(), m_drawData->getMatName(_cmd.toUInt())});
    }
    else
    {
      m_objects->changeMat(std::pair<size_t, std::string>{m_drawData->getMatID(normal), normal});
    }
  }
}

void MainScene::changeGeo(QString _cmd)
{
  std::string normal = _cmd.toStdString();
  bool check = false; //assuming a numeric value
  for(size_t i=0; i< static_cast<size_t>(_cmd.size()); ++i)
  {
    if(!check)
      switch(normal.at(i))
      {
      case '0':{break;}
      case '1':{break;}
      case '2':{break;}
      case '3':{break;}
      case '4':{break;}
      case '5':{break;}
      case '6':{break;}
      case '7':{break;}
      case '8':{break;}
      case '9':{break;}
      default:{check=true;break;} //character is not a number => we have a name
      }
  }
  if(check)
  {
    m_objects->changeGeo(std::pair<size_t, std::string>{m_drawData->getGeoID(normal), normal});
  }
  else
  {
    if(_cmd.toUInt() < m_drawData->geosize())
    {
      m_objects->changeGeo(std::pair<size_t, std::string>{_cmd.toUInt(), m_drawData->getGeoName(_cmd.toUInt())});
    }
    else
    {
      m_objects->changeGeo(std::pair<size_t, std::string>{m_drawData->getGeoID(normal), normal});
    }
  }
}

void MainScene::receiveFileCmd(QString _current)
{
  m_fileLoadCmd = _current.toStdString();
}

void MainScene::receiveSelCmd(QString _current)
{
  m_selectCmd = _current;
}

void MainScene::receiveModCmd(QString _current)
{
  m_modCmd = _current;
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

inline bool fileExists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void MainScene::deduceCreateMat(QString& _name)
{
  std::cout<<"Attempting to deduce material type and load it..."<<std::endl;
  std::string normal = _name.toStdString();
  unsigned short matType = 0; //wireframe by default
  std::string check = normal.substr(0,static_cast<size_t>(_name.size()-5));
  if(check == "phong"){matType = 1;}
  else if(check == "bump"){matType = 3;}
  else if(check == "fractal"){matType = 4;}
  else if(check == "envMap"){matType = 5;}
  else if(check.substr(check.size()-6, 6) == "redPBR"){matType = 2;}
  switch(matType)
  {
  case 0:{
    m_drawData->matPut(new MaterialWireframe(m_camera, m_shaderLib, &m_matrices));
    auto mat = m_drawData->matFind(m_drawData->matSize()-1);
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setName(name);
    mat->setShaderName(name);
    break;}
  case 1:{
    m_drawData->matPut(new MaterialPhong(m_camera, m_shaderLib, &m_matrices));
    auto mat = m_drawData->matFind(m_drawData->matSize()-1);
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setName(name);
    mat->setShaderName(name);
    break;}
  case 3:{
    m_drawData->matPut(new MaterialBump(m_camera, m_shaderLib, &m_matrices));
    auto mat = m_drawData->matFind(m_drawData->matSize()-1);
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setName(name);
    mat->setShaderName(name);
    break;}
  case 4:{
    m_drawData->matPut(new MaterialFractal(m_camera, m_shaderLib, &m_matrices));
    auto mat = m_drawData->matFind(m_drawData->matSize()-1);
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setName(name);
    mat->setShaderName(name);
    break;}
  case 5:{
    m_drawData->matPut(new MaterialEnvMap(m_camera, m_shaderLib, &m_matrices));
    auto mat = m_drawData->matFind(m_drawData->matSize()-1);
    auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
    mat->setName(name);
    mat->setShaderName(name);
    break;}
  case 2:{
    std::string params = check.substr(0, check.size()-6);
    if(!params.empty())
    {
      std::cout<<"Deducing PBR params..."<<std::endl;
      QString h1; h1 = h1.fromStdString(normal.substr(0,3));
      float a = h1.toFloat();
      QString h2; h2 = h2.fromStdString(normal.substr(5,3));
      float b = h2.toFloat();
      QString h3; h3 = h3.fromStdString(normal.substr(9,3));
      float c = h3.toFloat();
      m_drawData->matPut(new MaterialPBR(m_camera, m_shaderLib, &m_matrices, {a, b, c}, 1.0f, 1.0f, 0.5f, 1.0f));
      auto mat = m_drawData->matFind(m_drawData->matSize()-1);
      auto name = m_shaderLib->loadShaderProg(mat->shaderFileName());
      mat->setName(name);
      mat->setShaderName(name);
    }
    else
    {
      std::cout<<"Error: parameters for PBR set incorrectly. Use: (<R.R>,<G.G>,<B.B> redPBR.json) to load PBR material."<<std::endl;
      return;
    }
    break;
  }
  }
  std::cout<<"Material successfully loaded from: "<<"shaderPrograms"<<std::endl;
}

std::vector<size_t> MainScene::deduceSelectCmd(QString &_cmd)
{
  std::vector<size_t> ret;
  std::string normal = _cmd.toStdString();
  QString convertible = "";
  for(size_t i=0; i<normal.size(); ++i)
  {
    switch(normal.at(i)) {
    case '0':{convertible.append('0');break;}
    case '1':{convertible.append('1');break;}
    case '2':{convertible.append('2');break;}
    case '3':{convertible.append('3');break;}
    case '4':{convertible.append('4');break;}
    case '5':{convertible.append('5');break;}
    case '6':{convertible.append('6');break;}
    case '7':{convertible.append('7');break;}
    case '8':{convertible.append('8');break;}
    case '9':{convertible.append('9');break;}
    case ',':{ret.push_back(convertible.toULong());convertible.clear();break;}
    default: break;
    }
  }
  if(convertible!="")
  {
    ret.push_back(convertible.toUInt());
  }
  std::cout<<"Selecting :";
  for(auto i : ret)
    std::cout<<i<<" ";
  std::cout<<std::endl;
  return ret;
}

void MainScene::loadFile()
{
  std::string normal = m_fileLoadCmd;

  if(normal.size() > 5)
  {
    if(normal.size() > 6) //can be json or obj
    {
      if(normal.substr(normal.size()-4, 4) == ".obj")
      {
        std::cout<<"Loading geometry from: "<<"models/"<<normal<<" ..."<<std::endl;
        if(fileExists("models/"+normal))
        {
          Mesh* newMesh = new Mesh;
          newMesh->load("models/"+normal);
          m_drawData->geoPut(newMesh, normal.substr(0, normal.size()-4));
          std::cout<<"Geometry successfully loaded from: "<<"models/"<<normal<<std::endl;
        }
        else
        {
          std::cout<<"File is not in models folder or does not exist. Aborting..."<<std::endl;
          return;
        }
      }
      else if(normal.substr(normal.size()-5, 5) == ".json")
      {
        std::cout<<"Loading material from: "<<"shaderPrograms/"<<normal<<" ..."<<std::endl;
        std::string paramCheck = normal;
        if(normal.size() > 11)
        {
          paramCheck = normal.substr(normal.size()-11, 11);
          if(paramCheck != "redPBR.json") //not pbr with params
          {
            paramCheck = normal;
          }
        }
        if(fileExists("shaderPrograms/"+paramCheck))
        {
          QString converted; converted = converted.fromStdString(normal);
          deduceCreateMat(converted);
        }
        else
        {
          std::cout<<"File is not in shaderPrograms folder or does not exist. Aborting..."<<std::endl;
          return;
        }
      }
      else
      {
          std::cout<<"Filename error. Passed: "<<normal<<std::endl;
          std::cout<<"To load a mesh use <filename>.obj (must be in models/ folder)"<<std::endl;
          std::cout<<"To load a material use <filename>.json (must be in shaderPrograms/ folder)"<<std::endl;
      }
    }
    else //only obj with single-character names
    {
      if(normal.substr(normal.size()-4, 4) == ".obj")
      {
        std::cout<<"Loading geometry from: "<<normal<<" ..."<<std::endl;
        if(fileExists("models/"+normal))
        {
          Mesh* newMesh = new Mesh;
          newMesh->load("models/"+normal);
          m_drawData->geoPut(newMesh, normal.substr(0, normal.size()-4));
          std::cout<<"Geometry successfully loaded from: "<<"models/"<<normal<<std::endl;
        }
        else
        {
          std::cout<<"File is not in models folder or does not exist. Aborting..."<<std::endl;
          return;
        }
      }
    }
  }
  else
  {
    std::cout<<"Filename error. Passed: "<<normal<<std::endl;
    std::cout<<"To load a mesh use <filename>.obj (must be in models/ folder)"<<std::endl;
    std::cout<<"To load a material use <filename>.json (must be in shaderPrograms/ folder)"<<std::endl;
  }
}

void MainScene::wireframe(bool _value)
{
  m_wireframe = _value;
}

void MainScene::move(unsigned short _axis, float _val)
{
  m_objects->move(_axis, _val);
}

void MainScene::rotate(unsigned short _axis, float _val)
{
  m_objects->rotate(_axis, _val);
}

void MainScene::scale(unsigned short _axis, float _val)
{
  m_objects->scale(_axis, _val);
}



















