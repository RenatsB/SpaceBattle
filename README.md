# **MyLittleEditor**

A small scene graph/ scene object manager.
___

## **Content**
___
### 1. **[Introduction](#introduction)**
### 2. **[Library Prerequisites](#library-prerequisites)**
### 3. **[MLElib](#mlelib)**
### 4. **[Using The Library](#using-the-library)**
### 4. **[MLE Demo](#mylittleeditor-demo)**
### 5. **[Testing](#testing)**
### 6. **[Scene File Example](#scene-file-example)**
___

## **Introduction**

- MyLittleEditor is a project for my assignment to create a basic scene graph that would work as a library. It is coded in C++, with materials using json to pass shader names to the program.

- The current version includes a full functionality, demo included.

___

## **Library Prerequisites**
- Qt (QJson)
- GLM (Mat4, Vec3)
___

## **MLElib**

- **MyLittleEditor Library** is a small 3D preview and layouting tool, that requires no visualisation to work.
- It deals with Material and Geometry data using ID-Name pairs and virtual interface classes.
- It can load and save the scene object data (without Mesh nd Material data) to JSon.
- **Object Manager** deals with transformations, object storage, instantiation and read/write to file.
- **DataContainer** deals with geometric and material data storage and management using abstract classes as interfaces to more meaningful data.
- For more information refer to documentation
___

## **Using The Library**

- In the Project file add following lines, substituting path with appropriate:
```
INCLUDEPATH += <path>/MLElib/include
LIBS += -L<path>/MLElib -lMyLittleEditor

```
- Host material and geometry classes should inherit from BaseMaterial and BaseGeometry.
- In the module where you want to use this library, instantiate two members of type DataContainer and ObjectManager.
- Refer to documentation and code for more information.
___

## **MyLittleEditor Demo**

- **Demo** folder contains a working demo that uses nitronoid's OpenGLTemplate as a host.
- It includes a test runthrough with 1000 objects, using different meshes and materials, simple QT UI and basic controls.
- Load/save mechanism is also tested and **scenes** folder contains the example scene. Current scene is autosaved before loading new one.
___

## **Testing**

- **Test** folder contains a current test for the library. It is using mock classes for operations on BasicMesh and BasicMaterial (refer to documentation).
___

## **Scene File Example**

```
{
    "Object0": {
        "Active": true,
        "GeometryID": 1,
        "GeometryName": "Cube",
        "ID": 0,
        "MaterialID": 1,
        "MaterialName": "Phong",
        "Name": "TEST0",
        "Parent": null,
        "Position": [
            0,
            0,
            1
        ],
        "Rotation": [
            0,
            0,
            0
        ],
        "Scale": [
            0.20000000298023224,
            0.20000000298023224,
            0.20000000298023224
        ]
    },
    "Object1": {
        "Active": true,
        "GeometryID": 2,
        "GeometryName": "Sphere",
        "ID": 1,
        "MaterialID": 2,
        "MaterialName": "BluePBR",
        "Name": "TEST1",
        "Parent": 0,
        "Position": [
            0.5,
            0.03125,
            0.8660253882408142
        ],
        "Rotation": [
            0,
            30,
            0
        ],
        "Scale": [
            0.20000000298023224,
            0.20000000298023224,
            0.20000000298023224
        ]
    }
}
```
___
@ Renats Bikmajevs
___