
#include <GL/glut.h>
#include <fstream>

typedef float Color[3];

void getPiexl(GLint x, GLint y, Color color){
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void setPixel(GLint x, GLint y){
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

int compare(Color c1, Color c2){
	if (c1[0] != c2[0] || c1[1] != c2[1] || c1[2] != c2[2]){
		return 0;
	}
	return 1;
}

void add_color(int x, int y, Color f_color, Color b_color){
	Color tmp;
	getPiexl(x, y, tmp);
	if (compare(tmp, f_color) == 0 && compare(tmp, b_color) == 0){
		setPixel(x, y);
		add_color(x + 1, y, f_color, b_color);
		add_color(x - 1, y, f_color, b_color);
		add_color(x, y + 1, f_color, b_color);
		add_color(x, y - 1, f_color, b_color);
	}
}

void draw(){
	glBegin(GL_LINE_LOOP);
	/*
	glVertex2f(100, 100);
	glVertex2f(100, 200);
	glVertex2f(200, 100);
	*/
	float da[13][2] = {
		{ 190, 202 }, { 199, 202 }, { 199, 206 }, { 201, 206 }, { 201, 202 }, { 210, 202 },
		{ 210, 198 }, { 201, 198 }, { 205, 180 }, { 200, 190 }, { 195, 180 },
		{ 199, 198 }, { 190, 198 },
	};
	for (int i = 0; i<13; i++)
		glVertex2f(da[i][0], da[i][1]);
	glEnd();
	float x[12][2] = {
		{ 192, 198 }, { 193, 197 }, { 194, 198 }, { 195, 197 },
		{ 194, 196 }, { 195, 195 }, { 194, 194 }, { 193, 195 },
		{ 192, 194 }, { 191, 195 }, { 192, 196 }, { 191, 197 }
	};
	glBegin(GL_LINE_LOOP);
	{
		for (int i = 0; i<12; i++)
			glVertex2f(x[i][0], x[i][1]);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	{
		for (int i = 0; i < 12; i++)
			glVertex2f(400 - x[i][0], x[i][1]);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	{
		for (int i = 0; i<12; i++)
			glVertex2f(x[i][0], 380 - x[i][1]);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	{
		for (int i = 0; i<12; i++)
			glVertex2f(400 - x[i][0], 380 - x[i][1]);
	}
	glEnd();
}

void display(){
	Color f_color = { 0.0, 1.0, 1.0 };
	Color b_color = { 0.0, 1.0, 0.0 };
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	glColor3fv(b_color);
	draw();
	glColor3fv(f_color);
	add_color(200, 200, f_color, b_color);
	add_color(193, 196, f_color, b_color);
	add_color(207, 196, f_color, b_color);
	add_color(193, 184, f_color, b_color);
	add_color(207, 184, f_color, b_color);
	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ssss");

	glClearColor(1, 1, 1, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
