#include <cstdlib>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Elements.h"

Elements::Elements(int c):count {c}, comparsions{}, swaps{} {
    for(int i = 0; i < count; i++)
        elements.push_back({i+1,None});
}

void Elements::shuffle() {
    Item tmp {};
    for(int i = 0; i < count; i++) {
        int index = rand()%count;
        tmp = elements[i];
        elements[i] = elements[index];
        elements[index] = tmp;
    }
}

Elements::Item& Elements::operator[](int index){
    return elements[index];
}

int Elements::compare(int a, int b){
    comparsions++;
    return elements[a].value - elements[b].value;
}

void Elements::swap(int a, int b){
    swaps++;
    Item tmp = elements[a];
    elements[a] = elements[b];
    elements[b] = tmp;
}

void Elements::reset(){
    comparsions = 0;
    swaps = 0;
}
