#include "parameters.h"
#include "simulation.h"

#include <stdio.h>
#include <GL/glut.h>
#include <iostream>

#define PRE_ITERATIONS 0
#define ITERATIONS_PER_FRAME 50000

using namespace std;

void Render();
void keyboard(unsigned char, int, int);
void Idle();
void Resize(int, int);

Simulation sim(dimension, 3, 0.1, 1.4);

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
	glPointSize(250.0/(float)dimension);

    glutDisplayFunc(Render);
    glutReshapeFunc(Resize);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Idle);

    glutMainLoop();
    return 0;
}

const unsigned char colours[3][3] = {{ 199, 67, 60}, {168, 186, 182}, {159, 67, 149}};

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sim.evolve(ITERATIONS_PER_FRAME);
    sim.sample();

	glBegin(GL_POINTS);
	for (int i=0; i<dimension; i++ ) {
        for (int j=0; j<dimension; j++ ) {
            int spin = sim.lattice1[i*dimension+j];
            glColor3ubv(colours[spin]);
            glVertex2i(i,j);
        }
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
    glOrtho(-1,dimension,-1,dimension,-1,1);
}
