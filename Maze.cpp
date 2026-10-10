#include <GL/glut.h>

// Maze is 8 x 8 cells. Row 0 = bottom, column 0 = left.
const int   GRID_SIZE = 8;
const float CELL_SIZE = 0.22f;
const float MAZE_LEFT = -0.88f;
const float MAZE_BOTTOM = -0.88f;
const int PLAYER_VERTEX_COUNT = 18;

// 1 = wall, 0 = open
// Horizontal walls: row r is the line below cell row r (9 lines, 8 columns)
int hWall[9][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 1, 0},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

// Vertical walls: column c is the line left of cell column c (8 rows, 9 lines)
int vWall[8][9] = {
    {0, 1, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 0, 1, 1, 0},
    {0, 0, 1, 1, 0, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0}
};

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

void drawMaze()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);

    // Horizontal walls
    for (int r = 0; r <= GRID_SIZE; r++)
    {
        for (int c = 0; c < GRID_SIZE; c++)
        {
            if (hWall[r][c] == 1)
            {
                float x = MAZE_LEFT + c * CELL_SIZE;
                float y = MAZE_BOTTOM + r * CELL_SIZE;

                glBegin(GL_LINE_STRIP);
                    glVertex2f(x, y);
                    glVertex2f(x + CELL_SIZE, y);
                glEnd();
            }
        }
    }

    // Vertical walls
    for (int r = 0; r < GRID_SIZE; r++)
    {
        for (int c = 0; c <= GRID_SIZE; c++)
        {
            if (vWall[r][c] == 1)
            {
                float x = MAZE_LEFT + c * CELL_SIZE;
                float y = MAZE_BOTTOM + r * CELL_SIZE;

                glBegin(GL_LINE_STRIP);
                    glVertex2f(x, y);
                    glVertex2f(x, y + CELL_SIZE);
                glEnd();
            }
        }
    }

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

// Keeps the drawing square so the circle is not stretched
void reshape(int width, int height)
{
    int side = width;
    if (height < width)
    {
        side = height;
    }
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}

void initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
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
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
