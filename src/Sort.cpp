#include "Sort.h"


void SearchSort::sort(std::vector<Item>& elem, void(*display)(const Information&)){

    bool done = false;
    int curi = 0, mi = 0, scount = 0;
    int size = elem.size();
    comparsion = 0;

    while(!done){
        elem[curi].status = Status::None;
        elem[mi].status = Status::None;
        if(compare(elem[curi], elem[mi]) > 0){
            mi = curi;
        }
        ++curi;

        if(curi > size - scount - 1){
            int tmp = elem[size - scount - 1].value;
            elem[size - scount - 1].value = elem[mi].value;
            elem[mi].value = tmp;
            ++scount;
            mi = 0; curi = 0;
        }
        if(scount == size)
            done = true;

        elem[mi].status = Status::Key;
        elem[curi].status = Status::Search;
        for(int i = size - scount; i < size; ++i)
            elem[i].status = Status::Sorted;

        display({comparsion, name});
    }

    display({comparsion, name});
}

std::string Information::toString()const{
    std::string str = "";
    str += "Name: " + name + "\n";
    str += "Comparisons: " + std::to_string(comparsions) + "\n";
    return str;
}


void MergeSort::sort(std::vector<Item>& elem, void(*display)(const Information&)){
//    bool done = false;
    displayFunc = display;

    mSort(elem, 0, elem.size()-1);

    //display({comparsion, name});
}

std::vector<Item> MergeSort::mSort(std::vector<Item>& elem, int l, int r){
    std::vector<Item> tmp;
    int size = r-l;
    if(size == 0){
        tmp.push_back(elem[l]);
        return tmp;
    }

    for(size_t i=l;i<elem.size();++i){
        elem[i].status = Status::None;
    }

    std::vector<Item> left = mSort(elem, l, l+size/2);
    std::vector<Item> right = mSort(elem, l+size/2 + 1, r);
    int ll = l;
    int rr = l+size/2+1;

    auto li = left.begin();
    auto ri = right.begin();

    while(li != left.end()){
        if(compare(*li, *ri) < 0 || ri == right.end()){
            tmp.push_back(*li);
            ++li;
            elem[ll].status = Status::Key;
            ll++;
        } else {
            if(ri != right.end()){
                tmp.push_back(*ri);
                ++ri;
                elem[rr].status = Status::Selected;
                rr++;
            }
        }
        displayFunc({comparsion, name});
    }
    while(ri != right.end()){
        tmp.push_back(*ri);
        ++ri;
        elem[rr].status = Status::Selected;
        rr++;

        displayFunc({comparsion, name});
    }

    for(int i=0;i<=size;++i){
        elem[l+i] = tmp[i];
        elem[l+i].status = Status::Sorted;
    }
    displayFunc({comparsion, name});

    return tmp;
}



