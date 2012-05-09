#include "parameters.h"
#include "simulation.h"

#include <stdio.h>
#include <GL/glut.h>
#include <iostream>


using namespace std;

void Render();
void keyboard(unsigned char, int, int);
void Idle();
void Resize(int, int);

Simulation sim(DIMENSION, 0.4, 2);

/////////////// Main Program ///////////////////////////
int main(int argc, char* argv[])
{
    int start = glutGet(GLUT_ELAPSED_TIME);
    sim.evolve(PRE_ITERATIONS);
    int end = glutGet(GLUT_ELAPSED_TIME);
    cout << "Run-in time: " << end-start << "ms. " << PRE_ITERATIONS << " iterations." <<endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

    glutInitWindowSize(512,512);
    glutInitWindowPosition(100,100);

    glutCreateWindow("Potts model");

    glShadeModel(GL_SMOOTH);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glPointSize(300.0/(float)DIMENSION);

    glutDisplayFunc(Render);
    glutReshapeFunc(Resize);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Idle);

    glutMainLoop();
    return 0;
}

const unsigned char colours[4][3] = {{168, 186, 182}, { 199, 67, 60}, {159, 67, 149}, {255,255,255}};

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sim.evolve(ITERATIONS_PER_SAMPLE);
    sim.sample();

	glBegin(GL_POINTS);
    for (int i=0; i<DIMENSION; i++ ) {
        for (int j=0; j<DIMENSION; j++ ) {
            unsigned char diff = sim.difference[i*DIMENSION+j];
            glColor3ubv(colours[diff]);
            glVertex2i(i,j);
        }
    }
    glColor3ub(0,0,0);
    for (int i=0; i<DIMENSION; i++ ) {
        glVertex2i(i,sim.interface[i]);
    }
    glEnd();


    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
		case 27:
			exit(0);
    }
    glutPostRedisplay();
}

void Idle()
{
    glutPostRedisplay();
}

void Resize(int w, int h)
{
    // define the visible area of the window ( in pixels )
    if (h==0) h=1;
    glViewport(0,0,w,h);

    // Setup viewing volume

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //         L	   R 	  B 	T	 N	   F
    glOrtho(-1,DIMENSION,-1,DIMENSION,-1,1);
}
