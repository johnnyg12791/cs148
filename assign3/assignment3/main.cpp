// main.cpp

//
// For this project, we use OpenGL, GLUT
// and GLEW (to load OpenGL extensions)
//
#include "stglew.h"

#include <stdio.h>
#include <string.h>
//
// Globals used by this application.
// As a rule, globals are Evil, but this is a small application
// and the design of GLUT makes it hard to avoid them.
//

// Window size, kept for screenshots
static int gWindowSizeX = 0;
static int gWindowSizeY = 0;

// File locations
std::string vertexShader;
std::string fragmentShader;
std::string normalMap;
std::string displacementMap;
std::string meshBalloon;
std::string meshBalloon2;
std::string meshMountain;

// Light source attributes
static float ambientLight[]  = {1.5, 1.5, 1.5, 1.0};
static float specularLight[] = {1.0, 1.0, 1.0, 1.0};
static float diffuseLight[]  = {1.5, 1.5, 1.5, 1.0};

static float ambientLight1[]  = {1.0, 1.0, 1.0, 1.0};
static float specularLight1[] = {1.0, 1.0, 1.0, 1.0};
static float diffuseLight1[]  = {1.5, 1.5, 1.5, 1.0};


float lightPosition[] = {5.0f, 5.0f, 10.0f, 1.0f};
float lightPosition1[] = {-10.0f, 5.0f, -10.0f, 1.0f};

// Material color properties
static float materialAmbient[]  = { 0.5, 0.5, 0.5, 1.0 };
static float materialDiffuse[]  = { 0.5, 0.5, 0.8, 1.0 };
static float materialSpecular[] = { 0.8, 0.8, 0.8, 1.0 };
static float shininess          = 2.0;  // # between 1 and 128.

static float material2Ambient[]  = { 1., 1., 1., 1. };
static float material2Diffuse[]  = { 1., 1., 1., 1. };
static float material2Specular[] = { 1., 1., 1., 1. };
static float shininess2          = 1.;  // # between 1 and 128.

STImage   *surfaceNormImg;
STTexture *surfaceNormTex;

STImage   *surfaceDisplaceImg;
STTexture *surfaceDisplaceTex;

STShaderProgram *shader;

STVector3 mPosition;
STVector3 mLookAt;
STVector3 mRight;
STVector3 mUp;

// Stored mouse position for camera rotation, panning, and zoom.
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;
bool mesh = false; // draw mesh
bool smooth = true; // smooth/flat shading for mesh
bool normalMapping = true; // true=normalMapping, false=displacementMapping
bool proxyType=false; // false: use cylinder; true: use sphere

std::vector<STTriangleMesh*> gTriangleMeshes;
STPoint3 gMassCenter;
std::pair<STPoint3,STPoint3> gBoundingBox;

STTriangleMesh* bottleMesh = 0;
STTriangleMesh* balloonMesh = 0;
STTriangleMesh* mountainMesh = 0;

int TesselationDepth = 100;

void SetUpAndRight()
{
    mRight = STVector3::Cross(mLookAt - mPosition, mUp);
    mRight.Normalize();
    mUp = STVector3::Cross(mRight, mLookAt - mPosition);
    mUp.Normalize();
}

void resetCamera()
{
    mLookAt=STVector3(0.f,0.f,0.f);
    mPosition=STVector3(0.f,5.f,15.f);
    mUp=STVector3(0.f,1.f,0.f);

    SetUpAndRight();
}

void resetUp()
{
    mUp = STVector3(0.f,1.f,0.f);
    mRight = STVector3::Cross(mLookAt - mPosition, mUp);
    mRight.Normalize();
    mUp = STVector3::Cross(mRight, mLookAt - mPosition);
    mUp.Normalize();
}

//
// Initialize the application, loading all of the settings that
// we will be accessing later in our fragment shaders.
//
void Setup()
{
    // Set up lighting variables in OpenGL
    // Once we do this, we will be able to access them as built-in
    // attributes in the shader (see examples of this in normalmap.frag)
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_SPECULAR,  specularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT,   ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,   diffuseLight);
    
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_SPECULAR,  specularLight1);
    glLightfv(GL_LIGHT1, GL_AMBIENT,   ambientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,   diffuseLight1);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

    surfaceNormImg = new STImage(normalMap);
    surfaceNormTex = new STTexture(surfaceNormImg);
    
    surfaceDisplaceImg = new STImage(displacementMap);
    surfaceDisplaceTex = new STTexture(surfaceDisplaceImg);

    shader = new STShaderProgram();
    shader->LoadVertexShader(vertexShader);
    shader->LoadFragmentShader(fragmentShader);

    resetCamera();
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    


    //No more meshBottle
    STTriangleMesh::LoadObj(gTriangleMeshes,meshBalloon);
    STTriangleMesh::LoadObj(gTriangleMeshes,meshBalloon2);
    //STTriangleMesh::LoadObj(gTriangleMeshes,meshMountain);
    //STTriangleMesh::AddVertex(0.0f, 0.0f, -500.0f);
    gMassCenter=STTriangleMesh::GetMassCenter(gTriangleMeshes);
    std::cout<<"Mass Center: "<<gMassCenter<<std::endl;
    gBoundingBox=STTriangleMesh::GetBoundingBox(gTriangleMeshes);
    std::cout<<"Bounding Box: "<<gBoundingBox.first<<" - "<<gBoundingBox.second<<std::endl;

    for(unsigned int id=0;id<gTriangleMeshes.size();id++)
        gTriangleMeshes[id]->Recenter(gMassCenter);
    
    for(unsigned int id=0;id<gTriangleMeshes.size();id++){
        gTriangleMeshes[id]->mDrawAxis = false;
        if(proxyType) gTriangleMeshes[id]->CalculateTextureCoordinatesViaSphericalProxy();
        else gTriangleMeshes[id]->CalculateTextureCoordinatesViaCylindricalProxy(-6700,6700,0,0,2);
    }
    
    //bottleMesh=new STTriangleMesh(meshBottle);
    //balloonMesh=new STTriangleMesh(meshBalloon);
}

void CleanUp()
{
    for(unsigned int id=0;id<gTriangleMeshes.size();id++)delete gTriangleMeshes[id];
}

/**
 * Camera adjustment methods
 */
void RotateCamera(float delta_x, float delta_y)
{
    float yaw_rate=1.f;
    float pitch_rate=1.f;

    mPosition -= mLookAt;
    STMatrix4 m;
    m.EncodeR(-1*delta_x*yaw_rate, mUp);
    mPosition = m * mPosition;
    m.EncodeR(-1*delta_y*pitch_rate, mRight);
    mPosition = m * mPosition;

    mPosition += mLookAt;
}

void ZoomCamera(float delta_y)
{
    STVector3 direction = mLookAt - mPosition;
    float magnitude = direction.Length();
    direction.Normalize();
    float zoom_rate = 0.1f*magnitude < 0.5f ? .1f*magnitude : .5f;
    if(delta_y * zoom_rate + magnitude > 0)
    {
        mPosition += (delta_y * zoom_rate) * direction;
    }
}


void StrafeCamera(float delta_x, float delta_y)
{
    float strafe_rate = 0.05f;

    mPosition -= strafe_rate * delta_x * mRight;
    mLookAt   -= strafe_rate * delta_x * mRight;
    mPosition += strafe_rate * delta_y * mUp;
    mLookAt   += strafe_rate * delta_y * mUp;
}

//
// Display the output image from our vertex and fragment shaders
//
void DisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //addBackground();
    SetUpAndRight();

    gluLookAt(mPosition.x,mPosition.y,mPosition.z,
              mLookAt.x,mLookAt.y,mLookAt.z,
              mUp.x,mUp.y,mUp.z);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

    // Texture 0: surface normal map
    glActiveTexture(GL_TEXTURE0);
    surfaceNormTex->Bind();
    
    // Texture 1: surface normal map
    glActiveTexture(GL_TEXTURE1);
    surfaceDisplaceTex->Bind();
    
    // Bind the textures we've loaded into openGl to
    // the variable names we specify in the fragment
    // shader.
    shader->SetTexture("normalTex", 0);
    shader->SetTexture("displacementTex", 1);
	shader->SetTexture("colorTex", 2);
    
    // Invoke the shader.  Now OpenGL will call our
    // shader programs on anything we draw.
    shader->Bind();

        shader->SetUniform("normalMapping", -1.0);
        shader->SetUniform("displacementMapping", -1.0);
		shader->SetUniform("colorMapping", 1.0);
        
    glPushMatrix();
    // Pay attention to scale 
    STVector3 size_vector=gBoundingBox.second-gBoundingBox.first;
    float maxSize=(std::max)((std::max)(size_vector.x,size_vector.y),size_vector.z);
    glScalef(3.0f/maxSize,3.0f/maxSize,3.0f/maxSize);
    glTranslatef(-gMassCenter.x,-gMassCenter.y,-gMassCenter.z);
    //for(unsigned int id=0;id<gTriangleMeshes.size();id++) {
    //    gTriangleMeshes[id]->Draw(smooth);
    //}
    glTranslatef(0.0f, 15.0f, -1.0f);
    glPushMatrix(); //This is our "center"
    gTriangleMeshes[0]->Draw(smooth);
    gTriangleMeshes[3]->Draw(smooth);
    
    glTranslatef(-12.0f, -2.0f, 10.0f);
    gTriangleMeshes[0]->Draw(smooth);
    gTriangleMeshes[1]->Draw(smooth);
    glTranslatef(12.0f, 2.0f, -10.0f);
    
    glTranslatef(8.0f, 0.0f, -4.0f);
    gTriangleMeshes[0]->Draw(smooth);
    gTriangleMeshes[1]->Draw(smooth);
    glTranslatef(-8.0f, 0.0f, 4.0f);
    
    glTranslatef(0.0f, 2.0f, -100.0f);
    gTriangleMeshes[0]->Draw(smooth);
    gTriangleMeshes[1]->Draw(smooth);
    glTranslatef(0.0f, -2.0f, 100.0f);
    
    glTranslatef(20.0f, 10.0f, -50.f);
    gTriangleMeshes[2]->Draw(smooth);
    gTriangleMeshes[3]->Draw(smooth);
    glTranslatef(-20.0f, -10.0f, 50.0f);

    /*gTriangleMeshes[0]->mDrawAxis = false;
    glTranslatef(-2.0f, 0.0f, 0.0f);
    gTriangleMeshes[0]->Draw(smooth);
    gTriangleMeshes[0]->mDrawAxis = false;*/



    shader->UnBind();
    
    glActiveTexture(GL_TEXTURE0);
    surfaceNormTex->UnBind();
    
    glActiveTexture(GL_TEXTURE1);
    surfaceDisplaceTex->UnBind();
    
    glutSwapBuffers();
}




//
// Reshape the window and record the size so
// that we can use it for screenshots.
//
void ReshapeCallback(int w, int h)
{
	gWindowSizeX = w;
    gWindowSizeY = h;

    glViewport(0, 0, gWindowSizeX, gWindowSizeY);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	// Set up a perspective projection
    float aspectRatio = (float) gWindowSizeX / (float) gWindowSizeY;
	gluPerspective(30.0f, aspectRatio, .1f, 10000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SpecialKeyCallback(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_LEFT:
            StrafeCamera(10,0);
            break;
        case GLUT_KEY_RIGHT:
            StrafeCamera(-10,0);
            break;
        case GLUT_KEY_DOWN:
            StrafeCamera(0,-10);
            break;
        case GLUT_KEY_UP:
            StrafeCamera(0,10);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void KeyCallback(unsigned char key, int x, int y)
{
    switch(key) {
    case 's': {
            //
            // Take a screenshot, and save as screenshot.jpg
            //
            STImage* screenshot = new STImage(gWindowSizeX, gWindowSizeY);
            screenshot->Read(0,0);
            screenshot->Save("screenshot.jpg");
            delete screenshot;
        }
        break;
    case 'r':
        resetCamera();
        break;
    case 'u':
        resetUp();
        break;
    case 'n': // switch between normalMapping and displacementMapping
        normalMapping = !normalMapping;
        break;
    case 'f': // switch between smooth shading and flat shading
        smooth = !smooth;
        break;
    //case 'l': // do loop subdivision
    //    if(mesh){
    //        gTriangleMesh->LoopSubdivide();
	//		if(proxyType) gTriangleMesh->CalculateTextureCoordinatesViaSphericalProxy();
	//		else gTriangleMesh->CalculateTextureCoordinatesViaCylindricalProxy(-1,1,0,0,1);
    //    }
    //    else
    //        gManualTriangleMesh->LoopSubdivide();
    //    break;
    //case 'w':
    //    gTriangleMesh->Write("output.obj");
    //    break;
    case 'a':
        for(unsigned int id=0;id<gTriangleMeshes.size();id++)
            gTriangleMeshes[id]->mDrawAxis=!gTriangleMeshes[id]->mDrawAxis;
        break;
	case 'q':
		exit(0);
    default:
        break;
    }

    glutPostRedisplay();
}

/**
 * Mouse event handler
 */
void MouseCallback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON
        || button == GLUT_RIGHT_BUTTON
        || button == GLUT_MIDDLE_BUTTON)
    {
        gMouseButton = button;
    } else
    {
        gMouseButton = -1;
    }
    
    if (state == GLUT_UP)
    {
        gPreviousMouseX = -1;
        gPreviousMouseY = -1;
    }
}

/**
 * Mouse active motion callback (when button is pressed)
 */
void MouseMotionCallback(int x, int y)
{
    if (gPreviousMouseX >= 0 && gPreviousMouseY >= 0)
    {
        //compute delta
        float deltaX = x-gPreviousMouseX;
        float deltaY = y-gPreviousMouseY;
        gPreviousMouseX = x;
        gPreviousMouseY = y;
        
        //orbit, strafe, or zoom
        if (gMouseButton == GLUT_LEFT_BUTTON)
        {
            RotateCamera(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_MIDDLE_BUTTON)
        {
            StrafeCamera(deltaX, deltaY);
        }
        else if (gMouseButton == GLUT_RIGHT_BUTTON)
        {
            ZoomCamera(deltaY);
        }
        
    } else
    {
        gPreviousMouseX = x;
        gPreviousMouseY = y;
    }
    
}

void usage()
{
	printf("usage: assignment3 vertShader fragShader objMeshFile normalMappingTexture displacementMappingTexture\n");
}

int main(int argc, char** argv)
{
	if (argc != 6)
		usage();

    vertexShader   = argc>1?std::string(argv[1]):std::string("kernels/default.vert");
	fragmentShader = argc>2?std::string(argv[2]):std::string("kernels/phong.frag");
    //meshOBJ        = argc>3?std::string(argv[3]):std::string("turbosonic/turbosonic.obj");
    meshBalloon        = argc>3?std::string(argv[3]):std::string("meshes/balloonbottle1.obj");
	normalMap      = argc>4?std::string(argv[4]):std::string("images/normalmap.png");
	displacementMap= argc>5?std::string(argv[5]):std::string("images/displacementmap.jpeg");
    
    //meshBottle = "./meshes/balloonbottle1.obj";
    meshBalloon2 = "./meshes/balloonbottle2.obj";
    meshMountain = "./meshes/mountains.obj";
    
    //
    // Initialize GLUT.
    //
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(640, 480);
    glutCreateWindow("CS148 Assignment 3");
    
    //
    // Initialize GLEW.
    //
#ifndef __APPLE__
    glewInit();
    if(!GLEW_VERSION_2_0) {
        printf("Your graphics card or graphics driver does\n"
			   "\tnot support OpenGL 2.0, trying ARB extensions\n");

        if(!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader) {
            printf("ARB extensions don't work either.\n");
            printf("\tYou can try updating your graphics drivers.\n"
				   "\tIf that does not work, you will have to find\n");
            printf("\ta machine with a newer graphics card.\n");
            exit(1);
        }
    }
#endif

    // Be sure to initialize GLUT (and GLEW for this assignment) before
    // initializing your application.

    Setup();

    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glutSpecialFunc(SpecialKeyCallback);
    glutKeyboardFunc(KeyCallback);
    glutMouseFunc(MouseCallback);
    glutMotionFunc(MouseMotionCallback);
    glutIdleFunc(DisplayCallback);

    glutMainLoop();

    // Cleanup code should be called here.
    CleanUp();

    return 0;
}
