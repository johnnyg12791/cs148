//
//  OurScene.cpp
//  RayTracer
//
//  Created by Jonathan Gold on 11/6/14.
//  Copyright (c) 2014 Tianye Lu. All rights reserved.
//

#include "OurScene.h"

//Currently just copied from the example code line 465-500 Depth of field
void OurScene::initializeAssignment6()
{
    rtClear();
    
    ////global settings
    rtCamera(/*eye*/STPoint3(0.f,0.f,15.f),/*up*/STVector3(0.f,1.f,0.f),/*lookat*/STPoint3(0.f,0.f,-20.f),/*fov*/60.f,/*aspect*/1.f);
    rtOutput(/*width*/512,/*height*/512,/*path*/"../Standard_Tests/Assignment6f.png");
    rtBounceDepth(8);
    rtShadowBias(1e-4f);
    rtSampleRate(1);
    
    ////lighting
    rtAmbientLight(STColor3f(.1f,.1f,.1f));
    rtPointLight(STPoint3(3.f,12.f,10.f),STColor3f(1.f,1.f,1.f));

    //back wall(sky)
    //Material mat_wall(STColor3f(1.f,1.f,1.f),STColor3f(.2f,.5f,.9f),STColor3f(),STColor3f(),30.f);
    //rtMaterial(mat_wall);
    //bottom left (x,y,z), (length, width)
    //addBackgroundWall(STPoint3(-500.f,-200.f,-500.f),STVector2(1000.f,1000.f),true);
    //Sky will go here
    
    
    //ground (possible mountains)
    Material mat_ground(STColor3f(1.f,1.f,1.f),STColor3f(.8f,.8f,.8f),STColor3f(),STColor3f(),30.f);
    rtMaterial(mat_ground);
    //Not exactly sure what these correspond to but....seems to work
    addGround(STPoint3(-500.f,-50.f,-500.f),STVector2(1000.f,1000.f),true);
    
    
    Material mat_glass(/*ambient*/STColor3f(.1f,.1f,.1f),/*diffuse*/STColor3f(),/*spec*/STColor3f(0.5f,0.5f,0.5f),/*mirror*/STColor3f(.2f,.2f,.2f),/*shiness*/30.f,/*refr*/STColor3f(.7f,.6f,.9f),/*sn*/1.2f);
    rtMaterial(mat_glass);
    //These next two lines add a slighly transparent shadow (based on the attenuation number)
    rtUseTransparentShadow(true);
    rtAttenuation(.8f);
    
    rtScale(.4f, .4f, .4f);

    rtPushMatrix();
    //rtTriangleMesh("../Meshes_Materials/bottlenotexture.obj",true,false);
    rtTriangleMeshWithMaterialAndTexture("../Meshes_Materials/balloonrope.obj",true,false);
    rtPopMatrix();
    
    rtPushMatrix();
    rtTranslate(10.f, 5.f, -5.f);
    rtTriangleMeshWithMaterialAndTexture("../Meshes_Materials/balloonrope.obj",true,false);
    //rtTriangleMesh("../Meshes_Materials/bottlenotexture.obj",true,false);
    rtPopMatrix();
    
    rtPushMatrix();
    rtTranslate(-12.f, -7.f, -12.f);
    rtTriangleMeshWithMaterialAndTexture("../Meshes_Materials/balloonrope.obj",true,false);
    //rtTriangleMesh("../Meshes_Materials/bottlenotexture.obj",true,false);
    rtPopMatrix();
    
    
    Material mat_cloud(/*ambient*/STColor3f(.5f,.5f,.5f),/*diffuse*/STColor3f(.5f,.5f,.5f),/*spec*/STColor3f(.5f,.5f,.5f),/*mirror*/STColor3f(.5f,.5f,.5f),/*shiness*/120.f);
    rtMaterial(mat_cloud);
    rtMaterial(mat_ground);

    addCloud(-8, 14, 0, 1.2);
    addCloud(15, 20, -10, 1.8);
    
    
    //DEPTH OF FIELD
    //rtSetApeture(10.f);
    //rtSetFocus(STPoint3(0.f, 0.f, 3.f));
    
    accel_structure=AABB_TREE;
    AABBTree* aabb_tree=new AABBTree(objects);
    aabb_trees.push_back(aabb_tree);
}


//3 rows of 3 spheres makes a cloud
void OurScene::addCloud(int x, int y, int z, int size){
    for(int i = -1; i <= 1; i++){
        rtPushMatrix();
        rtTranslate(0, i, 0);
        rtSphere(STPoint3(x-1.5, y, z), size);
        rtSphere(STPoint3(x, y, z), size);
        rtSphere(STPoint3(x+1.5, y, z), size);
        rtPopMatrix();
    }
}


void OurScene::initializeAssignment6b()
{
    rtClear();
    
    ////global settings
    rtCamera(/*eye*/STPoint3(0.f,1.f,6.f),/*up*/STVector3(0.f,1.f,0.f),/*lookat*/STPoint3(0.f,0.f,0.f),/*fov*/55.f,/*aspect*/1.f);
    rtOutput(/*width*/512,/*height*/512,/*path*/"../Standard_Tests/Assignment6b.png");
    rtBounceDepth(10);
    rtUseShadow(true);
    rtShadowBias(1e-4f);
    rtSampleRate(4);
    
    rtAmbientLight(STColor3f(.1f,.1f,.1f));
    rtPointLight(STPoint3(0.f,3.f,2.f),STColor3f(1.f,1.f,1.f));
    
    ////ground
    Material mat_tri(/*ambient*/STColor3f(1.f,1.f,1.f),/*diffuse*/STColor3f(.4f,.4f,.4f),/*specular*/STColor3f(.0f,.0f,.0f),/*mirror*/STColor3f(.9f,.9f,.9f),/*shiness*/0.f);
    rtMaterial(mat_tri);
    addGround(STPoint3(-500.f,-1.f,-500.f),STVector2(1000.f,1000.f),true);
    
    ////sphere1
    Material mat_sphere1(/*ambient*/STColor3f(1.f,.75f,.75f),/*diffuse*/STColor3f(1.f,.75f,.75f),/*specular*/STColor3f(1.f,1.f,1.f),/*mirror*/STColor3f(.75f,.75f,.75f),/*shiness*/50.f);
    rtMaterial(mat_sphere1);
    //rtSphere(STPoint3(1.f,0.f,-3.f),1.f);
    rtPushMatrix();
    rtScale(.25, .25, .25);
    rtTranslate(3.f, -1.5f, -2.f);
    rtTriangleMesh("../Meshes_Materials/bottlenotexture.obj",true,false);
    rtPopMatrix();
    
    ////sphere2
    Material mat_sphere2(/*ambient*/STColor3f(.75f,.75f,1.f),/*diffuse*/STColor3f(.75f,.75f,1.f),/*specular*/STColor3f(0.f,0.f,0.f),/*mirror*/STColor3f(0.f,0.f,0.f),/*shiness*/0.f);
    rtMaterial(mat_sphere2);
    //rtSphere(STPoint3(-1.f,0.f,-1.f),1.f);
    rtPushMatrix();
    rtScale(.35, .45, .35);
    rtTranslate(-2.2f, -1.f, -1.f);
    rtTriangleMesh("../Meshes_Materials/bottlenotexture.obj",true,false);
    rtPopMatrix();
    
    ////sphere3
    Material mat_sphere3(/*ambient*/STColor3f(.0f,1.f,.0f),/*diffuse*/STColor3f(.0f,1.f,.0f),/*specular*/STColor3f(.3f,.3f,.3f),/*mirror*/STColor3f(0.f,0.3f,0.f),/*shiness*/50.f);
    rtMaterial(mat_sphere3);
    //rtSphere(STPoint3(.2f,-.5f,1.f),.5f);
    rtPushMatrix();
    rtScale(.20, .15, .20);
    rtTranslate(.2f, -4.f, 3.f);
    rtTriangleMesh("../Meshes_Materials/bottlenotexture.obj",true,false);
    rtPopMatrix();
    
    ////set focus on sphere 3
    rtSetApeture(20.f);
    rtSetFocus(STPoint3(.2f, -.5f, 1.f));
}


void OurScene::initializeAssignment4()
{
    rtClear();
    
    ////global settings
    rtCamera(/*eye*/STPoint3(4.f,5.5f,17.f),/*up*/STVector3(0.f,1.f,0.f),/*lookat*/STPoint3(10.f,3.f,0.f),/*fov*/45.f,/*aspect*/1.33f);
    rtOutput(/*width*/640,/*height*/480,/*path*/"../Standard_Tests/Assignment4.png");
    rtBounceDepth(5);
    rtUseTransparentShadow(true);
    rtShadowBias(.001f);
    //rtSampleRate(4);
    
    ////lighting
    rtAmbientLight(STColor3f(.1f,.1f,.1f));
    rtPointLight(STPoint3(15.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    rtPointLight(STPoint3(5.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    //rtPointLight(STPoint3(10.f,15.f,4.f),STColor3f(.2f,.2f,.2f));
    
    Material mat_glass1(/*ambient*/STColor3f(),/*diffuse*/STColor3f(),/*spec*/STColor3f(0.f,0.f,0.f),/*mirror*/STColor3f(0.f,0.f,0.f),/*shiness*/0.f,/*refr*/STColor3f(.9f,.3f,.1f),/*sn*/1.3f);
    Material mat_glass2(/*ambient*/STColor3f(),/*diffuse*/STColor3f(),/*spec*/STColor3f(1.f,1.f,1.f),/*mirror*/STColor3f(.1f,.1f,.1f),/*shiness*/30.f,/*refr*/STColor3f(.7f,.6f,.9f),/*sn*/1.3f);
    Material mat_metal(/*ambient*/STColor3f(.5f,.5f,.5f),/*diffuse*/STColor3f(.5f,.5f,.5f),/*spec*/STColor3f(.5f,.5f,.5f),/*mirror*/STColor3f(.5f,.5f,.5f),/*shiness*/120.f);

    rtMaterial(mat_metal);
    rtSphere(STPoint3(10.f,1.01f,6.f),1.f);
    
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
    Material mat_wall(STColor3f(.5f,.5f,1.f),STColor3f(.4f,.2f,.1f),STColor3f(),STColor3f(),30.f);
    rtMaterial(mat_ground);
    ////ground
    //addGround(STPoint3(0.f,0.f,0.f),STVector2(20.f,20.f),true);
    
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

void OurScene::addClusteredObjects()
{
    Material mat_metal(/*ambient*/STColor3f(.5f,.5f,.5f),/*diffuse*/STColor3f(.5f,.5f,.5f),/*spec*/STColor3f(.5f,.5f,.5f),/*mirror*/STColor3f(.5f,.5f,.5f),/*shiness*/120.f);
    
    rtMaterial(mat_metal);
    float z = 0;
    float x = 8;
    float y = 0;
    
    for(int i = -1; i <= 1; i++){
        for (int j = -1; j <=1; j++){
            if(abs(i - j)!=1){
                rtPushMatrix();
                rtTranslate(9*i, 9*j, 0);
                rtCylinder(STPoint3(x,y,z),STPoint3(x+1,y+1,z),1.f);
                rtCylinder(STPoint3(x-1.5,y,z),STPoint3(x-.5,y+1,z),1.f);
                rtCylinder(STPoint3(x,y+1.5,z),STPoint3(x+1,y+2.5,z),1.f);
                rtCylinder(STPoint3(x-1.5,y+1.5,z),STPoint3(x-.5,y+2.5,z),1.f);
                
                rtSphere(STPoint3(x-.5, y+.75f, z+1), 1);
                rtSphere(STPoint3(x-1.5, y+1.75f, z+1), 1);
                rtSphere(STPoint3(x+.5, y-.25f, z+1), 1);
                //rtSphere(STPoint3(x-.5, y+3.25f, z), 1);
                rtTranslate(10.f,0.f,0.f);
                rtTriangleMesh("../Standard_Tests/helenbottle.obj",true,false);

                rtPopMatrix();
            }
        }
    }
    
    
}

void OurScene::addUniformObjects()
{
    Material mat_metal(/*ambient*/STColor3f(.5f,.5f,.5f),/*diffuse*/STColor3f(.5f,.5f,.5f),/*spec*/STColor3f(.5f,.5f,.5f),/*mirror*/STColor3f(.5f,.5f,.5f),/*shiness*/120.f);
    
    rtMaterial(mat_metal);
    float z = 0;
    
    for(int i = -6; i <= 8; i++){
        for (int j = -5; j <=6; j++){
            rtPushMatrix();
            rtTranslate(2*i, 2*j, 0);
            rtSphere(STPoint3(8.f,0.0f,z), .5);
            rtSphere(STPoint3(9.f,0.0f,z), .5);
            rtSphere(STPoint3(8.f,1.0f,z), .5);
            rtSphere(STPoint3(9.f,1.0f,z), .5);

            rtPopMatrix();
        }
    }
}


void OurScene::initializeAssignment5AABB()
{
    //Setup Camera and lighting
    rtClear();
    ////global settings //View from above
    rtCamera(/*eye*/STPoint3(0.f,0.f,30.f),/*up*/STVector3(0.f,1.f,0.f),/*lookat*/STPoint3(10.f,3.f,0.f),/*fov*/45.f,/*aspect*/1.33f);
    rtOutput(/*width*/640,/*height*/480,/*path*/"../Standard_Tests/Assignment5AABB.png");
    rtBounceDepth(5);
    rtUseTransparentShadow(true);
    rtShadowBias(.001f);
    rtAmbientLight(STColor3f(.1f,.1f,.1f));
    rtPointLight(STPoint3(15.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    rtPointLight(STPoint3(5.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    
    //Make some objects for our image
    addClusteredObjects();
    //addUniformObjects();
    //addWallsAndGround();
    

    //AABB Acceleration (ie, what we care about for this assignment)
    accel_structure=AABB_TREE;
    AABBTree* aabb_tree=new AABBTree(objects);
    aabb_trees.push_back(aabb_tree);
    
}

void OurScene::initializeAssignment5Grid()
{
    //Lights, Camera....
    rtClear();
    ////global settings //View from above
    rtCamera(/*eye*/STPoint3(0.f,0.f,30.f),/*up*/STVector3(0.f,1.f,0.f),/*lookat*/STPoint3(10.f,3.f,0.f),/*fov*/45.f,/*aspect*/1.33f);
    rtOutput(/*width*/640,/*height*/480,/*path*/"../Standard_Tests/Assignment5Grid.png");
    rtBounceDepth(5);
    rtUseTransparentShadow(true);
    rtShadowBias(.001f);
    rtAmbientLight(STColor3f(.1f,.1f,.1f));
    rtPointLight(STPoint3(15.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    rtPointLight(STPoint3(5.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    
    //Action!
    //addClusteredObjects();
    addUniformObjects();
    
    
    //Renderrrr
    //Adding UniformGrid acceleration
    accel_structure=UNIFORM_GRID;
    AABB scene_bounding_box;getObjectsAABB(objects,scene_bounding_box);
    int subdivision[3]={60,60,2};
    uniform_grid=new UniformGrid(objects,scene_bounding_box,subdivision);
    
    
}

void OurScene::initializeAssignment5SampleRate(int rate)
{
    rtClear();
    ////global settings //View from above
    rtCamera(/*eye*/STPoint3(4.f,5.5f,17.f),/*up*/STVector3(0.f,1.f,0.f),/*lookat*/STPoint3(10.f,3.f,0.f),/*fov*/45.f,/*aspect*/1.33f);
    rtOutput(/*width*/640,/*height*/480,"../Standard_Tests/Assignment5SampleRate_" + std::to_string(rate) + ".png");
    rtBounceDepth(5);
    rtUseTransparentShadow(true);
    rtShadowBias(.001f);
    rtSampleRate(rate);
    ////lighting
    
    rtAmbientLight(STColor3f(.1f,.1f,.1f));
    rtPointLight(STPoint3(15.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    rtPointLight(STPoint3(5.f,10.f,15.f),STColor3f(.6f,.6f,.6f));
    //rtPointLight(STPoint3(10.f,15.f,4.f),STColor3f(.2f,.2f,.2f));
    
    Material mat_glass1(/*ambient*/STColor3f(),/*diffuse*/STColor3f(),/*spec*/STColor3f(0.f,0.f,0.f),/*mirror*/STColor3f(0.f,0.f,0.f),/*shiness*/0.f,/*refr*/STColor3f(.9f,.3f,.1f),/*sn*/1.3f);
    Material mat_glass2(/*ambient*/STColor3f(),/*diffuse*/STColor3f(),/*spec*/STColor3f(1.f,1.f,1.f),/*mirror*/STColor3f(.1f,.1f,.1f),/*shiness*/30.f,/*refr*/STColor3f(.7f,.6f,.9f),/*sn*/1.3f);
    Material mat_metal(/*ambient*/STColor3f(.5f,.5f,.5f),/*diffuse*/STColor3f(.5f,.5f,.5f),/*spec*/STColor3f(.5f,.5f,.5f),/*mirror*/STColor3f(.5f,.5f,.5f),/*shiness*/120.f);
    
    rtMaterial(mat_metal);
    rtSphere(STPoint3(10.f,1.01f,6.f),1.f);
    
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
    //addGround(STPoint3(0.f,0.f,0.f),STVector2(20.f,20.f),true);
    
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
    
    //Uniform Grid
    accel_structure=UNIFORM_GRID;
    AABB scene_bounding_box;getObjectsAABB(objects,scene_bounding_box);
    int subdivision[3]={5,5,2};
    uniform_grid=new UniformGrid(objects,scene_bounding_box,subdivision);
    
    //AABB Tree
    //accel_structure=AABB_TREE;
    //AABBTree* aabb_tree=new AABBTree(objects);
    //aabb_trees.push_back(aabb_tree);
    
}


void OurScene::addWallsAndGround()
{
    ////environment box
    Material mat_ground(STColor3f(1.f,1.f,1.f),STColor3f(.8f,.8f,.8f),STColor3f(),STColor3f(),0.f);
    Material mat_wall(STColor3f(1.f,1.f,1.f),STColor3f(.4f,.2f,.1f),STColor3f(),STColor3f(),30.f);
    rtMaterial(mat_ground);
    ////ground
    //addGround(STPoint3(0.f,0.f,0.f),STVector2(20.f,20.f),true);
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
