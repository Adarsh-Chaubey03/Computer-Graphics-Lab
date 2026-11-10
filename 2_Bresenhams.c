#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int startX, startY, endX, endY;

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    glBegin(GL_POINTS);

    while (1)
    {
        glVertex2i(x1, y1);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err = err - dy;
            x1 = x1 + sx;
        }

        if (e2 < dx)
        {
            err = err + dx;
            y1 = y1 + sy;
        }
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);

    drawLine(startX, startY, endX, endY);

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    printf("Enter starting point (x1 y1): ");
    scanf("%d %d", &startX, &startY);

    printf("Enter ending point (x2 y2): ");
    scanf("%d %d", &endX, &endY);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Bresenham's Line Drawing Algorithm");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}