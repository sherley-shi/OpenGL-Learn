#include <iostream>
#include <string>
#include <GL/glut.h>
#include <stack>
#include <cmath>
#include "./Point.h"


#define PI 3.14
#define ALPHA 25
#define STEP 0.5


using namespace std;


GLfloat colors[][3] = {
    {0.0, 0.1, 0.5},
    {1.0, 0.6, 0.3},
    {0.2, 0.4, 0.6},
    {0.5, 0.5, 0.5},
    {0.8, 0.6, 0.4},
    {0.3, 0.8, 0.2},
};

string rule, t_rule;
string way[3] = {
    "F",
    "FF[++F-F-F][-F+F+F]",
    "FF-[--F+F+F]+[+F+F-F]"
};
int n=5;    //迭代次数 模拟书上的
Point ps(0, 0, 0);
stack<Point> st;

void LSystem(){
    //rule.clear(), t_rule.clear();
    rule = way[rand()%3];
    cout << rule << endl;
    for( int i=0; i<n; i++ ){
        int curlen = t_rule.length();
        int pos=0, j=0;
        while( j<curlen ){
            if( t_rule[j] == 'F' ){
                //等于F的时候进入递归
                rule += way[rand() % 3];
                j++;
                pos = rule.length()-1;
            }
            else{
                rule += t_rule[j++];
                pos++;
            }
        }
        t_rule = rule;
        rule.clear();
    }
    rule = t_rule;
    cout << rule << endl;
}

void draw(){
    Point cp=ps, np=ps;
    cp.dir = 80;
    int len = rule.length();
    glRotatef(180, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 30.0, 0.0);
    glPushMatrix();
    int index=0;
    while ( index<len ){
        switch(rule[index]){
            case 'F':
                  //进入新的循环
                  np.x = cp.x+STEP*cos(cp.dir*(PI/180));
                  np.y = cp.y-STEP*sin(cp.dir*(PI/180));
                  np.dir = cp.dir;
                  glColor3fv(colors[rand()%6]);
                  glBegin(GL_LINES);
                  {
                      glVertex2f(cp.x, cp.y);
                      glVertex2f(np.x, np.y);
                  }
                  glEnd();
                  cp = np;
                  break;
            case '[':
                st.push(cp);
                  break;
            case ']':
                  cp = st.top();
                  st.pop();
                  break;
            case '+':
                  //角度逆时针旋转
                  cp.dir += ALPHA;
                  break;
            case '-':
                  cp.dir -= ALPHA;
            default:
                  ;
        }
        index++;
    }
    glPopMatrix();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    LSystem();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h){
    w=w>h?h:w;
    glViewport(0, 0, GLsizei(w), GLsizei(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Grass");
    init();
    glOrtho(-50, 50, -50, 50, -50, 50);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
