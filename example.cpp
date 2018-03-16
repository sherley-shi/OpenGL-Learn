#include <iostream>
#include <GL/glut.h>

using  namespace std;


void draw(){
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(300, 300);
    glutCreateWindow("OpenGL Programming");
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
