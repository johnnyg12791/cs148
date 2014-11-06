//
//  OurScene.cpp
//  RayTracer
//
//  Created by Jonathan Gold on 11/6/14.
//  Copyright (c) 2014 Tianye Lu. All rights reserved.
//

#include "OurScene.h"

void OurScene::initializeAssignment1()
{
    rtClear();
    
    ////global settings
    rtCamera(/*eye*/STPoint3(0.f,0.f,10.f),/*up*/STVector3(0.f,1.f,0.f),/*lookat*/STPoint3(0.f,0.f,0.f),/*fov*/45.f,/*aspect*/1.f);
    rtOutput(/*width*/512,/*height*/512,/*path*/"../Standard_Tests/Assign1.png");
    rtBounceDepth(1);
    rtShadowBias(1e-4f);
    rtSampleRate(4);
    
    ////lighting:
    rtAmbientLight(STColor3f(.1f,.1f,.1f));
    rtPointLight(/*location*/STPoint3(4.f,4.f,8.f),STColor3f(.5f,.5f,.5f));
    rtPointLight(/*location*/STPoint3(4.f,-2.f,8.f),STColor3f(.5f,.5f,.5f));
    //rtDirectionalLight(/*direction*/STVector3(-1.f,-1.f,-1.f),STColor3f(.5f,.5f,.5f));
    rtAreaLight(/*v1*/STPoint3(1.5f,.25f,.75f),/*v2*/STPoint3(1.5f,-.25f,1.25f),/*v3*/STPoint3(1.5f,.25f,1.25f),STColor3f(.8f,.8f,.8f));
    
    ////objects:
    ////sphere
    Material mat_sphere(STColor3f(0.f,0.f,1.f),STColor3f(0.f,0.f,.8f),STColor3f(1.f,1.f,1.f),STColor3f(0.f,0.f,0.f),30.f);
    rtMaterial(mat_sphere);
    rtSphere(STPoint3(-.5f,-.5f,1.f),1.f);
    
    ////background wall
    Material mat_ground(STColor3f(1.f,1.f,1.f),STColor3f(0.8f,0.8f,.8f),STColor3f(0.f,0.f,0.f),STColor3f(0.f,0.f,0.f),30.f);
    rtMaterial(mat_ground);
    addBackgroundWall(STPoint3(-8.f,-8.f,-1.f),STVector2(16.f,16.f));
}



void OurScene::addBackgroundWall(const STPoint3& min_corner,const STVector2& size,bool counterclockwise/*=true*/)
{
    if(counterclockwise){
        rtTriangle(min_corner,STPoint3(min_corner.x+size.x,min_corner.y,min_corner.z),STPoint3(min_corner.x+size.x,min_corner.y+size.y,min_corner.z));
        rtTriangle(min_corner,STPoint3(min_corner.x+size.x,min_corner.y+size.y,min_corner.z),STPoint3(min_corner.x,min_corner.y+size.y,min_corner.z));
    }
    else{
        rtTriangle(min_corner,STPoint3(min_corner.x+size.x,min_corner.y+size.y,min_corner.z),STPoint3(min_corner.x+size.x,min_corner.y,min_corner.z));
        rtTriangle(min_corner,STPoint3(min_corner.x,min_corner.y+size.y,min_corner.z),STPoint3(min_corner.x+size.x,min_corner.y+size.y,min_corner.z));
    }
}

void OurScene::addWall(const STPoint3& min_corner,const STVector3& u,const STVector3& v,bool counterclockwise/*=true*/)
{
    if(counterclockwise){
        rtTriangle(min_corner,min_corner+u,min_corner+u+v);
        rtTriangle(min_corner,min_corner+u+v,min_corner+v);
    }
    else{
        rtTriangle(min_corner,min_corner+u+v,min_corner+u);
        rtTriangle(min_corner,min_corner+v,min_corner+u+v);
    }
}

