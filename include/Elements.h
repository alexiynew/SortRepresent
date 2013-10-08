#include <vector>
#ifndef ELEMENTS_H
#define ELEMENTS_H
class Elements {
public:
    enum Status {None, Key};
    struct Item {
        int value;
        Status state;
    };


    Elements(int);
    void shuffle();
    int Count() const {
        return count;
    }
    int Comparsions() const{return comparsions;}
    int Swaps() const {return swaps;}
    Elements::Item& operator[](int);
    int compare(int, int);
    void swap(int, int);
    void reset();

private:
    const int count;
    std::vector<Item> elements;
    int comparsions;
    int swaps;


};

#endif // ELEMENTS_H
