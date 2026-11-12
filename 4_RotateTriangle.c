#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926

struct Point {
    float x;
    float y;
};

// Original triangle
struct Point triangle[3] = {
    {1.0, 1.0},
    {4.0, 1.0},
    {2.5, 4.0}
};

// Rotation about origin
struct Point rotateAboutOrigin(struct Point p, float angle)
{
    struct Point r;

    float rad = angle * PI / 180.0;

    r.x = p.x * cos(rad) - p.y * sin(rad);
    r.y = p.x * sin(rad) + p.y * cos(rad);

    return r;
}

// Rotation about fixed point
struct Point rotateAboutFixedPoint(
    struct Point p, float angle, float xr, float yr)
{
    struct Point r;

    float rad = angle * PI / 180.0;

    // Step 1: Move fixed point to origin
    float x = p.x - xr;
    float y = p.y - yr;

    // Step 2: Rotate
    float xNew = x * cos(rad) - y * sin(rad);
    float yNew = x * sin(rad) + y * cos(rad);

    // Step 3: Move back
    r.x = xNew + xr;
    r.y = yNew + yr;

    return r;
}

// Draw triangle
void drawTriangle(struct Point t[3])
{
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 3; i++)
    {
        glVertex2f(t[i].x, t[i].y);
    }

    glEnd();
}

// Display function
void display()
{
    struct Point rotatedOrigin[3];
    struct Point rotatedFixed[3];

    float angle = 25.0;
    float xr = 2.0;
    float yr = 2.0;

    // Calculate rotated coordinates
    for (int i = 0; i < 3; i++)
    {
        rotatedOrigin[i] =
            rotateAboutOrigin(triangle[i], angle);

        rotatedFixed[i] =
            rotateAboutFixedPoint(
                triangle[i], angle, xr, yr);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    // Original triangle - White
    glColor3f(1.0, 1.0, 1.0);
    drawTriangle(triangle);

    // Origin rotation - Red
    glColor3f(1.0, 0.0, 0.0);
    drawTriangle(rotatedOrigin);

    // Fixed point rotation - Green
    glColor3f(0.0, 1.0, 0.0);
    drawTriangle(rotatedFixed);

    // Origin - Yellow
    glColor3f(1.0, 1.0, 0.0);
    glPointSize(7.0);

    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
    glEnd();

    // Fixed point - Cyan
    glColor3f(0.0, 1.0, 1.0);

    glBegin(GL_POINTS);
    glVertex2f(xr, yr);
    glEnd();

    glFlush();
}

// Initialization
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-6.0, 8.0, -6.0, 8.0);
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Triangle Rotation");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}