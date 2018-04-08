#include <iostream>
#include <queue>
#include <GL/glut.h>
#include <stack>

#define WIDTH 200
#define HEIGH 200
#define Gl_FILL 0x1B02
using namespace std;

const int direction[4][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};


const float X[12][2]={
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

float shuang[16][2] = {
    {-12.5, 2}, {-2.5, 2}, {-2.5, 5}, {2.5, 5},
    {2.5, 2}, {12.5, 2}, {12.5, -2}, {2.5, -2},
    {0.5, -6}, {7.5, -12}, {2.5, -12}, {-1.01, -5.5},
    {-2.5, -12}, {-7.5, -12}, {-2.5, -2}, {-12.5, -2}
};

struct point{
    int x, y;
};


typedef float Color[3];
Color fill_color={0.0, 1.0, 0.0};
Color border_color={1.0, 0.0, 0.0};


void setPiexl(GLint x, GLint y, Color color){
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}


bool compare(Color c1, Color c2){
    if ( c1[0]!=c2[0] || c1[1]!=c2[1] || c1[2]!=c2[2] )
        return false;
    return true;
}


bool isPixelValid(int x, int y, Color fill_color, Color border_color){
    Color tmp;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, tmp);
    if( !compare(tmp, fill_color) && !compare(tmp, border_color) )
        return true;
    return false;
}


int fill_left(GLint x, GLint y, Color fill_color, Color border_color){
    while(isPixelValid(x, y, fill_color, border_color)){
        setPiexl(x, y, fill_color);
        x--;
    }
    return x+1;
}

int fill_right(GLint x, GLint y, Color fill_color, Color border_color){
    while(isPixelValid(x, y, fill_color, border_color)){
        setPiexl(x, y, fill_color);
        x++;
    }
    return x-1;
}


void SearchSeed(stack<point>& st, GLint x_left, GLint x_right, GLint y, Color fill_color, Color border_color){
    int x = x_left;
    bool find_new_seed=false;
    while(x<x_right){
        find_new_seed=false;
        while(isPixelValid(x, y, fill_color, border_color)){
            find_new_seed=true;
            x++;
        }
        if(find_new_seed){
            point data;
            if(isPixelValid(x, y, fill_color, border_color) && x==x_right){
                data.x=x, data.y=y;
                st.push(data);
            }
            else{
                data.x=x-1, data.y=y;
                st.push(data);
            }
        }
    }
}


void ScanLineSeed(GLint x, GLint y, Color fill_color, Color border_color){
    stack<point> st;
    point tmp;
    tmp.x=x, tmp.y=y;
    st.push(tmp);
    while(!st.empty()){
        point tmp=st.top();
        st.pop();
        int x_left=fill_left(tmp.x,  tmp.y, fill_color, border_color);
        int x_right=fill_right(tmp.x+1, tmp.y, fill_color, border_color);
        SearchSeed(st, x_left, x_right, tmp.y-1, fill_color, border_color);
        SearchSeed(st, x_left, x_right, tmp.y+1, fill_color, border_color);
    }
}


void DrawShuang(){
    //glColor3f(0.0, 1.0, 1.0);
    //绿色的爽, 以400.500作为一个中心
    //glColor3f(0.0, 1.0, 0.0);
    /*
    glVertex2f(150.0, 550.0);
    glVertex2f(370.0, 550.0);

    glVertex2f(370.0, 650.0);
    glVertex2f(430.0, 650.0);

    glVertex2f(430.0, 550.0);
    glVertex2f(650.0, 550.0);

    glVertex2f(650.0, 500.0);
    glVertex2f(430.0, 500.0);


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
    
    //画四个叉
    /*
    glBegin(GL_LINE_LOOP);
    {
        for( int i=0; i<12; i++ ){
            glVertex2f(X[i][0], X[i][1]);
        }
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    {
        for( int i=0; i<12; i++ ){
            glVertex2f(2*400-X[i][0], X[i][1]);
        }
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    {
        for( int i=0; i<12; i++ ){
            glVertex2f(X[i][0], 700-X[i][1]);
        }
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    {
        for( int i=0; i<12; i++ ){
            glVertex2f(800-X[i][0], 700-X[i][1]);
        }
    }
    glEnd();
    */
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for( int i=0; i<16; i++ )
        glVertex2f(shuang[i][0], shuang[i][1]);
    glEnd();
    //f(200, 400, fColor);
    ScanLineSeed(0, 0, fill_color, border_color);
    glFlush();
}


void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    DrawShuang();
    /*
    glColor3f(0.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(10, 10);
    glVertex2f(10, 0);
    glVertex2f(20, 0);
    glEnd();
    ScanLineSeed(15, 0, fill_color, border_color);
    glFlush();
    */
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
    glutMainLoop();
    return 0;
}
