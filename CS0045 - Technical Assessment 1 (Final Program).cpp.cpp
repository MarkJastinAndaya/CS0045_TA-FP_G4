/*
    CS0045 - Technical Assessment 1
    OpenGL Maze Game

    Requirements covered in this file:
    - Complete scene with maze walls, player, and triangle shape
    - At least two OpenGL primitive types
    - At least three colors
    - Player rendered using a vertex array
*/

#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

using namespace std;

// ------------------------------------------------------------
// Global Variables
// ------------------------------------------------------------
const int PLAYER_VERTEX_COUNT = 18;

float playerX = -0.77f;
float playerY = -0.77f;

GLfloat playerVertices[] = {
    0.000f, 0.000f,
    0.050f, 0.000f,
    0.046f, 0.019f,
    0.035f, 0.035f,
    0.019f, 0.046f,
    0.000f, 0.050f,
    -0.019f, 0.046f,
    -0.035f, 0.035f,
    -0.046f, 0.019f,
    -0.050f, 0.000f,
    -0.046f, -0.019f,
    -0.035f, -0.035f,
    -0.019f, -0.046f,
    0.000f, -0.050f,
    0.019f, -0.046f,
    0.035f, -0.035f,
    0.046f, -0.019f,
    0.050f, 0.000f};

// ------------------------------------------------------------
// Function Prototypes
// ------------------------------------------------------------
void initialize();
void display();
void drawInstructions();
void drawOuterWall();
void drawWallStrip(float x1, float y1, float x2, float y2);
void drawMaze();
void drawTriangle();
void drawPlayer();
void keyboard(unsigned char key, int x, int y);

// ------------------------------------------------------------
// Main Function
// ------------------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(200, 50);

    glutCreateWindow("CS0045 - Technical Assessment 1");

    initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

// ------------------------------------------------------------
// OpenGL Setup
// ------------------------------------------------------------
void initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// ------------------------------------------------------------
// Text
// ------------------------------------------------------------
void drawInstructions()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(-0.95f, 0.90f);

    glutBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        reinterpret_cast<const unsigned char*>(
            "W = Move Up | S = Move Down"
        )
    );

    glRasterPos2f(-0.95f, 0.82f);

    glutBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        reinterpret_cast<const unsigned char*>(
            "A = Move Left | D = Move Right | R = Reset"
        )
    );
}
// ------------------------------------------------------------
// Maze Walls
// ------------------------------------------------------------
void drawOuterWall()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(6.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.88f, -0.88f);
    glVertex2f(0.88f, -0.88f);
    glVertex2f(0.88f, 0.88f);
    glVertex2f(-0.88f, 0.88f);
    glEnd();

    glLineWidth(1.0f);
}

void drawWallStrip(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawMaze()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);

    drawWallStrip(-0.66f, -0.88f, -0.66f, -0.66f);
    drawWallStrip(-0.44f, -0.66f, 0.22f, -0.66f);
    drawWallStrip(0.44f, -0.88f, 0.44f, -0.66f);
    drawWallStrip(0.66f, -0.66f, 0.88f, -0.66f);

    drawWallStrip(-0.88f, -0.44f, -0.66f, -0.44f);
    drawWallStrip(-0.44f, -0.66f, -0.44f, -0.22f);
    drawWallStrip(-0.22f, -0.44f, 0.22f, -0.44f);
    drawWallStrip(0.22f, -0.66f, 0.22f, -0.22f);
    drawWallStrip(0.44f, -0.44f, 0.66f, -0.44f);
    drawWallStrip(0.66f, -0.44f, 0.66f, -0.22f);

    drawWallStrip(-0.66f, -0.22f, -0.66f, 0.22f);
    drawWallStrip(-0.66f, 0.00f, -0.44f, 0.00f);
    drawWallStrip(-0.22f, -0.22f, -0.22f, 0.22f);
    drawWallStrip(0.00f, -0.22f, 0.44f, -0.22f);
    drawWallStrip(0.44f, -0.22f, 0.44f, 0.22f);
    drawWallStrip(0.66f, 0.00f, 0.88f, 0.00f);

    drawWallStrip(-0.88f, 0.22f, -0.44f, 0.22f);
    drawWallStrip(-0.44f, 0.22f, -0.44f, 0.66f);
    drawWallStrip(-0.22f, 0.44f, 0.22f, 0.44f);
    drawWallStrip(0.22f, 0.22f, 0.22f, 0.66f);
    drawWallStrip(0.44f, 0.44f, 0.66f, 0.44f);
    drawWallStrip(0.66f, 0.22f, 0.66f, 0.66f);

    drawWallStrip(-0.66f, 0.66f, -0.22f, 0.66f);
    drawWallStrip(0.00f, 0.66f, 0.44f, 0.66f);
    drawWallStrip(0.66f, 0.66f, 0.88f, 0.66f);

    glLineWidth(1.0f);
}

// ------------------------------------------------------------
// Static Triangle Shape
// ------------------------------------------------------------
void drawTriangle()
{
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f(0.72f, 0.72f);
    glVertex2f(0.82f, 0.72f);
    glVertex2f(0.77f, 0.82f);
    glEnd();
}

// ------------------------------------------------------------
// Vertex Array Player
// ------------------------------------------------------------
void drawPlayer()
{
    glColor3f(0.0f, 0.0f, 1.0f);

    glPushMatrix();
    glTranslatef(playerX, playerY, 0.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, playerVertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, PLAYER_VERTEX_COUNT);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

// ------------------------------------------------------------
// Display Callback
// ------------------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawInstructions();

    glPushMatrix();
        glTranslatef(0.0f, -0.10f, 0.0f);
        glScalef(0.86f, 0.86f, 1.0f);

        drawOuterWall();
        drawMaze();
        drawTriangle();
        drawPlayer();
    glPopMatrix();

    glFlush();
}

// ------------------------------------------------------------
// Wall Collisions
// ------------------------------------------------------------
struct WallSegment
{
    float x1, y1, x2, y2;
};

bool touchesWall(float x, float y)
{
    static const WallSegment walls[] = {
        {-0.88f, -0.88f, 0.88f, -0.88f},
        {0.88f, -0.88f, 0.88f, 0.88f},
        {-0.88f, 0.88f, 0.88f, 0.88f},
        {-0.88f, -0.88f, -0.88f, 0.88f},
        {-0.66f, -0.88f, -0.66f, -0.66f},
        {-0.44f, -0.66f, 0.22f, -0.66f},
        {0.44f, -0.88f, 0.44f, -0.66f},
        {0.66f, -0.66f, 0.88f, -0.66f},
        {-0.88f, -0.44f, -0.66f, -0.44f},
        {-0.44f, -0.66f, -0.44f, -0.22f},
        {-0.22f, -0.44f, 0.22f, -0.44f},
        {0.22f, -0.66f, 0.22f, -0.22f},
        {0.44f, -0.44f, 0.66f, -0.44f},
        {0.66f, -0.44f, 0.66f, -0.22f},
        {-0.66f, -0.22f, -0.66f, 0.22f},
        {-0.66f, 0.00f, -0.44f, 0.00f},
        {-0.22f, -0.22f, -0.22f, 0.22f},
        {0.00f, -0.22f, 0.44f, -0.22f},
        {0.44f, -0.22f, 0.44f, 0.22f},
        {0.66f, 0.00f, 0.88f, 0.00f},
        {-0.88f, 0.22f, -0.44f, 0.22f},
        {-0.44f, 0.22f, -0.44f, 0.66f},
        {-0.22f, 0.44f, 0.22f, 0.44f},
        {0.22f, 0.22f, 0.22f, 0.66f},
        {0.44f, 0.44f, 0.66f, 0.44f},
        {0.66f, 0.22f, 0.66f, 0.66f},
        {-0.66f, 0.66f, -0.22f, 0.66f},
        {0.00f, 0.66f, 0.44f, 0.66f},
        {0.66f, 0.66f, 0.88f, 0.66f}};

    const float playerRadius = 0.060f;

    for (unsigned int i = 0; i < sizeof(walls) / sizeof(walls[0]); ++i)
    {
        float closestX = x;
        float closestY = y;

        if (closestX < walls[i].x1)
            closestX = walls[i].x1;
        if (closestX > walls[i].x2)
            closestX = walls[i].x2;
        if (closestY < walls[i].y1)
            closestY = walls[i].y1;
        if (closestY > walls[i].y2)
            closestY = walls[i].y2;

        float dx = x - closestX;
        float dy = y - closestY;
        if (dx * dx + dy * dy < playerRadius * playerRadius)
            return true;
    }
    return false;
}

// ------------------------------------------------------------
// Keyboard Callback
// ------------------------------------------------------------
void keyboard(unsigned char key, int, int)
{
    const float step = 0.025f;
    float nextX = playerX;
    float nextY = playerY;

    switch (key)
    {
    case 'w':
    case 'W':
        nextY += step;
        break;
    case 'a':
    case 'A':
        nextX -= step;
        break;
    case 's':
    case 'S':
        nextY -= step;
        break;
    case 'd':
    case 'D':
        nextX += step;
        break;
    case 'r':
    case 'R':
        playerX = -0.77f;
        playerY = -0.77f;
        glutPostRedisplay();
        return;
    default:
        return;
    }

    if (!touchesWall(nextX, nextY))
    {
        playerX = nextX;
        playerY = nextY;
    }

    glutPostRedisplay();
}
