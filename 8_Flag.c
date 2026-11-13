
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

float wave = 0.0f;
int animate = 0;

float bezier(float p0, float p1, float p2, float p3, float t)
{
    float u = 1.0f - t;

    return u * u * u * p0
         + 3 * u * u * t * p1
         + 3 * u * t * t * p2
         + t * t * t * p3;
}

float getWave(float x)
{
    float t = x / 6.0f;

    if (t < 0)
        t = 0;

    if (t > 1)
        t = 1;

    float y = bezier(0.0f, 0.8f, -0.8f, 0.0f, t);

    return y * sinf(wave);
}

void drawRect(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);

    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);

    glEnd();
}

void drawFlag()
{
    float x;
    float dx = 0.15f;

    glColor3f(0.35f, 0.20f, 0.05f);

    glBegin(GL_QUADS);
    glVertex2f(-4.2f, -3.5f);
    glVertex2f(-4.0f, -3.5f);
    glVertex2f(-4.0f, 3.5f);
    glVertex2f(-4.2f, 3.5f);
    glEnd();

    glColor3f(1.0f, 0.55f, 0.0f);

    for (x = 0; x < 6.0f; x += dx)
    {
        float y1 = getWave(x);
        float y2 = getWave(x + dx);

        glBegin(GL_QUADS);

        glVertex2f(-4.0f + x, 2.0f + y1);
        glVertex2f(-4.0f + x + dx, 2.0f + y2);
        glVertex2f(-4.0f + x + dx, 1.0f + y2);
        glVertex2f(-4.0f + x, 1.0f + y1);

        glEnd();
    }

    glColor3f(1.0f, 1.0f, 1.0f);

    for (x = 0; x < 6.0f; x += dx)
    {
        float y1 = getWave(x);
        float y2 = getWave(x + dx);

        glBegin(GL_QUADS);

        glVertex2f(-4.0f + x, 1.0f + y1);
        glVertex2f(-4.0f + x + dx, 1.0f + y2);
        glVertex2f(-4.0f + x + dx, 0.0f + y2);
        glVertex2f(-4.0f + x, 0.0f + y1);

        glEnd();
    }

    glColor3f(0.0f, 0.55f, 0.25f);

    for (x = 0; x < 6.0f; x += dx)
    {
        float y1 = getWave(x);
        float y2 = getWave(x + dx);

        glBegin(GL_QUADS);

        glVertex2f(-4.0f + x, 0.0f + y1);
        glVertex2f(-4.0f + x + dx, 0.0f + y2);
        glVertex2f(-4.0f + x + dx, -1.0f + y2);
        glVertex2f(-4.0f + x, -1.0f + y1);

        glEnd();
    }

    glColor3f(0.0f, 0.2f, 0.6f);

    float cx = -1.0f;
    float cy = 0.5f;
    float radius = 0.38f;

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 100; i++)
    {
        float angle = 2.0f * PI * i / 100.0f;

        float px = cx + radius * cosf(angle);
        float py = cy + radius * sinf(angle);

        glVertex2f(px, py);
    }

    glEnd();

    for (int i = 0; i < 24; i++)
    {
        float angle = 2.0f * PI * i / 24.0f;

        glBegin(GL_LINES);

        glVertex2f(cx, cy);
        glVertex2f(cx + radius * cosf(angle),
                   cy + radius * sinf(angle));

        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    drawFlag();

    glutSwapBuffers();
}

void update(int value)
{
    if (animate)
    {
        wave += 0.08f;

        if (wave > 2.0f * PI)
            wave -= 2.0f * PI;

        glutPostRedisplay();
    }

    glutTimerFunc(30, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
            animate = 1;
            printf("Animation Started\n");
            break;

        case '2':
            animate = 0;
            printf("Animation Stopped\n");
            break;

        case '3':
            animate = 0;
            wave = 0.0f;
            printf("Flag Reset\n");
            glutPostRedisplay();
            break;

        case '4':
            exit(0);
            break;

        default:
            printf("Invalid choice\n");
    }
}

void menu(int option)
{
    switch (option)
    {
        case 1:
            animate = 1;
            break;

        case 2:
            animate = 0;
            break;

        case 3:
            animate = 0;
            wave = 0.0f;
            glutPostRedisplay();
            break;

        case 4:
            exit(0);
            break;
    }
}

void init()
{
    glClearColor(0.85f, 0.90f, 0.95f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-5.0, 3.0, -4.0, 4.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(900, 700);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("Animated Indian Flag - Bezier Curve");

    init();

    printf("\n====================================\n");
    printf("     FLAG ANIMATION MENU\n");
    printf("====================================\n");
    printf("1. Start Animation\n");
    printf("2. Stop Animation\n");
    printf("3. Reset Flag\n");
    printf("4. Exit\n");
    printf("====================================\n");

    glutCreateMenu(menu);

    glutAddMenuEntry("Start Animation", 1);
    glutAddMenuEntry("Stop Animation", 2);
    glutAddMenuEntry("Reset Flag", 3);
    glutAddMenuEntry("Exit", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(30, update, 0);

    glutMainLoop();

    return 0;
}
