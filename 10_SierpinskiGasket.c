
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// Structure for 3D point
struct Point {
    float x, y, z;
};

// Calculate midpoint between two points
struct Point midpoint(struct Point a, struct Point b)
{
    struct Point m;

    m.x = (a.x + b.x) / 2.0f;
    m.y = (a.y + b.y) / 2.0f;
    m.z = (a.z + b.z) / 2.0f;

    return m;
}

// Draw one triangle
void triangle(struct Point a, struct Point b,
              struct Point c,
              float r, float g, float bcolor)
{
    glColor3f(r, g, bcolor);

    glBegin(GL_TRIANGLES);

    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);
    glVertex3f(c.x, c.y, c.z);

    glEnd();
}

// Draw all four faces of tetrahedron
void drawTetrahedron(struct Point a, struct Point b,
                     struct Point c, struct Point d)
{
    triangle(a, b, c, 1.0f, 0.0f, 0.0f);
    triangle(a, b, d, 0.0f, 1.0f, 0.0f);
    triangle(a, c, d, 0.0f, 0.0f, 1.0f);
    triangle(b, c, d, 1.0f, 1.0f, 0.0f);
}

// Recursive Sierpinski function
void sierpinski(struct Point a, struct Point b,
                struct Point c, struct Point d,
                int depth)
{
    struct Point ab, ac, ad, bc, bd, cd;

    // Base condition
    if (depth == 0)
    {
        drawTetrahedron(a, b, c, d);
        return;
    }

    // Calculate six midpoints
    ab = midpoint(a, b);
    ac = midpoint(a, c);
    ad = midpoint(a, d);

    bc = midpoint(b, c);
    bd = midpoint(b, d);
    cd = midpoint(c, d);

    // Recursive calls for four smaller tetrahedrons
    sierpinski(a, ab, ac, ad, depth - 1);
    sierpinski(ab, b, bc, bd, depth - 1);
    sierpinski(ac, bc, c, cd, depth - 1);
    sierpinski(ad, bd, cd, d, depth - 1);
}

// User-selected recursion depth
int depth;

// Display function
void display(void)
{
    struct Point a = {-1.0f, -0.7f, -0.6f};
    struct Point b = {1.0f, -0.7f, -0.6f};
    struct Point c = {0.0f, -0.7f, 1.0f};
    struct Point d = {0.0f, 1.0f, 0.0f};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);

    sierpinski(a, b, c, d, depth);

    glutSwapBuffers();
}

// Initialization
void init(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.8, 1.8, -1.5, 1.5, -5.0, 5.0);
}

// Main function
int main(int argc, char **argv)
{
    printf("Enter number of recursive steps (0-6): ");

    if (scanf("%d", &depth) != 1 ||
        depth < 0 || depth > 6)
    {
        printf("Invalid input. Enter an integer from 0 to 6.\n");
        return 1;
    }

    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH
    );

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("3D Sierpinski Gasket");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
