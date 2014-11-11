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
    rtCamera(/*eye*/STPoint3(4.f,5.5f,17.f),/*up*/STVector3(0.f,1.f,0.f),/*lookat*/STPoint3(10.f,3.f,0.f),/*fov*/45.f,/*aspect*/1.33f);
    rtOutput(/*width*/640,/*height*/480,/*path*/"../Standard_Tests/Assignment4.png");
    rtBounceDepth(5);
    rtUseTransparentShadow(true);
    rtShadowBias(.001f);
    rtSampleRate(4);
    
    ////lighting
    rtAmbientLight(STColor3f(.1f,.1f,.1f));
    rtPointLight(STPoint3(15.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    rtPointLight(STPoint3(5.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    //rtPointLight(STPoint3(10.f,15.f,4.f),STColor3f(.2f,.2f,.2f));
    
    Material mat_glass1(/*ambient*/STColor3f(),/*diffuse*/STColor3f(),/*spec*/STColor3f(0.f,0.f,0.f),/*mirror*/STColor3f(0.f,0.f,0.f),/*shiness*/0.f,/*refr*/STColor3f(.9f,.3f,.1f),/*sn*/1.3f);
    Material mat_glass2(/*ambient*/STColor3f(),/*diffuse*/STColor3f(),/*spec*/STColor3f(1.f,1.f,1.f),/*mirror*/STColor3f(.1f,.1f,.1f),/*shiness*/30.f,/*refr*/STColor3f(.7f,.6f,.9f),/*sn*/1.3f);
    Material mat_metal(/*ambient*/STColor3f(.5f,.5f,.5f),/*diffuse*/STColor3f(.5f,.5f,.5f),/*spec*/STColor3f(.5f,.5f,.5f),/*mirror*/STColor3f(.5f,.5f,.5f),/*shiness*/120.f);
    
    //rtMaterial(mat_glass1);
    //rtSphere(STPoint3(8.f,1.01f,5.f),1.f);
    
    rtMaterial(mat_metal);
    rtSphere(STPoint3(10.f,1.01f,6.f),1.f);
    
    //rtMaterial(mat_metal);
    //rtCylinder(STPoint3(9.f,0.01f,5.f),STPoint3(9.f,3.01f,5.f),1.f);
    
    rtMaterial(mat_metal);
    rtBox(STPoint3(16.f,1.f,1.f),STVector3(2.f,4.f,.8f));
    
    Material mat_glass(/*ambient*/STColor3f(.1f,.1f,.1f),/*diffuse*/STColor3f(),/*spec*/STColor3f(0.5f,0.5f,0.5f),/*mirror*/STColor3f(.2f,.2f,.2f),/*shiness*/30.f,/*refr*/STColor3f(.7f,.6f,.9f),/*sn*/1.2f);
    rtMaterial(mat_glass2);
    rtAttenuation(1.f);
    rtPushMatrix();
    rtTranslate(7.f,2.5f,5.f);
    rtTriangleMesh("../Standard_Tests/helenbottle.obj",true,false);
    rtPopMatrix();
    
    rtMaterial(mat_glass1);
    rtPushMatrix();
    rtTranslate(10.f,2.5f,3.f);
    rtTriangleMesh("../Standard_Tests/helenbottle.obj",true,false);
    rtPopMatrix();
    
    ////environment box
    Material mat_ground(STColor3f(1.f,1.f,1.f),STColor3f(.8f,.8f,.8f),STColor3f(),STColor3f(),0.f);
    Material mat_wall(STColor3f(1.f,1.f,1.f),STColor3f(.4f,.2f,.1f),STColor3f(),STColor3f(),30.f);
    rtMaterial(mat_ground);
    ////ground
    addGround(STPoint3(0.f,0.f,0.f),STVector2(20.f,20.f),true);
    
    rtMaterial(mat_wall);
    ////ceil
    addGround(STPoint3(0.f,0.f,0.f),STVector2(20.f,20.f),false);
    ////background wall
    addBackgroundWall(STPoint3(0.f,0.f,0.f),STVector2(20.f,20.f),true);
    ////forward wall
    addBackgroundWall(STPoint3(0.f,0.f,20.f),STVector2(20.f,20.f),false);
    ////left wall
    addWall(STPoint3(0.f,0.f,0.f),STVector3(0.f,20.f,0.f),STVector3(0.f,0.f,20.f),true);
    ////right wall
    addWall(STPoint3(20.f,0.f,0.f),STVector3(0.f,20.f,0.f),STVector3(0.f,0.f,20.f),false);
}




//These three functions were copied from the example scene starter code
void OurScene::addGround(const STPoint3& min_corner,const STVector2& size,bool counterclockwise/*=true*/)
{
    if(counterclockwise){
        rtTriangle(min_corner,STPoint3(min_corner.x+size.x,min_corner.y,min_corner.z+size.y),STPoint3(min_corner.x+size.x,min_corner.y,min_corner.z));
        rtTriangle(min_corner,STPoint3(min_corner.x,min_corner.y,min_corner.z+size.y),STPoint3(min_corner.x+size.x,min_corner.y,min_corner.z+size.y));
    }
    else{
        rtTriangle(min_corner,STPoint3(min_corner.x+size.x,min_corner.y,min_corner.z),STPoint3(min_corner.x+size.x,min_corner.y,min_corner.z+size.y));
        rtTriangle(min_corner,STPoint3(min_corner.x+size.x,min_corner.y,min_corner.z+size.y),STPoint3(min_corner.x,min_corner.y,min_corner.z+size.y));
    }
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
