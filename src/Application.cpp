#include "Application.h"
#include "Painter.h"
#include "Sort.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>

namespace Application {

int dtime = 0;

Painter p;

std::vector<Item> el;

Sort* sorts[]{
    new MergeSort,
    new SearchSort
};

void display(const Information& info){
    glClear(GL_COLOR_BUFFER_BIT);
    p.draw(el);

    p.showInfo(info.toString());
    glutSwapBuffers();
}

void display() {
    display({});
}

std::vector<Item> generate_Elements(int count){
    std::vector<Item> elem;
    for(int i=0;i<count; ++i)
        elem.push_back({i+1, Status::None});

    Item tmp;
    for(int i = 0; i < count; i++) {
        int index = rand()%(count-1);
        tmp = elem[i];
        elem[i] = elem[index];
        elem[index] = tmp;
    }
    return elem;
}

void update(int d){
    el = generate_Elements(40);
    sorts[0]->sort(el, display);
    el = generate_Elements(40);
    sorts[1]->sort(el, display);
}

void init(int& argc, char* argv[]) {
    glutInit(&argc, argv);
    p.CreateWindow(argv[0], 800, 480);

    glutDisplayFunc(display);
    glutTimerFunc(dtime, update, 0);

}

void run(int s) {
    dtime = s;
    glutMainLoop();
}

}



