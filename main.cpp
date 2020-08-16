#include <time.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <list>

using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "Punto.h"
#include "Linea.h"
#include "Curva.h"
#include "Application.h"

float red = 0.0, green = 1.0, blue = 0.0;

int brushSize = 4;
int eraserSize = 1;

bool isRandom = false;
bool isEraser = false;
bool isRadial = false;

float window_w = 500;
float window_h = 500;

int shape = 1;

Application *app = Application::Instance();

vector<Punto> puntosTMP;

void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);
	glBegin(GL_POINTS);

	app->dibujarPuntos();
	app->dibujarLineas();
	app->dibujarCurvas();

	glEnd();
	glutSwapBuffers();
}

void clear()
{
	app->eliminarPuntos();
	app->eliminarLineas();
	app->eliminarCurvas();
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void agregarPunto(int mousex, int mousey, bool yInvert = false)
{
	Punto punto(mousex, window_h - mousey, isEraser ? 0.0 : red, isEraser ? 0.0 : green, isEraser ? 0.0 : blue);
	if (yInvert)
		punto.sety(mousey);
	app->agregarPunto(punto);
}

void agregarLinea(int mousex, int mousey)
{
	Punto punto(mousex, window_h - mousey, red, green, blue);
	puntosTMP.push_back(punto);

	if (puntosTMP.size() == 2)
	{
		Linea linea(puntosTMP[0], puntosTMP[1], red, green, blue);
		app->agregarLinea(linea);
		puntosTMP.clear();
	}
}

void agregarCurva(int mousex, int mousey)
{
	Punto punto(mousex, window_h - mousey, red, green, blue);
	puntosTMP.push_back(punto);

	if (puntosTMP.size() == 4)
	{
		Curva curva(puntosTMP);
		app->agregarCurva(curva);
		puntosTMP.clear();
	}
}

void agregarBrush(int x, int y)
{
	for (int i = 0; i < brushSize; i++)
	{
		int randX = rand() % (brushSize + 1) - brushSize / 2 + x;
		int randY = rand() % (brushSize + 1) - brushSize / 2 + y;
		agregarPunto(randX, randY);
	}
}

void agregarRectangulo(int mousex, int mousey)
{
	Punto punto(mousex, window_h - mousey);
	puntosTMP.push_back(punto);

	if (puntosTMP.size() == 2)
	{
		GLint x1 = puntosTMP[0].getx();
		GLint x2 = puntosTMP[1].getx();

		GLint y1 = puntosTMP[0].gety();
		GLint y2 = puntosTMP[1].gety();

		Linea linea1(Punto(x1, y1), Punto(x2, y1), red, green, blue);
		Linea linea2(Punto(x2, y1), Punto(x2, y2), red, green, blue);
		Linea linea3(Punto(x2, y2), Punto(x1, y2), red, green, blue);
		Linea linea4(Punto(x1, y2), Punto(x1, y1), red, green, blue);

		app->agregarLinea(linea1);
		app->agregarLinea(linea2);
		app->agregarLinea(linea3);
		app->agregarLinea(linea4);

		puntosTMP.clear();
	}
}

void agregarCirculo(int mousex, int mousey)
{
	Punto punto(mousex, window_h - mousey, red, green, blue);
	puntosTMP.push_back(punto);

	if (puntosTMP.size() == 2)
	{
		GLint x1 = puntosTMP[0].getx();
		GLint x2 = puntosTMP[1].getx();

		GLint y1 = puntosTMP[0].gety();
		GLint y2 = puntosTMP[1].gety();

		int r = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		double d;
		int x, y;

		x = 0;
		y = r;
		d = 1.25 - r;

		while (x <= y)
		{
			agregarPunto(x1 + x, y1 + y, true);
			agregarPunto(x1 - x, y1 + y, true);
			agregarPunto(x1 + x, y1 - y, true);
			agregarPunto(x1 - x, y1 - y, true);
			agregarPunto(x1 + y, y1 + x, true);
			agregarPunto(x1 - y, y1 + x, true);
			agregarPunto(x1 + y, y1 - x, true);
			agregarPunto(x1 - y, y1 - x, true);
			x++;
			if (d < 0)
			{
				d += 2 * x + 3;
			}
			else
			{
				y--;
				d += 2 * (x - y) + 5;
			}
		}
		puntosTMP.clear();
	}
}

void drawRadialBrush(int x, int y)
{
	int xc = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int yc = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	int dx, dy;

	dx = xc - x;
	dy = yc - y;

	agregarPunto(xc + dx, yc + dy);
	agregarPunto(xc - dx, yc + dy);
	agregarPunto(xc + dx, yc - dy);
	agregarPunto(xc - dx, yc - dy);
	agregarPunto(xc + dy, yc + dx);
	agregarPunto(xc - dy, yc + dx);
	agregarPunto(xc + dy, yc - dx);
	agregarPunto(xc - dy, yc - dx);
}

void erase(int x, int y)
{
	for (int i = -eraserSize; i <= eraserSize; i++)
	{
		for (int j = -eraserSize; j <= eraserSize; j++)
		{
			agregarPunto(x + i, y + j);
		}
	}
}

void mouse(int bin, int state, int x, int y)
{
	if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (isRandom)
		{
			srand(time(NULL));
			red = float(rand()) / float(RAND_MAX);
			green = float(rand()) / float(RAND_MAX);
			blue = float(rand()) / float(RAND_MAX);
		}
		if (isEraser)
		{
			erase(x, y);
		}
		else
		{
			if (shape == 1)
			{
				if (isRadial)
					drawRadialBrush(x, y);
				else
					agregarPunto(x, y);
			}
			else if (shape == 6)
			{
				agregarBrush(x, y);
			}
			else
			{
				if (shape == 2)
					agregarLinea(x, y);
				else if (shape == 3)
					agregarRectangulo(x, y);
				else if (shape == 4)
					agregarCirculo(x, y);
				else if (shape == 5)
					agregarCurva(x, y);
			}
		}
	}
}

void motion(int x, int y)
{
	if (isEraser)
		erase(x, y);
	else
	{
		if (shape == 1)
		{
			if (isRadial)
				drawRadialBrush(x, y);
			else
				agregarPunto(x, y);
		}
		if (shape == 6)
			agregarBrush(x, y);
	}
}

void reshape(int w, int h)
{
	window_w = w;
	window_h = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void processMainMenu(int value)
{
	switch (value)
	{
	case 1:
		clear();
		break;
	case 2:
		app->eliminarUltimaLinea();
		break;
	case 3:
		app->eliminarUltimaCurva();
		break;
	}
}

void processBrushSizeMenu(int value)
{
	shape = 6;
	isEraser = false;
	brushSize = value;
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
}

void processColourMenu(int value)
{
	isEraser = false;
	isRandom = false;

	switch (value)
	{
	case 1:
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		break;
	case 2:
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		break;
	case 3:
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;
	case 4:
		red = 0.5;
		green = 0.0;
		blue = 0.5;
		break;
	case 5:
		red = 1.0;
		green = 1.0;
		blue = 0.0;
		break;
	case 6:
		isRandom = true;
		break;
	}
}

void processShapeMenu(int value)
{
	shape = value;
	isEraser = false;
	isRadial = false;
	puntosTMP.clear();

	switch (shape)
	{
	case 1:
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		break;
	case 2:
	case 3:
	case 4:
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		break;
	}
}

void processEraserSizeMenu(int value)
{
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	eraserSize = value;
	isEraser = true;
}

void processRadicalBrushMenu(int value)
{
	isRadial = value == 1 ? true : false;
	shape = 1;
}

void createOurMenu()
{
	int colourMenu = glutCreateMenu(processColourMenu);
	glutAddMenuEntry("Rojo", 1);
	glutAddMenuEntry("Verde", 2);
	glutAddMenuEntry("Azul", 3);
	glutAddMenuEntry("Morado", 4);
	glutAddMenuEntry("Amarillo", 5);
	glutAddMenuEntry("Random", 6);

	int sizeMenu = glutCreateMenu(processBrushSizeMenu);
	glutAddMenuEntry("4px", 4);
	glutAddMenuEntry("8px", 8);
	glutAddMenuEntry("12px", 12);
	glutAddMenuEntry("16px", 16);

	int shapeMenu = glutCreateMenu(processShapeMenu);
	glutAddMenuEntry("Punto", 1);
	glutAddMenuEntry("Linea", 2);
	glutAddMenuEntry("Rectangulo", 3);
	glutAddMenuEntry("Circulo", 4);
	glutAddMenuEntry("Curva", 5);
	glutAddSubMenu("Airbrush", sizeMenu);

	int eraserSizeMenu = glutCreateMenu(processEraserSizeMenu);
	glutAddMenuEntry("Pqueño", 2);
	glutAddMenuEntry("Mediano", 6);
	glutAddMenuEntry("Largo", 10);

	int radicalBrushMenu = glutCreateMenu(processRadicalBrushMenu);
	glutAddMenuEntry("True", 1);
	glutAddMenuEntry("False", 2);

	int main_id = glutCreateMenu(processMainMenu);
	glutAddSubMenu("Color", colourMenu);
	glutAddSubMenu("Figuras", shapeMenu);
	glutAddSubMenu("Dividir en 4", radicalBrushMenu);
	glutAddSubMenu("Borrar Puntos", eraserSizeMenu);
	glutAddMenuEntry("Borrar Ultima Curva", 3);
	glutAddMenuEntry("Borrar Ultima Linea", 2);
	glutAddMenuEntry("Limpiar Pantalla", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init(void)
{
	glClearColor(0.5, 1.0, 0.0, 1.0);
	glColor3f(red, green, blue);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, window_w, 0.0, window_h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void FPS(int val)
{
	glutPostRedisplay();
	glutTimerFunc(0, FPS, 0);
}

void callbackInit()
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(17, FPS, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(window_w, window_h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Paint");
	callbackInit();
	init();
	createOurMenu();
	glutMainLoop();
	return (0);
}

