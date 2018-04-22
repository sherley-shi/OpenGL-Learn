#include <iostream>
#include <GL/glut.h>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include "transformation.h"


#define SOLID 1
#define WIRE 2


using namespace std;


// datas
static float R=0,.5;
int spinX=0, spinY=0, spinZ=0;
int moveX, moveY, moveZ, des=0;
float scale=1.0;
vector<point> cube_ps={
    point{0.3, 0.3, 0.3, 1},
    point{0.3, 0.3, -0.3, 1},
    point{-0.3, 0.3, -0.3, 1},
    point{-0.3, 0.3, 0.3, 1},
    point{0.3, -0.3, 0.3, 1},
    point{0.3, -0.3, -0.3, 1},
    point{-0.3, -0.3, -0.3, 1},
    point{-0.3, -0.3, 0.3, 1}
};
int rt[4]={0, 1, 5, 4};
int lt[4]={3, 2, 6, 7};
int ft[4]={0, 3, 7, 4};
int bt[4]={1, 2, 6, 5};
TransFormation *tf = new TransFormation(cube_ps);


// functions
void mouseClick(int btn, int state, int x, int y);
void mouseMove(int x, int y);
void draw_ball(double R, double x, double y, double z, int MODE);
void draw_cube();
void key_callback(unsigned char key, int x, int y);
void init();
void display();
void reshape(int w, int h);


int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutCreateWindow("zs de  ballon");
    init();
    glutDisplayFunc(display);
    //glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(key_callback);
    glutMainLoop();
    return 0;
}


void mouseClick(int btn , int state, int x, int y){
    printf("点击: btn: %d\n", btn);
    if( btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN ){
        printf("全局回调函数启动\n");
        glutIdleFunc(display);
    }
    if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
        printf("全局回调函数关闭\n");
        glutIdleFunc(NULL);
    }
    moveX=x, moveY=y;
}


//鼠标移动事件
//glutMotionFunc()调用
void mouseMove(int x, int y){
    int dx=x-moveX;
    int dy=y-moveY;
    printf("dx:%d, dy:%d\n", dx, dy);
    spinX+=dx, spinY+=dy;
    glutPostRedisplay();
    moveX=x, moveY=y;
}


//看球的模式，以及用xyz进行评议后显示
//模拟默认的球半径是0.1每次空格加1
void draw_ball(double R, double x, double y, double z, int MODE){
    glPushMatrix();
    glTranslated(x, y, z);
    if (MODE==SOLID){
        glutSolidSphere(R, 20, 20);
    } else if(MODE == WIRE){
        glutWireSphere(R, 20, 20);
    }
    glPopMatrix();
    glFlush();
}

//画球
void draw_cube(){
    //画四个面让小圆套在正方体内，然后鼠标拖动完成旋转
    glBegin(GL_QUADS);
    {
        for( int i=0; i<4; i++ ){
            glColor3f(cube_ps[rt[i]].x, cube_ps[rt[i]].y, cube_ps[rt[i]].z);
            glVertex3f(cube_ps[rt[i]].x, cube_ps[rt[i]].y, cube_ps[rt[i]].z);
        }
        for ( int i=0; i<4; i++ ){
            glColor3f(cube_ps[bt[i]].x, cube_ps[bt[i]].y, cube_ps[bt[i]].z);
            glVertex3f(cube_ps[bt[i]].x, cube_ps[bt[i]].y, cube_ps[bt[i]].z);
        }
        for( int i=0; i<4; i++ ){
            glColor3f(cube_ps[lt[i]].x, cube_ps[lt[i]].y, cube_ps[lt[i]].z);
            glVertex3f(cube_ps[lt[i]].x, cube_ps[lt[i]].y, cube_ps[lt[i]].z);
        }
        for( int i=0; i<4; i++ ){
            glColor3f(cube_ps[ft[i]].x, cube_ps[ft[i]].y, cube_ps[ft[i]].z);
            glVertex3f(cube_ps[ft[i]].x, cube_ps[ft[i]].y, cube_ps[ft[i]].z);
        }
    }
    glEnd();
    glFlush();
}

void key_callback(unsigned char key, int x, int y){
    switch(key) {
    case 'w':
        //向上移动
        des+=2;
        tf->Translate(0, des, 0);
        printf("按下 w, des=:%d\n", des);
        break;
    case 's':
        des-=2;
        tf->Translate(0, des, 0);
        printf("按下s, des=%d\n", des);
        break;
    case 'D':
        //放大
        R+=1;
        printf("球放大1倍\n");
        tf->Scale(scale, scale, scale);
        break;
    case 'd':
        //缩小
        R-=0.2;
        if (scale<=0)
            scale=0.5;
        printf("球缩小\n");
        tf->Scale(scale, scale, scale);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

//初始化
void init(){
    glLoadIdentity();
}


void display(){
    glRotatef(spinX, 1, 0, 0);
    glRotatef(spinY, 0, 1, 0);
    glRotatef(spinZ, 0, 0, 1);
    spinX++, spinY++, spinZ++;
    sleep(1);
    //usleep(600000);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_ball(0.1, 0, des, 0, 1);
    draw_cube();
}
//变形
void reshape(int w, int h){
    w=w>h?h:w;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
}
