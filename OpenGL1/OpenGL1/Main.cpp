#pragma comment(lib, "libglew32.lib")
#pragma comment(lib, "freeglut_static.lib")
#define _CRT_SECURE_NO_WARNINGS
#define GLEW_STATIC
#define FREEGLUT_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0
#include <glew.h>
#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "object.h"
#include "load_3ds.h"
#include "load_bmp.h"

int aatoggle;

float xpos = 0, ypos = -5, zpos = 0, xrot = 0, yrot = 0, zrot = 0;
float lastx, lasty;
float rotquad;
float testx = 0, testy = 0, testz = 3, testscale = 1;

obj_type object;

GLfloat light_ambient[]= { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_position[]= { 45.0f, 1.0f, 1.0f, 0.0f };

//Materials settings
GLfloat mat_ambient[]= { 0.1f, 0.1f, 0.1f, 0.0f };
GLfloat mat_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat mat_specular[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_shininess[]= { 1.0f };


void init()
{
	glClearColor(0.25, 0.25, 0.25, 1.0);


	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	glShadeModel(GL_SMOOTH); // Type of shading for the polygons
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Texture mapping perspective correction (OpenGL... thank you so much!)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
	glEnable(GL_CULL_FACE); // Enable the back face culling
	glEnable(GL_DEPTH_TEST); // Enable the depth test (also called z buffer)


	glEnable(GL_TEXTURE_2D); //This Enable the Texture mapping
    Load3DS(&object,"test.3ds");
    object.id_texture=LoadBMP("texture.bmp"); //The Function LoadBitmap() return the current texture ID
    //If the last function returns -1 it means the file was not found so we exit from the program
	if(object.id_texture==-1)
	{
		getchar();
		exit(0);
	}
}
void camera()
{
	glRotatef(xrot, -1.0, 0.0, 0.0); //(left and right)
	glRotatef(yrot, 0.0, -1.0, 0.0); //(up and down)
	glRotatef(zrot, 0.0, 0.0, -1.0); //(zoom in and out)
	glTranslated(-xpos, -ypos, -zpos); //translate the screen to the position of our camera
}
void enable()
{
	glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glEnable(GL_LIGHT1);
}
void antialiasing()
{
	if(aatoggle==0)
	{
		glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_POINT_SMOOTH);
	}
	if(aatoggle==1)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glLoadIdentity(); // Initialize the model matrix as identity
	camera();
	enable();
	antialiasing();

	/*
	//DRAW CUBE
	glPushMatrix();
	glTranslatef(testx, testy, testz);
	//glTranslatef(0.0f, 0.0f,-7.0f); //Translate Into The Screen 7.0 Units
	glRotatef(rotquad,0.0f,1.0f,0.0f); //Rotate The cube around the Y axis
	glRotatef(rotquad,1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f); //Color Blue
		glVertex3f( 1.0f  * testscale, 1.0f  * testscale,-1.0f  * testscale); //Top Right Of The Quad (Top)
		glVertex3f(-1.0f  * testscale, 1.0f  * testscale,-1.0f  * testscale); //Top Left Of The Quad (Top)
		glVertex3f(-1.0f  * testscale, 1.0f  * testscale, 1.0f  * testscale); //Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f  * testscale, 1.0f  * testscale, 1.0f  * testscale); //Bottom Right Of The Quad (Top)
		glColor3f(1.0f, 0.5f, 0.0f); //Color Orange
		glVertex3f( 1.0f  * testscale,-1.0f  * testscale, 1.0f  * testscale); //Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f  * testscale,-1.0f  * testscale, 1.0f  * testscale); //Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f  * testscale,-1.0f  * testscale,-1.0f  * testscale); //Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f  * testscale,-1.0f  * testscale,-1.0f  * testscale); //Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f, 0.0f, 0.0f); //Color Red
		glVertex3f( 1.0f  * testscale, 1.0f  * testscale, 1.0f  * testscale); //Top Right Of The Quad (Front)
		glVertex3f(-1.0f  * testscale, 1.0f  * testscale, 1.0f  * testscale); //Top Left Of The Quad (Front)
		glVertex3f(-1.0f  * testscale,-1.0f  * testscale, 1.0f  * testscale); //Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f  * testscale,-1.0f  * testscale, 1.0f  * testscale); //Bottom Right Of The Quad (Front)
		glColor3f(1.0f, 1.0f, 0.0f); //Color Yellow
		glVertex3f( 1.0f  * testscale,-1.0f  * testscale,-1.0f  * testscale); //Top Right Of The Quad (Back)
		glVertex3f(-1.0f  * testscale,-1.0f  * testscale,-1.0f  * testscale); //Top Left Of The Quad (Back)
		glVertex3f(-1.0f  * testscale, 1.0f  * testscale,-1.0f  * testscale); //Bottom Left Of The Quad (Back)
		glVertex3f( 1.0f  * testscale, 1.0f  * testscale,-1.0f  * testscale); //Bottom Right Of The Quad (Back)
		glColor3f(0.0f, 0.0f, 1.0f); //Color Blue
		glVertex3f(-1.0f  * testscale, 1.0f  * testscale, 1.0f  * testscale); //Top Right Of The Quad (Left)
		glVertex3f(-1.0f  * testscale, 1.0f  * testscale,-1.0f  * testscale); //Top Left Of The Quad (Left)
		glVertex3f(-1.0f  * testscale,-1.0f  * testscale,-1.0f  * testscale); //Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f  * testscale,-1.0f  * testscale, 1.0f  * testscale); //Bottom Right Of The Quad (Left)
		glColor3f(1.0f, 0.0f, 1.0f); //Color Violet
		glVertex3f( 1.0f  * testscale, 1.0f  * testscale,-1.0f  * testscale); //Top Right Of The Quad (Right)
		glVertex3f( 1.0f  * testscale, 1.0f  * testscale, 1.0f  * testscale); //Top Left Of The Quad (Right)
		glVertex3f( 1.0f  * testscale,-1.0f  * testscale, 1.0f  * testscale); //Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f  * testscale,-1.0f  * testscale,-1.0f  * testscale); //Bottom Right Of The Quad (Right)
	glEnd();
	rotquad +=0.025f;
	glPopMatrix();

	//QUAD-PLANE
	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-8.0f, 8.0f, 0.0f); //RED
	glColor3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f( 8.0f, 8.0f, 0.0f); //GREEN
	glColor3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f( 8.0f,-8.0f, 0.0f); //BLUE
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-8.0f,-8.0f, 0.0f); //WHITE
	glEnd();
	glPopMatrix();
	*/
	
	/*
	//XYZ-ARROWS
	glPushMatrix();
	glBegin(GL_LINES);
	//X-AXIS
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f( 100.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-100.0f, 0.0f, 0.0f);
	//Y-AXIS
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f( 0.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f( 0.0f,-100.0f, 0.0f);
	//Z-AXIS
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 0.0f, 0.0f, 100.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 0.0f, 0.0f,-100.0f);
	glEnd();
	glPopMatrix();
	*/

	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, -2.0f);
	glBegin(GL_TRIANGLES); //glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
	//glBindTexture(GL_TEXTURE_2D, object.id_texture); //We set the active texture
	//glColor3f(0.0f, 0.0f, 0.0f);
	if(object.id_texture!=-1)
	{
		glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 
		glEnable(GL_TEXTURE_2D); // Texture mapping ON
	}
	else
	{
		glDisable(GL_TEXTURE_2D); // Texture mapping OFF
	}
	for(int l_index=0; l_index<object.polygons_qty; l_index++)
	{
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
                      object.mapcoord[ object.polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
                    object.vertex[ object.polygon[l_index].a ].y,
                    object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
                      object.mapcoord[ object.polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
                    object.vertex[ object.polygon[l_index].b ].y,
                    object.vertex[ object.polygon[l_index].b ].z);
        
        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
                      object.mapcoord[ object.polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
                    object.vertex[ object.polygon[l_index].c ].y,
                    object.vertex[ object.polygon[l_index].c ].z);
    }
	glEnd();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w/(GLfloat)h, 1.0, 1000.0);
	//glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
	if(key=='o')testz=25;
	if(key=='1')xrot = 90;
	if(key=='2')yrot = 0;
	if(key=='3')zrot = 0;
	if(key=='q')
	{
		xrot += 1;
		if(xrot > 360)xrot -= 360;
	}
	if(key=='z')
	{
		xrot -= 1;
		if(xrot < -360)xrot += 360;
	}
	if(key=='w')
	{
		float xrotrad, yrotrad, zrotrad;
		xrotrad = (xrot/180*3.141592654f);
		yrotrad = (yrot/180*3.141592654f);
		zrotrad = (zrot/180*3.141592654f);
		xpos -= float(sin(zrotrad));
		ypos += float(cos(zrotrad));
		zpos -= float(cos(xrotrad));
	}
	if(key=='s')
	{
		float xrotrad, yrotrad, zrotrad;
		xrotrad = (xrot/180*3.141592654f);
		yrotrad = (yrot/180*3.141592654f);
		zrotrad = (zrot/180*3.141592654f);
		xpos += float(sin(zrotrad));
		ypos -= float(cos(zrotrad));
		zpos += float(cos(xrotrad));
	}
	if(key=='a')
	{
		float zrotrad;
		zrotrad = (zrot/180*3.141592654f);
		xpos -= float(cos(zrotrad))*0.75;
		ypos -= float(sin(zrotrad))*0.75;
	}
	if(key=='d')
	{
		float zrotrad;
		zrotrad = (zrot/180*3.141592654f);
		xpos += float(cos(zrotrad))*0.75;
		ypos += float(sin(zrotrad))*0.75;
	}
	if(key=='r')testz += 1.0f;
	if(key=='f')testz -= 1.0f;
	if(key=='l')testx += 1.0f;
	if(key=='j')testx -= 1.0f;
	if(key=='i')testy += 1.0f;
	if(key=='k')testy -= 1.0f;
	if(key=='g')testscale--;
	if(key=='h')testscale++;
	if(key=='p')
	{
		if(aatoggle==0)aatoggle++;
		else{aatoggle--;}
	}
	if(key==27){exit(0);}
}
void mouseMovement(int x, int y)
{
	int diffx = x-lastx;
	int diffy = y-lasty;
	lastx = x;
	lasty = y;
	xrot -= (float)diffy; //UP AND DOWN
	//yrot += (float)diffx; //TILT LEFT AND RIGHT
	zrot -= (float)diffx; //LEFT AND RIGHT
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition (0, 0);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(mouseMovement);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}