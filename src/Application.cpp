#include "Application.h"
#include "Elements.h"
#include "Painter.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <chrono>


namespace Application {

using clock = std::chrono::high_resolution_clock;
using time_point = std::chrono::high_resolution_clock::time_point;

const int N = 100;

Elements el(N);
Painter p;
time_point last_call = clock::now();


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    p.draw(el);
    p.showInfo();
    glutSwapBuffers();
}

void timer(int val){
    p.Info().time_span = std::chrono::duration_cast<std::chrono::duration<double>>(clock::now() - last_call).count();


    p.Info().comparsions = el.Comparsions();
    p.Info().swaps = el.Swaps();

    display();

    last_call = clock::now();
    glutTimerFunc(1000/60, timer, 0);
}

void init(int& argc, char* argv[]) {
    glutInit(&argc, argv);
    p.CreateWindow(argv[0], 800, 480);

    glutDisplayFunc(display);
    glutTimerFunc(1000/60, timer, 0);

    el[20].state = Elements::Key;
    el.shuffle();

}

void run() {
    glutMainLoop();
}

}



