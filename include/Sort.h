#ifndef SORT_H
#define SORT_H
#include <string>
#include <vector>
#include <iostream>

enum class Status {
    None, Key, Search, Sorted, Selected
};



struct Item {
    int value;
    Status status;
};

class Sort {
public:
    virtual bool sort(std::vector<Item>&)=0;
    int Comparsion() {
        return comparsion;
    }
    std::string Name() {
        return name;
    }
protected:
    std::string name;
    bool done;
    int comparsion;
    int compare(const Item& v1, const Item& v2) {
        comparsion++;
        return v1.value - v2.value;
    }
    void swap(Item& v1, Item& v2) {
        int tmp = v1.value;
        v1.value = v2.value;
        v2.value = tmp;
    }

private:
};

class SelectionSort : public Sort {
public:
    SelectionSort():curi(0), mi(0), scount(0) {
        name = "Search Sort";
        done = false;
    }
    bool sort(std::vector<Item>&);
private:
    int curi, mi, scount;
};


class MergeSort : public Sort {
public:
    MergeSort():li(0), ri(0) {
        name = "Merge Sort";
        done = false;
    }
    bool sort(std::vector<Item>&);

private:
    struct Recurs_level {
        int left, right;
        std::vector<Item> p_left;
        std::vector<Item> p_right;
    };
    std::vector<Recurs_level> stack;
    int li, ri;
    std::vector<Item> tmp;

};

class BubbleSort : public Sort {
public:
    BubbleSort():i(0), j(0) {
        name  = "Bubble Sort";
        done = false;
    };
    bool sort (std::vector<Item>&);
private:
    int i, j;

};

class QuickSort : public Sort {
public :
    QuickSort():base(-1), l(0), r(0) {
        name = "Quick Sort";
        done = false;
    }
    bool sort (std::vector<Item>&);
private:
    int base, l, r;
    struct Recurs_level {
        int ll, rr;
    };
    std::vector<Recurs_level> stack;
};

class HeapSort : public Sort {
public :
    HeapSort():size(-1), index(-1), is_heap(false) {
        name = "Heap Sort";
        done = false;
    }
    bool sort(std::vector<Item>&);
private:
    int size, index;
    std::vector<int> stack;
    bool is_heap;
    void heapify(std::vector<Item>&);
};

class ShakerSort : public Sort {
public:
    ShakerSort(): left(-1), right(-1), index(0), s(0), move_left(true){
        name = "Shaker Sort";
        done = false;
    }
    bool sort(std::vector<Item>&);
private:
    int left, right, index, s;
    bool move_left;
};

class CombSort : public Sort {
public :
    CombSort():jump(0), index(0), swaped(false){
        name="Comb Sort";
        done = false;
    }
    bool sort(std::vector<Item>&);
private:
    size_t jump, index;
    bool swaped;
};

class InsertionSort: public Sort{
public:
    InsertionSort():i(1), j(0){
        name = "Insertion Sort";
        done = false;
    }
    bool sort(std::vector<Item>&);
private:
    size_t i, j;
};

class ShellSort: public Sort{
public:
    ShellSort(): i(0), j(0), d(-1){
        name = "Shell Sort";
        done = false;
    }
    bool sort(std::vector<Item>&);
private:
    int i, j, d;
};

class RadxSort:public Sort{
public:
    RadxSort():d(sizeof(Item::value) * 8 - 1), i(0), l(0), r(0){
        name = "Radx Sort";
        done = false;

        bag[0] = std::vector<Item>();
        bag[1] = std::vector<Item>();
    }
    bool sort(std::vector<Item>&);
private:
    std::vector<Item> bag[2];
    int d;
    size_t i, l, r;
};

#endif // SORT_H
