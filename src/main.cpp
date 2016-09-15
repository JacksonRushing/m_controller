// Core Libraries
#include <windows.h>
#include <iostream>
#include <string>
#include <math.h>
#include <GLUT/glut.h>
#include "m_controller.h"
// 3rd Party Libraries
XINPUT_STATE* controller1;
int ticks = 0;
// Defines and Core variables
#define FRAMES_PER_SECOND 60
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND; // Miliseconds per frame

int windowWidth = 800;
int windowHeight = 600;

int mousepositionX;
int mousepositionY;



// A few conversions to know


float randInRange(int min, int max)
{
	return min + (float)(rand() / (float)(RAND_MAX + 1) * (max - min + 1));
}
/* function DisplayCallbackFunction(void)
* Description:
*  - this is the openGL display routine
*  - this draws the sprites appropriately
*/
void DisplayCallbackFunction(void)
{

	float r = randInRange(0, 1);
	float g = randInRange(0, 1);
	float b = randInRange(0, 1);
	/* clear the screen */
	//glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(r, g, b, 1.0f);
	//glClearColor(0.2, 0.2, 0.2, 0.2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();



	/* This is where we draw things */
	glColor3f(0.5f, 0.0f, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	/*
	glVertex3f(-0.25f, -0.25f, 0.0f); //--
	glVertex3f(0.25, -0.25f, 0.0f); //+-
	glVertex3f(0.25, 0.25f, 0.0f); //++
	glVertex3f(-0.25f, 0.25f, 0.0f); //-+
	*/
	/*
	glVertex3f(-0.25f - r, -0.25f + r, 0.0f); //--
	glVertex3f(0.25f -g, -0.25f + g, 0.0f); //+-
	glVertex3f(0.25f +b, 0.25f - b, 0.0f); //++
	glVertex3f(-0.25f + r, 0.25f + r, 0.0f); //-+
	*/

	glVertex3f(randInRange(-1, 1), randInRange(-1, 1), 0.0f); //--
	glVertex3f(randInRange(-1, 1), randInRange(-1, 1), 0.0f); //+-
	glVertex3f(randInRange(-1, 1), randInRange(-1, 1), 0.0f); //++
	glVertex3f(randInRange(-1, 1), randInRange(-1, 1), 0.0f); //-+

	glEnd();






	/* Swap Buffers to Make it show up on screen */
	glutSwapBuffers();
}

/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	std::cout << "Key Down:" << (int)key << std::endl;

	switch (key)
	{
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(0);
		break;
	case 'w':
		std::cout << getFirstControllerId() << std::endl;
		break;

	}
}

/* function void KeyboardUpCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is lifted
*/
void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
}

/* function TimerCallbackFunction(int value)
* Description:
*  - this is called many times per second
*  - this enables you to animate things
*  - no drawing, just changing the state
*  - changes the frame number and calls for a redisplay
*  - FRAME_DELAY is the number of milliseconds to wait before calling the timer again
*/
void TimerCallbackFunction(int value)
{
	/* this call makes it actually show up on screen */
	glutPostRedisplay();
	/* this call gives it a proper frame delay to hit our target FPS */
	glutTimerFunc(FRAME_DELAY, TimerCallbackFunction, 0);
	ticks++;
}

/* function WindowReshapeCallbackFunction()
* Description:
*  - this is called whenever the window is resized
*  - and sets up the projection matrix properly
*  - currently set up for an orthographic view (2D only)
*/
void WindowReshapeCallbackFunction(int w, int h)
{
	// switch to projection because we're changing projection
	float asp = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	windowWidth = w;
	windowHeight = h;

	//switch back to modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	// Handle mouse clicks
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			std::cout << "LEFT CLICK" << std::endl;
			break;

		case GLUT_RIGHT_BUTTON:
			std::cout << "RIGHT CLICK" << std::endl;
			break;

		case GLUT_MIDDLE_BUTTON:
			std::cout << "MIDDLE CLICK" << std::endl;
			break;

		}
		std::cout << "Mouse x: " << x << "Y: " << y << std::endl;
	}



}


/* function MouseMotionCallbackFunction()
* Description:
*   - this is called when the mouse is clicked and moves
*/
void MouseMotionCallbackFunction(int x, int y)
{
}

/* function MousePassiveMotionCallbackFunction()
* Description:
*   - this is called when the mouse is moved in the window
*/
void MousePassiveMotionCallbackFunction(int x, int y)
{
	mousepositionX = x;
	mousepositionY = y;
}

/* function main()
* Description:
*  - this is the main function
*  - does initialization and then calls glutMainLoop() to start the event handler
*/
int main(int argc, char **argv)
{
	/* initialize the window and OpenGL properly */
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("radical window, my man");

	/* set up our function callbacks */
	glutDisplayFunc(DisplayCallbackFunction);	//draw
	glutKeyboardFunc(KeyboardCallbackFunction);	//keyDown
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);	//keyUp
	glutReshapeFunc(WindowReshapeCallbackFunction);	//windowResized
	glutMouseFunc(MouseClickCallbackFunction);	//mouseClick
	glutMotionFunc(MouseMotionCallbackFunction);	//mouseMovedActive
	glutPassiveMotionFunc(MousePassiveMotionCallbackFunction);	//mouseMovedPassive
	glutTimerFunc(1, TimerCallbackFunction, 0);	//timer or tick, incremental amount of time every frame				

												/* start the event handler */
	glutMainLoop();

	return 0;
}