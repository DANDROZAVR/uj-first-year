#include <iostream>
#include <complex>
 
 
#define y1 Y1
#define pb push_back
#define ll long long
#define _ <<" "<<
 
class vector {
    std::string *vec;
    int size, capacity;
public:
    ~vector() {
        delete[] vec;
    }
    vector(int a = 4, int b = 0, std::string s = "") {
        capacity = std::max(a, 1);
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
            capacity = std::max(capacity, 1);
            while (capacity < newCapacity) capacity <<= 1;
            std::string *newVec = new std::string[capacity];
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
vector ans;
void solve(vector &now, int iteratLet, int left, int right) {
    if (left > right) return;
    //std::cout << "NOW = " << iteratLet  << " " << left << " " << right << " " << now << " " << std::endl;
    if (right - left <= 3) {
        for (int j = left; j <= right; ++j){
            std::string val = now[j];
            int i = j - 1;
            while(i >= left && now[i] > val){
                now[i + 1] = now[i];
                --i;
            }
            now[i + 1] = val;
        }
    } else {
        vector sortByLet[27];
        for (int i = left; i <= right; ++i) {
            if (now[i].size() <= iteratLet) {
                sortByLet[0].add(now[i]);
            } else {
                sortByLet[now[i][iteratLet] - 'A' + 1].add(now[i]);
            }
        }
        vector res;
        int l = left, r = left - 1;
        for (int i = 0; i < 27; ++i) {
            //std::cout << i << " " << l << " " << r << '\n';
            for (int j = 0; j < sortByLet[i].getSize(); ++j)
                now[++r] = sortByLet[i][j];
            if (i != 0)
                solve(now, iteratLet + 1, l, r);
            l = r + 1;
        }
    }
}
 
int main(int argc, char* argv[]){
#ifdef Estb_probitie
    freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
    freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
#endif
    int z;
    std::cin >> z;
    while(z--){
        int n;
        std::cin >> n;
        vector v;
        for (int i = 0; i < n; ++i){
            std::string s;
            std::cin >> s;
            v.add(s);
        }
        solve(v, 0, 0, v.getSize() - 1);
        for (int i = 0; i < v.getSize(); ++i)
            std::cout << v[i] << " ";
        std::cout << '\n';
        ans.clear();
    }
}