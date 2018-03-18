#include <QtTest/QtTest>

class testMaterial : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void test_setName();
  void test_setID();
  void test_getName();
  void test_getID();
private:
  void setName(std::string _new);
  std::string getName() const;
  void setID(size_t _new);
  size_t getID() const;
private:
  std::string m_name="";
  size_t m_id=0;
};

void testMaterial::setName(std::string _new)
{
  m_name = _new;
}

std::string testMaterial::getName() const
{
  return m_name;
}

void testMaterial::setID(size_t _new)
{
  m_id = _new;
}

size_t testMaterial::getID() const
{
  return m_id;
}

void testMaterial::test_setName()
{
  std::string str0  = "Name";
  std::string str1  = "";
  std::string str2  = std::string{'\n'};
  std::string str3  = std::string{"\b"};
  double      numn  = std::nan("cookie");
  std::string str4  = std::string{std::to_string(numn)};

  QCOMPARE(getName(), std::string{""});
  setName(str0);
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(getName(), str1);
  QCOMPARE(getName(), str0);
  setName(str1);
  QCOMPARE(getName(), str1);
  setName(str2);
  QEXPECT_FAIL("","Passing a newline",Continue);
  QCOMPARE(getName(), std::string{"\n"});
  setName(str3);
  QCOMPARE(getName(), std::string{"\b"});
  setName(str4);
  QEXPECT_FAIL("","Passed stringified nan",Continue);
  QCOMPARE(getName(), std::string{"cookie"});
}

void testMaterial::test_setID()
{
  unsigned long num0 = 0;
  char        num1  = '\n';
  float       num2  = 0.45f;
  int         num3  = 12225;
  bool        num4  = false;
  //void*       num5  = NULL;
  unsigned long num5 = '@';
  double      num6  = std::nan("nan");

  QCOMPARE(getID(), num0);
  setID(num1);
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(getID(), static_cast<unsigned long>(num0));
  QCOMPARE(getID(), static_cast<unsigned long>(num1));
  setID(num2);
  QCOMPARE(getID(), static_cast<unsigned long>(num2));
  setID(num3);
  QCOMPARE(getID(), static_cast<unsigned long>(num3));
  setID(num4);
  QCOMPARE(getID(), static_cast<unsigned long>(num4));
  setID(num5);
  QEXPECT_FAIL("","Passing a at char",Continue);
  QCOMPARE(getID(), num5);
  setID(num6);
  QEXPECT_FAIL("","Passing nan value nan",Continue);
  QCOMPARE(getID(), static_cast<unsigned long>(num6));
}

void testMaterial::test_getName()
{
  std::string stored = "";

  std::string str0 = "Name";
  std::string str1 = "";
  std::string str2 = std::string{'\n'};
  std::string str3 = std::string{"\b"};
  double      numn = std::nan("nani");
  std::string str4 = std::string{std::to_string(numn)};

  stored = getName();
  QCOMPARE(stored, std::string{""});
  setName(str0);
  stored = getName();
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(stored, str1);
  QCOMPARE(stored, str0);
  setName(str1);
  stored = getName();
  QCOMPARE(stored, str1);
  setName(str2);
  stored = getName();
  QEXPECT_FAIL("","Passing a newline",Continue);
  QCOMPARE(stored, std::string{"\n"});
  setName(str3);
  stored = getName();
  QCOMPARE(stored, std::string{"\b"});
  setName(str4);
  stored = getName();
  QEXPECT_FAIL("","Passed stringified nan",Continue);
  QCOMPARE(stored, std::string{"nani"});
}

void testMaterial::test_getID()
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

  stored = getID();
  QCOMPARE(stored, num0);
  setID(num1);
  stored = getID();
  QEXPECT_FAIL("","Checking against previous value",Continue);
  QCOMPARE(stored, static_cast<unsigned long>(num0));
  QCOMPARE(stored, static_cast<unsigned long>(num1));
  setID(num2);
  stored = getID();
  QCOMPARE(stored, static_cast<unsigned long>(num2));
  setID(num3);
  stored = getID();
  QCOMPARE(stored, static_cast<unsigned long>(num3));
  setID(num4);
  stored = getID();
  QCOMPARE(stored, static_cast<unsigned long>(num4));
  setID(num5);
  stored = getID();
  QEXPECT_FAIL("","Passing an at char",Continue);
  QCOMPARE(stored, num5);
  setID(num6);
  stored = getID();
  QEXPECT_FAIL("","Passing a nan value nano",Continue);
  QCOMPARE(stored, static_cast<unsigned long>(num6));
}
