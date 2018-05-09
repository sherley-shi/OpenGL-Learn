#include <iostream>
#include <GL/glut.h>
#include "Bezier.h"
#include <cmath>


#define R 5
#define MAGIC 0.5
#define PI 3.1415926


using namespace std;

Point Limit1[4][4] = {
    {
    Point{R*sin(0)*sin(0), R*cos(0), R*sin(0)*cos(0)},
    Point{R*MAGIC*sin(PI/2)*sin(0), R*cos(0), R*MAGIC*sin(PI/2)*cos(0)},
    Point{R*sin(PI/2)*sin(0), R*MAGIC*cos(0), R*sin(PI/2)*cos(0)},
    Point{R*sin(PI/2)*sin(0), R*cos(PI/2), R*sin(PI/2)*cos(0)}
    },
    {
    Point{R*sin(0)*sin(0), R*cos(0), R*sin(0)*cos(0)},
    Point{R*MAGIC*MAGIC*sin(PI/2)*sin(PI/2), R*cos(0), R*MAGIC*sin(PI/2)*cos(0)},
    Point{R*MAGIC*sin(PI/2)*sin(PI/2), R*MAGIC*cos(0), R*sin(PI/2)*cos(0)},
    Point{R*MAGIC*sin(PI/2)*sin(PI/2), R*cos(PI/2), R*sin(PI/2)*cos(0)}
    },
    {
    Point{R*sin(0)*cos(0), R*cos(0), R*sin(0)*cos(0)},
    Point{R*MAGIC*sin(PI/2)*sin(PI/2), R*cos(0), R*MAGIC*MAGIC*sin(PI/2)*cos(0)},
    Point{R*sin(PI/2)*sin(PI/2), R*MAGIC*cos(0), R*MAGIC*sin(PI/2)*cos(0)},
    Point{R*sin(PI/2)*sin(PI/2), R*cos(PI/2), R*MAGIC*sin(PI/2)*cos(0)}
    },
    {
    Point{R*sin(0)*cos(0), R*cos(0), R*sin(0)*cos(0)},
    Point{R*MAGIC*sin(PI/2)*sin(PI/2), R*cos(0), R*MAGIC*sin(PI/2)*cos(PI/2)},
    Point{R*sin(PI/2)*sin(PI/2), R*MAGIC*cos(0), R*sin(PI/2)*cos(PI/2)},
    Point{R*sin(PI/2)*sin(PI/2), R*cos(PI/2), R*sin(PI/2)*cos(PI/2)}
    }
};
Point Limit2[4][4], Limit3[4][4], Limit4[4][4], Limit5[4][4],
      Limit6[4][4], Limit7[4][4], Limit8[4][4];

DoBezier *db;


//初始化其他的七个卦限, 一程序开始需要的数据
void init(){
    for( int i=0; i<4; i++ ){
        for( int j=0; j<4; j++ ){
            Limit2[i][j] = Point{Limit1[i][j].x, Limit1[i][j].y, -Limit1[i][j].z};
            Limit3[i][j] = Point{-Limit1[i][j].x, Limit1[i][j].y, -Limit1[i][j].z};
            Limit4[i][j] = Point{-Limit1[i][j].x, Limit1[i][j].y, Limit1[i][j].z};
            Limit5[i][j] = Point{Limit1[i][j].x, -Limit1[i][j].y, Limit1[i][j].z};
            Limit6[i][j] = Point{Limit1[i][j].x, -Limit1[i][j].y, -Limit1[i][j].z};
            Limit7[i][j] = Point{-Limit1[i][j].x, -Limit1[i][j].y, -Limit1[i][j].z};
            Limit8[i][j] = Point{-Limit1[i][j].x, -Limit1[i][j].y, Limit1[i][j].z};
        }
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    db = new DoBezier();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    db->ReadControlPoint(Limit1);
    //db->DrawContorlPoint();
    db->DrawControlGrid();
    db->DrawPatch();
    db->ReadControlPoint(Limit2);
    //db->DrawContorlPoint();
    db->DrawControlGrid();
    db->DrawPatch();
    db->ReadControlPoint(Limit3);
    //db->DrawContorlPoint();
    db->DrawControlGrid();
    db->DrawPatch();
    db->ReadControlPoint(Limit4);
    //db->DrawContorlPoint();
    db->DrawControlGrid();
    db->DrawPatch();
    db->ReadControlPoint(Limit5);
    //db->DrawContorlPoint();
    db->DrawControlGrid();
    db->DrawPatch();
    db->ReadControlPoint(Limit6);
    //db->DrawContorlPoint();
    db->DrawControlGrid();
    db->DrawPatch();
    db->ReadControlPoint(Limit7);
    //db->DrawContorlPoint();
    db->DrawControlGrid();
    db->DrawPatch();
    db->ReadControlPoint(Limit8);
    //db->DrawContorlPoint();
    db->DrawControlGrid();
    db->DrawPatch();
    glFlush();
}
void reshape(int w, int h){
    w=w>h?h:w;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("BALL");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
