#ifndef DEQUE_HELPER_H
#define DEQUE_HELPER_H

#include <deque>

void dequeNext(std::deque<int>& q) {
    int front = q.front();
    q.pop_front();
    q.push_back(front);
}

void dequePrev(std::deque<int>& q) {
    int back = q.back();
    q.pop_back();
    q.push_front(back);
}

#endif  // DEQUE_HELPER_H