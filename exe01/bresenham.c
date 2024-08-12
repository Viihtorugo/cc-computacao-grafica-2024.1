#include <stdio.h>
#include <GL/glut.h>

// comando para execução
// gcc cg.c -o main -lGL -lGLU -lglut -lm

int points[100][2];
int count_points = 0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glPointSize(30.0);
    glOrtho(0, 10, 0, 10, 1, -1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POINTS);
    for (int i = 0; i < count_points; i++)
    {
        glVertex2i(points[i][0], points[i][1]);
    }

    glEnd();

    glFlush();
}

// dx = x final - x inicial
// dy = y final - y inicial
// d start = dy - dx/2
// delta e = 2dy
// delta ne = 2 * (dy - dx);

void bresenham(int x, int y, int dx, int dy, int d, int xf, int yf, int e, int ne)
{
    printf("(%d,%d)\n", x, y);
    points[count_points][0] = x;
    points[count_points][1] = y;
    count_points++;
    if (x == xf && y == yf)
        return;

    if (d > 0)
    {
        x++;
        y++;
        bresenham(x, y, dx, dy, d + ne, xf, yf, e, ne);
    }
    else
    {
        x++;
        bresenham(x, y, dx, dy, d + e, xf, yf, e, ne);
    }
}

int main(int argc, char **argv)
{
    // P inicial
    int x1 = 1, y1 = 1;
    // P final
    int x2 = 8, y2 = 5;

    // dx e dy
    int dx = x2 - x1, dy = y2 - y1;

    // delta e && delta ne
    int e = 2 * dy;
    int ne = 2 * (dy - dx);

    // d start
    int d_start = dy - dx / 2;

    printf("e = %d; ne = %d;  dx = %d; dy = %d; d_start = %d.\n", e, ne, dx, dy, d_start);

    bresenham(x1, y1, dx, dy, d_start, x2, y2, e, ne);

    glutInit(&argc, argv);
    glutCreateWindow("Desenho de Pontos OpenGL");
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;

    return 0;
}