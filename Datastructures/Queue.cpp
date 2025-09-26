    // Datastructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdexcept>
#include <array>
#include <iostream>

#if defined(DEBUG) || defined(_DEBUG) 

#define DBGEXCEPT 
#else
#define DBGEXCEPT noexcept

#endif


template<typename t, size_t sz>
class LinearQueue {
private:
    std::array<t, sz> internalBuffer{};
    size_t space = 0;
public:
   inline size_t max_capacity() {
        return sz;
    }
    size_t size() {
        return space;
    }
    // Returns success, 
    bool Enqueue(t Val) DBGEXCEPT{
#if defined(DEBUG) || defined(_DEBUG) 
        if (space >= max_capacity()) {
            throw std::out_of_range("Queue maximum capacity reached");
        }
#endif
        internalBuffer[space] = Val;
        space++;
        return space <= max_capacity();

    }
    t Dequeue() {
#if defined(DEBUG) || defined(_DEBUG) 
        if (space < 1) {
            throw std::out_of_range("Attempted to dequeue empty queue");
    }
#endif
        for (unsigned i = 1; i < max_capacity(); i++) {
            internalBuffer[i - 1] = internalBuffer[i];
        }
        space--;
    }
    class Iterator {
        LinearQueue* q;
        size_t idx;
    public:
        Iterator(LinearQueue* queue, size_t index) : q(queue), idx(index) {};
        Iterator& operator++() {
            idx++;
            return *this;
        }
        bool operator==(const Iterator& b) const {
            return idx == b.idx && q == b.q;
        }
        t& operator*() {
#if defined(DEBUG) || defined(_DEBUG) 
            if (idx > q->size()) {
                throw std::out_of_range{ "Queue iterator reference larger then current queue used size" };
            }
#endif
            return q->internalBuffer[idx];

        }
    };  
    Iterator begin() {
        return Iterator(this, 0);
    };
    Iterator end() {
        return Iterator(this, space);
    }
    

};




int main()
{
    LinearQueue<int, 10> a;
    for (unsigned int i = 0; i < 10; i++) {
        a.Enqueue(i);
    };
    a.Dequeue();
   // a.test();
    for (auto i : a) {
        std::cout << i << "\n";
    }
    
   
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
