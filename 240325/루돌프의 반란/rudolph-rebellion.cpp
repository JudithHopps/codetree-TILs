#include <iostream>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
const int dy[] = {-1, 0, 1, 0,-1,-1,1,1};
const int dx[] = {0, 1, 0, -1,-1,1,-1,1};
const int INF = 987654321;

struct S
{
    int y, x, score, die, sleep;
} santa[34];

int N, M, P, C, D, RY, RX, p, y, x, idx, diffY, diffX, safe, a[54][54];

void interaction(int idx, int dy, int dx)
{
    int y = santa[idx].y;
    int x = santa[idx].x;
    a[y][x] = 0;

    int ny = y + dy;
    int nx = x + dx;

    if (ny < 0 || nx < 0 || ny >= N || nx >= N)
    {
        santa[idx].die = 1;
        safe--;
        return;
    }

    int ni = a[ny][nx];
    if (ni)
    {
        interaction(ni, dy, dx);
    }
    a[ny][nx] = idx;
    santa[idx].y = ny;
    santa[idx].x = nx;
}

void crashR(int idx, int score, int dy, int dx)
{
    santa[idx].score += score;

    a[santa[idx].y][santa[idx].x] = 0;
    
    santa[idx].y += dy * score;
    santa[idx].x += dx * score;

    if (santa[idx].y < 0 || santa[idx].x < 0 || santa[idx].y >= N || santa[idx].x >= N)
    {
        santa[idx].die = 1;
        safe--;
        return;
    }
    else
    {
        santa[idx].sleep = M-2;
        int ni = a[santa[idx].y][santa[idx].x];
        if (ni)
        {
            interaction(ni, dy, dx);
        }
        a[santa[idx].y][santa[idx].x] = idx;

    }
}
// 루돌프의 움직임 처리 함수
void moveR() {
    // 가장 가까운 산타를 향해 8방향 중 하나
    int dist = INF, p = -1;
    for (int i = 1; i <= P; i++) {
        if (santa[i].die) continue;
        int now_dist = (santa[i].y - RY) * (santa[i].y - RY) + (santa[i].x - RX) * (santa[i].x - RX);
        if (dist > now_dist) {
            dist = now_dist;
            p = i;
        } else if (now_dist == dist) {
            if (santa[p].y == santa[i].y) {
                if (santa[p].x < santa[i].x) {
                    p = i;
                }
            } else if (santa[p].y < santa[i].y) {
                p = i;
            }
        }
    }
    if(p == -1) return;
    priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (int j = 0; j < 8; j++) {
        int ny = RY + dy[j];
        int nx = RX + dx[j];
        if (ny < 0 || nx < 0 || ny >= N || nx >= N ) continue;
        int now_dist = (ny - santa[p].y) * (ny - santa[p].y) + (nx - santa[p].x) * (nx - santa[p].x);

        if (dist <= now_dist) continue;
        pq.push({now_dist, j});
    }

    if(pq.empty()) return;
    int j = pq.top().second;
    RY += dy[j];
    RX += dx[j];
    if (a[RY][RX]) crashR(a[RY][RX], C, dy[j], dx[j]);
}

// 산타의 움직임 처리 함수
void moveS() {
    for (int i = 1; i <= P; i++) {
        if (santa[i].die) continue;
        if (santa[i].sleep) {
            if(santa[i].sleep == M){
                santa[i].sleep = 0;
            } else {
                // cout << M << "턴 중 " << i << "번째 자고 있어\n";
                continue;
            }
        }

        priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        int y = santa[i].y;
        int x = santa[i].x;
        int dist = (y - RY) * (y - RY) + (x - RX) * (x - RX);

        for (int j = 0; j < 4; j++) {
            int ny = y + dy[j];
            int nx = x + dx[j];
            if (ny < 0 || nx < 0 || ny >= N || nx >= N || a[ny][nx]) continue;
            int now_dist = (ny - RY) * (ny - RY) + (nx - RX) * (nx - RX);

            if (dist <= now_dist) continue;
            pq.push({now_dist, j});
        }
        if(pq.empty()) continue;

        int j = pq.top().second;
        int ny = y + dy[j]; 
        int nx = x + dx[j]; 

        a[y][x] = 0; // 이전 위치 초기화
        a[ny][nx] = i; // 새로운 위치에 산타 저장
        santa[i].y = ny;
        santa[i].x = nx;

        if (RY == ny && RX == nx) {
            crashR(i, D, dy[j] * -1, dx[j] * -1);
        }
    }
}
void getScore()
{
    for (int i = 1; i <= P; i++)
    {
        if (santa[i].die)
            continue;
        santa[i].score++;
    }
}

void print()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == RY && j == RX)
            {
                cout << "R ";
            }
            else
            {
                cout << a[i][j] << " ";
            }
        }
        cout << "\n";
    }
    cout << "\n\n";
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> P >> C >> D;
    cin >> RY >> RX;
    safe = P;
    RY--;
    RX--;

    for (int i = 1; i <= P; i++)
    {
        cin >> idx >> y >> x;
        santa[idx].y = --y;
        santa[idx].x = --x;
        santa[idx].die = 0;
        santa[idx].score = 0;
        santa[idx].sleep = 0;

        // cout << santa[idx].y << " , " <<santa[idx].x << "\n";
        a[santa[idx].y][santa[idx].x] = idx;
    }

    // print();
    while (M-- && safe)
    {
        // 루돌프 move
        moveR();

        // print(); 
        // 산타 move
        moveS();


        // 산타 점수
        if(safe) getScore();

        // print();
    }

    // 정답 출력
    for (int i = 1; i <= P; i++)
    {
        cout << santa[i].score << " ";
    }

    return 0;
}