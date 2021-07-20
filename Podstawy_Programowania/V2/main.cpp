#include <iostream>
 
#define y1 Y1
#define pb push_back
#define ll long long
#define _ <<" "<<
using namespace std;
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
    void enqueue(point x){
        //cout << "size = " << size << " capac = " <<capac << '\n';
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
const int X[4] = {0, 0, 1, -1};
const int Y[4] = {1, -1, 0, 0};
 
int main(int argc, char* argv[]){
    #ifdef Estb_probitie
        freopen("C:\\1\\work\\Satori_pp\\input.txt", "r", stdin);
        freopen("C:\\1\\work\\Satori_pp\\output.txt", "w", stdout);
    #endif
    int z;
    cin >> z;
    while(z--){
        int n, m;
        cin >> n >> m;
        queue q(n * m + 1);
        queue q2(n * m + 1);
        int a[n][m];
        int vis[n][m], vis2[n][m];
        for (int i = 0; i < n; ++i) {
            fill(vis[i], vis[i] + m, 0);
            fill(vis2[i], vis2[i] + m, 0);
        }
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            if (a[i][j] == 3) {
                q.enqueue({i, j});
                q2.enqueue({i, j});
                vis[i][j] = 1;
                vis2[i][j] = 1;
            }
        }
        while(!q.empty()){
            int x = q.front().getX();
            int y = q.front().getY();
            //cout << "ver = " <<x _ y << '\n';
            q.dequeue();
            for (int i = 0; i < 4; ++i){
                int nx = X[i] + x;
                int ny = Y[i] + y;
                if (nx < 0 || ny < 0 || nx == n || ny == m || vis[nx][ny]) continue;
                if (a[nx][ny] == 1 || a[nx][ny] == 2) continue;
                //cout << nx _ ny << '\n';
                vis[nx][ny] = vis[x][y] + 1;
                q.enqueue({nx, ny});
            }
        }
        while(!q2.empty()){
            int x = q2.front().getX();
            int y = q2.front().getY();
            q2.dequeue();
            for (int i = 0; i < 4; ++i){
                int nx = X[i] + x;
                int ny = Y[i] + y;
                if (nx < 0 || ny < 0 || nx == n || ny == m || vis2[nx][ny]) continue;
                if (a[nx][ny] == 2) continue;
                vis2[nx][ny] = vis2[x][y] + 1;
                q2.enqueue({nx, ny});
            }
        }
        int ans = 1e9;
        int ind = -1;
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (a[i][j] > 3){
                if (a[i][j] % 2 == 1){
                    if (vis2[i][j] < ans && vis2[i][j]){
                        ans = vis2[i][j];
                        ind = a[i][j];
                    }
                } else {
                    if (vis[i][j] < ans && vis[i][j]){
                        ans = vis[i][j];
                        ind = a[i][j];
                    }
                }
            }
        if (ans == 1e9) ans = 0;
        cout << ind << " " << ans - 1<< '\n';
    }
}