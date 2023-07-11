#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
int x=2,y=-1;
int where=3;
float tx=0,ty=0;
float theta=0;

void drawTriangle(float x1, float y1)
{
    glColor3f(0.0,0.5,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(x1,y1);
    glVertex2f(x1+1.0,y1+1.0);
    glVertex2f(x1+2.0,y1+0.0);
    glFlush();
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if(where==1)
    {
        tx=0;
        ty=0;
        theta+=1;
    }
    if(where==2)
    {
        tx=x;
        ty=y;
        theta+=1;
    }
    glTranslatef(tx,ty,0);
    glRotatef(theta,0,0,1);
    glTranslatef(-tx,-ty,0);
    drawTriangle(tx,ty);
    glutPostRedisplay();
    glutSwapBuffers();
}

void select(int opt)
{
    where=opt;
}

void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    gluOrtho2D(-500,500,-500,500);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(1000,1000);
    glutInitWindowSize(2000,2000);
    glutCreateWindow("Rotate Triangle");
    init();
    glutDisplayFunc(display);
    glutCreateMenu(select);
    glutAddMenuEntry("Rotate at Origin",1);
    glutAddMenuEntry("Rotate at Point",2);
    glutAddMenuEntry("Stop",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}
