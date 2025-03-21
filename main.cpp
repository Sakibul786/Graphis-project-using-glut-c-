#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <math.h>
using namespace std;

float _ang_tri = 0.0;//train
bool moving = false; //train
float carPosition = 0.0;//car
float bx = 0.0; //car1
float _rain = 0.0;
bool active=false;
int window=0,ship=0;
float speed=0.0;


float cloud1PosX = 0.0f; //  first cloud
float cloud2PosX = -150.0f; // second cloud
const float cloudSpeed = 1.0f; // Speed

bool isNight = false;
bool rainday = false;


//Sun Function

void drawSun(float x, float y) {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(x, y, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.1416 / 180;
        float xPos = 50 * cos(theta);
        float yPos = 50 * sin(theta);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    glPopMatrix();
}

//Moon Function

void drawMoon(float x, float y) {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(x, y, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.1416 / 180; //deg to rad
        float xPos = 50 * cos(theta);
        float yPos = 50 * sin(theta);
        glVertex2f(xPos, yPos);
    }
    glEnd();
    glPopMatrix();
}

// circle function for cloud

void drawCircle(float centerX, float centerY, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.1416 / 180.0f;
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();
}


// Function to draw a single cloud

void drawCloud(float x, float y) {
    if (isNight) return;

    if (rainday) {
        glColor3f(0.2f, 0.2f, 0.2f); // Dark gray for rain clouds
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    drawCircle(x, y, 30);
    drawCircle(x + 35, y, 30);
    drawCircle(x - 35, y, 30);
    drawCircle(x + 15, y + 25, 25);
    drawCircle(x - 15, y + 25, 25);
}

//car function

void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

//Lampost Function

void drawLampPost(float x, float y) {
    // Lamp post piller
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(x, y);
    glVertex2f(x + 10, y);
    glVertex2f(x + 10, y + 100);
    glVertex2f(x, y + 100);
    glEnd();

        // Lamp light
    if (isNight) {
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 0.0f);
        for (int i = 0; i < 360; i += 10) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(x + 15 * cos(angle) + 5, y + 100 + 15 * sin(angle)); // light
        }
        glEnd();
    }
    else if (rainday) {
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 0.0f);
        for (int i = 0; i < 360; i += 10) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(x + 15 * cos(angle) + 5, y + 100 + 15 * sin(angle)); // light
        }
        glEnd();
    }

    else {
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        for (int i = 0; i < 360; i += 10) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(x + 15 * cos(angle) + 5, y + 100 + 15 * sin(angle)); // light
        }
        glEnd();
    }

}


///display function

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0,1500,0,1000);
	glMatrixMode(GL_MODELVIEW);


	 ///Sky

if (isNight && rainday) {
    glColor3f(0.1f, 0.1f, 0.2f);
} else if (isNight) {
    glColor3f(0.0f, 0.0f, 0.2f);
} else if (rainday) {
    glColor3f(0.3f, 0.3f, 0.5f);
} else {
    glColor3f(0.529f, 0.808f, 0.922f);
}
    glBegin(GL_QUADS);
    glVertex2i(0, 550);
    glVertex2i(1500, 550);
    glVertex2i(1500, 1000);
    glVertex2i(0, 1000);
    glEnd();


    /// SUN OR MOON

if (isNight && !rainday) {
    drawMoon(1250, 900);
} else if (!isNight) {
    drawSun(1250, 900);
}


   ///clouds
   //2 clouds

    drawCloud(cloud1PosX, 950.0f); // Cloud 1
    drawCloud(cloud2PosX, 850.0f); // Cloud 2

     if (rainday) {
        drawCloud(600, 900);
        drawCloud(800, 850);
        drawCloud(1000, 920);
        drawCloud(1250, 900);
    }



    ///Hill

if (isNight && rainday) {
        glColor3f(0.1f, 0.3f, 0.1f);
    } else if (isNight) {
        glColor3f(0.0f, 0.2f, 0.05f);
    } else if (rainday) {
        glColor3f(0.0f, 0.5f, 0.1f);
    } else {
        glColor3f(0.0f, 0.4f, 0.1f);
    }

    glBegin(GL_POLYGON);
    glVertex2i(-50, 686);
    glVertex2i(250, 850);
    glVertex2i(500, 800);
    glVertex2i(750, 850);
    glVertex2i(1000, 750);
    glVertex2i(1250, 840);
    glVertex2i(1550, 686);
    glEnd();

//  layer of hills

 if (isNight && rainday) {
        glColor3f(0.15f, 0.35f, 0.15f);
    } else if (isNight) {
        glColor3f(0.1f, 0.25f, 0.1f);
    } else if (rainday) {
        glColor3f(0.2f, 0.6f, 0.2f);
    } else {
        glColor3f(0.2f, 0.7f, 0.2f);
    }

    glBegin(GL_POLYGON);
    glVertex2i(100, 686);
    glVertex2i(250, 730);
    glVertex2i(500, 710);
    glVertex2i(750, 750);
    glVertex2i(1050, 720);
    glVertex2i(1300, 740);
    glVertex2i(1450, 710);
    glVertex2i(1500, 686);
    glEnd();




    ///Road
 if (isNight && rainday) {
        glColor3f(0.1f, 0.1f, 0.1f);
    } else if (isNight) {
        glColor3f(0.2f, 0.2f, 0.2f);
    } else if (rainday) {
        glColor3f(0.25f, 0.25f, 0.25f);
    } else {
        glColor3f(0.3f, 0.3f, 0.3f);
    }
    glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_QUADS);
    glVertex2i(0,600);
    glVertex2i(1500,600);
    glVertex2i(1500,686);
    glVertex2i(0,686);
    glEnd();

    if (isNight) {
        glColor3f(0.8f, 0.8f, 0.8f);
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2i(0,641);
    glVertex2i(1500,641);
    glVertex2i(1500,646);
    glVertex2i(0,646);
     glEnd();

    ///Lampost

    drawLampPost(100, 685);
    drawLampPost(300, 685);
    drawLampPost(500, 685);
    drawLampPost(700, 685);
    drawLampPost(900, 685);
    drawLampPost(1100, 685);
    drawLampPost(1300, 685);



    ///car

    glPushMatrix();
    glTranslatef(carPosition, 0.0, 0.0);

    //Car Body
    glColor3f(0.33f, 0.33f, 0.33f);
    glBegin(GL_QUADS);
    glVertex2i(200, 650);
    glVertex2i(300, 650);
    glVertex2i(300, 700);
    glVertex2i(200, 700);
    glEnd();


     glColor3f(0.33f, 0.33f, 0.33f);
     glBegin(GL_QUADS);
     glVertex2i(220, 700);
     glVertex2i(280, 700);
     glVertex2i(260, 730);
     glVertex2i(240, 730);
     glEnd();


     // Left Wheel
    glPushMatrix();
    glTranslatef(220, 640, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
    float theta = i * 3.1416 / 180;
    float x = 12 * cos(theta);
    float y = 12 * sin(theta);
    glVertex2f(x, y);
}
    glEnd();
    glPopMatrix();

    // Right Wheel
    glPushMatrix();
    glTranslatef(280, 640, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
    float theta = i * 3.1416 / 180;
    float x = 12 * cos(theta);
    float y = 12 * sin(theta);
    glVertex2f(x, y);
}
    glEnd();
    glPopMatrix();

glPopMatrix();

    //car1

     glPushMatrix();
    glTranslatef(bx, 0, 0);

    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(1410, 610);
    glVertex2d(1490, 610);
    glVertex2d(1485, 640);
    glVertex2d(1410, 640);
    glEnd();

    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(1420, 640);
    glVertex2d(1475, 640);
    glVertex2d(1465, 670);
    glVertex2d(1430, 670);
    glEnd();

    // car window
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(1425, 640);
    glVertex2d(1445, 640);
    glVertex2d(1445, 660);
    glVertex2d(1430, 660);
    glEnd();

    // car window
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(1450, 640);
    glVertex2d(1470, 640);
    glVertex2d(1465, 660);
    glVertex2d(1450, 660);
    glEnd();

    // car wheel
    glColor3ub(0, 0, 0);
    circle(10, 14, 1435, 610);
    circle(10, 14, 1465, 610);

    glColor3ub(245, 245, 245);
    circle(6, 10, 1435, 610);
    circle(6, 10, 1465, 610);

    glPopMatrix();


    /// Grass Color (Changes with Rain & Night)
if (isNight && rainday) {
    glColor3f(0.1f, 0.3f, 0.1f);
} else if (isNight) {
    glColor3f(0.2f, 0.4f, 0.2f);
} else if (rainday) {
    glColor3f(0.4f, 0.6f, 0.2f);
} else {
    glColor3f(0.6f, 0.8f, 0.2f);
}
glBegin(GL_QUADS);
glVertex2i(0, 340);
glVertex2i(1500, 340);
glVertex2i(1500, 600);
glVertex2i(0, 600);
glEnd();


/// Trees
for (int i = 50; i < 1500; i += 150) {
    // Tree trunk
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2i(i, 340);
    glVertex2i(i + 20, 340);
    glVertex2i(i + 20, 400);
    glVertex2i(i, 400);
    glEnd();

    // Tree Leaves
    if (isNight && rainday) {
        glColor3f(0.0f, 0.2f, 0.0f);
    } else if (isNight) {
        glColor3f(0.0f, 0.3f, 0.0f);
    } else if (rainday) {
        glColor3f(0.0f, 0.4f, 0.0f);
    } else {
        glColor3f(0.0f, 0.6f, 0.0f);
    }

    glBegin(GL_TRIANGLES);
    glVertex2i(i - 30, 400);
    glVertex2i(i + 50, 400);
    glVertex2i(i + 10, 460);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2i(i - 25, 430);
    glVertex2i(i + 45, 430);
    glVertex2i(i + 10, 490);
    glEnd();
}

/// Middle Trees
for (int i = 100; i < 1500; i += 150) {
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2i(i, 470);
    glVertex2i(i + 20, 470);
    glVertex2i(i + 20, 530);
    glVertex2i(i, 530);
    glEnd();

    // Tree Leaves (Change based on Rain & Night)
    if (isNight && rainday) {
        glColor3f(0.0f, 0.2f, 0.0f);
    } else if (isNight) {
        glColor3f(0.0f, 0.3f, 0.0f);
    } else if (rainday) {
        glColor3f(0.0f, 0.4f, 0.0f);
    } else {
        glColor3f(0.0f, 0.6f, 0.0f);
    }

    glBegin(GL_TRIANGLES);
    glVertex2i(i - 30, 530);
    glVertex2i(i + 50, 530);
    glVertex2i(i + 10, 590);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2i(i - 25, 560);
    glVertex2i(i + 45, 560);
    glVertex2i(i + 10, 620);
    glEnd();
}

/// Railway Line (Darkens at Night)
if (isNight) {
    glColor3ub(100, 100, 100); // Darker railway at night
} else {
    glColor3ub(150, 150, 144);
}
    glBegin(GL_QUADS);
    glVertex2i(0, 340);
    glVertex2i(0, 365);
    glVertex2i(1500, 365);
    glVertex2i(1500, 340);
    glEnd();

/// Upper & Lower Border Lines (Dark at Night)
if (isNight) {
    glColor3ub(50, 50, 50);
} else {
    glColor3ub(0, 0, 0);
}

    glBegin(GL_QUADS);
    glVertex2i(0, 362);
    glVertex2i(1500, 362);
    glVertex2i(1500, 365);
    glVertex2i(0, 365);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(0, 340);
    glVertex2i(1500, 340);
    glVertex2i(1500, 344);
    glVertex2i(0, 344);
    glEnd();

/// Rail Tracks (Darker at Night)
if (isNight) {
    glColor3ub(50, 50, 50);
} else {
    glColor3ub(0, 0, 0);
}
glBegin(GL_LINES);
for (float j = 0; j <= 1500; j += 20) {
    glVertex2i(10 + j, 340);
    glVertex2i(15 + j, 365);
}
glEnd();

    ///train

    //Rail Body

    glPushMatrix();
    glTranslatef(_ang_tri, 0.0, 0.0);

    glColor3f(0.192, 0.576, 0.705);
    glBegin(GL_QUADS);
    glVertex2i(100, 360);
    glVertex2i(170, 360);
	glVertex2i(170, 410);
	glVertex2i(100, 410);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(110, 385);
    glVertex2i(120, 385);
	glVertex2i(120, 400);
	glVertex2i(110, 400);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(130, 385);
    glVertex2i(140, 385);
	glVertex2i(140, 400);
	glVertex2i(130, 400);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(150, 385);
    glVertex2i(160, 385);
	glVertex2i(160, 400);
	glVertex2i(150, 400);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
    glVertex2i(100, 370);
    glVertex2i(170, 370);
	glVertex2i(170, 375);
	glVertex2i(100, 375);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(170, 360);
    glVertex2i(176, 370);
	glVertex2i(176, 420);
	glVertex2i(170, 410);
	glEnd();


	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(101, 410);
    glVertex2i(170, 410);
	glVertex2i(176, 420);
	glVertex2i(105, 420);
	glEnd();

	glPushMatrix();
    glTranslatef(115, 352, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=10;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
   glPopMatrix();


    glPushMatrix();
    glTranslatef(155, 352, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=10;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
   glPopMatrix();


    glPushMatrix();
    glTranslatef(75, 0, 0);

    glColor3f(0.192, 0.576, 0.705);
    glBegin(GL_QUADS);
    glVertex2i(100, 360);
    glVertex2i(170, 360);
	glVertex2i(170, 410);
	glVertex2i(100, 410);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(110, 385);
    glVertex2i(120, 385);
	glVertex2i(120, 400);
	glVertex2i(110, 400);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(130, 385);
    glVertex2i(140, 385);
	glVertex2i(140, 400);
	glVertex2i(130, 400);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(150, 385);
    glVertex2i(160, 385);
	glVertex2i(160, 400);
	glVertex2i(150, 400);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
    glVertex2i(100, 370);
    glVertex2i(170, 370);
	glVertex2i(170, 375);
	glVertex2i(100, 375);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(170, 360);
    glVertex2i(176, 370);
	glVertex2i(176, 420);
	glVertex2i(170, 410);
	glEnd();


	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(101, 410);
    glVertex2i(170, 410);
	glVertex2i(176, 420);
	glVertex2i(105, 420);
	glEnd();

	glPushMatrix();
    glTranslatef(115, 352, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=10;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
   glPopMatrix();


   glPushMatrix();
    glTranslatef(155, 352, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=10;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();

    glPopMatrix();



    glPushMatrix();
    glTranslatef(-75, 0, 0);

    glColor3f(0.192, 0.576, 0.705);
    glBegin(GL_QUADS);
    glVertex2i(100, 360);
    glVertex2i(170, 360);
	glVertex2i(170, 410);
	glVertex2i(100, 410);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(110, 385);
    glVertex2i(120, 385);
	glVertex2i(120, 400);
	glVertex2i(110, 400);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(130, 385);
    glVertex2i(140, 385);
	glVertex2i(140, 400);
	glVertex2i(130, 400);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(150, 385);
    glVertex2i(160, 385);
	glVertex2i(160, 400);
	glVertex2i(150, 400);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
    glVertex2i(100, 370);
    glVertex2i(170, 370);
	glVertex2i(170, 375);
	glVertex2i(100, 375);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(170, 360);
    glVertex2i(176, 370);
	glVertex2i(176, 420);
	glVertex2i(170, 410);
	glEnd();


	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(101, 410);
    glVertex2i(170, 410);
	glVertex2i(176, 420);
	glVertex2i(105, 420);
	glEnd();

	glPushMatrix();
    glTranslatef(115, 352, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=10;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
   glPopMatrix();


    glPushMatrix();
    glTranslatef(155, 352, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=10;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(150, 0, 0);

    glColor3f(0.192, 0.576, 0.705);
    glBegin(GL_QUADS);
    glVertex2i(100, 360);
    glVertex2i(170, 360);
	glVertex2i(170, 410);
	glVertex2i(100, 410);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(110, 385);
    glVertex2i(120, 385);
	glVertex2i(120, 400);
	glVertex2i(110, 400);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(130, 385);
    glVertex2i(140, 385);
	glVertex2i(140, 400);
	glVertex2i(130, 400);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(150, 385);
    glVertex2i(160, 385);
	glVertex2i(160, 400);
	glVertex2i(150, 400);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
    glVertex2i(100, 370);
    glVertex2i(170, 370);
	glVertex2i(170, 375);
	glVertex2i(100, 375);
	glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(170, 360);
    glVertex2i(176, 370);
	glVertex2i(176, 420);
	glVertex2i(170, 410);
	glEnd();


	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(101, 410);
    glVertex2i(170, 410);
	glVertex2i(176, 420);
	glVertex2i(105, 420);
	glEnd();

	glPushMatrix();
    glTranslatef(115, 352, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=10;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
   glPopMatrix();


   glPushMatrix();
    glTranslatef(155, 352, 0.0);
    glBegin(GL_POLYGON);
    glColor3ub(109, 109, 115);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=10;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();

    glPopMatrix();

    glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
    glVertex2i(322, 405);
    glVertex2i(330, 405);
	glVertex2i(330, 392);
	glVertex2i(322, 392);
	glEnd();

	glColor3f(0.325, 0.101, 0.619);
	glBegin(GL_QUADS);
    glVertex2i(310, 413);
    glVertex2i(300, 413);
	glVertex2i(300, 418);
	glVertex2i(310, 418);
	glEnd();

	glPushMatrix();
    glTranslatef(303, 427, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.709, 0.701, 0.717);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=3;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(293, 430, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.709, 0.701, 0.717);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/200;
		float r=4;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(283, 432, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.709, 0.701, 0.717);
	for(int i=0;i<360;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/180;
		float r=5;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();

    glPopMatrix();

   /// Wall & Dam
if (isNight && rainday) {
    glColor3f(0.3, 0.2, 0.1);
} else if (isNight) {
    glColor3f(0.4, 0.2, 0.1);
} else if (rainday) {
    glColor3f(0.5, 0.25, 0.1);
} else {
    glColor3f(0.6, 0.3, 0.0);
}
glBegin(GL_POLYGON);
glVertex2f(0.0f, 310.0f);
glVertex2f(1500.0f, 310.0f);
glVertex2f(1500.0f, 340.0f);
glVertex2f(0.0f, 340.0f);
glEnd();


/// Dam
if (isNight && rainday) {
    glColor3f(0.3, 0.2, 0.1);
} else if (isNight) {
    glColor3f(0.4, 0.2, 0.1);
} else if (rainday) {
    glColor3f(0.5, 0.25, 0.1);
} else {
    glColor3f(0.6, 0.3, 0.0);
}
glBegin(GL_POLYGON);
glVertex2f(0.0f, 310.0f);
glVertex2f(1500.0f, 310.0f);
glVertex2f(1500.0f, 340.0f);
glVertex2f(0.0f, 340.0f);
glEnd();


if (isNight) {
    glColor3f(0.3, 0.3, 0.3);
} else {
    glColor3f(0.5, 0.5, 0.5);
}
float y1 = 5.0f;
for (float y = 310.0f; y <= 340.0f; y += y1) {
    glBegin(GL_LINES);
    glVertex2f(0.0f, y);
    glVertex2f(1500.0f, y);
    glEnd();
}

if (isNight) {
    glColor3f(0.3, 0.15, 0.1);
} else {
    glColor3f(0.4, 0.2, 0.1);
}
for (float x = 50.0f; x <= 1450.0f; x += 100.0f) {
    glBegin(GL_LINES);
    glVertex2f(x, 310.0f); // Bottom
    glVertex2f(x, 340.0f); // Top
    glEnd();
}





   /// Beach Color
if (isNight && rainday) {
    glColor3f(0.4f, 0.3f, 0.2f);
} else if (isNight) {
    glColor3f(0.6f, 0.5f, 0.3f);
} else if (rainday) {
    glColor3f(0.8f, 0.7f, 0.5f);
} else {
    glColor3f(0.94f, 0.85f, 0.56f);
}

// Draw Beach
glBegin(GL_POLYGON);
glVertex2f(0.0f, 250.0f);
glVertex2f(1500.0f, 250.0f);
glVertex2f(1500.0f, 310.0f);
glVertex2f(0.0f, 310.0f);
glEnd();


/// Water Color
if (isNight && rainday) {
    glColor3f(0.0f, 0.2f, 0.3f);
} else if (isNight) {
    glColor3f(0.0f, 0.3f, 0.5f);
} else if (rainday) {
    glColor3f(0.0f, 0.3f, 0.5f);
} else {
    glColor3f(0.0f, 0.5f, 0.7f);
}

// Draw Water
glBegin(GL_POLYGON);
glVertex2f(0.0f, 0.0f);
glVertex2f(1500.0f, 0.0f);
glVertex2f(1500.0f, 250.0f);
glVertex2f(0.0f, 250.0f);
glEnd();










    ///---------->SHIP CODE <------------
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.55f, 0.0f, 0.0f);//red
    glVertex2f(ship+150,100);
    glVertex2f(ship+530,100);
    glVertex2f(ship+500,70);
    glVertex2f(ship+170,70);
    glVertex2f(ship+150,80);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);//white body
    glVertex2f(ship+100,180);
    glVertex2f(ship+100,150);
    glVertex2f(ship+150,100);
    glVertex2f(ship+530,100);
    glVertex2f(ship+610,180);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.5f);//body shadow
    glVertex2f(ship+100,180);
    glVertex2f(ship+100,170);
    glVertex2f(ship+600,170);
    glVertex2f(ship+610,180);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.678f, 0.847f, 0.902f);//body window
    glVertex2f(ship+150,165);
    glVertex2f(ship+540,165);
    glVertex2f(ship+540,150);
    glVertex2f(ship+150,150);
    glEnd();
    glBegin(GL_QUADS);
    window=0;
    for(int i=0;i<20;i++){
        glColor3f(0.4f, 0.5f, 0.8f);//body window
        glVertex2f(ship+window+160,165);
        glVertex2f(ship+window+170,165);
        glVertex2f(ship+window+170,150);
        glVertex2f(ship+window+160,150);
        window+=20;
    }
    glEnd();
    glBegin(GL_QUADS);
    window=0;
    for(int i=0;i<40;i++){
        glColor3f(0.1f, 0.1f, 0.1f);//body window
        glVertex2f(ship+window+155,140);
        glVertex2f(ship+window+160,140);
        glVertex2f(ship+window+160,130);
        glVertex2f(ship+window+155,130);
        window+=10;
    }
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);//first layer
    glVertex2f(ship+150,180);
    glVertex2f(ship+540,180);
    glVertex2f(ship+540,200);
    glVertex2f(ship+150,200);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.5f);//first layer shadow
    glVertex2f(ship+150,200);
    glVertex2f(ship+540,200);
    glVertex2f(ship+540,205);
    glVertex2f(ship+150,205);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.678f, 0.847f, 0.902f);// window
    glVertex2f(ship+150,185);
    glVertex2f(ship+540,185);
    glVertex2f(ship+540,195);
    glVertex2f(ship+150,195);
    glEnd();
    glBegin(GL_QUADS);
    window=0;
    for(int i=0;i<19;i++){
        glColor3f(0.4f, 0.5f, 0.8f);// window
        glVertex2f(ship+window+160,185);
        glVertex2f(ship+window+170,185);
        glVertex2f(ship+window+170,195);
        glVertex2f(ship+window+160,195);
        window+=20;
    }
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);//second layer
    glVertex2f(ship+150,205);
    glVertex2f(ship+540,205);
    glVertex2f(ship+530,225);
    glVertex2f(ship+160,225);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.5f);//second layer shadow
    glVertex2f(ship+160,225);
    glVertex2f(ship+530,225);
    glVertex2f(ship+530,230);
    glVertex2f(ship+160,230);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.678f, 0.847f, 0.902f);// window
    glVertex2f(ship+160,210);
    glVertex2f(ship+530,210);
    glVertex2f(ship+530,220);
    glVertex2f(ship+160,220);
    glEnd();
    glBegin(GL_QUADS);
    window=0;
    for(int i=0;i<18;i++){
        glColor3f(0.4f, 0.5f, 0.8f);// window
        glVertex2f(ship+window+170,210);
        glVertex2f(ship+window+180,210);
        glVertex2f(ship+window+180,220);
        glVertex2f(ship+window+170,220);
        window+=20;
    }
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);//third layer
    glVertex2f(ship+170,230);
    glVertex2f(ship+310,230);
    glVertex2f(ship+300,245);
    glVertex2f(ship+180,245);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.5f, 0.8f);// window
    glVertex2f(ship+180,232);
    glVertex2f(ship+300,232);
    glVertex2f(ship+293,243);
    glVertex2f(ship+187,243);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);//chimney
    glVertex2f(ship+400,230);
    glVertex2f(ship+450,230);
    glVertex2f(ship+450,280);
    glVertex2f(ship+400,280);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);//chimney shadow
    glVertex2f(ship+400,280);
    glVertex2f(ship+450,280);
    glVertex2f(ship+450,285);
    glVertex2f(ship+400,285);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);//design
    glVertex2f(ship+210,245);
    glVertex2f(ship+210,290);
    glVertex2f(ship+250,290);
    glVertex2f(ship+280,245);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.5f);//design
    glVertex2f(ship+210,245);
    glVertex2f(ship+210,250);
    glVertex2f(ship+278,250);
    glVertex2f(ship+280,245);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void Rain(int value) {
    if (rainday) {
        _rain += 5.0f;

        glColor3f(1.0, 1.0, 1.0);

        for (int i = 0; i < 1050; i++) {
            int x = rand() % 1500;
            int y = rand() % 950;

            glBegin(GL_LINES);
            glVertex2d(x, y);
            glVertex2d(x, y - 10); // Adjusted to give a downward rain effect
            glEnd();
        }
        glutPostRedisplay();
        glutTimerFunc(5, Rain, 0);
    }


glutSwapBuffers();
}

void update(int value){
    if(active){
    ship+=5;
    glutPostRedisplay();
    glutTimerFunc(20,update,0);
    }
}

void updateTrain(int value) {
    if (moving) {
        _ang_tri += 6.0; // Move train

        // Reset position when train goes out of screen
        if (_ang_tri > 1500) {
            _ang_tri = -200;  // Reset train to the left
        }

        glutPostRedisplay();
        glutTimerFunc(20, updateTrain, 0);
    }
}

void mouse(int button, int state, int x, int y) {
    // Left mouse button click
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        moving = !moving; // Toggle movement state
        if (moving) {
            glutTimerFunc(speed, updateTrain, 0); // Start the timer with the current speed
        }
    }
    // Right mouse button click
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (speed > 5) {
            speed -= 5;
        }
        if (moving) {
            glutTimerFunc(speed, updateTrain, 0); // Restart the timer with the new speed
        }
    }
}



void handleKeyboard(unsigned char key, int x, int y) {
    if (key == 'w') { //start
        active=true;
        glutTimerFunc(20,update,0);
    }
    if (key == 's') { //stop
        active=false;
    }
    if (key == 'a') { //reset
            ship=0;
        active=false;
    }
     if (key == 'n') {
        isNight = true; //night
    }
     if (key == 'd') {
        isNight = false; //day
    }

    if (key == 'r') { //stop
        rainday=true;
        Rain(_rain);

    }
    if (key == 'c') { //stop
        rainday=false;
    }
    glutPostRedisplay(); // Redraw the screen with the new scenario
}
void timer(int value) {
    carPosition -= 4.0f; // Move car to the left
    if (carPosition < -300) carPosition = 1500; // Reset position if off-screen

    //_ang_tri += 3.0f; // Move train to right
    //if (_ang_tri > 1500) _ang_tri = -300; // Reset train position

     bx += 2.8f;
    if (bx > 0){
        bx = -1500;}

    // Move clouds to the right
    cloud1PosX += cloudSpeed;
    cloud2PosX += cloudSpeed;

    // Reset position when clouds go off-screen
    if (cloud1PosX > 1500) {
        cloud1PosX = -100; // Reset cloud 1
    }
    if (cloud2PosX > 1500) {
        cloud2PosX = -100; // Reset cloud 2
    }

    glutPostRedisplay(); // Redraw scene
    glutTimerFunc(16, timer, 0); // Call this function again after 16ms
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1500, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Maritime World Journey");

    // Display controls in the command prompt

    cout << "=== Controls ===" << endl;
    cout << "Keyboard Operations:" << endl;
    cout << "  W - Start the ship" << endl;
    cout << "  S - Stop the ship" << endl;
    cout << "  A - Reset the ship position" << endl;
    cout << "  N - Switch to night mode" << endl;
    cout << "  D - Switch to day mode" << endl;
    cout << "  R - Start rain" << endl;
    cout << "  C - Stop rain" << endl;

    cout << "\nMouse Operations:" << endl;
    cout << "  Left Click - Start/Stop the train" << endl;
    cout << "  Right Click - Increase train speed" << endl;

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0); // Start the timer
    glutMouseFunc(mouse);
    glutKeyboardFunc(handleKeyboard);

    glutMainLoop();
    return 0;
}
