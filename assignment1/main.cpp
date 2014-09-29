#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Question 1: In a GLUT program, how is control passed
// back to the programmer?  How is this set up during
// initialization?

int win_width = 512;
int win_height = 512;
int draw_mode=1;

//Took away the arguments, I think it's easier to call the transforms first, then draw seperately
void drawLeftHalfArch(){
    glBegin(GL_TRIANGLE_STRIP);
    
    //HELEN made all of the vertices 3-dimensional, again trying to solve the overlap problem by using z coordinates. No luck yet.
    
    //Base
    glVertex3f(0.1f,0.1f,-1.f);
    glVertex3f(0.2f,0.1f,-1.f);
    glVertex3f(0.1f,0.6f,-1.f);
    glVertex3f(0.2f,0.6f,-1.f);
    //Arch
    glVertex3f(0.125f,0.7f,-1.f);
    glVertex3f(0.235f,0.725f,-1.f);
    glVertex3f(0.175f,0.77f,-1.f);
    glVertex3f(0.275f,0.8f,-1.f);
    glVertex3f(0.2f,0.84f,-1.f);
    glVertex3f(0.275f,0.9f,-1.f);
    glVertex3f(0.275f,0.8f,-1.f);
    glVertex3f(0.3f,0.91f,-1.f);
    glVertex3f(0.3f,0.82f,-1.f);
    
    glEnd();
}
//as opposed to redrawing it, copy the previous image matrix
void drawRightHalfArch(){
    //Here is where I add the flipped arch
    //There are 2 ways to do the translating, either before or after the scale
    //from experimenting I found out it was 0.6f, or -0.6f if you do it after
    //glTranslatef(0.6f, 0.0f, 0.0f);
    glPushMatrix();

    glScalef(-1.0f, 1.0f, 1.0f);
    glTranslatef(-0.6f, 0.0f, 0.0f);

    drawLeftHalfArch();
    glPopMatrix();
}



//Draw a sun in the top left corner
void addSun(){
    glColor3f(1.f,1.f,0.f);
    glBegin(GL_POLYGON);
    //for (int i = 0; i < 8; i++) {
    //    glVertex3d(sin(i/8.0*2*M_PI), cos(i/8.0*2*M_PI), 0.0f);
    //}
    
    
    glVertex3f(0.02f,0.88f,0.f);
    glVertex3f(0.04f,0.94f,0.f);
    glVertex3f(0.10f,0.98f,0.f);
    glVertex3f(0.16f,0.94f,0.f);
    glVertex3f(0.18f,0.88f,0.f);
    glVertex3f(0.16f,0.84f,0.f);
    glVertex3f(0.10f,0.79f,0.f);
    glVertex3f(0.04f,0.84f,0.f);
    
    glEnd();
}

void display( void )
{
  glClear( GL_COLOR_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  switch(draw_mode){
      case 1:
          //First half of red arch
          glLoadIdentity();
          glPushMatrix();
          
          //glTranslatef(0.0f, 0.0f, 0.0f);
          glColor3f(1.0f, 0.0f, 0.0f);
          drawLeftHalfArch();
          drawRightHalfArch();
          //now the flipped arch is added

          addSun();
          break;
          
      case 2:
          //copy code from case 1
          glLoadIdentity();
          glPushMatrix();
          glColor3f(1.0f, 0.0f, 0.0f);
          //drawLeftHalfArch();
          glColor3f(1.0f, 1.0f, 0.0f);
          //drawRightHalfArch();
          //now the flipped arch is added
          
          //HELEN'S ADDITION: Here I'm trying to see what we can do with translating and scaling. I can't figure out how to get the second arch to appear behind the first one, however.
          glColor3f(0.0f, 1.0f, 1.0f);
          
          glTranslatef(0.15f,0.05f,-0.5f);
          glScalef(0.85f, 0.85f, 0.f);
          drawLeftHalfArch();
          drawRightHalfArch();
          glPopMatrix();
          
          glColor3f(1.0f, 0.0f, 0.0f);
          drawLeftHalfArch();
          drawRightHalfArch();
        
          addSun();
          break;

      case 3:// Draw a triangle
          glColor3f(0.f,0.f,1.f);
          glBegin(GL_TRIANGLES);
          glVertex3f(0.2f,0.1f,0.f);
          glVertex3f(0.4f,0.1f,0.f);
          glVertex3f(0.3f,0.2f,0.f);
          glEnd();
          break;

      case 4:// Draw a quad
          glColor3f(1.f,1.f,0.f);
          glBegin(GL_QUADS);
          glVertex3f(0.6f,0.7f,0.f);
          glVertex3f(0.8f,0.7f,0.f);
          glVertex3f(0.8f,0.9f,0.f);
          glVertex3f(0.6f,0.9f,0.f);
          glEnd();
          break;

      case 5:// Draw a polygon
          glColor3f(1.f,0.f,1.f);
          glBegin(GL_POLYGON);
          glVertex3f(0.6f,0.7f,0.f);
          glVertex3f(0.8f,0.9f,0.f);
          glVertex3f(0.9f,0.7f,0.f);
          glVertex3f(0.8f,0.8f,0.f);
          glVertex3f(0.6f,0.9f,0.f);
          glEnd();
          break;

	  case 6://triangle strip
          glLoadIdentity();
          glBegin(GL_TRIANGLE_STRIP);

          glColor3f(1.f,0.f,0.f);
          glVertex2f(0.2f,0.2f);

          glColor3f(0.f,1.f,0.f);
          glVertex2f(0.2f,0.8f);

          glColor3f(0.f,0.f,1.f);
          glVertex2f(0.5f,0.2f);

          glColor3f(1.f,1.f,0.f);
          glVertex2f(0.5f,0.8f);

          glColor3f(0.f,1.f,1.f);
          glVertex2f(0.8f,0.2f);

          glColor3f(1.f,0.f,1.f);
          glVertex2f(0.8f,0.8f);

          glEnd();
          break;

      case 7://use transforms

          glLineWidth(4.);
          glLoadIdentity();

          //body
          glPushMatrix(); //push identity
          glTranslatef(0.5f,0.75f,0.f);
          glBegin(GL_LINES);
          glColor3f(1.f,1.f,1.f);
          glVertex3f(0.0f,0.0f,0.f);
          glVertex3f(0.0f,-0.25f,0.f);
          glEnd();

          //right arm
          glPushMatrix(); //push body transform
          glRotatef(35.f,0.f,0.f,1.f);
          glBegin(GL_LINES);
          glColor3f(1.f,0.f,0.f);
          glVertex3f(0.0f,0.0f,0.f);
          glVertex3f(0.0f,-0.25f,0.f);
          glEnd();

          //right forearm
          glPushMatrix(); //push right arm transform
          glTranslatef(0.f,-0.25f,0.f);
          glRotatef(-15.f,0.f,0.f,1.f);
          glBegin(GL_LINES);
          glColor3f(0.f,1.f,0.f);
          glVertex3f(0.0f,0.0f,0.f);
          glVertex3f(0.0f,-0.25f,0.f);
          glEnd();

          glPopMatrix(); //load right arm transform
          glPopMatrix(); //load body transform

          //left arm
          glPushMatrix(); //push body transform
          glRotatef(-35.f,0.f,0.f,1.f);
          glBegin(GL_LINES);
          glColor3f(1.f,0.f,0.f);
          glVertex3f(0.0f,0.0f,0.f);
          glVertex3f(0.0f,-0.25f,0.f);
          glEnd();

          //left forearm
          glPushMatrix(); //push left arm transform
          glTranslatef(0.f,-0.25f,0.f);
          glRotatef(15.f,0.f,0.f,1.f);
          glBegin(GL_LINES);
          glColor3f(0.f,1.f,0.f);
          glVertex3f(0.0f,0.0f,0.f);
          glVertex3f(0.0f,-0.25f,0.f);
          glEnd();

          glPopMatrix(); //load left arm transform
          glPopMatrix(); //load body transform

          //right leg
          glPushMatrix(); //push body transform
          glTranslatef(0.f,-0.25f,0.f);
          glRotatef(25.f,0.f,0.f,1.f);
          glBegin(GL_LINES);
          glColor3f(0.f,0.f,1.f);
          glVertex3f(0.0f,0.0f,0.f);
          glVertex3f(0.0f,-0.25f,0.f);
          glEnd();

          //right lower leg
          glPushMatrix(); //push right leg transform
          glTranslatef(0.f,-0.25f,0.f);
          glRotatef(-15.f,0.f,0.f,1.f);
          glBegin(GL_LINES);
          glColor3f(1.f,1.f,0.f);
          glVertex3f(0.0f,0.0f,0.f);
          glVertex3f(0.0f,-0.25f,0.f);
          glEnd();

          glPopMatrix(); //load right leg transform
          glPopMatrix(); //load body transform

          //left leg
          glPushMatrix(); //push body transform
          glTranslatef(0.f,-0.25f,0.f);
          glRotatef(-25.f,0.f,0.f,1.f);
          glBegin(GL_LINES);
          glColor3f(0.f,0.f,1.f);
          glVertex3f(0.0f,0.0f,0.f);
          glVertex3f(0.0f,-0.25f,0.f);
          glEnd();

          //left lower leg
          glPushMatrix(); //push left leg transform
          glTranslatef(0.f,-0.25f,0.f);
          glRotatef(15.f,0.f,0.f,1.f);
          glBegin(GL_LINES);
          glColor3f(1.f,1.f,0.f);
          glVertex3f(0.0f,0.0f,0.f);
          glVertex3f(0.0f,-0.25f,0.f);
          glEnd();

          glPopMatrix(); //load left leg transform
          glPopMatrix(); //load body transform

          glBegin(GL_TRIANGLES);
          glColor3f(1.f,1.f,1.f);
          glVertex3f(-0.1f,0.f,0.f);
          glVertex3f(0.1f,0.f,0.f);
          glVertex3f(0.f,0.15f,0.f);
          glEnd();

          break;
  }

  glutSwapBuffers();
}

void reshape( int w, int h )
{
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  // Question 3: What do the calls to glOrtho()
  // and glViewport() accomplish?
  glOrtho( 0., 1., 0., 1., -1., 1. );//kind of like viewport....
    //(left clip, right clip, bottom clip, top clip, near clip, far clip)
    //This has the z's
    //This is in [0,1] scale, where 1 is the size of the window
    
  glViewport( 0, 0, w, h );//as the window is resized, so is the "viewport" which is the area we have drawn in (and can see)//ie, if we have w/2, h/2 the viewport is 1/4 of the screen (bottom left).//This is in pixel scale

  win_width = w;
  win_height = h;

  glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y ) {
  switch(key) {
      case '1':// Press number keys to switch the draw mode
      case '2':
      case '3':
      case '4':
      case '5':
	  case '6':
      case '7':
          draw_mode=key-'0';
          glutPostRedisplay();
          break;
      case 27: // Escape key
          exit(0);
          break;
  }
}

int main (int argc, char *argv[]) {

  glutInit( &argc, argv );
  // Question 2: What does the parameter to glutInitDisplayMode()
  // specify?
    
    //HELEN ADDED GLUT_DEPTH so that things will overlap properly, except that it's unclear how this actually works. Might need to do more reasearch.
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowSize( win_width, win_height );

  glutCreateWindow( "Intro Graphics Assignment 1" );

  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );

  glutMainLoop();
}
