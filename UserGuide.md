# MyLittleEditor User Guide (WIP)

___

## **Content**
___
### 1. **[Introduction](#introduction)**
### 2. **[Demo User Interface](#Demo User Interface)**
### 3. **[Example Scene File](#Example Scene File)**
### 4. **More to come in the future.**
___

## **Introduction**
___

- MyLittleEditor is a project for my assignment to create a basic scene graph that would work as a library. It is coded in C++, with materials using json to pass shader names to the program.

- The current version is a work in progress.

___

## **Demo User Interface**
___

- UI in MyLittleEditor is based on Qt forms.

- to be continued...

___

## **Example Scene File**
___
``
The following scene contains 3 objects, second and third are attached to first, and third one is invisible.
``
```
$OBJECT_START;
    $A=T;
    $POS=0.5,0.2,0.0;
    $ROT=5.38,35.785,0.0;
    $SCL=1.0,1.0,1.0;
    $NAME=MyCube;
    $ID=0;
    $P=;
    $C=1,2;
    $GEONAME=Cube;
    $GEOID=1;
    $MATNAME=Phong;
    $MATID=1;
$OBJECT_END;

$OBJECT_START;
    $A=T;
    $POS=-2.0,0.0,0.0;
    $ROT=-5.38,-35.785,0.0;
    $SCL=1.0,1.0,1.0;
    $NAME=AttachedSphere;
    $ID=1;
    $P=0;
    $C=;
    $GEONAME=Sphere;
    $GEOID=2;
    $MATNAME=bluePBR;
    $MATID=2;
$OBJECT_END;

$OBJECT_START;
    $A=F;
    $POS=-0.5,0.0,-1.0;
    $ROT=0.0,0.0,0.0;
    $SCL=1.0,1.0,1.0;
    $NAME=InvisibleCube;
    $ID=3;
    $P=0;
    $C=;
    $GEONAME=Cube;
    $GEOID=1;
    $MATNAME=yellowPBR;
    $MATID=3;
$OBJECT_END;
```