#include <QtTest/QtTest>
#include "mockObjectManager.h"

class testObjectManager : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void createSceneObjectFull();
  void createSceneObjectSimple();
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
void testObjectManager::createSceneObjectFull()
{

}

void testObjectManager::createSceneObjectSimple()
{

}

void testObjectManager::selectObjectByID()
{

}

void testObjectManager::selectObjectByName()
{

}

void testObjectManager::selectObjectsByIDs()
{

}

void testObjectManager::selectObjectsByNames()
{

}

void testObjectManager::deselectObjectByID()
{

}

void testObjectManager::deselectObjectByName()
{

}

void testObjectManager::deselectObjectsByIDs()
{

}

void testObjectManager::deselectObjectsByNames()
{

}

void testObjectManager::isSelectedByID()
{

}

void testObjectManager::isSelectedByName()
{

}

void testObjectManager::move()
{

}

void testObjectManager::scale()
{

}

void testObjectManager::rotate()
{

}

void testObjectManager::constructTranslateVector()
{

}

void testObjectManager::changeGeo()
{

}

void testObjectManager::changeMat()
{

}

void testObjectManager::objectAt()
{

}

void testObjectManager::findObjectByID()
{

}

void testObjectManager::findObjectByName()
{

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
