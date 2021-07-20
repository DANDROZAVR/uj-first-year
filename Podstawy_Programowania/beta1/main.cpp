#ifndef CPP_PROJECTS_SOLUTION_H
#define CPP_PROJECTS_SOLUTION_H
 
#include <iostream>
#include <algorithm>
#include <string>
 
class vector {
    std::string *vec;
    int size, capacity;
public:
    ~vector() {
        delete[] vec;
    }
    vector(int a = 4, int b = 0, std::string s = "") {
        capacity = max(a, 1);
        vec = new std::string[a];
        fill(vec, vec + b, s);
        size = b;
    }
    vector(const vector &newV) {
        size = newV.size;
        capacity = newV.capacity;
        vec = new std::string[capacity];
        copy(newV.vec, newV.vec + size, vec);
    }
    int getSize() const {
        return size;
    }
    void clear() {
        size = 0;
    }
    void add(std::string s) {
        if (size == capacity) {
            resize(size + 1, false);
        }
        vec[size] = s;
        ++size;
    }
    void erase(int index) {
        if (index >= size || index < 0) return;
        for (int i = index; i + 1 < size; ++i)
            vec[i] = vec[i + 1];
        --size;
    }
    void insert(int index, std::string s) {
        if (index > size) return;
        if (size == capacity) {
            resize(size + 1, false);
        }
        for (int i = size; i > index; --i)
            vec[i] = vec[i - 1];
        vec[index] = s;
        ++size;
    }
    void resize(int newCapacity, bool increaseSize = true) {
        if (newCapacity > capacity) {
            capacity = max(capacity, 1);
            while (capacity < newCapacity) capacity <<= 1;
            auto newVec = new std::string[capacity];
            copy(vec, vec + size, newVec);
            delete[] vec;
            vec = newVec;
        }
        if (size < newCapacity && increaseSize)
            fill(vec + size, vec + newCapacity, "");
        if (increaseSize)
            size = newCapacity;
    }
    std::string& operator[](int index) const {
        if (index >= size) index = size - 1;
        return vec[index];
    }
    void operator=(const vector &newVec) {
        if (this == &newVec) return;
        delete[] vec;
        vec = new std::string[newVec.capacity];
        copy(newVec.vec, newVec.vec + newVec.size, vec);
        size = newVec.size;
        capacity = newVec.capacity;
    }
    operator bool() const {
        return size != 0;
    }
    bool operator!() const {
        return size == 0;
    }
    friend std::ostream& operator<<(std::ostream &stream, vector &v){
        for (int i = 0; i < v.size; ++i)
            stream << v[i] << " ";
        return stream;
    }
    friend std::istream& operator>>(std::istream &stream, vector &v){
        for (int i = 0; i < v.size; ++i)
            stream >> v[i];
        return stream;
    }
};
#endif //CPP_PROJECTS_SOLUTION_H