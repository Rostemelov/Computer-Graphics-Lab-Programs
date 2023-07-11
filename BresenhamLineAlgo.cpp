#include<stdio.h>
#include<stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

int x1,x2,y1,y2;

void draw_pixel(int x,int y)
{
    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);
    glVertex2i(x,y);
    glEnd();
}

void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
}

void draw_line()
{
    int i=1,e,dx,dy,x=x1,y=y1;
    dx=x2-x1;dy=y2-y1;
    e=2*dy-dx;
    draw_pixel(x,y);
    do
    {
        while(e>=0)
        {
            y=y+1;
            e=e-2*dx;
        }
        x=x+1;
        e=e+2*dy;
        draw_pixel(x,y);
        i++;
    }while(i<=dx);
}

void display()
{
    draw_line();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    printf("Enter Start and ending points");
    scanf("%d%d%d%d", &x1,&y1,&x2,&y2);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Bresenham");
    glutInitWindowSize(500.0,500.0);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
