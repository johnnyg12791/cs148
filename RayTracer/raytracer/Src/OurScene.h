//
//  OurScene.h
//  RayTracer
//
//  Created by Jonathan Gold on 11/6/14.
//  Copyright (c) 2014 Tianye Lu. All rights reserved.
//

#ifndef __RayTracer__OurScene__
#define __RayTracer__OurScene__

#include <stdio.h>
#include "Scene.h"

class OurScene : public Scene
{
public:
    using Scene::Render;
    using Scene::initializeSceneFromScript;
    
    OurScene(){}
    ~OurScene(){}
    
    void initializeAssignment1();
    
    //Copied this code from the example scene
    ////initializing scenes
    ////example scenes assignment 4: basic geometry, shading, texturing, and transparency
    /*void initializeSceneBasicGeometry();
    void initializeSceneBasicLightingAndShading();
    void initializeSceneTransform();
    void initializeSceneObjMesh();      ////totoro
    void initializeSceneObjMesh2();     ////turbosonic
    void initializeSceneTexture();
    void initializeSceneTransparentObject();
    void initializeSceneTransparentObject2();
    
    ////example scenes for assignment 5: acceleration structures
    void initializeSceneAccelerationStructureGrid();   ////uniform distributed
    void initializeSceneAccelerationStructureBVH();   ////clustered objects
    
    ////example assignment 6: partipating media and camera effects
    void initializeSceneParticipatingMedia();
    void initializeSceneDepthOfField();
    */
    ////void commonly used functions
    void addGround(const STPoint3& min_corner,const STVector2& size,bool counterclockwise=true);
    void addBackgroundWall(const STPoint3& min_corner,const STVector2& size,bool counterclockwise=true);
    void addWall(const STPoint3& min_corner,const STVector3& u,const STVector3& v,bool counterclockwise=true);
};

#endif /* defined(__RayTracer__OurScene__) */
