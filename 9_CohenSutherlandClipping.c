
#include <GL/glut.h>
#include <stdio.h>

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

double xmin = 200, ymin = 150;
double xmax = 600, ymax = 450;

double x_start, y_start, x_end, y_end;
double cx1, cy1, cx2, cy2;
int accepted = 0;

int computeCode(double x, double y)
{
    int code = INSIDE;

    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;

    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;

    return code;
}

int cohenSutherlandClip(double *x1, double *y1, double *x2, double *y2)
{
    int code1 = computeCode(*x1, *y1);
    int code2 = computeCode(*x2, *y2);

    while (1)
    {
        double x, y;
        int codeOut;

        if ((code1 | code2) == 0)
            return 1;

        if ((code1 & code2) != 0)
            return 0;

        codeOut = code1 ? code1 : code2;

        if (codeOut & TOP)
        {
            x = *x1 + (*x2 - *x1) * (ymax - *y1) / (*y2 - *y1);
            y = ymax;
        }
        else if (codeOut & BOTTOM)
        {
            x = *x1 + (*x2 - *x1) * (ymin - *y1) / (*y2 - *y1);
            y = ymin;
        }
        else if (codeOut & RIGHT)
        {
            y = *y1 + (*y2 - *y1) * (xmax - *x1) / (*x2 - *x1);
            x = xmax;
        }
        else
        {
            y = *y1 + (*y2 - *y1) * (xmin - *x1) / (*x2 - *x1);
            x = xmin;
        }

        if (codeOut == code1)
        {
            *x1 = x;
            *y1 = y;
            code1 = computeCode(*x1, *y1);
        }
        else
        {
            *x2 = x;
            *y2 = y;
            code2 = computeCode(*x2, *y2);
        }
    }
}

void drawLine(double ax, double ay, double bx, double by)
{
    glBegin(GL_LINES);
    glVertex2d(ax, ay);
    glVertex2d(bx, by);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2d(xmin, ymin);
    glVertex2d(xmax, ymin);
    glVertex2d(xmax, ymax);
    glVertex2d(xmin, ymax);
    glEnd();

    glColor3f(0.6f, 0.6f, 0.6f);
    drawLine(x_start, y_start, x_end, y_end);

    if (accepted)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(3.0f);
        drawLine(cx1, cy1, cx2, cy2);
        glLineWidth(1.0f);
    }

    glFlush();
}

void init(void)
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 800, 0, 600);
}

int main(int argc, char **argv)
{
    printf("Enter x_start y_start x_end y_end: ");

    if (scanf("%lf %lf %lf %lf", &x_start, &y_start, &x_end, &y_end) != 4)
    {
        printf("Invalid input.\n");
        return 1;
    }

    cx1 = x_start;
    cy1 = y_start;
    cx2 = x_end;
    cy2 = y_end;

    accepted = cohenSutherlandClip(&cx1, &cy1, &cx2, &cy2);

    if (accepted)
    {
        printf("Line accepted after clipping.\n");
        printf("Clipped endpoints: (%.2f, %.2f) to (%.2f, %.2f)\n", cx1, cy1, cx2, cy2);
    }
    else
    {
        printf("Line rejected: outside the clipping window.\n");
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Cohen-Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

