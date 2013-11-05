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

Sort* sorts[] {
    new RadxSort,
    new ShellSort,
    new InsertionSort,
    new CombSort,
    new ShakerSort,
    new HeapSort,
    new QuickSort,
    new BubbleSort,
    new MergeSort,
    new SelectionSort
};

int s_size = sizeof(sorts) / sizeof(Sort*);

int cur_sort = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    p.draw(el);

    if(cur_sort < s_size) {
        p.showInfo({sorts[cur_sort]->Name(), sorts[cur_sort]->Comparsion()});
    }

    glutSwapBuffers();
}

void generate_Elements(int count) {
    el.clear();
    for(int i=0; i<count; ++i)
        el.push_back({i+1, Status::None});
    srand(time(0));
    Item tmp;
    for(int i = 0; i < count; i++) {
        int index = rand()%(count-1);
        tmp = el[i];
        el[i] = el[index];
        el[index] = tmp;
    }
}

void update(int d) {

    if(cur_sort < s_size) {
        if(sorts[cur_sort]->sort(el)) {
            cur_sort++;
            if(cur_sort < s_size) {
                generate_Elements(40);
            }
        }
    }

    display();

    glutTimerFunc(dtime, update, 0);
}

void init(int& argc, char* argv[]) {
    glutInit(&argc, argv);
    p.CreateWindow(argv[0], 800, 480);

    generate_Elements(40);

    glutDisplayFunc(display);
    glutTimerFunc(dtime, update, 0);

}

void run(int s) {
    dtime = s;
    glutMainLoop();
}

}



