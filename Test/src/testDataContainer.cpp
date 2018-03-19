#include <QtTest/QtTest>
#include "mockDataContainer.h"

class testObjectManager : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void matSize();
  void geosize();
  void geoFindByID();
  void geoFindByName();
  void matFindByID();
  void matFindByName();
  void matPut();
  void matPutWithName();
  void geoPut();
  void geoPutWithName();
  void matRemoveByID();
  void matRemoveByName();
  void geoRemoveByID();
  void geoRemoveByName();
  void setGeoName();
  void setMatName();
  void getMatName();
  void getGeoName();
  void getGeoNames();
  void getMatNames();
  void getMatID();
  void getGeoID();
  void checkGeoIDs();
  void checkMatIDs();
  void getFreeGeoID();
  void getFreeMatID();
  void getCurrentGeoIDs();
  void getCurrentMatIDs();
  void checkMatNames();
  void checkGeoNames();
private:
  std::unique_ptr<mockDataContainer> Data = static_cast<std::unique_ptr<mockDataContainer>>(new mockDataContainer());
};
void testObjectManager::matSize()
{
  QCOMPARE(Data->matSize(), static_cast<size_t>(0));
  Data->matPut(new mockMatGeo(), "Mat1");
  QCOMPARE(Data->matSize(), static_cast<size_t>(1));
  Data->matPut(new mockMatGeo(), "Mat2");
  Data->matPut(new mockMatGeo(), "Mat3");
  QCOMPARE(Data->matSize(), static_cast<size_t>(3));
  Data->matRemove("Mat1");
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(Data->matSize(), static_cast<size_t>(3));
  Data->matRemove("Mat2");
  Data->matRemove("Mat3");
}

void testObjectManager::geosize()
{
  QCOMPARE(Data->geosize(), static_cast<size_t>(0));
  Data->geoPut(new mockMatGeo(), "Mat1");
  QCOMPARE(Data->geosize(), static_cast<size_t>(1));
  Data->geoPut(new mockMatGeo(), "Mat2");
  Data->geoPut(new mockMatGeo(), "Mat3");
  QCOMPARE(Data->geosize(), static_cast<size_t>(3));
  Data->geoRemove("Mat1");
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(Data->geosize(), static_cast<size_t>(3));
  Data->geoRemove("Mat2");
  Data->geoRemove("Mat3");
}

void testObjectManager::geoFindByID()
{
  size_t testID1 = 1;
  //since IDs are assigned automatically, the bottom ones will not work
  size_t testID2 = '@';
  size_t testID3 = 9999;
  std::pair<size_t, std::string> testPair{0,""};
  Data->geoPut(new mockMatGeo(), "GeoID1");
  Data->geoPut(new mockMatGeo(), "GeoID2");
  Data->geoPut(new mockMatGeo(), "GeoID3");
  QEXPECT_FAIL("","Checking against ID1",Continue);
  QCOMPARE(Data->geoFind(testID1), nullptr);
  QCOMPARE(Data->geoFind(testID2), nullptr);
  QCOMPARE(Data->geoFind(testID3), nullptr);
  Data->geoRemove("GeoID1");
  Data->geoRemove("GeoID2");
  Data->geoRemove("GeoID3");
}

void testObjectManager::geoFindByName()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->geoPut(new mockMatGeo(), name1);
  Data->geoPut(new mockMatGeo(), name2);
  Data->geoPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->geoFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->geoFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->geoFind(name3), nullptr);
  QCOMPARE(Data->geoFind(name4), nullptr);
  Data->geoRemove(name1);
  Data->geoRemove(name2);
  Data->geoRemove(name3);
}

void testObjectManager::matFindByID()
{
  size_t testID1 = 1;
  //since IDs are assigned automatically, the bottom ones will not work
  size_t testID2 = '@';
  size_t testID3 = 9999;
  std::pair<size_t, std::string> testPair{0,""};
  Data->matPut(new mockMatGeo(), "MatID1");
  Data->matPut(new mockMatGeo(), "MatID2");
  Data->matPut(new mockMatGeo(), "MatID3");
  QEXPECT_FAIL("","Checking against ID1",Continue);
  QCOMPARE(Data->matFind(testID1), nullptr);
  QCOMPARE(Data->matFind(testID2), nullptr);
  QCOMPARE(Data->matFind(testID3), nullptr);
  Data->matRemove("GeoID1");
  Data->matRemove("GeoID2");
  Data->matRemove("GeoID3");
}

void testObjectManager::matFindByName()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->matPut(new mockMatGeo(), name1);
  Data->matPut(new mockMatGeo(), name2);
  Data->matPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->matFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->matFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->matFind(name3), nullptr);
  QCOMPARE(Data->matFind(name4), nullptr);
  Data->matRemove(name1);
  Data->matRemove(name2);
  Data->matRemove(name3);
}

void testObjectManager::matPut()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->matPut(new mockMatGeo(), name1);
  Data->matPut(new mockMatGeo(), name2);
  Data->matPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->matFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->matFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->matFind(name3), nullptr);
  QCOMPARE(Data->matFind(name4), nullptr);
  Data->matRemove(name1);
  Data->matRemove(name2);
  Data->matRemove(name3);
}

void testObjectManager::matPutWithName()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->matPut(new mockMatGeo(), name1);
  Data->matPut(new mockMatGeo(), name2);
  Data->matPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->matFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->matFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->matFind(name3), nullptr);
  QCOMPARE(Data->matFind(name4), nullptr);
  Data->matRemove(name1);
  Data->matRemove(name2);
  Data->matRemove(name3);
}

void testObjectManager::geoPut()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->geoPut(new mockMatGeo(), name1);
  Data->geoPut(new mockMatGeo(), name2);
  Data->geoPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->geoFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->geoFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->geoFind(name3), nullptr);
  QCOMPARE(Data->geoFind(name4), nullptr);
  Data->geoRemove(name1);
  Data->geoRemove(name2);
  Data->geoRemove(name3);
}

void testObjectManager::geoPutWithName()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->geoPut(new mockMatGeo(), name1);
  Data->geoPut(new mockMatGeo(), name2);
  Data->geoPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->geoFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->geoFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->geoFind(name3), nullptr);
  QCOMPARE(Data->geoFind(name4), nullptr);
  Data->geoRemove(name1);
  Data->geoRemove(name2);
  Data->geoRemove(name3);
}

void testObjectManager::matRemoveByID()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->matPut(new mockMatGeo(), name1);
  Data->matPut(new mockMatGeo(), name2);
  Data->matPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->matFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->matFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->matFind(name3), nullptr);
  QCOMPARE(Data->matFind(name4), nullptr);
  Data->matRemove(name1);
  Data->matRemove(name2);
  Data->matRemove(name3);
}

void testObjectManager::matRemoveByName()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->matPut(new mockMatGeo(), name1);
  Data->matPut(new mockMatGeo(), name2);
  Data->matPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->matFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->matFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->matFind(name3), nullptr);
  QCOMPARE(Data->matFind(name4), nullptr);
  Data->matRemove(name1);
  Data->matRemove(name2);
  Data->matRemove(name3);
}

void testObjectManager::geoRemoveByID()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->geoPut(new mockMatGeo(), name1);
  Data->geoPut(new mockMatGeo(), name2);
  Data->geoPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->geoFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->geoFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->geoFind(name3), nullptr);
  QCOMPARE(Data->geoFind(name4), nullptr);
  Data->geoRemove(name1);
  Data->geoRemove(name2);
  Data->geoRemove(name3);
}

void testObjectManager::geoRemoveByName()
{
  std::string name1 = "Test1";
  std::string name2 = "Test2";
  std::string name3 = "Test3";
  std::string name4 = "DoesNotExist";
  Data->geoPut(new mockMatGeo(), name1);
  Data->geoPut(new mockMatGeo(), name2);
  Data->geoPut(new mockMatGeo(), name3);
  QEXPECT_FAIL("","Checking against name1",Continue);
  QCOMPARE(Data->geoFind(name1), nullptr);
  QEXPECT_FAIL("","Checking against name2",Continue);
  QCOMPARE(Data->geoFind(name2), nullptr);
  QEXPECT_FAIL("","Checking against name3",Continue);
  QCOMPARE(Data->geoFind(name3), nullptr);
  QCOMPARE(Data->geoFind(name4), nullptr);
  Data->geoRemove(name1);
  Data->geoRemove(name2);
  Data->geoRemove(name3);
}

void testObjectManager::setGeoName()
{
  Data->geoPut(new mockMatGeo(), "TestJ");
  QEXPECT_FAIL("","Checking against first value",Continue);
  QCOMPARE(Data->geoFind("TestJ"), nullptr);
  Data->setGeoName(0, "NewName");
  QCOMPARE(Data->geoFind("TestJ"), nullptr);
  QEXPECT_FAIL("","Checking against new value",Continue);
  QCOMPARE(Data->geoFind("NewName"), nullptr);
  Data->geoRemove(0);
}

void testObjectManager::setMatName()
{
  Data->matPut(new mockMatGeo(), "TestJ");
  QEXPECT_FAIL("","Checking against first value",Continue);
  QCOMPARE(Data->matFind("TestJ"), nullptr);
  Data->setMatName(0, "NewName");
  QCOMPARE(Data->matFind("TestJ"), nullptr);
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(Data->matFind("NewName"), nullptr);
  Data->matRemove(0);
}

void testObjectManager::getMatName()
{
  Data->matPut(new mockMatGeo(), "TestK");
  QEXPECT_FAIL("","Checking against first value",Continue);
  QCOMPARE(Data->matFind("TestK"), nullptr);
  Data->setMatName(0, "NewName");
  QCOMPARE(Data->matFind("TestK"), nullptr);
  QEXPECT_FAIL("","Checking against last value",Continue);
  QCOMPARE(Data->matFind("NewName"), nullptr);
  Data->matRemove(0);
}

void testObjectManager::getGeoName()
{
  Data->geoPut(new mockMatGeo(), "TestK");
  QEXPECT_FAIL("","Checking against first value",Continue);
  QCOMPARE(Data->geoFind("TestK"), nullptr);
  Data->setGeoName(0, "NewName");
  QCOMPARE(Data->geoFind("TestK"), nullptr);
  QEXPECT_FAIL("","Checking against last value",Continue);
  QCOMPARE(Data->geoFind("NewName"), nullptr);
  Data->geoRemove(0);
}

void testObjectManager::getGeoNames()
{
  Data->geoPut(new mockMatGeo(), "TestL1");
  Data->geoPut(new mockMatGeo(), "TestL2");
  Data->geoPut(new mockMatGeo(), "TestL3");
  Data->geoPut(new mockMatGeo(), "TestL4");
  std::vector<std::string> geoNames = Data->getGeoNames();
  QCOMPARE(geoNames.at(0), std::string{"TestL1"});
  QCOMPARE(geoNames.at(1), std::string{"TestL2"});
  QCOMPARE(geoNames.at(2), std::string{"TestL3"});
  QCOMPARE(geoNames.at(3), std::string{"TestL4"});
  Data->geoRemove(0);
  Data->geoRemove(1);
  Data->geoRemove(2);
  Data->geoRemove(3);
}

void testObjectManager::getMatNames()
{
  Data->matPut(new mockMatGeo(), "TestM1");
  Data->matPut(new mockMatGeo(), "TestM2");
  Data->matPut(new mockMatGeo(), "TestM3");
  Data->matPut(new mockMatGeo(), "TestM4");
  std::vector<std::string> matNames = Data->getMatNames();
  QCOMPARE(matNames.at(0), std::string{"TestM1"});
  QCOMPARE(matNames.at(1), std::string{"TestM2"});
  QCOMPARE(matNames.at(2), std::string{"TestM3"});
  QCOMPARE(matNames.at(3), std::string{"TestM4"});
  Data->matRemove(0);
  Data->matRemove(1);
  Data->matRemove(2);
  Data->matRemove(3);
}

void testObjectManager::getMatID()
{
  Data->matPut(new mockMatGeo(), "TestN1");
  Data->matPut(new mockMatGeo(), "TestN2");
  Data->matPut(new mockMatGeo(), "TestN3");
  QCOMPARE(Data->getMatID("TestN1"), static_cast<size_t>(0));
  QCOMPARE(Data->getMatID("TestN2"), static_cast<size_t>(1));
  QCOMPARE(Data->getMatID("TestN3"), static_cast<size_t>(2));
  Data->matRemove(0);
  Data->matRemove(1);
  Data->matRemove(2);
}

void testObjectManager::getGeoID()
{
  Data->geoPut(new mockMatGeo(), "TestN1");
  Data->geoPut(new mockMatGeo(), "TestN2");
  Data->geoPut(new mockMatGeo(), "TestN3");
  QCOMPARE(Data->getGeoID("TestN1"), static_cast<size_t>(0));
  QCOMPARE(Data->getGeoID("TestN2"), static_cast<size_t>(1));
  QCOMPARE(Data->getGeoID("TestN3"), static_cast<size_t>(2));
  Data->geoRemove(0);
  Data->geoRemove(1);
  Data->geoRemove(2);
}

void testObjectManager::checkIDs()
{
  Data->geoPut(new mockMatGeo(), "TestO1");
  Data->geoPut(new mockMatGeo(), "TestO2");
  Data->geoPut(new mockMatGeo(), "TestO3");
  Data->geoRemove(1);
  Data->geoPut(new mockMatGeo(), "TestO4");
  QCOMPARE(Data->getGeoID("TestO1"), static_cast<size_t>(0));
  QCOMPARE(Data->getGeoName(0), std::string{"TestO1"});
  QEXPECT_FAIL("","Checking deleted/ refilled cell",Continue);
  QCOMPARE(Data->getGeoName(1), std::string{"TestO2"});
  QCOMPARE(Data->getGeoID("TestO4"), static_cast<size_t>(1));
  QCOMPARE(Data->getGeoName(1), std::string{"TestO4"});
  QCOMPARE(Data->getGeoID("TestO3"), static_cast<size_t>(2));
  QCOMPARE(Data->getGeoName(0), std::string{"TestO3"});
  Data->geoRemove(0);
  Data->geoRemove(1);
  Data->geoRemove(2);
}

void testObjectManager::checkGeoIDs()
{
  Data->geoPut(new mockMatGeo(), "TestO1");
  Data->geoPut(new mockMatGeo(), "TestO2");
  Data->geoPut(new mockMatGeo(), "TestO3");
  Data->geoRemove(1);
  Data->geoPut(new mockMatGeo(), "TestO4");
  QCOMPARE(Data->getGeoID("TestO1"), static_cast<size_t>(0));
  QCOMPARE(Data->getGeoName(0), std::string{"TestO1"});
  QEXPECT_FAIL("","Checking deleted/ refilled cell",Continue);
  QCOMPARE(Data->getGeoName(1), std::string{"TestO2"});
  QCOMPARE(Data->getGeoID("TestO4"), static_cast<size_t>(1));
  QCOMPARE(Data->getGeoName(1), std::string{"TestO4"});
  QCOMPARE(Data->getGeoID("TestO3"), static_cast<size_t>(2));
  QCOMPARE(Data->getGeoName(0), std::string{"TestO3"});
  Data->geoRemove(0);
  Data->geoRemove(1);
  Data->geoRemove(2);
}

void testObjectManager::checkMatIDs()
{
  Data->matPut(new mockMatGeo(), "TestO1");
  Data->matPut(new mockMatGeo(), "TestO2");
  Data->matPut(new mockMatGeo(), "TestO3");
  Data->matRemove(1);
  Data->matPut(new mockMatGeo(), "TestO4");
  QCOMPARE(Data->getMatID("TestO1"), static_cast<size_t>(0));
  QCOMPARE(Data->getMatName(0), std::string{"TestO1"});
  QEXPECT_FAIL("","Checking deleted/ refilled cell",Continue);
  QCOMPARE(Data->getMatName(1), std::string{"TestO2"});
  QCOMPARE(Data->getMatID("TestO4"), static_cast<size_t>(1));
  QCOMPARE(Data->getMatName(1), std::string{"TestO4"});
  QCOMPARE(Data->getMatID("TestO3"), static_cast<size_t>(2));
  QCOMPARE(Data->getMatName(0), std::string{"TestO3"});
  Data->matRemove(0);
  Data->matRemove(1);
  Data->matRemove(2);
}

void testObjectManager::getFreeGeoID()
{
  Data->geoPut(new mockMatGeo(), "TestO1");
  Data->geoPut(new mockMatGeo(), "TestO2");
  Data->geoPut(new mockMatGeo(), "TestO3");
  Data->geoRemove(1);
  QCOMPARE(Data->getFreeGeoID(), static_cast<size_t>(1));
  Data->geoPut(new mockMatGeo(), "TestO4");
  QEXPECT_FAIL("","Checking deleted/ refilled cell",Continue);
  QCOMPARE(Data->getFreeGeoID(), static_cast<size_t>(1));
  QCOMPARE(Data->getFreeGeoID(), static_cast<size_t>(3));
  Data->geoRemove(0);
  Data->geoRemove(1);
  Data->geoRemove(2);
}

void testObjectManager::getFreeMatID()
{
  Data->matPut(new mockMatGeo(), "TestO1");
  Data->matPut(new mockMatGeo(), "TestO2");
  Data->matPut(new mockMatGeo(), "TestO3");
  Data->matRemove(1);
  QCOMPARE(Data->getFreeMatID(), static_cast<size_t>(1));
  Data->matPut(new mockMatGeo(), "TestO4");
  QEXPECT_FAIL("","Checking deleted/ refilled cell",Continue);
  QCOMPARE(Data->getFreeMatID(), static_cast<size_t>(1));
  QCOMPARE(Data->getFreeMatID(), static_cast<size_t>(3));
  Data->matRemove(0);
  Data->matRemove(1);
  Data->matRemove(2);
}

void testObjectManager::getCurrentGeoIDs()
{
  Data->matPut(new mockMatGeo(), "TestO1");
  Data->matPut(new mockMatGeo(), "TestO2");
  Data->matPut(new mockMatGeo(), "TestO3");
  Data->matRemove(1);
  QCOMPARE(Data->getFreeMatID(), static_cast<size_t>(1));
  Data->matPut(new mockMatGeo(), "TestO4");
  QEXPECT_FAIL("","Checking deleted/ refilled cell",Continue);
  QCOMPARE(Data->getFreeMatID(), static_cast<size_t>(1));
  QCOMPARE(Data->getFreeMatID(), static_cast<size_t>(3));
  Data->matRemove(0);
  Data->matRemove(1);
  Data->matRemove(2);
}

void testObjectManager::getCurrentMatIDs()
{
  Data->matPut(new mockMatGeo(), "TestP1");
  Data->matPut(new mockMatGeo(), "TestP2");
  Data->matPut(new mockMatGeo(), "TestP3");
  std::vector<size_t> current = Data->getCurrentMatIDs();
  QCOMPARE(current.at(0), static_cast<size_t>(0));
  QCOMPARE(current.at(1), static_cast<size_t>(0));
  QCOMPARE(current.at(2), static_cast<size_t>(0));
  Data->matRemove(0);
  Data->matRemove(1);
  Data->matRemove(2);
}

void testObjectManager::checkMatNames()
{
  Data->matPut(new mockMatGeo(), "TestQ");
  Data->matPut(new mockMatGeo(), "TestQ");
  Data->matPut(new mockMatGeo(), "TestQ");
  Data->checkMatNames();
  QEXPECT_FAIL("","Checking against starting values",Continue);
  QCOMPARE(Data->getMatName(0), std::string{"TestQ"});
  QCOMPARE(Data->getMatName(0), std::string{"TestQ1"});
  QCOMPARE(Data->getMatName(0), std::string{"TestQ2"});
  QCOMPARE(Data->getMatName(0), std::string{"TestQ3"});
  Data->matRemove(0);
  Data->matRemove(1);
  Data->matRemove(2);
}

void testObjectManager::checkGeoNames()
{
  Data->geoPut(new mockMatGeo(), "TestQ");
  Data->geoPut(new mockMatGeo(), "TestQ");
  Data->geoPut(new mockMatGeo(), "TestQ");
  Data->checkGeoNames();
  QEXPECT_FAIL("","Checking against starting values",Continue);
  QCOMPARE(Data->getGeoName(0), std::string{"TestQ"});
  QCOMPARE(Data->getGeoName(0), std::string{"TestQ1"});
  QCOMPARE(Data->getGeoName(0), std::string{"TestQ2"});
  QCOMPARE(Data->getGeoName(0), std::string{"TestQ3"});
  Data->geoRemove(0);
  Data->geoRemove(1);
  Data->geoRemove(2);
}
