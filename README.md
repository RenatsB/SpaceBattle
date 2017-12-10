# Programming Paradigms 2017-2018
# OO Design and Programming Assignment
# Generation of densely populated scenes

This project is using NGL and GoogleTest

NGLScene is taken from :
<<https://github.com/NCCA/Instancing/blob/master/InstanceMeshes/include/NGLScene.h>>
with added modifications.
Also includes:
NGLSceneMouseControls.cpp
WindowParams.h

Instead of keeping geometry and texture data within
the object class, it is kept seperately and system relies on IDs
to get the corresponding data.

Object placement and creation can either be done automatically
or manually using a simple GUI.

Mock objects included for testing.

