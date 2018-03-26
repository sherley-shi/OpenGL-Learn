#include <iostream>
#include <GL/glut.h>
#include <cstdio>
#include <ctime>
#include <cmath>

#define R 100
#define PI 3.1415926

int H_LEN = R-25, M_LEN=R-15;

//十分秒, 用来计算角度
float s, h, m, cnt;

using namespace std;
void DrawRound(int x0, int y0, int r){    
        int x, y, d;
        x=0, y=r, d=3-2*r;
        glVertex2i(x0+x, y0+y);
        while(x<y){
            if(d<0){
                d=d+4*x+6;
            }
            else{
                d=d+4*(x-y)+10;
                y--;
            }
            x++;
            glVertex2i(x0+x, y0+y);
            glVertex2i(x0+y, y0+x);
            glVertex2i(x0+y, y0-x);
            glVertex2i(x0+x, y0-y);
            glVertex2i(x0-x, y0-y);
            glVertex2i(x0-y, y0-x);
            glVertex2i(x0-y, y0+x);
            glVertex2i(x0-x, y0+y);
        }
}

void Draw12Points(){
    for( int i=0; i<12; i++ ){
        if (i == 0){
            //12点
            glLineWidth(30);
            glColor3f(1.0, 0.0, 0.0);
        }
        else{
            glLineWidth(20);
            glColor3f(0.0, 0.0, 0.0);
        }
        glBegin(GL_LINES);
            glVertex2f(400+(R-3)*sin(2*PI/12*i), 400+(R-3)*cos(2*PI/12*i));
            glVertex2f(400+(R)*sin(2*PI/12*i), 400+(R)*cos(2*PI/12*i));
        glEnd();
    }
}

//传如圆心的位置
void MidPointLine(float start_x, float start_y, float end_x, float end_y){
    int a,b,d1,d2,d,x,y;
    float m;
    if (end_x<start_x){d=start_x,start_x=end_x,end_x=d;d=start_y, start_y=end_y,end_y=d;}
    a=start_y-end_y,b=end_x-start_x;
    if (b==0) 
        m=-1*a*100;  
    else 
        m=(float)a/(start_x-end_x);x=start_x,y=start_y;
    glVertex2f(x,y);         
    if (m>=0 && m<=1)
    {
        d=2*a+b;d1=2*a,d2=2*(a+b);  
        while (x<end_x)  
        {  
            if (d<=0){   
                x++,y++,d+=d2;
            }  
            else{   
                x++,d+=d1;  
            }  
            glVertex2f(x,y);  
        }
    }  
    else if (m<=0 && m>=-1){
        d=2*a-b;d1=2*a-2*b,d2=2*a;  
        while (x<end_x){  
            if (d>0){   
                x++,y--,d+=d1;
            }  
            else{   
                x++,d+=d2;  
            }
            glVertex2f(x,y);  
        }  
    }  
    else if (m>1){
        d=a+2*b;d1=2*(a+b),d2=2*b;
        while (y<end_y){  
            if (d>0){   
                x++,y++,d+=d1;
            }
            else{   
                y++,d+=d2;
            }
            glVertex2f(x,y);  
        }  
    }
    else{
        d=a-2*b;d1=-2*b,d2=2*(a-b); 
        while (y>end_y){  
            if (d<=0){   
                x++,y--,d+=d2;
            }
            else{   
                y--,d+=d1;  
            }
            glVertex2f(x,y);  
        }
    }   
 
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glPointSize(8);
    glBegin(GL_POINTS);
    {
        DrawRound(400, 400, R);
    }
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glPointSize(10);
    Draw12Points();

    //时针
    float s_angel, m_angel, h_angel;
    //分针, 1m=60秒, 1h=3600s
    cnt=60;
    //秒真的数
    s_angel=s/cnt;
    cnt*=60;
    //分针的度数
    m_angel=(m*60+s)/cnt;
    cnt*=12;
    //时针的度数
    h_angel=(h*3600+m*60+s)/cnt;

    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(8);
    glBegin(GL_LINES);
    {
        MidPointLine(400, 400, 400+R*sin(2*PI*s_angel), 400+R*cos(2*PI*s_angel));
    }
    glEnd();

    glLineWidth(10);
    glBegin(GL_LINES);
    {
        MidPointLine(400, 400, 400+M_LEN*sin(2*PI*m_angel), 400+M_LEN*cos(2*PI*m_angel));
    }
    glEnd();

    glLineWidth(12);
    glBegin(GL_LINES);
    {
        MidPointLine(400, 400, 400+H_LEN*sin(2*PI*h_angel), 400+H_LEN*cos(2*PI*h_angel));
    }
    glEnd();

    glutSwapBuffers();
    //glFlush();
}
//窗口放大的调整
void reshapse(GLsizei w, GLsizei h){
    w=w>h?h:w;
    glViewport(0, 0, w, h);
}

void update(){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);
    h=timeinfo->tm_hour;
    m=timeinfo->tm_min;
    s=timeinfo->tm_sec;
    glutPostRedisplay();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 800);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Round");
    init();
    glutReshapeFunc(reshapse);
    glutIdleFunc(update);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapse);
    glutMainLoop();
    return 0;
}
