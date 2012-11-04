//
//  main.cpp
//  StarTroupial
//
//  Created by Jenny Valdez on 27/10/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include <time.h>
#include "objectManager.h"

using namespace std;

// Variables
bool paused = false;
float fps = 60;

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
    
    float pos[] = {-2800, -2350, 100};
    drawText(pos, title);
    
    // Draw fps
    if (debug || fps != 60) {
        sprintf(integerString, "%1.2f", fps);
        sprintf(title, "FPS: ");
        strcat(title, integerString);
        
        float pos[] = {-2800, 2290, 100};
        drawText(pos, title);
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
    // Animate the world
    if (!paused) {
        updateObjects();
        addObjects();
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
    switch (key) {
        case 'p': case 'P':
            paused = !paused;
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
        case ' ':                // Add bullet
            bullets.push_back(player.shoot());
            break;
    }
    
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
    glutTimerFunc(1000 / fps, timer, 0);
    
    init();
    
    glutMainLoop();
}
