#include <GL/glut.h>
#include <math.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Red Triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.7, 0.5);
    glVertex2f(-0.9, 0.1);
    glVertex2f(-0.5, 0.1);
    glEnd();

    // Draw Green Square
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.9, 0.5);
    glVertex2f(0.9, 0.1);
    glVertex2f(0.5, 0.1);
    glEnd();

    // Draw Blue Hexagon
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);

    int i;
    for(i = 0; i < 6; ++i) {
        float theta = 2.0f * 3.1415926f * (float)i / 6.0f;
        float x = 0.3f * cosf(theta);
        float y = 0.3f * sinf(theta) - 0.5f;
        glVertex2f(x, y);
    }

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Lab Assignment: 3 OpenGL Shapes");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}