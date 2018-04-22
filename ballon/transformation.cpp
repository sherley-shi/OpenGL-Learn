#include <iostream>
#include "transformation.h"


TransFormation::TransFormation(std::vector<point>&ps){
    ps=ps;
    E();
}

void TransFormation::E(){
    for( int i=0; i<4; i++ ){
        for( int j=0; j<4; j++ ){
            if(i==j)
                matrix[i][j]=1;
            else
                matrix[i][j]=0;
        }
    }
}

void TransFormation::MultiMatrix(){
    for( unsigned int i=0; i<ps.size(); i++ ){
        ps[i].x=ps[i].x*matrix[0][0]+ps[i].y*matrix[1][0]+ps[i].z*matrix[2][0]+ps[i].res*matrix[3][0];
        ps[i].y=ps[i].x*matrix[0][1]+ps[i].y*matrix[1][1]+ps[i].z*matrix[2][1]+ps[i].res*matrix[3][1];
        ps[i].z=ps[i].x*matrix[0][2]+ps[i].y*matrix[1][2]+ps[i].z*matrix[2][2]+ps[i].res*matrix[3][2];
        ps[i].res=ps[i].x*matrix[0][3]+ps[i].y*matrix[1][3]+ps[i].z*matrix[2][3]+ps[i].res*matrix[3][3];
    }
}

void TransFormation::Translate(float x, float y, float z){
    //当鼠标划过，圆和正方体换这套
    E();
    matrix[3][0]=x, matrix[3][1]=y, matrix[3][2]=z;
    MultiMatrix();
}

void TransFormation::ReflectX(){
    E();
    matrix[1][1]=-1, matrix[2][2]=-1;
    MultiMatrix();
}

void TransFormation::Scale(float x, float y, float z){
    E();
    matrix[0][0]=x, matrix[1][1]=y, matrix[2][2]=z;
    MultiMatrix();
}

