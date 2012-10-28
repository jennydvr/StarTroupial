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
int fps = 60;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    for (int i = 0; i != stars.size(); ++i)
        stars[i].draw();
    
    for (int i = 0; i != rings.size(); ++i)
        rings[i].draw();
    
 //   player.draw();
    
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

void update() {
    // Update stars
    if (rand() % 100 + 1 > 80)
        stars.push_back(star());
    
    for (int i = 0; i != stars.size(); ++i)
        stars[i].update();
    
    // Update rings
    addRings(rand() % 8);
    
    for (int i = 0; i != rings.size(); ++i)
        rings[i].update();
    
    // Remove dead stuff
    remove_if(rings.begin(), rings.end(), ring::isDead);
    remove_if(stars.begin(), stars.end(), star::isDead);
}

void timer(int v) {
    // Animate the world
    if (!paused)
        update();
    
    // Draw the current frame
    glutPostRedisplay();
    glutTimerFunc(1000 / fps, timer, 0);
}

void init() {
    GLfloat black[] = {0, 0, 0, 1};
    GLfloat white[] = {1, 1, 1, 1};
    GLfloat direction[] = {1, 1, 1, 0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, direction);
    
    glEnable(GL_LIGHTING);                // so the renderer considers light
    glEnable(GL_LIGHT0);                  // turn LIGHT0 on
    glEnable(GL_DEPTH_TEST);              // so the renderer considers depth
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'p': case 'P':
            paused = !paused;
            break;
    }
    
    if (paused)
        return;
    
    switch (key) {
        case 'w': case 'W':       // Up -> +y
            player.move(0, 0.25);
            break;
        case 's': case 'S':      // Down -> -y
            player.move(0, -0.25);
            break;
        case 'a': case 'A':      // Left -> +x
            player.move(-0.25, 0);
            break;
        case 'd': case 'D':      // Right -> -x
            player.move(0.25, 0);
            break;
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    srand(time(NULL));
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
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
