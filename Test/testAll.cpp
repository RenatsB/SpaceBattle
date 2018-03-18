#include "testMaterial.cpp"
#include "testMesh.cpp"
#include "testSceneObject.cpp"
#include "testDataContainer.cpp"
#include "testObjectManager.cpp"

#define MAT_TEST
//#define GEO_TEST
//#define SO_TEST
//#define DATAC_TEST
//#define OBJMGR_TEST

#ifdef MAT_TEST
  QTEST_APPLESS_MAIN(testMaterial)
  #include "moc/testMaterial.moc"
#endif

#ifdef GEO_TEST
  QTEST_APPLESS_MAIN(testMesh)
  #include "moc/testMesh.moc"
#endif

/*#ifdef SO_TEST
  QTEST_APPLESS_MAIN(testSceneObject)
  #include "moc/testSceneObject.moc"
#endif

#ifdef DATAC_TEST
  QTEST_APPLESS_MAIN(testDataContainer)
  #include "moc/testDataContainer.moc"
#endif

#ifdef OBJMGR_TEST
  QTEST_APPLESS_MAIN(testObjectManager)
  #include "moc/testObjectManager.moc"
#endif*/
