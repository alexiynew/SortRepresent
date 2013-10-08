#ifndef PAINTER_H
#define PAINTER_H
#include "Elements.h"

class Painter {

public:
    Painter();
    void CreateWindow(const char*, int , int);
    void draw(Elements&);
    struct Information{
        double time_span;
        int comparsions;
        int swaps;
    };
    Information& Info(){return info;}
    void showInfo();

private:
    void setColor(int);
    void drawRect(float, float, float, float);
    int w_Width;
    int w_Height;
    Information info;
    void print_str(const char*, float, float);

};

#endif // PAINTER_H
