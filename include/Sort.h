#ifndef SORT_H
#define SORT_H
#include <string>
#include <vector>
#include <iostream>

enum class Status {None, Key, Search, Sorted, Selected};



struct Item {
    int value;
    Status status;
};

struct Information {
   // double time_span;
    int comparsions;
    //int swaps;
    //bool done;
    std::string name;

    std::string toString()const;
};

class Sort {
    public:
        Sort(): name{"No sort"}{};
        virtual void sort(std::vector<Item>&, void(*)(const Information&))=0;
        std::string Name(){return name;}
    protected:
        std::string name;
        int comparsion;
        int compare(const Item& v1, const Item v2){comparsion++; return v1.value - v2.value;}
    private:
};

class SearchSort : public Sort {
    public:
        SearchSort(){
            name = {"SearchSort"};
        }
        void sort(std::vector<Item>&, void(*)(const Information&));

};


class MergeSort : public Sort {
    public:
        MergeSort(){
            name = {"MergeSort"};
        }
        void sort(std::vector<Item>&, void(*)(const Information&));
    private:
        void(* displayFunc)(const Information&);
        std::vector<Item> mSort(std::vector<Item>&, int , int);
   //     std::vector<Item> merge(const std::vector<Item>&, const std::vector<Item>&);

};

#endif // SORT_H
