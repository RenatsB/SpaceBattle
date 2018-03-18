#include <QtTest/QtTest>
#include "mockObjectManager.cpp"

class testObjectManager : public QObject
{
  Q_OBJECT
private:
  std::unique_ptr<mockObjectManager> ObjMgr;
private Q_SLOTS:
  void test_constructA();
};
