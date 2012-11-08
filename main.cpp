//
//  main.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include "objectManager.h"

using namespace std;

// Variables
bool paused = false;
float fps = 60;
bool gameOver = false;

// Draws a text on screen
void drawText(float pos[], char *text) {
	glPushMatrix();
    
        // The font is too big, so it needs to be resized
        glScalef(1/152.38, 1/152.38, 1/152.38);
        glScalef(3.5, 3, 3);
        glTranslatef(pos[0], pos[1], pos[2]);
    
        for (char* c = text; *c != '\0'; ++c)
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    
	glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    // Draw objects
    drawObjects();
    
    // Draw score
    char integerString[32];
    char title[64] = "Score: ";
    
    sprintf(integerString, "%d", score);
    strcat(title, integerString);
    
    float pos0[] = {-2800, -2350, 100};
    drawText(pos0, title);
    
    // Draw time
    sprintf(integerString, "%d", gametime);
    sprintf(title, "Time: ");
    strcat(title, integerString);
    
    float pos1[] = {2200, 2250, 100};
    drawText(pos1, title);
    
    // Draw fps
    if (debug || fps != 60) {
        sprintf(integerString, "%1.2f", fps);
        sprintf(title, "FPS: ");
        strcat(title, integerString);
        
        float pos2[] = {-2800, 2250, 100};
        drawText(pos2, title);
    }
    
    // Game over
    if (gameOver) {
        sprintf(title, "GAME OVER");
        float pos3[] = {-2800, 2250, 100};
        drawText(pos3, title);
        
        
        sprintf(title, "Play again = r  Quit = q");
        float pos4[] = {-2800, 2050, 100};
        drawText(pos4, title);
    }
    
    glPopMatrix();
    glFlush();
}

void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    
    // Set perspective view
    glLoadIdentity();
    gluPerspective(90, GLfloat(w) / GLfloat(h), 1, 50);
    
    // Set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
}

void timer(int v) {
    // Check game over
    gameOver = checkGametime();
    
    if (gameOver) {
        paused = debug = false;
        fps = 60;
        glutPostRedisplay();
        glutTimerFunc(1000 / fps, timer, 0);
        return;
    }
    
    // Animate the world
    if (!paused) {
        updateObjects();
        addObjects();
        checkGametime();
    }
    
    // Draw the current frame
    glutPostRedisplay();
    glutTimerFunc(1000 / fps, timer, 0);
}

void init() {
    srand((unsigned int)time(NULL));
    
    GLfloat black[] = {0.1, 0.1, 0.1, 1};
    GLfloat white[] = {1, 1, 1, 1};
    GLfloat direction[] = {0, 25, 50, 0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    
    glEnable(GL_LIGHTING);          // so the renderer considers light
    glEnable(GL_LIGHT0);            // turn LIGHT0 on
    glEnable(GL_DEPTH_TEST);        // so the renderer considers depth
    glEnable(GL_COLOR_MATERIAL);    // enable color tracking
    glEnable(GL_BLEND);
    
    glShadeModel(GL_SMOOTH);                            // Gourad shading
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  // define what will be changed with glColor
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void keyboard(unsigned char key, int x, int y) {
    if (gameOver) {
        switch (key) {
            case 'r': case 'R': // Reset game
                resetGame();
                break;
            case 'q':           // Quit game
                exit(0);
                break;
        }
        
        return;
    }
    
    switch (key) {
        case 'p': case 'P':
            paused = !paused;
            
            if (paused)
                pausedTime = glutGet(GLUT_ELAPSED_TIME);
            else
                initialGametime += glutGet(GLUT_ELAPSED_TIME) - pausedTime;
            break;
        case '+':
            fps *= (fps != 60) ? 2 : 1;
            break;
        case '-':
            fps /= (fps > 0.05) ? 2 : 1;
            break;
        case 'o': case 'O':
            debug = !debug;
            break;
    }
    
    if (paused)
        return;
    
    switch (key) {
        case 'w': case 'W':       // Up -> +y
            player.update(0, 0.25);
            break;
        case 's': case 'S':      // Down -> -y
            player.update(0, -0.25);
            break;
        case 'a': case 'A':      // Left -> +x
            player.update(-0.25, 0);
            break;
        case 'd': case 'D':      // Right -> -x
            player.update(0.25, 0);
            break;
    }
    
    glutPostRedisplay();
}

#define BUFSIZE 512

void processHits(GLint hits, GLuint buffer[]) {
    
	unsigned int j = 0, menor = buffer[1], ident = 0;
	GLuint numNames;
    
    if (hits == 0) {      // No intersections with asteroids
        bullets.push_back(player.shoot(-1, -1, -1));
        return;
    }
    
	for (int i = 0; i != hits; ++i) {
		numNames = buffer[j];
		
		if (menor >= buffer[j+1]) {
			menor =	buffer[j+1];
			ident = buffer[(j+2) + 1];
		}
        
		j = (j + 4) + (numNames - 1);
	}
    
    bullets.push_back(player.shoot(asteroids[ident].x, asteroids[ident].y, asteroids[ident].z));
}

void pick(int button, int state, int x, int y) {
	GLuint selectBuf[BUFSIZE];
	GLint hits, viewport[4];
    
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;
    
	glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(BUFSIZE, selectBuf);
    
	glRenderMode(GL_SELECT);
    
	glInitNames();
	glPushName(0);
    
 	glMatrixMode(GL_PROJECTION);
 	glPushMatrix();
        glLoadIdentity();
    
        gluPickMatrix(GLfloat(x), GLfloat(viewport[3] - y), 1.0, 1.0, viewport);
        gluPerspective(90, GLfloat(viewport[2])/GLfloat(viewport[3]), 0.0001, 1000.0);
    
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity ();
            gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
    
            drawObjects(GL_SELECT);
        glPopMatrix();
    
        glMatrixMode(GL_PROJECTION);
 	glPopMatrix();
    glFlush();
	
	hits = glRenderMode (GL_RENDER);
	
	processHits (hits, selectBuf);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("StarTroupial");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(pick);
    glutTimerFunc(1000 / fps, timer, 0);
    
    // Initialize visual stuff
    init();
    
    // Initialize sounds
#ifdef USE_SOUNDS
    initSounds();
#endif
    
    glutMainLoop();
}
