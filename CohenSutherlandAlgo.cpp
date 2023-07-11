#include<stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
double x1,y1,x2,y2,m;
double ex1=-1,ex2=-1,ey1=-1,ey2=-1;
double xl=50,xr=100,yt=100,yb=50;
int reg_codes[]={-1,-1};

void drawline()
{
    glBegin(GL_LINES);
    glPointSize(5);
    glColor3f(0.0,1.0,1.0);
    glVertex2d(ex1,ey1);
    glVertex2d(ex2,ey2);
    glEnd();
}

void endpoints()
{
    glBegin(GL_POINTS);
    glPointSize(10);
    glColor3f(0.0,1.0,0.0);
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    glEnd();
}

void windows()
{
    glBegin(GL_LINE_LOOP);
    glPointSize(5);
    glColor3f(1.0,0.0,0.0);
    glVertex2d(xl,yt);
    glVertex2d(xl,yb);
    glVertex2d(xr,yb);
    glVertex2d(xr,yt);
    glEnd();
}

void display()
{
    windows();
    endpoints();
    drawline();
    glFlush();
}

void regcode()
{
    if((x1>xl&&x1<xr)&&(y1>yb&&y1<yt))
    {
        reg_codes[0]=0;
    }
    if((x2>xl&&x2<xr)&&(y2>yb&&y2<yt))
    {
        reg_codes[1]=0;
    }
//------------------------------------------------------------------------------------------------------
    if(x1<xl)
    {
        reg_codes[0]=1;
    }
    if(x2<xl)
    {
        reg_codes[1]=1;
    }
//------------------------------------------------------------------------------------------------------
    if(x1>xr)
    {
        reg_codes[0]=2;
    }
    if(x2>xr)
    {
        reg_codes[1]=2;
    }
//-------------------------------------------------------------------------------------------------------
    if(y1<yb)
    {
        reg_codes[0]=4;
    }
    if(y2<yb)
    {
        reg_codes[1]=4;
    }
//----------------------------------------------------------------------------------------------------------
    if(y1>yt)
    {
        reg_codes[0]=8;
    }
    if(y2>yt)
    {
        reg_codes[1]=8;
    }
//--------------------------------------------------------------------------------------------------------------
}

void cohen()
{
    if(reg_codes[0]==reg_codes[1] && reg_codes[1]!=0)
    {
        ex1=0;ex2=0;ey1=0;ey2=0;
        return;
    }
    else
    {
        if(reg_codes[0]==0)
        {
            ex1=x1;ey1=y1;
        }
        if(reg_codes[1]==0)
        {
            ex2=x2;ey2=y2;
        }
 //---------------------------------------------------------------------------------------------------------------------------
        if(reg_codes[0]==1)
        {
            ex1=xl;
            ey1=m*(xl-x1)+y1;
        }
        if(reg_codes[1]==1)
        {
            ex2=xl;
            ey2=m*(xl-x2)+y2;
        }
//-----------------------------------------------------------------------------------------------------------------------------------
    if(reg_codes[0]==2)
        {
            ex1=xr;
            ey1=m*(x1-xr)+y1;
        }
        if(reg_codes[1]==2)
        {
            ex2=xr;
            ey2=m*(x2-xr)+y2;
        }
//--------------------------------------------------------------------------------------------------------------------------------
       if(reg_codes[0]==4)
        {
            ey1=yb;
            ex1=(yb-y1)/m+x1;
        }
        if(reg_codes[1]==4)
        {
            ey2=yb;
            ex2=(yb-y2)/m+x2;
        }
//-----------------------------------------------------------------------------------------------------------------------------------
    if(reg_codes[0]==8)
        {
            ey1=yt;
            ey1=(y1-yt)/m+x1;
        }
        if(reg_codes[1]==8)
        {
            ey2=yt;
            ex2=(y2-yt)/m+x2;
        }
//--------------------------------------------------------------------------------------------------------------------------------
    }
}



void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,200,0,200);
}
int main(int argc, char *argv[])
{
    printf("Enter the endpoints of the line:\n");
    scanf("%lf%lf%lf%lf", &x1,&y1,&x2,&y2);
    m=(y2-y1)/(x2-x1);
    regcode();
    printf("The region codes are: %d and %d\n", reg_codes[0],reg_codes[1]);
    cohen();
    printf("The coordinates after clipping are: (%f,%f), (%f,%f)", ex1,ey1,ex2,ey2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Cohen Sutherland");
    glutInitWindowSize(300,300);
    glutInitWindowPosition(0,0);
    glutDisplayFunc(display);
    init();
    glutMainLoop();

    return EXIT_SUCCESS;
}
