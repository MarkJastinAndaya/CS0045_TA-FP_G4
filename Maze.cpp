#include <GL/glut.h>

const int PLAYER_VERTEX_COUNT = 18;

// Player (starts in the bottom-left cell)
float playerX = -0.77f;
float playerY = -0.77f;

// Vertex array for the player circle: center + 16 rim points + repeated first rim point
GLfloat playerVertices[] = {
    0.000f,  0.000f,
    0.050f,  0.000f,
    0.046f,  0.019f,
    0.035f,  0.035f,
    0.019f,  0.046f,
    0.000f,  0.050f,
   -0.019f,  0.046f,
   -0.035f,  0.035f,
   -0.046f,  0.019f,
   -0.050f,  0.000f,
   -0.046f, -0.019f,
   -0.035f, -0.035f,
   -0.019f, -0.046f,
    0.000f, -0.050f,
    0.019f, -0.046f,
    0.035f, -0.035f,
    0.046f, -0.019f,
    0.050f,  0.000f
};

void drawOuterWall()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(6.0f);

    // Outer wall is manually plotted point by point.
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.88f, -0.88f); // bottom-left
    glVertex2f( 0.88f, -0.88f); // bottom-right
    glVertex2f( 0.88f,  0.88f); // top-right
    glVertex2f(-0.88f,  0.88f); // top-left
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
    drawWallStrip(-0.44f, -0.66f,  0.22f, -0.66f);
    drawWallStrip( 0.44f, -0.88f,  0.44f, -0.66f);
    drawWallStrip( 0.66f, -0.66f,  0.88f, -0.66f);

    drawWallStrip(-0.88f, -0.44f, -0.66f, -0.44f);
    drawWallStrip(-0.44f, -0.66f, -0.44f, -0.22f);
    drawWallStrip(-0.22f, -0.44f,  0.22f, -0.44f);
    drawWallStrip( 0.22f, -0.66f,  0.22f, -0.22f);
    drawWallStrip( 0.44f, -0.44f,  0.66f, -0.44f);
    drawWallStrip( 0.66f, -0.44f,  0.66f, -0.22f);

    drawWallStrip(-0.66f, -0.22f, -0.66f,  0.22f);
    drawWallStrip(-0.66f,  0.00f, -0.44f,  0.00f);
    drawWallStrip(-0.22f, -0.22f, -0.22f,  0.22f);
    drawWallStrip( 0.00f, -0.22f,  0.44f, -0.22f);
    drawWallStrip( 0.44f, -0.22f,  0.44f,  0.22f);
    drawWallStrip( 0.66f,  0.00f,  0.88f,  0.00f);

    drawWallStrip(-0.88f,  0.22f, -0.44f,  0.22f);
    drawWallStrip(-0.44f,  0.22f, -0.44f,  0.66f);
    drawWallStrip(-0.22f,  0.44f,  0.22f,  0.44f);
    drawWallStrip( 0.22f,  0.22f,  0.22f,  0.66f);
    drawWallStrip( 0.44f,  0.44f,  0.66f,  0.44f);
    drawWallStrip( 0.66f,  0.22f,  0.66f,  0.66f);

    drawWallStrip(-0.66f,  0.66f, -0.22f,  0.66f);
    drawWallStrip( 0.00f,  0.66f,  0.44f,  0.66f);
    drawWallStrip( 0.66f,  0.66f,  0.88f,  0.66f);

    glLineWidth(1.0f);
}

void drawTriangle()
{
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
        glVertex2f(0.72f, 0.72f);
        glVertex2f(0.82f, 0.72f);
        glVertex2f(0.77f, 0.82f);
    glEnd();
}

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

void initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawOuterWall();
    drawMaze();
    drawTriangle();
    drawPlayer();
    glutSwapBuffers();
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("2D Maze Game");
    
    
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
