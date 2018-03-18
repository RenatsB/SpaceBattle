#include <QtTest/QtTest>
#include "mockSceneObject.cpp"

class testSceneObject : public QObject
{
  Q_OBJECT
private:
  std::unique_ptr<mockSceneObject> Obj = nullptr;
private Q_SLOTS:
  void test_setName();
  void test_setID();
  void test_getName();
  void test_getID();
};

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
