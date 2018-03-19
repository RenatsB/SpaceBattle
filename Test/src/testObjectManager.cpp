#include <QtTest/QtTest>
#include "mockObjectManager.h"

class testObjectManager : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void createSceneObjectSimple();
  void removeObjectByID();
  void removeObjectByName();
  void selectObjectByID();
  void selectObjectByName();
  void selectObjectsByIDs();
  void selectObjectsByNames();
  void deselectObjectByID();
  void deselectObjectByName();
  void deselectObjectsByIDs();
  void deselectObjectsByNames();
  void isSelectedByID();
  void isSelectedByName();
  void move();
  void scale();
  void rotate();
  void constructTranslateVector();
  void changeGeo();
  void changeMat();
  void objectAt();
  void findObjectByID();
  void findObjectByName();
  void getObjectByID();
  void getObjectByName();
  void getObjectID();
  void getObjectCount();
  void checkObjectIDs();
  void getFreeID();
  void getCurrentIDs();
private:
  std::unique_ptr<mockObjectManager> ObjMgr;
};

void testObjectManager::createSceneObjectSimple()
{
  ObjMgr->createObject("TestA");
  QCOMPARE(ObjMgr->getObjectCount(), static_cast<size_t>(1));
  ObjMgr->removeObject("TestA");
}

void testObjectManager::removeObjectByID()
{
  ObjMgr->createObject("TestA");
  QCOMPARE(ObjMgr->getObjectCount(), static_cast<size_t>(1));
  ObjMgr->removeObject(0);
}

void testObjectManager::removeObjectByName()
{
  ObjMgr->createObject("TestA");
  QCOMPARE(ObjMgr->getObjectCount(), static_cast<size_t>(1));
  ObjMgr->removeObject("TestA");
}

void testObjectManager::selectObjectByID()
{
  ObjMgr->createObject("TestA");
  ObjMgr->createObject("TestB");
  ObjMgr->selectObject(0);
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(ObjMgr->isSelected(1), true);
  QCOMPARE(ObjMgr->isSelected(0), true);
  ObjMgr->removeObject("TestA");
  ObjMgr->removeObject("TestB");
}

void testObjectManager::selectObjectByName()
{
  ObjMgr->createObject("TestA");
  ObjMgr->createObject("TestB");
  ObjMgr->selectObject("TestA");
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(ObjMgr->isSelected("TestB"), true);
  QCOMPARE(ObjMgr->isSelected("TestA"), true);
  ObjMgr->removeObject("TestA");
  ObjMgr->removeObject("TestB");
}

void testObjectManager::selectObjectsByIDs()
{
  ObjMgr->createObject("TestC1");
  ObjMgr->createObject("TestC2");
  ObjMgr->selectObject(std::vector<size_t>{0,1});
  QCOMPARE(ObjMgr->isSelected("TestC1"), true);
  QCOMPARE(ObjMgr->isSelected("TestC2"), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::selectObjectsByNames()
{
  ObjMgr->createObject("TestC1");
  ObjMgr->createObject("TestC2");
  ObjMgr->selectObject(std::vector<std::string>{"TestC1","TestC2"});
  QCOMPARE(ObjMgr->isSelected("TestC1"), true);
  QCOMPARE(ObjMgr->isSelected("TestC2"), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::deselectObjectByID()
{
  ObjMgr->createObject("TestC1");
  ObjMgr->createObject("TestC2");
  ObjMgr->selectObject("");
  QCOMPARE(ObjMgr->isSelected("TestC1"), true);
  QCOMPARE(ObjMgr->isSelected("TestC2"), true);
  ObjMgr->deselectObject(0);
  QEXPECT_FAIL("","Checking first value after deselection",Continue);
  QCOMPARE(ObjMgr->isSelected(0), true);
  QCOMPARE(ObjMgr->isSelected(1), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::deselectObjectByName()
{
  ObjMgr->createObject("TestC1");
  ObjMgr->createObject("TestC2");
  ObjMgr->selectObject("");
  QCOMPARE(ObjMgr->isSelected("TestC1"), true);
  QCOMPARE(ObjMgr->isSelected("TestC2"), true);
  ObjMgr->deselectObject("TestC1");
  QEXPECT_FAIL("","Checking first value after deselection",Continue);
  QCOMPARE(ObjMgr->isSelected("TestC1"), true);
  QCOMPARE(ObjMgr->isSelected("TestC2"), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::deselectObjectsByIDs()
{
  ObjMgr->createObject("TestC1");
  ObjMgr->createObject("TestC2");
  ObjMgr->selectObject("");
  QCOMPARE(ObjMgr->isSelected("TestC1"), true);
  QCOMPARE(ObjMgr->isSelected("TestC2"), true);
  ObjMgr->deselectObject(std::vector<size_t>{0,1});
  QEXPECT_FAIL("","Checking first value after deselection",Continue);
  QCOMPARE(ObjMgr->isSelected("TestC1"), true);
  QEXPECT_FAIL("","Checking second value after deselection",Continue);
  QCOMPARE(ObjMgr->isSelected("TestC2"), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::deselectObjectsByNames()
{
  ObjMgr->createObject("TestC1");
  ObjMgr->createObject("TestC2");
  ObjMgr->selectObject("");
  QCOMPARE(ObjMgr->isSelected("TestC1"), true);
  QCOMPARE(ObjMgr->isSelected("TestC2"), true);
  ObjMgr->deselectObject(std::vector<std::string>{"TestC1","TestC2"});
  QEXPECT_FAIL("","Checking first value after deselection",Continue);
  QCOMPARE(ObjMgr->isSelected("TestC1"), true);
  QEXPECT_FAIL("","Checking second value after deselection",Continue);
  QCOMPARE(ObjMgr->isSelected("TestC2"), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::isSelectedByID()
{
  ObjMgr->createObject("TestD1");
  ObjMgr->createObject("TestD2");
  ObjMgr->selectObject(0);
  QEXPECT_FAIL("","Checking second non-selected value",Continue);
  QCOMPARE(ObjMgr->isSelected(1), true);
  QCOMPARE(ObjMgr->isSelected(0), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::isSelectedByName()
{
  ObjMgr->createObject("TestD1");
  ObjMgr->createObject("TestD2");
  ObjMgr->selectObject(0);
  QEXPECT_FAIL("","Checking second non-selected value",Continue);
  QCOMPARE(ObjMgr->isSelected("TestD2"), true);
  QCOMPARE(ObjMgr->isSelected("TestD1"), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::move()
{
  ObjMgr->createObject("TestEtransforms");
  QCOMPARE(ObjMgr->getObject(0)->getPosition().x, static_cast<float>(0.f));
  ObjMgr->selectObject(0);
  ObjMgr->move(0,4.f);
  QCOMPARE(ObjMgr->getObject(0)->getPosition().x, static_cast<float>(4.f));
  ObjMgr->deselectObject(0);
  ObjMgr->removeObject(0);
}

void testObjectManager::scale()
{
  ObjMgr->createObject("TestEtransforms");
  QCOMPARE(ObjMgr->getObject(0)->getScale().x, static_cast<float>(0.f));
  ObjMgr->selectObject(0);
  ObjMgr->scale(0,4.f);
  QCOMPARE(ObjMgr->getObject(0)->getScale().x, static_cast<float>(4.f));
  ObjMgr->deselectObject(0);
  ObjMgr->removeObject(0);
}

void testObjectManager::rotate()
{
  ObjMgr->createObject("TestEtransforms");
  QCOMPARE(ObjMgr->getObject(0)->getRotation().x, static_cast<float>(0.f));
  ObjMgr->selectObject(0);
  ObjMgr->rotate(0,4.f);
  QCOMPARE(ObjMgr->getObject(0)->getRotation().x, static_cast<float>(4.f));
  ObjMgr->deselectObject(0);
  ObjMgr->removeObject(0);
}

void testObjectManager::constructTranslateVector()
{
  glm::vec3 A = ObjMgr->constructTranslateVector(0, 3.f);
  QCOMPARE(A.x, static_cast<float>(3.f));
  glm::vec3 B = ObjMgr->constructTranslateVector(1, 15.f);
  QCOMPARE(B.y, static_cast<float>(15.f));
  glm::vec3 C = ObjMgr->constructTranslateVector(2, -38.f);
  QCOMPARE(C.z, static_cast<float>(-38.f));
}

void testObjectManager::changeGeo()
{
  std::pair<size_t, std::string> newGeo{3, "Cookie"};
  std::pair<size_t, std::string> original;
  ObjMgr->createObject("TestG");
  original.first = ObjMgr->objectAt(0)->getGeoID();
  original.second = ObjMgr->objectAt(0)->getGeoName();
  ObjMgr->objectAt(0)->setGeo(newGeo);
  QCOMPARE(ObjMgr->objectAt(0)->getGeoID(), newGeo.first);
  QCOMPARE(ObjMgr->objectAt(0)->getGeoName(), newGeo.second);
  ObjMgr->removeObject(0);
}

void testObjectManager::changeMat()
{
  std::pair<size_t, std::string> newMat{3, "Chocolate"};
  std::pair<size_t, std::string> original;
  ObjMgr->createObject("TestG");
  original.first = ObjMgr->objectAt(0)->getMatID();
  original.second = ObjMgr->objectAt(0)->getMatName();
  ObjMgr->objectAt(0)->setGeo(newMat);
  QCOMPARE(ObjMgr->objectAt(0)->getMatID(), newMat.first);
  QCOMPARE(ObjMgr->objectAt(0)->getMatName(), newMat.second);
  ObjMgr->removeObject(0);
}

void testObjectManager::objectAt()
{
  ObjMgr->createObject("TestH1");
  ObjMgr->createObject("TestH2");
  QCOMPARE(ObjMgr->objectAt(0)->getName(), std::string{"TestH1"});
  QCOMPARE(ObjMgr->objectAt(1)->getName(), std::string{"TestH2"});
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::findObjectByID()
{
  ObjMgr->createObject("TestI1");
  ObjMgr->createObject("TestI2");
  QEXPECT_FAIL("","Checking non-existent value",Continue);
  QCOMPARE(ObjMgr->findObject('@'), true);
  QCOMPARE(ObjMgr->findObject(0), true);
  QCOMPARE(ObjMgr->findObject(1), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::findObjectByName()
{
  ObjMgr->createObject("TestI1");
  ObjMgr->createObject("TestI2");
  QEXPECT_FAIL("","Checking non-existent value",Continue);
  QCOMPARE(ObjMgr->findObject("WheresMyCookie"), true);
  QCOMPARE(ObjMgr->findObject("TestI1"), true);
  QCOMPARE(ObjMgr->findObject("TestI2"), true);
  ObjMgr->removeObject(0);
  ObjMgr->removeObject(1);
}

void testObjectManager::getObjectByID()
{

}

void testObjectManager::getObjectByName()
{

}

void testObjectManager::getObjectID()
{

}

void testObjectManager::getObjectCount()
{

}

void testObjectManager::checkObjectIDs()
{

}

void testObjectManager::getFreeID()
{

}

void testObjectManager::getCurrentIDs()
{

}
