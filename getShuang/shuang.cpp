#include <iostream>
#include <queue>
#include <GL/glut.h>
#include <cstdio>
#include <cstdlib>

#define WIDTH 800
#define HEIGH 800
#define Gl_FILL 0x1B02
using namespace std;

typedef  float Color[3];

const int direction[4][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};

const int X[12][2]={
    {200, 460},
    {230, 430},
    {260, 460},
    {280, 440},
    {250, 410},
    {280, 380},
    {260, 360},
    {230, 390},
    {200, 360},
    {180, 380},
    {210, 410},
    {180, 440},
};

struct point{
    int x, y;
};


const int index1[4]={0,1, 6, 7};
const int index2[4]={3, 4, 9, 10};
const float fColor[3]={0.0, 0.0, 1.0};//16711680, 16777216


bool compare(Color color1, Color color2){
    if( color1[0]!=color2[0] || color1[1]!= color2[1] || color1[2]!=color2[3]){
        return false;
    }
    return true;
}


void DrawShuang(){
    glColor3f(0.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    //绿色的爽, 以400.500作为一个中心
    //glColor3f(0.0, 1.0, 0.0);
    glVertex2f(150.0, 550.0);
    glVertex2f(650.0, 550.0);
    glVertex2f(650.0, 500.0);
    glVertex2f(150.0, 500.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(370.0, 550.0);
    glVertex2f(370.0, 650.0);
    glVertex2f(430.0, 650.0);
    glVertex2f(430.0, 550.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(430.0, 500.0);
    glVertex2f(350.0, 100.0);
    glVertex2f(290.0, 100.0);
    glVertex2f(370.0, 500.0);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(400.0, 350.0);
    glVertex2f(500.0, 100.0);
    glVertex2f(450.0, 100.0);
    glVertex2f(383.3, 266.8);
    glEnd();
    /*
    //下半部分
    glVertex2f(400.0, 350.0);
    glVertex2f(500.0, 100.0);
    glVertex2f(450.0, 100.0);
    //焦点
    glVertex2f(383.3, 266.8);
    glVertex2f(350.0, 100.0);
    glVertex2f(290, 100.0);
    glVertex2f(370.0, 500.0);
    glVertex2f(150.0, 500.0);
    glEnd();
    */
    glFlush();

    //画四个叉
    glBegin(GL_POLYGON);
    {
        for( int i=0; i<4; i++ )
            glVertex2f(X[index1[i]][0], X[index1[i]][1]);
    }
    glEnd();
    glBegin(GL_POLYGON);
    {
        for( int i=0; i<4; i++ )
            glVertex2f(X[index2[i]][0], X[index2[i]][1]);
    }
    glEnd();


    glBegin(GL_POLYGON);
    {
        for( int i=0; i<4; i++ ){
            glVertex2f(2*400-X[index1[i]][0], X[index1[i]][1]);
        }
    }
    glEnd();
    glBegin(GL_POLYGON);
    {
        for( int i=0; i<4; i++ )
            glVertex2f(2*400-X[index2[i]][0], X[index2[i]][1]);
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        for( int i=0; i<4; i++ ){
            glVertex2f(X[index1[i]][0], 700-X[index1[i]][1]);
        }
    }
    glEnd();
    glBegin(GL_POLYGON);
    {
        for( int i=0; i<4; i++ )
            glVertex2f(X[index2[i]][0], 700-X[index2[i]][1]);
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        for( int i=0; i<4; i++ ){
            glVertex2f(800-X[index1[i]][0], 700-X[index1[i]][1]);
        }
    }
    glEnd();
    glBegin(GL_POLYGON);
    {
        for( int i=0; i<4; i++ )
            glVertex2f(800-X[index2[i]][0], 700-X[index2[i]][1]);
    }
    glEnd();
    //f(200, 400, fColor);

    glFlush();
}



void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGH);
    glMatrixMode(GL_MODELVIEW);
}



void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    DrawShuang();
}


void reshape(GLsizei w, GLsizei h){
    w=w>h?h:w;
    glViewport(0, 0, w, h);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGH);
    glutCreateWindow("SHUANG");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    /*
    GLint* p=(GLint*)malloc(1);
    glReadPixels(150, 550, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, p);
    cout << int(p[0]) << endl;
    free(p);
    */
    glutMainLoop();
    return 0;
}
