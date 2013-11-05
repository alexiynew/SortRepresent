#include "Sort.h"


bool SelectionSort::sort(std::vector<Item>& elem) {

    int size = elem.size();

    if(!done) {
        elem[curi].status = Status::None;
        elem[mi].status = Status::None;
        if(compare(elem[curi], elem[mi]) > 0) {
            mi = curi;
        }
        ++curi;

        if(curi > size - scount - 1) {
            int tmp = elem[size - scount - 1].value;
            elem[size - scount - 1].value = elem[mi].value;
            elem[mi].value = tmp;
            ++scount;
            mi = 0;
            curi = 0;
        }
        if(scount == size)
            done = true;

        elem[mi].status = Status::Key;
        elem[curi].status = Status::Search;

        for(int i = size - scount; i < size; ++i)
            elem[i].status = Status::Sorted;

    }

    return done;
}

bool MergeSort::sort(std::vector<Item>& elem) {
    if(!done) {
        if(stack.empty()) {
            stack.push_back({0, static_cast<int>(elem.size()-1)});
        } else {
            int l = stack.back().left;
            int r = stack.back().right;

            if(l == r) {
                stack.pop_back();
                if(stack.empty()) {
                    return done = true;
                }

                if(stack.back().p_left.empty()) {
                    stack.back().p_left.push_back(elem[l]);
                } else if(stack.back().p_right.empty()) {
                    stack.back().p_right.push_back(elem[l]);
                }
                return false;
            }
            int size = r-l + 1;
            int rr = l+size/2 ;

            if(stack.back().p_left.empty()) {
                stack.push_back({l, rr-1});
            } else if(stack.back().p_right.empty()) {
                stack.push_back({rr, r});
            } else {
                int rs = stack.back().p_right.size();
                int ls = stack.back().p_left.size();

                if(tmp.empty() || static_cast<int>(tmp.size()) < ls + rs) {
                    if(li < ls) {
                        if(compare(stack.back().p_left[li], stack.back().p_right[ri]) < 0 || ri == rs) {
                            elem[l+li].status = Status::Key;
                            tmp.push_back(stack.back().p_left[li++]);
                        } else {
                            if(ri < rs) {
                                elem[rr+ri].status = Status::Selected;
                                tmp.push_back(stack.back().p_right[ri++]);
                            }
                        }
                    } else if(ri < rs) {
                        elem[rr+ri].status = Status::Selected;
                        tmp.push_back(stack.back().p_right[ri++]);
                    }


                } else {

                    for(size_t i = 0; i < tmp.size(); ++i) {
                        elem[l+i] = tmp[i];
                        elem[l+i].status = Status::Sorted;
                    }
                    stack.pop_back();
                    if(stack.empty()) {
                        return done = true;
                    }
                    if(stack.back().p_left.empty()) {
                        stack.back().p_left = tmp;
                    } else if(stack.back().p_right.empty()) {
                        stack.back().p_right = tmp;
                    }
                    li = 0;
                    ri = 0;
                    tmp.clear();
                }
            }

        }
    }

    return done;
}

bool BubbleSort::sort(std::vector<Item>& elem) {
    if(!done) {
        int size = elem.size()-1;
        if(j < size) {
            if(i < size - j) {

                if(compare(elem[i], elem[i + 1]) > 0) {
                    int tmp = elem[i].value;
                    elem[i].value = elem[i + 1].value;
                    elem[i + 1].value = tmp;
                    elem[i + 2].status = Status::Search;
                }

                ++i;
                elem[i].status = Status::Key;
                elem[i - 1].status = Status::None;

                elem[size - j + 1].status = Status::Sorted;
            } else {
                elem[size - j].status = Status::Sorted;
                i = 0;
                ++j;
            }
        } else {
            done = true;
        }
    }
    return done;
}

bool QuickSort::sort(std::vector<Item>& elem) {
    if(!done) {
        if(stack.empty()) {
            stack.push_back({0, static_cast<int>(elem.size() - 1)});
        } else {
            if(base == -1) {
                base = stack.back().rr;
                l = stack.back().ll;
                if(elem[base].status == Status::Sorted) {
                    base--;
                }
                if(base <= l) {
                    elem[base].status = Status::Sorted;
                    stack.pop_back();
                    if(stack.empty()) {
                        done = true;
                    }
                    base = -1;
                    return false;
                }

                r = base-1;
                elem[base].status = Status::Key;
                elem[r].status = Status::Selected;
                elem[l].status = Status::Selected;
            } else {
                if(l < r) {

                    if(compare(elem[l], elem[base]) <= 0) {
                        elem[l].status = Status::None;
                        l++;
                        elem[l].status = Status::Selected;
                    } else if(compare(elem[r], elem[base]) >= 0) {
                        elem[r].status = Status::None;
                        r--;
                        elem[r].status = Status::Selected;
                    } else {
                        int tmp = elem[l].value;
                        elem[l].value = elem[r].value;
                        elem[r].value = tmp;
                        elem[r].status = Status::None;
                        elem[l].status = Status::None;
                        l++;
                        r--;
                        elem[r].status = Status::Selected;
                        elem[l].status = Status::Selected;
                    }
                } else {
                    if(compare(elem[r], elem[base]) < 0) {
                        r++;
                    }
                    int tmp = elem[base].value;
                    elem[base].value = elem[r].value;
                    elem[r].value = tmp;
                    elem[r].status = Status::Sorted;
                    elem[base].status = Status::None;
                    Recurs_level left {stack.back().ll, l};
                    Recurs_level right {r + 1, stack.back().rr};
                    stack.pop_back();
                    stack.push_back(right);
                    stack.push_back(left);
                    base = -1;
                }
            }
        }
    }
    return done;
}

bool HeapSort::sort(std::vector<Item>& elem) {
    if(!done) {
        if(size == -1) {
            size = elem.size();
        }
        if(index == -1) {
            index = size /2 - 1;
        }
        if(!is_heap) {
            heapify(elem);
        } else{
            swap(elem[0], elem[--size]);
            elem[size].status = Status::Sorted;
            if(size <= 1){
                done = true;
                elem[0].status = Status::Sorted;
            } else {
                is_heap = false;
            }
        }
    }

    return done;
}

void HeapSort::heapify(std::vector<Item>& elem) {
    for(auto& x : elem){
        if(x.status != Status::Sorted){
            x.status = Status::None;
        }
    }

    int i = index;
    if(!stack.empty()){
        i = stack.back();
        stack.pop_back();
    }
    elem[i].status = Status::Key;

    int l = i * 2 + 1;
    int r = l + 1;

    if(l < size) {
        elem[l].status = Status::Selected;
        int to_swap = (r < size) ? ((compare(elem[l], elem[r]) >= 0) ? l : r) : l;
        elem[to_swap].status = Status::Selected;
        if(compare(elem[to_swap], elem[i]) > 0) {
            swap(elem[to_swap], elem[i]);
            stack.push_back(to_swap);
            elem[to_swap].status = Status::Search;
            elem[i].status = Status::Search;
            return;
        }
    }

    if(index != 0){
        --index;
    } else {
        is_heap = true;
    }
}

bool ShakerSort::sort(std::vector<Item>& elem){
    if(!done){
        if(left == -1){
            left = 1;
            right = elem.size() - 1;
            index = right;
        }

        if(move_left){
            if(compare(elem[index - 1], elem[index]) > 0){
                swap(elem[index], elem[index-1]);
                s = 0;
            }
            s++;
            elem[index].status = Status::None;
            index--;
            elem[index].status = Status::Key;
            if(index < left){
                left += s;
                index = left;
                move_left = false;
                s = 0;
                for(int i=0; i<left; ++i){
                    elem[i].status = Status::Sorted;
                }
            }
        } else {
            if(compare(elem[index - 1], elem[index]) > 0){
                swap(elem[index - 1], elem[index]);
                s = 0;
            }
            s++;
            elem[index -1].status = Status::None;
            index++;
            elem[index -1].status = Status::Key;
            if(index > right){
                right -= s;
                index = right;
                move_left = true;
                s = 0;
                for(int i=right; i<static_cast<int>(elem.size()); ++i){
                    elem[i].status = Status::Sorted;
                }
            }
        }
        if(left > right){
            done = true;
            elem[left-1].status = Status::Sorted;
        }
    }
    return done;
}

bool CombSort::sort(std::vector<Item>& elem){
    if(!done){
        if(jump == 0){
            jump = elem.size();
            index = 0;
        } else {
            if(jump >= 1 || swaped){
                elem[index+jump -1].status = Status::None;
                elem[index ? index-1 : 0].status = Status::None;
                if(index+jump<elem.size()){
                    elem[index+jump].status = Status::Search;
                    elem[index].status = Status::Key;
                    if(compare(elem[index], elem[index+jump]) > 0){
                        swap(elem[index], elem[index+jump]);
                        swaped = true;
                    }
                    ++index;
                    if(jump == 1){
                        elem[index > 1 ? index-2 : 0].status = Status::Sorted;
                    }
                } else {
                    if(jump > 1){
                        jump /= 1.24733;
                    } else {
                        elem[elem.size() - 1].status = Status::Sorted;
                        elem[elem.size() - 2].status = Status::Sorted;
                        done = true;
                    }
                    swaped = false;
                    index = 0;
                }
            }
        }
    }
    return done;
}

bool InsertionSort::sort(std::vector<Item>& elem){
    if(!done){
        if(i <= elem.size()){
            elem[i].status = Status::Key;
            if(j > 0 && compare(elem[j-1], elem[j]) > 0){
                swap(elem[j], elem[j-1]);
                if(i != elem.size()){
                    elem[j].status = Status::None;
                } else {
                    for(int ii = j; ii >= 0; --ii)
                        elem[ii].status = Status::Sorted;
                }
                --j;
                elem[j].status = Status::Search;
            } else {
                if(i != elem.size()){
                    elem[j].status = Status::None;
                } else {
                    elem[j].status = Status::Sorted;
                }
                j = i;
                elem[i].status = Status::None;
                ++i;
                elem[i].status = Status::Key;
            }
        } else {
            done = true;
        }
    }
    return done;
}

bool ShellSort::sort(std::vector<Item>& elem){
    if(!done){
        for(size_t ii = 0; ii < elem.size(); ++ii){
            elem[ii].status = Status::None;
        }
        if(d == -1){
            d = elem.size() / 2;
        } else {
            if(d != 0){
                for(int ii = d; d > 1 && ii < static_cast<int>(elem.size()); ii += d){
                    elem[ii].status = Status::Selected;
                }
                if(i < static_cast<int>(elem.size())){
                    if(j >= d && compare(elem[j-1], elem[j]) > 0){
                        swap(elem[j], elem[j-1]);
                        j -= d;
                        elem[j].status = Status::Search;
                    } else {
                        j = i;
                        ++i;
                        elem[i].status = Status::Key;
                    }
                } else {
                    i = d - 1;
                    d /= 2;
                }
            } else {
                for(size_t ii = 0; ii < elem.size(); ++ii){
                    elem[ii].status = Status::Sorted;
                }
                done = true;
            }
        }
    }
    return done;
}

bool RadxSort::sort(std::vector<Item>& elem){
    if(!done){
        if(d >= 0){
            if(i < elem.size()){
                int index = (elem[i].value >> ((sizeof(Item::value) * 8 - 1)-d)) & 1;
                bag[index].push_back(elem[i]);
                if(index){
                    elem[i].status = Status::Key;
                } else {
                    elem[i].status = Status::Search;
                }
                ++i;
            } else{
                if(l < bag[0].size()){
                    elem[l] = bag[0][l];

                    if(bag[1].empty()){
                        elem[l].status = Status::Sorted;
                    }
                    ++l;
                } else if (r < bag[1].size()){
                    elem[l+r] = bag[1][r];
                    ++r;
                } else {
                    if(bag[1].empty()){
                        done = true;
                    }
                    bag[0].clear();
                    bag[1].clear();
                    --d;
                    i = 0; l = 0; r = 0;
                }
            }
        } else {
            done = true;
        }
    }
    return done;
}


