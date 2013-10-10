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

struct {

    int mi = 0, curi = 0, scount = 0;
    bool done = false;

    void operator()(Elements& elem){
        if(done) return;
        elem[curi].state = Elements::None;
        elem[mi].state = Elements::None;
        if(elem.compare(curi, mi) > 0){
            mi = curi;
        }
        ++curi;

        if(curi > elem.Count() - scount - 1){
            elem.swap(mi, elem.Count() - scount - 1);
            ++scount;
            mi = 0; curi = 0;
        }
        if(scount == elem.Count())
            done = true;

        elem[mi].state = Elements::Key;
        elem[curi].state = Elements::Search;
        for(int i = elem.Count() - scount; i < elem.Count(); ++i)
            elem[i].state = Elements::Sorted;

    }
} SearchSort;


void timer(int val) {
    p.Info().time_span = std::chrono::duration_cast<std::chrono::duration<double>>(clock::now() - last_call).count();

    SearchSort(el);

    p.Info().comparsions = el.Comparsions();
    p.Info().swaps = el.Swaps();

    p.Info().name = "SearchSort";
    p.Info().done = SearchSort.done;



    display();

    last_call = clock::now();
    glutTimerFunc(1000/120, timer, 0);
}

void init(int& argc, char* argv[]) {
    glutInit(&argc, argv);
    p.CreateWindow(argv[0], 800, 480);

    glutDisplayFunc(display);
    glutTimerFunc(1000/120, timer, 0);


    el.shuffle();

}

void run() {
    glutMainLoop();
}

}



