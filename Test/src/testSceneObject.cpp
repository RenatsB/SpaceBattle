#include <QtTest/QtTest>
#include "mockSceneObject.cpp"

class testSceneObject : public QObject
{
  Q_OBJECT
private:
  std::unique_ptr<mockSceneObject> Obj;
  bool checkObjDefault(const mockSceneObject* _ref) const;
  bool checkObjFull(const mockSceneObject* _ref, std::string _name, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _sc,
                    std::pair<size_t, std::string>_geo, std::pair<size_t, std::string>_mat) const;
private Q_SLOTS:
  void test_constructA();
  void test_constructB();
  void test_setName();
  void test_setID();
  void test_getName();
  void test_getID();
  void test_reset();
  void test_setParent();
  void test_getParent();
  void test_addChild();
  void test_setChildren();
  void test_getChildren();
  void test_moveObject ();
  void test_setPosition ();
  void test_rotateObject ();
  void test_setRotation ();
  void test_scaleObject ();
  void test_setScale ();
  void test_getPosition ();
  void test_getRotation ();
  void test_getScale ();
  void test_setActive();
  void test_isActive();
  void test_updateMatrix();
  void test_getMVmatrix();
  void test_setGeo();
  void test_setMat();
  void test_getGeoID();
  void test_getGeoName();
  void test_getMatID();
  void test_getMatName();
};

bool testSceneObject::checkObjDefault(const mockSceneObject* _ref) const
{
  if(_ref->getName().empty())
    return false;
  if(_ref->getPosition() != glm::vec3(0,0,0))
    return false;
  if(_ref->getRotation() != glm::vec3(0,0,0))
    return false;
  if(_ref->getScale() != glm::vec3(1,1,1))
    return false;
  if(_ref->getID() != size_t{0})
    return false;
  if(!_ref->getChildren().empty())
    return false;
  if(_ref->getGeoID() != size_t{1})
    return false;
  if(_ref->getGeoName() != std::string{"Mesh1"})
    return false;
  if(_ref->getMatID() != size_t{1})
    return false;
  if(_ref->getMatName() != std::string{"Material1"})
    return false;
  if(_ref->getParent() != nullptr)
    return false;
  if(_ref->getMVmatrix() != glm::mat4{1})
    return false;
  return true;
}

bool testSceneObject::checkObjFull(const mockSceneObject* _ref, std::string _name, glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _sc,
                  std::pair<size_t, std::string>_geo, std::pair<size_t, std::string>_mat) const
{
  if(_ref->getName() != _name)
    return false;
  if(_ref->getPosition() != _pos)
    return false;
  if(_ref->getRotation() != _rot)
    return false;
  if(_ref->getScale() != _sc)
    return false;
  if(_ref->getID() != size_t{0})
    return false;
  if(!_ref->getChildren().empty())
    return false;
  if(_ref->getGeoID() != _geo.first)
    return false;
  if(_ref->getGeoName() != _geo.second)
    return false;
  if(_ref->getMatID() != _mat.first)
    return false;
  if(_ref->getMatName() != _mat.second)
    return false;
  if(_ref->getParent() != nullptr)
    return false;
  if(_ref->getMVmatrix() == glm::mat4{1})
    return false;
  return true;
}

void testSceneObject::test_constructA()
{
  std::string newName = "TestA";
  glm::vec3 newPos{1,0,1};
  glm::vec3 newRot{30, 90, 80};
  glm::vec3 newScale{23, 0.1, 50};
  std::pair<size_t, std::string> newGeo{28, "Cookie_A"};
  std::pair<size_t, std::string> newMat{52, "Chocolate_A"};
  mockSceneObject* testA = new mockSceneObject(newName, newPos, newRot, newScale, newGeo, newMat);

  QCOMPARE(checkObjFull(testA, newName, newPos, newRot, newScale, newGeo, newMat), true);
}

void testSceneObject::test_constructB()
{
  std::string newName = "TestA";
  glm::vec3 newPos{0,0,0};
  glm::vec3 newRot{0,0,0};
  glm::vec3 newScale{1,1,1};
  std::pair<size_t, std::string> newGeo{29, "Cookie_B"};
  std::pair<size_t, std::string> newMat{53, "Chocolate_B"};
  mockSceneObject* testB = new mockSceneObject(newName, newPos, newRot, newScale, newGeo, newMat);

  QCOMPARE(checkObjFull(testB, newName, newPos, newRot, newScale, newGeo, newMat), true);
}

void testSceneObject::test_setName()
{
  std::string str0  = "Name";
  std::string str1  = "";
  std::string str2  = std::string{'\n'};
  std::string str3  = std::string{"\b"};
  double      numn  = std::nan("cookie");
  std::string str4  = std::string{std::to_string(numn)};

  QCOMPARE(Obj->getName(), std::string{""});
  Obj->setName(str0);
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(Obj->getName(), str1);
  QCOMPARE(Obj->getName(), str0);
  Obj->setName(str1);
  QCOMPARE(Obj->getName(), str1);
  Obj->setName(str2);
  QEXPECT_FAIL("","Passing a newline",Continue);
  QCOMPARE(Obj->getName(), std::string{"\n"});
  Obj->setName(str3);
  QCOMPARE(Obj->getName(), std::string{"\b"});
  Obj->setName(str4);
  QEXPECT_FAIL("","Passed stringified nan",Continue);
  QCOMPARE(Obj->getName(), std::string{"cookie"});
}

void testSceneObject::test_setID()
{
  unsigned long num0 = 0;
  char        num1  = '\n';
  float       num2  = 0.45f;
  int         num3  = 12225;
  bool        num4  = false;
  //void*       num5  = NULL;
  unsigned long num5 = '@';
  double      num6  = std::nan("nan");

  QCOMPARE(Obj->getID(), num0);
  Obj->changeID(num1);
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(Obj->getID(), static_cast<unsigned long>(num0));
  QCOMPARE(Obj->getID(), static_cast<unsigned long>(num1));
  Obj->changeID(num2);
  QCOMPARE(Obj->getID(), static_cast<unsigned long>(num2));
  Obj->changeID(num3);
  QCOMPARE(Obj->getID(), static_cast<unsigned long>(num3));
  Obj->changeID(num4);
  QCOMPARE(Obj->getID(), static_cast<unsigned long>(num4));
  Obj->changeID(num5);
  QEXPECT_FAIL("","Passing a at char",Continue);
  QCOMPARE(Obj->getID(), num5);
  Obj->changeID(num6);
  QEXPECT_FAIL("","Passing nan value nan",Continue);
  QCOMPARE(Obj->getID(), static_cast<unsigned long>(num6));
}

void testSceneObject::test_getName()
{
  std::string stored = "";

  std::string str0 = "Name";
  std::string str1 = "";
  std::string str2 = std::string{'\n'};
  std::string str3 = std::string{"\b"};
  double      numn = std::nan("nani");
  std::string str4 = std::string{std::to_string(numn)};

  stored = Obj->getName();
  QCOMPARE(stored, std::string{""});
  Obj->setName(str0);
  stored = Obj->getName();
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(stored, str1);
  QCOMPARE(stored, str0);
  Obj->setName(str1);
  stored = Obj->getName();
  QCOMPARE(stored, str1);
  Obj->setName(str2);
  stored = Obj->getName();
  QEXPECT_FAIL("","Passing a newline",Continue);
  QCOMPARE(stored, std::string{"\n"});
  Obj->setName(str3);
  stored = Obj->getName();
  QCOMPARE(stored, std::string{"\b"});
  Obj->setName(str4);
  stored = Obj->getName();
  QEXPECT_FAIL("","Passed stringified nan",Continue);
  QCOMPARE(stored, std::string{"nani"});
}

void testSceneObject::test_getID()
{
  size_t stored = 0;

  unsigned long num0 = 0;
  char        num1  = '\n';
  float       num2  = 0.45f;
  int         num3  = 12225;
  bool        num4  = false;
  //void*       num5  = NULL;
  unsigned long num5 = '@';
  double      num6  = std::nan("nano");

  stored = Obj->getID();
  QCOMPARE(stored, num0);
  Obj->changeID(num1);
  stored = Obj->getID();
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(stored, static_cast<unsigned long>(num0));
  QCOMPARE(stored, static_cast<unsigned long>(num1));
  Obj->changeID(num2);
  stored = Obj->getID();
  QCOMPARE(stored, static_cast<unsigned long>(num2));
  Obj->changeID(num3);
  stored = Obj->getID();
  QCOMPARE(stored, static_cast<unsigned long>(num3));
  Obj->changeID(num4);
  stored = Obj->getID();
  QCOMPARE(stored, static_cast<unsigned long>(num4));
  Obj->changeID(num5);
  stored = Obj->getID();
  QEXPECT_FAIL("","Passing an at char",Continue);
  QCOMPARE(stored, num5);
  Obj->changeID(num6);
  stored = Obj->getID();
  QEXPECT_FAIL("","Passing a nan value nano",Continue);
  QCOMPARE(stored, static_cast<unsigned long>(num6));
}

void testSceneObject::test_reset()
{
  Obj->reset();
  QCOMPARE(checkObjDefault(Obj.get()), true);
}

void testSceneObject::test_setParent()
{
  Obj->reset();
  QCOMPARE(Obj->getParent(), nullptr);
  std::pair<size_t,std::string> testCtemp{0,"blah"};
  mockSceneObject* testC = new mockSceneObject("TestC", testCtemp, testCtemp);
  Obj->setParent(testC);
  QCOMPARE(Obj->getParent(), testC);
  Obj->reset();
}

void testSceneObject::test_getParent()
{
  Obj->reset();
  QCOMPARE(Obj->getParent(), nullptr);
  std::pair<size_t,std::string> testDtemp{0,"blahoooo"};
  mockSceneObject* testD1 = new mockSceneObject("TestC", testDtemp, testDtemp);
  mockSceneObject* testD2= new mockSceneObject("TestC", testDtemp, testDtemp);
  mockSceneObject* testD3 = new mockSceneObject("TestC", testDtemp, testDtemp);
  mockSceneObject* testD4 = new mockSceneObject("TestC", testDtemp, testDtemp);
  Obj->setParent(testD1);
  QEXPECT_FAIL("","Checking against nullptr",Continue);
  QCOMPARE(Obj->getParent(), nullptr);
  QCOMPARE(Obj->getParent(), testD1);
  Obj->setParent(testD2);
  QEXPECT_FAIL("","checking against other unused pointer",Continue);
  QCOMPARE(Obj->getParent(), testD3);
  Obj->setParent(testD4);
  Obj->setParent(testD1);
  Obj->setParent(testD2);
  Obj->setParent(testD3);
  Obj->setParent(testD4);
  QEXPECT_FAIL("","checking against previously tested",Continue);
  QCOMPARE(Obj->getParent(), testD3);
  QCOMPARE(Obj->getParent(), testD4);
  Obj->reset();
}

void testSceneObject::test_addChild()
{
  Obj->reset();
  QCOMPARE(Obj->getChildren(), nullptr);
  std::pair<size_t,std::string> testEtemp{100500,"DTheRockJ"};
  mockSceneObject* testE1 = new mockSceneObject("TestE1", testEtemp, testEtemp);
  mockSceneObject* testE2= new mockSceneObject("TestE2", testEtemp, testEtemp);
  mockSceneObject* testE3 = new mockSceneObject("TestE3", testEtemp, testEtemp);
  mockSceneObject* testE4 = new mockSceneObject("TestE4", testEtemp, testEtemp);
  std::vector<mockSceneObject*> testEvec;
  testEvec.emplace_back(testE1);
  testEvec.emplace_back(testE2);
  testEvec.emplace_back(testE3);
  testEvec.emplace_back(testE4);
  Obj->addChild(testE1);
  QEXPECT_FAIL("","Checking agains nullptr",Continue);
  QCOMPARE(Obj->getChildren(), nullptr);
  QCOMPARE(Obj->getChildren().at(0), testE1);
  Obj->setChildren(std::vector<mockSceneObject*>{nullptr});
  Obj->addChild(testE2);
  Obj->addChild(testE3);
  Obj->addChild(testE4);
  QEXPECT_FAIL("","Check agains last used object",Continue);
  QCOMPARE(Obj->getChildren().at(0), testE4);
  QCOMPARE(Obj->getChildren().at(0), testE2);
  QCOMPARE(Obj->getChildren().at(1), testE3);
  QCOMPARE(Obj->getChildren().at(2), testE4);
  Obj->reset();
}

void testSceneObject::test_setChildren()
{
  Obj->reset();
  QCOMPARE(Obj->getChildren(), nullptr);
  std::pair<size_t,std::string> testFtemp{67,"SomeName"};
  mockSceneObject* testF1 = new mockSceneObject("TestF1", testFtemp, testFtemp);
  mockSceneObject* testF2= new mockSceneObject("TestF2", testFtemp, testFtemp);
  mockSceneObject* testF3 = new mockSceneObject("TestF3", testFtemp, testFtemp);
  mockSceneObject* testF4 = new mockSceneObject("TestF4", testFtemp, testFtemp);
  std::vector<mockSceneObject*> testFvec;
  testFvec.emplace_back(testF1);
  testFvec.emplace_back(testF2);
  testFvec.emplace_back(testF3);
  testFvec.emplace_back(testF4);
  Obj->setChildren(testFvec);
  QCOMPARE(Obj->getChildren().at(0), testF1);
  QCOMPARE(Obj->getChildren().at(1), testF2);
  QCOMPARE(Obj->getChildren().at(2), testF3);
  QCOMPARE(Obj->getChildren().at(3), testF4);
  Obj->reset();
  QCOMPARE(Obj->getChildren().at(0), nullptr);
}

void testSceneObject::test_getChildren()
{
  Obj->reset();
  QCOMPARE(Obj->getChildren(), nullptr);
  std::pair<size_t,std::string> testGtemp{228,"TooManyNames"};
  mockSceneObject* testG1 = new mockSceneObject("TestF1", testGtemp, testGtemp);
  mockSceneObject* testG2= new mockSceneObject("TestF2", testGtemp, testGtemp);
  mockSceneObject* testG3 = new mockSceneObject("TestF3", testGtemp, testGtemp);
  mockSceneObject* testG4 = new mockSceneObject("TestF4", testGtemp, testGtemp);
  std::vector<mockSceneObject*> testGvec;
  testGvec.emplace_back(testG1);
  testGvec.emplace_back(testG2);
  testGvec.emplace_back(testG3);
  testGvec.emplace_back(testG4);
  Obj->setChildren(testGvec);
  QCOMPARE(Obj->getChildren().at(0), testG1);
  QCOMPARE(Obj->getChildren().at(1), testG2);
  QCOMPARE(Obj->getChildren().at(2), testG3);
  QCOMPARE(Obj->getChildren().at(3), testG4);
  Obj->reset();
  QCOMPARE(Obj->getChildren().at(0), nullptr);
}

void testSceneObject::test_moveObject ()
{
  glm::vec3 tr1{0,0,0};
  glm::vec3 tr2{'@','#','%'};
  glm::vec3 tr3{std::nanf("nanx"),std::nanf("nany"),std::nanf("nanz")};
  glm::vec3 tr4{-123213.35435,-124324554.65878769,-5436464.3254654};
  glm::vec3 original = Obj->getPosition();

  QCOMPARE(Obj->getPosition().x, float{0.f});
  QCOMPARE(Obj->getPosition().y, float{0.f});
  QCOMPARE(Obj->getPosition().z, float{0.f});

  Obj->moveObject(tr1);
  QCOMPARE(Obj->getPosition().x, float{0.f});
  QCOMPARE(Obj->getPosition().y, float{0.f});
  QCOMPARE(Obj->getPosition().z, float{0.f});

  Obj->moveObject(tr2);
  QCOMPARE(Obj->getPosition().x, original.x+tr2.x);
  QCOMPARE(Obj->getPosition().y, original.y+tr2.y);
  QCOMPARE(Obj->getPosition().z, original.z+tr2.z);
  original+=tr2;

  Obj->moveObject(tr3);
  QEXPECT_FAIL("","Check nanX",Continue);
  QCOMPARE(Obj->getPosition().x, original.x+tr3.x);
  QEXPECT_FAIL("","Check nanY",Continue);
  QCOMPARE(Obj->getPosition().y, original.y+tr3.y);
  QEXPECT_FAIL("","Check nanZ",Continue);
  QCOMPARE(Obj->getPosition().z, original.z+tr3.z);
  Obj->reset();
  Obj->moveObject(original);

  Obj->moveObject(tr4);
  QCOMPARE(Obj->getPosition().x, original.x+tr4.x);
  QCOMPARE(Obj->getPosition().y, original.y+tr4.y);
  QCOMPARE(Obj->getPosition().z, original.z+tr4.z);
  original+=tr4;

  Obj->moveObject(-original);
  QCOMPARE(Obj->getPosition().x, float{0.f});
  QCOMPARE(Obj->getPosition().y, float{0.f});
  QCOMPARE(Obj->getPosition().z, float{0.f});

  Obj->reset();
}

void testSceneObject::test_setPosition ()
{
  glm::vec3 tr1{0,0,0};
  glm::vec3 tr2{'@','#','%'};
  glm::vec3 tr3{std::nanf("nanx"),std::nanf("nany"),std::nanf("nanz")};
  glm::vec3 tr4{-123213.35435,-124324554.65878769,-5436464.3254654};

  QCOMPARE(Obj->getPosition().x, float{0.f});
  QCOMPARE(Obj->getPosition().y, float{0.f});
  QCOMPARE(Obj->getPosition().z, float{0.f});

  Obj->setPosition(tr1);
  QCOMPARE(Obj->getPosition().x, float{0.f});
  QCOMPARE(Obj->getPosition().y, float{0.f});
  QCOMPARE(Obj->getPosition().z, float{0.f});

  Obj->setPosition(tr2);
  QCOMPARE(Obj->getPosition().x, tr2.x);
  QCOMPARE(Obj->getPosition().y, tr2.y);
  QCOMPARE(Obj->getPosition().z, tr2.z);

  Obj->setPosition(tr3);
  QEXPECT_FAIL("","Check nanX",Continue);
  QCOMPARE(Obj->getPosition().x, tr3.x);
  QEXPECT_FAIL("","Check nanY",Continue);
  QCOMPARE(Obj->getPosition().y, tr3.y);
  QEXPECT_FAIL("","Check nanZ",Continue);
  QCOMPARE(Obj->getPosition().z, tr3.z);
  Obj->reset();

  Obj->setPosition(tr4);
  QCOMPARE(Obj->getPosition().x, tr4.x);
  QCOMPARE(Obj->getPosition().y, tr4.y);
  QCOMPARE(Obj->getPosition().z, tr4.z);

  Obj->setPosition(glm::vec3{0,0,0});
  QCOMPARE(Obj->getPosition().x, float{0.f});
  QCOMPARE(Obj->getPosition().y, float{0.f});
  QCOMPARE(Obj->getPosition().z, float{0.f});

  Obj->reset();
}

void testSceneObject::test_rotateObject ()
{
  glm::vec3 tr1{0,0,0};
  glm::vec3 tr2{'@','#','%'};
  glm::vec3 tr3{std::nanf("nanx"),std::nanf("nany"),std::nanf("nanz")};
  glm::vec3 tr4{-123213.35435,-124324554.65878769,-5436464.3254654};
  glm::vec3 original = Obj->getRotation();

  QCOMPARE(Obj->getRotation().x, float{0.f});
  QCOMPARE(Obj->getRotation().y, float{0.f});
  QCOMPARE(Obj->getRotation().z, float{0.f});

  Obj->rotateObject(tr1);
  QCOMPARE(Obj->getRotation().x, float{0.f});
  QCOMPARE(Obj->getRotation().y, float{0.f});
  QCOMPARE(Obj->getRotation().z, float{0.f});

  Obj->rotateObject(tr2);
  QCOMPARE(Obj->getRotation().x, original.x+tr2.x);
  QCOMPARE(Obj->getRotation().y, original.y+tr2.y);
  QCOMPARE(Obj->getRotation().z, original.z+tr2.z);
  original+=tr2;

  Obj->rotateObject(tr3);
  QEXPECT_FAIL("","Check nanX",Continue);
  QCOMPARE(Obj->getRotation().x, original.x+tr3.x);
  QEXPECT_FAIL("","Check nanY",Continue);
  QCOMPARE(Obj->getRotation().y, original.y+tr3.y);
  QEXPECT_FAIL("","Check nanZ",Continue);
  QCOMPARE(Obj->getRotation().z, original.z+tr3.z);
  Obj->reset();
  Obj->rotateObject(original);

  Obj->rotateObject(tr4);
  QCOMPARE(Obj->getRotation().x, original.x+tr4.x);
  QCOMPARE(Obj->getRotation().y, original.y+tr4.y);
  QCOMPARE(Obj->getRotation().z, original.z+tr4.z);
  original+=tr4;

  Obj->rotateObject(-original);
  QCOMPARE(Obj->getRotation().x, float{0.f});
  QCOMPARE(Obj->getRotation().y, float{0.f});
  QCOMPARE(Obj->getRotation().z, float{0.f});

  Obj->reset();
}

void testSceneObject::test_setRotation ()
{
  glm::vec3 tr1{0,0,0};
  glm::vec3 tr2{'@','#','%'};
  glm::vec3 tr3{std::nanf("nanx"),std::nanf("nany"),std::nanf("nanz")};
  glm::vec3 tr4{-123213.35435,-124324554.65878769,-5436464.3254654};

  QCOMPARE(Obj->getRotation().x, float{0.f});
  QCOMPARE(Obj->getRotation().y, float{0.f});
  QCOMPARE(Obj->getRotation().z, float{0.f});

  Obj->setRotation(tr1);
  QCOMPARE(Obj->getRotation().x, float{0.f});
  QCOMPARE(Obj->getRotation().y, float{0.f});
  QCOMPARE(Obj->getRotation().z, float{0.f});

  Obj->setRotation(tr2);
  QCOMPARE(Obj->getRotation().x, tr2.x);
  QCOMPARE(Obj->getRotation().y, tr2.y);
  QCOMPARE(Obj->getRotation().z, tr2.z);

  Obj->setRotation(tr3);
  QEXPECT_FAIL("","Check nanX",Continue);
  QCOMPARE(Obj->getRotation().x, tr3.x);
  QEXPECT_FAIL("","Check nanY",Continue);
  QCOMPARE(Obj->getRotation().y, tr3.y);
  QEXPECT_FAIL("","Check nanZ",Continue);
  QCOMPARE(Obj->getRotation().z, tr3.z);
  Obj->reset();

  Obj->setRotation(tr4);
  QCOMPARE(Obj->getRotation().x, tr4.x);
  QCOMPARE(Obj->getRotation().y, tr4.y);
  QCOMPARE(Obj->getRotation().z, tr4.z);

  Obj->setRotation(glm::vec3{0,0,0});
  QCOMPARE(Obj->getRotation().x, float{0.f});
  QCOMPARE(Obj->getRotation().y, float{0.f});
  QCOMPARE(Obj->getRotation().z, float{0.f});

  Obj->reset();
}

void testSceneObject::test_scaleObject ()
{
  glm::vec3 tr1{0,0,0};
  glm::vec3 tr2{'@','#','%'};
  glm::vec3 tr3{std::nanf("nanx"),std::nanf("nany"),std::nanf("nanz")};
  glm::vec3 tr4{-123213.35435,-124324554.65878769,-5436464.3254654};
  glm::vec3 original = Obj->getScale();

  QCOMPARE(Obj->getScale().x, float{0.f});
  QCOMPARE(Obj->getScale().y, float{0.f});
  QCOMPARE(Obj->getScale().z, float{0.f});

  Obj->scaleObject(tr1);
  QCOMPARE(Obj->getScale().x, float{0.f});
  QCOMPARE(Obj->getScale().y, float{0.f});
  QCOMPARE(Obj->getScale().z, float{0.f});

  Obj->scaleObject(tr2);
  QCOMPARE(Obj->getScale().x, original.x+tr2.x);
  QCOMPARE(Obj->getScale().y, original.y+tr2.y);
  QCOMPARE(Obj->getScale().z, original.z+tr2.z);
  original+=tr2;

  Obj->scaleObject(tr3);
  QEXPECT_FAIL("","Check nanX",Continue);
  QCOMPARE(Obj->getScale().x, original.x+tr3.x);
  QEXPECT_FAIL("","Check nanY",Continue);
  QCOMPARE(Obj->getScale().y, original.y+tr3.y);
  QEXPECT_FAIL("","Check nanZ",Continue);
  QCOMPARE(Obj->getScale().z, original.z+tr3.z);
  Obj->reset();
  Obj->scaleObject(original);

  Obj->scaleObject(tr4);
  QCOMPARE(Obj->getScale().x, original.x+tr4.x);
  QCOMPARE(Obj->getScale().y, original.y+tr4.y);
  QCOMPARE(Obj->getScale().z, original.z+tr4.z);
  original+=tr4;

  Obj->scaleObject(-original);
  QCOMPARE(Obj->getScale().x, float{0.f});
  QCOMPARE(Obj->getScale().y, float{0.f});
  QCOMPARE(Obj->getScale().z, float{0.f});

  Obj->reset();
}

void testSceneObject::test_setScale ()
{
  glm::vec3 tr1{0,0,0};
  glm::vec3 tr2{'@','#','%'};
  glm::vec3 tr3{std::nanf("nanx"),std::nanf("nany"),std::nanf("nanz")};
  glm::vec3 tr4{-123213.35435,-124324554.65878769,-5436464.3254654};

  QCOMPARE(Obj->getScale().x, float{0.f});
  QCOMPARE(Obj->getScale().y, float{0.f});
  QCOMPARE(Obj->getScale().z, float{0.f});

  Obj->setScale(tr1);
  QCOMPARE(Obj->getScale().x, float{0.f});
  QCOMPARE(Obj->getScale().y, float{0.f});
  QCOMPARE(Obj->getScale().z, float{0.f});

  Obj->setScale(tr2);
  QCOMPARE(Obj->getScale().x, tr2.x);
  QCOMPARE(Obj->getScale().y, tr2.y);
  QCOMPARE(Obj->getScale().z, tr2.z);

  Obj->setScale(tr3);
  QEXPECT_FAIL("","Check nanX",Continue);
  QCOMPARE(Obj->getScale().x, tr3.x);
  QEXPECT_FAIL("","Check nanY",Continue);
  QCOMPARE(Obj->getScale().y, tr3.y);
  QEXPECT_FAIL("","Check nanZ",Continue);
  QCOMPARE(Obj->getScale().z, tr3.z);
  Obj->reset();

  Obj->setScale(tr4);
  QCOMPARE(Obj->getScale().x, tr4.x);
  QCOMPARE(Obj->getScale().y, tr4.y);
  QCOMPARE(Obj->getScale().z, tr4.z);

  Obj->setScale(glm::vec3{0,0,0});
  QCOMPARE(Obj->getScale().x, float{0.f});
  QCOMPARE(Obj->getScale().y, float{0.f});
  QCOMPARE(Obj->getScale().z, float{0.f});

  Obj->reset();
}

void testSceneObject::test_getPosition ();
void testSceneObject::test_getRotation ();
void testSceneObject::test_getScale ();
void testSceneObject::test_setActive();
void testSceneObject::test_isActive();
void testSceneObject::test_updateMatrix();
void testSceneObject::test_getMVmatrix();
void testSceneObject::test_setGeo();
void testSceneObject::test_setMat();
void testSceneObject::test_getGeoID();
void testSceneObject::test_getGeoName();
void testSceneObject::test_getMatID();
void testSceneObject::test_getMatName();
