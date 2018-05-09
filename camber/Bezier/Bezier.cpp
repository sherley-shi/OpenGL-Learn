#include <iostream>
#include <GL/glut.h>
#include "Bezier.h"
#include <cmath>


DoBezier::DoBezier(){}

DoBezier::~DoBezier(){}

void DoBezier::ReadControlPoint(Point ps[][4]){
    //读入数据, 三维曲线需要16个点
    for( int i=0; i<4; i++){
        for( int j=0; j<4; j++ ){
            this->p[i][j] = ps[i][j];
        }
    }
}


void DoBezier::DrawPatch(){
    double tmp_m[4][4] = {
        {-1, 3, -3, 1},
        {3, -6, 3, 0},
        {-3, 3, 0, 0},
        {1, 0, 0, 0}
    };
    Point tmp_ps[4][4];
    for( int i=0; i<4; i++ ){
        for( int j=0; j<4; j++ ){
            tmp_ps[i][j] = this->p[i][j];
        }
    }
    this->LeftMulti(tmp_m, tmp_ps);
    //这个矩阵的对称
    this->RightMulti(tmp_ps, tmp_m);
    double u0, u1, u2, u3, v0, v1, v2, v3;
    double step=0.01;
    glColor3f(1, 1, 0);
    glLineWidth(2);
    glPushMatrix();
    for( double  u=0; u<=1; u+=step ){
        glBegin(GL_LINE_STRIP);
        u3 = u*u*u, u2=u*u, u1=u, u0=1;
        for( double v=0; v<=1; v+=step ){
            v3 = v*v*v, v2=v*v, v1=v, v0=1;
            Point new_p = (u3*tmp_ps[0][0]+u2*tmp_ps[1][0]+u1*tmp_ps[2][0]+u0*tmp_ps[3][0])*v3+
                (u3*tmp_ps[0][1]+u2*tmp_ps[1][1]+u1*tmp_ps[2][1]+u0*tmp_ps[3][1])*v2+
                (u3*tmp_ps[0][2]+u2*tmp_ps[1][2]+u1*tmp_ps[2][2]+u0*tmp_ps[3][2])*v1+
                (u3*tmp_ps[0][3]+u2*tmp_ps[1][3]+u1*tmp_ps[2][3]+u0*tmp_ps[3][3])*v0;
            glVertex3f(new_p.x, new_p.y, new_p.z);
        }
        glEnd();
    }
    for(double v=0; v<=1; v+=step){
        v3=v*v*v, v2=v*v,v1=v,v0=1;
        glBegin(GL_LINE_STRIP);
        for(double u=0; u<=1; u+=step){
            u3=u*u*u, u2=u*u, u1=u, u0=1;
            Point new_p = (u3*tmp_ps[0][0]+u2*tmp_ps[1][0]+u1*tmp_ps[2][0]+u0*tmp_ps[3][0])*v3+
                (u3*tmp_ps[0][1]+u2*tmp_ps[1][1]+u1*tmp_ps[2][1]+u0*tmp_ps[3][1])*v2+
                (u3*tmp_ps[0][2]+u2*tmp_ps[1][2]+u1*tmp_ps[2][2]+u0*tmp_ps[3][2])*v1+
                (u3*tmp_ps[0][3]+u2*tmp_ps[1][3]+u1*tmp_ps[2][3]+u1*tmp_ps[3][3])*v0;
            glVertex3f(new_p.x, new_p.y, new_p.z);
        }
        glEnd();
    }
    glPopMatrix();
}

void DoBezier::LeftMulti(double Matrix[][4], Point p[][4]){
    Point tmp[4][4];
    for( int i=0; i<4; i++ ){
        for( int j=0; j<4; j++ ){
            tmp[i][j] = Matrix[i][0]*p[0][j]+Matrix[i][1]*p[1][j]+Matrix[i][2]*p[2][j]+
                        Matrix[i][3]*p[3][j];
        }
    }
    for(int i=0; i<4; i++){
        for( int j=0; j<4; j++ ){
            p[i][j] = tmp[i][j];
        }
    }
}

void DoBezier::RightMulti(Point p[][4], double Matrix[][4]){
    Point tmp[4][4];
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            tmp[i][j] = p[i][0]*Matrix[0][j]+p[i][1]*Matrix[1][j]+p[i][2]*Matrix[2][j]+\
                        p[i][3]*Matrix[3][j];
        }
    }
    for( int i=0; i<4; i++ ){
        for(int j=0; j<4; j++){
            p[i][j] = tmp[i][j];
        }
    }
}

void DoBezier::DrawControlGrid(){
    Point tmp[4][4];
    for( int i=0; i<4; i++ ){
        for( int j=0; j<4; j++ ){
            tmp[i][j].x = p[i][j].x;
            tmp[i][j].y = p[i][j].y;
            tmp[i][j].z = p[i][j].z;
        }
    }
    glColor3f(0, 0, 1);
    glLineWidth(2);
    for(int i=0; i<4; i++){
        glBegin(GL_LINE_STRIP);
        for( int j=0; j<4; j++ ){
            glVertex3f(tmp[i][j].x, tmp[i][j].y, tmp[i][j].z);
        }
        glEnd();
    }
    for(int j=0; j<4; j++){
        glBegin(GL_LINE_STRIP);
        for(int i=0; i<4; i++){
            glVertex3f(tmp[i][j].x, tmp[i][j].y, tmp[i][j].z);
        }
        glEnd();
    }
}

void DoBezier::DrawContorlPoint(){
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    for( int i=0;i <4; i++ ){
        for( int j=0; j<4; j++ ){
            glVertex3f(p[i][j].x, p[i][j].y, p[i][j].z);
        }
    }
    glEnd();
}

