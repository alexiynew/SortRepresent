#include "Painter.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

Painter::Painter():info{}{

}

void Painter::CreateWindow(const char* name, int w, int h){
    w_Width = w;
    w_Height = h;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(w_Width, w_Height);
    glutInitWindowPosition(200, 10);
    glutCreateWindow(name);

    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1,0,1,-1,1);

}


void Painter::setColor(int ci){
    struct {
        float r, g, b;
    } Colors []{
        {0.3f, 0.3f, 0.3f},
        {0.1f, 0.8f, 0.3f}
    };

    glColor3f(Colors[ci].r, Colors[ci].g, Colors[ci].b);
}

void Painter::draw(Elements& el){
    w_Width = glutGet(GLUT_WINDOW_WIDTH);
    w_Height = glutGet(GLUT_WINDOW_HEIGHT);
    int N = el.Count();
    float scale = 1.0f / N;
    if(w_Width <= N){
        glBegin(GL_LINES);
        for(int i = 0; i<N; i++){
            setColor(el[i].state);
            glVertex2f(i*scale, 0);
            glVertex2f(i*scale, el[i].value*scale);
        }
        glEnd();
    } else {
        glBegin(GL_QUADS);
        for(int i = 0; i<N; i++){
            setColor(el[i].state);
            glVertex2f((i+1)*scale, 0);
            glVertex2f((i+1)*scale, el[i].value*scale);
            glVertex2f((i+0.1)*scale, el[i].value*scale);
            glVertex2f((i+0.1)*scale, 0);
        }
        glEnd();
    }
}


void Painter::showInfo(){
    std::string str = "";
    str += "Comparisons: " + std::to_string(info.comparsions) + "\t\t";
    str += "Swaps: " + std::to_string(info.swaps) + "\t\t";
    str += "Time span: " + std::to_string(info.time_span) + "\t\t";
    str += "width: " + std::to_string(w_Width) + "\t\t";
    str += "height: " + std::to_string(w_Height) + "\t\t";

    glColor3f(1,1,1);
    print_str(str.c_str(), 2.0/w_Width, 1-10.0/w_Height);
}

void Painter::print_str(const char* s, float x, float y){
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, reinterpret_cast<const unsigned char*>(s));
}
