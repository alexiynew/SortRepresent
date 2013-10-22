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
    displayFunc = display;
    mSort(elem, 0, elem.size() - 1);
}

std::vector<Item> MergeSort::mSort(std::vector<Item>& elem, int l, int r){

    if(r == l) return {elem[l]};

    for(int i=l;i<=r;++i)
        elem[i].status = Status::None;

    int size = r-l + 1;
    int ll = l;
    int rr = l+size/2 ;

    std::vector<Item> left = mSort(elem, l, rr - 1 );
    std::vector<Item> right = mSort(elem, rr , r);

    auto li = left.begin();
    auto ri = right.begin();

    std::vector<Item> tmp;
    while(li != left.end()){
        if(compare(*li, *ri) < 0 || ri == right.end()){
            tmp.push_back(*li++);
            elem[ll++].status = Status::Key;
        } else {
            if(ri != right.end()){
                tmp.push_back(*ri++);
                elem[rr++].status = Status::Selected;
            }
        }
        displayFunc({comparsion, name});
    }
    while(ri != right.end()){
        tmp.push_back(*ri++);
        elem[rr++].status = Status::Selected;
        displayFunc({comparsion, name});
    }

    for(size_t i=0; i<tmp.size(); ++i){
        elem[l+i] = tmp[i];
        elem[l+i].status = Status::Sorted;
    }
    displayFunc({comparsion, name});

    return tmp;
}



