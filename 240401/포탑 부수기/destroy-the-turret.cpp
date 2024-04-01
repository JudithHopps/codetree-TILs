#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
bool visited[14][14], isAttacked[14][14];
int a[14][14],last[14][14],backY[14][14],backX[14][14],n, m, K, att;
int sy, sx, ey, ex;
const int dy[] = { 0,1,0,-1 ,-1,-1,1,1};
const int dx[] = { 1,0,-1,0, -1,1,-1,1 };

struct A {
	int att, last, y, x;
};

vector<A> v;
bool cmp(A a, A b) {
	if (a.att != b.att) return a.att < b.att;
	if (a.last != b.last) return a.last > b.last;
	if (a.y + a.x != b.y + b.x) return a.y + a.x > b.y + b.x;
	return a.x > b.x;
}
void resetArr(bool arr[14][14], bool flag) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = flag;
		}
	}
}
void init() {
	// 현재 살아있는 포탑 v에 저장
	v.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] == 0) continue;
			A temp;
			temp.att = a[i][j];
			temp.y = i;
			temp.x = j;
			temp.last = last[i][j];
			v.push_back(temp);
		}
	}
	// 공격여부 확인 배열, visited 배열 초기화 
	resetArr(visited, false);
	resetArr(isAttacked, false);
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = false;
			isAttacked[i][j] = false;
		}
	}*/
	//// backY,backX 초기화 
	memset(backY, 0, sizeof(backY));
	memset(backX, 0, sizeof(backX));
}
void plusAtt(int k) {
	sort(v.begin(), v.end(), cmp);

	A week = v[0];

	a[week.y][week.x] += (n + m);
	week.att = a[week.y][week.x];
	att = week.att;
	last[week.y][week.x] = k;
	week.last = k;
	v[0] = week;

}
bool canLazer() {
	sy = v[0].y;
	sx = v[0].x;
	ey = v[v.size() - 1].y;
	ex = v[v.size() - 1].x;

	queue<pair<int, int>> q;
	q.push({ sy,sx });
	visited[sy][sx] = true;

	while (q.size()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		if (y == ey && x == ex) {
			break;
		}
		for (int i = 0; i < 4; i++) {
			int ny = (y + dy[i] +n) % n;
			int nx = (x + dx[i] +m) % m;
			if (a[ny][nx] == 0 || visited[ny][nx]) continue;
			visited[ny][nx] = true;
			backY[ny][nx] = y;
			backX[ny][nx] = x;
			q.push({ ny,nx });
		}
	}
	
	return visited[ey][ex];
}
void goLazer() {
	isAttacked[sy][sx] = true;
	isAttacked[ey][ex] = true;
	a[ey][ex] = max(a[ey][ex] - att, 0);
	int y = backY[ey][ex], x = backX[ey][ex];
	while (!(y == sy && x == sx)) {
		isAttacked[y][x] = true;
		a[y][x] = max(a[y][x] - att / 2, 0);
		y = backY[y][x];
		x = backX[y][x];
	}
}
void goPotan() {
	isAttacked[sy][sx] = true;
	isAttacked[ey][ex] = true;
	a[ey][ex] = max(a[ey][ex] - att, 0);
	int y = ey, x = ex;

	for (int i = 0; i < 8; i++) {
		int ny = (y + dy[i] + n) % n;
		int nx = (x + dx[i] + m) % m;
		if (a[ny][nx] == 0 || visited[ny][nx]) continue;
		a[ny][nx] = max(a[ny][nx] - att / 2, 0);
		isAttacked[ny][nx] = true;
	}
}
void getStrong() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] == 0 || isAttacked[i][j]) continue;
			a[i][j]++;
		}
	}
}
int getMax() {
	int mx = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			mx = max(mx, a[i][j]);
		}
	}
	return mx;
}
void print(int arr[14][14]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
}
int main()
{
	//freopen("data.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m >> K;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	//print(a);
	for (int k = 1; k <= K; k++) {
		// 현재 살아있는 포탑 v에 저장
		// 공격여부 확인 배열, visited 배열 초기화 
		// backY,backX 초기화 
		init();
		
		// 1개만 살아있으면 stop
		if (v.size() <= 1) break;

		// 공격자에게 +(N+M)점수 부여  + 최근 공격 갱신
		plusAtt(k);
		
		// lazer공격 가능
		if (canLazer()) {
			//cout << "Can\n";
			goLazer();
		}
		// potan 공격
		else {
			//cout << "Can't\n";
			goPotan();
		}

		// 공격 무관한 포탑 공격력 +1
		getStrong();

		//print(a);
	}

	cout << getMax() << "\n";
	return 0;
}