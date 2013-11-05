#ifndef PAINTER_H
#define PAINTER_H
#include "Sort.h"
#include <string>
#include <vector>

struct Information {
    Information(std::string n, int c) {
        name = n;
        comparsions = c;
    }
    int comparsions;
    std::string name;
    std::string toString()const;
};

class Painter {

public:
    Painter();
    void CreateWindow(const char*, int , int);
    void draw(std::vector<Item>&);
    void showInfo(const Information& );

private:
    void setColor(Status);
    void drawRect(float, float, float, float);
    int w_Width;
    int w_Height;
    void print_str(const char*, float, float);

};

#endif // PAINTER_H
