#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int n, m, k, a[14][14],b[14][14],c[14][14], d, EY, EX,y,x,py[14],px[14], ret;
struct A {
    int dist, y, x;
};
vector<A> people;

bool cmp (A c , A b){
    if(c.dist==b.dist){
            if(c.y==b.y){
                return c.x < b.x;
            }
            return c.y < b.y;
    }
    return c.dist < b.dist;
    
}
void print() {
    cout << "\n";
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            if(i==EY && j==EX){
                cout << "E ";
            }else {

            cout << a[i][j] << " ";
            }
        }
        cout << "\n";
    }
}
void input() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> k;
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < m;i++){
        cin >> py[i] >> px[i];
        py[i]--, px[i]--;
    }
    cin >> EY >> EX;
    EY--, EX--;
    a[EY][EX] = 0;
    for (int i = 0; i < m;i++){
        int dist = abs(py[i]-EY) + abs(px[i]-EX);
        // pq.push({dist, py[i], px[i]});
        people.push_back({dist, py[i], px[i]});
    }

}
bool canGo(int ny,int nx,int i){
    if(a[ny][nx] || ny<0||nx<0||ny>=n||nx>=n)
        return false;
    // cout << people[i].y <<" , " << people[i].x  << " 움직임\n" ;
   
    ret++;
    return true;
}
void move (){
    for (int i = 0; i < people.size();i++)
    {
        int y = people[i].y;
        int x = people[i].x;
        int dist = abs(EX -x) + abs(EY - y);
        people[i].dist = dist;
        int ny = y, nx = x;

        if(people[i].y < EY){
            ny = y + 1;
            if(canGo(ny,nx,i)){
                people[i] = {dist - 1, ny, nx};
            }
        } else if(people[i].y > EY){
            ny = y - 1;
            if(canGo(ny,nx,i)){
                people[i] = {dist - 1, ny, nx};
            }
        }else if(people[i].x < EX){
            nx = x + 1;
            if(canGo(ny,nx,i)){
                people[i] = {dist - 1, ny, nx};
            }
        }else if(people[i].x > EX){
            nx = x - 1;
            if(canGo(ny,nx,i)){
                people[i] = {dist - 1, ny, nx};
            }
        }

        // 탈출
        if(people[i].dist <= 0){
            people.erase(people.begin() + i);
            i--;
        }
    }
}
void rotSet90(int mnY, int mnX, int mxY, int mxX) {
    int n = mxY - mnY + 1; // 세로 방향으로의 길이
    // 가로 방향으로의 길이는 자동으로 처리됨 (n을 사용하여 정사각형 영역으로 가정)
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            int temp = a[mnY + i][mnX + j]; // 상단 왼쪽 값을 임시 저장

            // 시계 방향으로 90도 회전
            a[mnY + i][mnX + j] = max(a[mxY - j][mnX + i] -1 , 0); // 하단 왼쪽 -> 상단 왼쪽
            a[mxY - j][mnX + i] = max(a[mxY - i][mxX - j]-1, 0); // 하단 오른쪽 -> 하단 왼쪽
            a[mxY - i][mxX - j] = max(a[mnY + j][mxX - i]-1, 0); // 상단 오른쪽 -> 하단 오른쪽
            a[mnY + j][mxX - i] = max(temp-1 , 0); // 임시 저장한 값 -> 상단 오른쪽
        }
    }

    a[mnY + n / 2][mnX + n / 2] = max(a[mnY + n / 2][mnX + n / 2]-1,0);
}

void rotate90(){
    sort(people.begin(), people.end(), cmp);
    // cout << "가까운 사람 : " << people[0].y << " , " << people[0].x << "\n";
    // cout <<"출구        : " << EY << " , " << EX << "\n";
    int mnY = min(people[0].y, EY);
    int mnX = min(people[0].x, EX);
    int mxY = max(people[0].y, EY);
    int mxX = max(people[0].x, EX);

    int diffY = mxY - mnY;
    int diffX = mxX - mnX;
    // cout <<"diff : " << diffY <<" , " <<  diffX << "\n";

    if(diffY < diffX){
        // y 좌표의 크기를 늘려야 함!! 
        while(diffY != diffX){
            mnY--;
            diffY++;
        }
    } else if (diffX < diffY){
        // x 좌표의 크기를 늘려야 함!!
         while(diffY != diffX){
            mnX--;
            diffX++;
        }
    }
    while(mnY<0){
        mnY++;
        mxY++;
    }
    while(mnX < 0){
        mnX++;
        mxX++;
    }
    // cout << mnY << " , " << mnX << "\n";
    // cout << mxY << " , " << mxX << "\n";
    // print();
    rotSet90(mnY, mnX, mxY, mxX);

    //     cout << mnY << " , " << mnY + siz << "\n";
    //     cout << mn << " , " << mn + siz << "\n";
    //     // cout << nx << ", " << mx << "\n";

        // // 맵
        // // mn ~ mx 정사각형 만큼 a를 시계방향으로 회전해줘

        // // 배열 b에 배열 a를 시계방향으로 회전하여 저장
        // //b[j][mx - i + mn] = a[i][j];!!!!
        // for (int i = mnY; i <= mxY; i++){
        //     for (int j = mnX; j <= mxX; j++){
        //         b[x-mnX + mnY][mnY-y+mnX] = max(a[i][j]-1,0);
        //     }
        // }

        // // 배열 b를 배열 a에 복사
        // for (int i = mnY; i <= mxY; i++){
        //     for (int j = mnX; j <= mxX; j++){
        //         a[i][j] = b[i][j];
        //     }
        // }

      // 사람 위치 업데이트
    for (int i = 0; i < people.size(); i++) {
        int y = people[i].y;
        int x = people[i].x;
        if (mxY >= y && y >= mnY && mxX >= x && x >= mnX) {
           
            people[i].y = mnY + (x - mnX); // 수정된 부분
            people[i].x = mxX - (y - mnY); // 수정된 부분

            if (people[i].y < mnY || people[i].y > mxY || people[i].x< mnX || people[i].x > mxX) {
            // 탈출구의 새 위치가 사각형 영역을 벗어나는 경우, 기존 위치로 되돌림
                people[i].y = y;
                people[i].x = mnY + (mxX - y);
            }
        }
    }

    // 탈출구 위치 업데이트
    // cout <<"탈출구 : " << EY << " , " << EX <<"\n";
    if (mxY >= EY && EY >= mnY && mxX >= EX && EX >= mnX) {
       int tempY = EY; // 임시 변수를 사용해 EY 값을 보존
        EY = mnY + (EX - mnX); // 수정된 부분
        EX = mxX - (tempY - mnY); // 수정된 부분

        // 탈출구의 새 위치가 사각형 영역을 벗어나는지 확인하고 필요한 경우 조정
        if (EY < mnY || EY > mxY || EX < mnX || EX > mxX) {
            // 탈출구의 새 위치가 사각형 영역을 벗어나는 경우, 기존 위치로 되돌림
            EY = tempY;
            EX = mnY + (mxX - tempY);
        }

    }
}


int main(){

    input(); 
    // print(); 
    while(k-- && !people.empty()){
        move();
        // print();
        rotate90();

        // print(); 

        // cout << ret << "\n"
        //  << EY+1 << " " << EX+1 << "\n";
        // cout << "--------------------\n\n";
    }

    cout << ret << "\n"
         << EY+1 << " " << EX+1 << "\n";

    return 0;
}