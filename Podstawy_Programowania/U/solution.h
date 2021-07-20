//#include <iostream>
 
class point{
    private:
        int x, y;
    public:
        point(){x = y = 0;}
        point(int _x, int _y){x = _x; y = _y;}
        int getX(){return x;}
        int getY(){return y;}
        void print(){std::cout<<x << " " << y << '\n';}
};
 
class queue{
    private:
        point *a;
        int size = 0, capac = 0, begin = 0;//, maxSize = 0;
    public:
        queue(){a = new point[15]; capac = 15; size = 0; begin = 0;// maxSize = 15;
         }
        queue(int _capac){
            capac = _capac;
            size = 0;
            //maxSize = capac;
            begin = 0;
            a = new point[_capac];
        }
        ~queue(){delete []a;}
        bool full(){return size == capac;}
        bool empty(){return size == 0;}
        point front(){
            if (!size) return {0, 0};
            return a[begin];
        } // подумать о &
        void enqueue(point &x){
            if (size == capac) return;
            a[(begin + size++) % capac] = x;
        }
        void clear(){size = 0;}
        point dequeue(){
            if (!size) return {0, 0};
            point elem = a[begin];
            ++begin;
            if (begin == capac) begin = 0;
            --size;
            return elem;
        }
        void resize(int _capac){
            if (_capac <= capac) return;
            //if (n <= maxSize) return;
            //if (!maxSize) maxSize = 1;
            //while(maxSize < n) maxSize ;
            //maxSize = n;
            //std::cout<<begin<<" "<<size<<" "<<capac<<'\n';
            point *b = new point[_capac];
            if (begin + size <= capac){
                std::copy(a + begin, a + begin + size, b);
            } else {
                int rig = capac - begin;
                //std::cout << begin <<" "<<size<<" "<<rig<<std::endl;
                std::copy(a + begin, a + capac, b);
                std::copy(a, a + size - rig, b + rig);
            }
            capac = _capac;
            delete[] a;
            begin = 0;
            a = b;
        }
};
 
class stack{
private:
    long long *a;
    int size, capac, maxSize;
public:
    stack(){a = new long long[15]; capac = 15; size = 0; maxSize = 15;}
    stack(int _capac){
        capac = _capac;
        size = 0;
        maxSize = capac;
        while(maxSize < size) maxSize <<= 1;
        a = new long long[maxSize];
    }
    ~stack(){delete[] a;}
    bool full(){ return size == capac;}
    bool empty(){return size == 0;}
    long long top(){
        if (!size) return 0;
        return a[size - 1];
    } // подумать о &
    void push(long long &x){
        if (size == capac) return;
        a[size++] = x;
    }
    long long pop(){
        if (!size) return 0;
        return a[--size];
    }
    void clear(){size = 0;}
    void resize(int n){
        if (n <= capac) return;
        capac = n;
        if (n <= maxSize) return;
        if (!maxSize) maxSize = 1;
        while(maxSize < n) maxSize <<= 1;
        long long *b = new long long[maxSize];
        std::copy(a, a + size, b);
        delete[] a;
        a = b;
    }
};