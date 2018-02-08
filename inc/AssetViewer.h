#ifndef ASSETVIEWER_H_
#define ASSETVIEWER_H_

#include "Scene.h"
#include "Utility.h"
#include "GUIModule.h"

class AssetViewer
{
public:
  AssetViewer()=default;
  ~AssetViewer();
  bool init();

private:
  Scene m_contents;
  GUIModule m_graphicalOutput;
};

#endif
