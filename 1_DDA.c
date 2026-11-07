
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

float x1 = 50.0, y_start = 50.0;
float x2 = 400.0, y2 = 300.0;

void display()
{
    float dx = x2 - x1;
    float dy = y2 - y_start;
    float steps;

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    float xinc = dx / steps;
    float yinc = dy / steps;

    float x = x1;
    float y = y_start;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POINTS);

    for (int i = 0; i <= steps; i++)
    {
        glVertex2f(round(x), round(y));

        x += xinc;
        y += yinc;
    }

    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("DDA Line Drawing Algorithm");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
