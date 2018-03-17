#include <QtTest/QtTest>
#include "mock/TestMat.h"

class testMaterial : public QObject
{
    Q_OBJECT
private:
  TestMat Mat;
private Q_SLOTS:
    void setName();
};
