#include <GL/glut.h>

void teapot(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.75, 0.30, 0.08);
    glutSolidTeapot(0.1);
    glPopMatrix();
}

void tableTop(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.55, 0.27, 0.07);
    glScalef(0.6, 0.02, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void tableLeg(GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.45, 0.20, 0.05);
    glScalef(0.02, 0.3, 0.02);
    glutSolidCube(1);
    glPopMatrix();
}

void light() {
    GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    GLfloat light_position[] = {2.0, 6.0, 3.0, 1.0};
    GLfloat light_intensity[] = {0.8, 0.8, 0.8, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_intensity);
}

void display() {
    GLfloat teapotP = -0.04;
    GLfloat tabletopP = -0.15;
    GLfloat tablelegP = 0.2;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        -2, 2, 5,
        0, 0, 0,
        0, 1, 0
    );

    light();

    teapot(0, teapotP, 0);
    tableTop(0, tabletopP, 0);
    tableLeg(tablelegP, -0.3, tablelegP);
    tableLeg(-tablelegP, -0.3, tablelegP);
    tableLeg(-tablelegP, -0.3, -tablelegP);
    tableLeg(tablelegP, -0.3, -tablelegP);

    glFlush();
}

void myinit() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("A Teapot on Table");

    myinit();
    glutDisplayFunc(display);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}