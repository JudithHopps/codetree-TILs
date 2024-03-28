#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
const int dy[] = { 0, 1, 0, -1, -1, -1, 1, 1 };
const int dx[] = { 1, 0, -1, 0, -1, 1, -1, 1 };

int n, m, K, cur = 0, sub = 0, potab = 0, map[14][14], a[14][14], b[14][14], visited[14][14];
bool flag = false;
struct A
{
	int attack, last, y, x;
};
vector<A> v;

void print(int arr[14][14]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
}
bool cmp(A a, A b)
{
	if (a.attack == b.attack)
	{
		if (a.last == b.last)
		{
			if (a.x + a.y == b.y + b.x)
			{
				return a.x > b.x;
			}
			else
				return a.x + a.y > b.y + b.x;
		}
		return a.last > b.last;
	}
	return a.attack < b.attack;
}
void plusAttack()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map[i][j]==0 || b[i][j])
				continue;
			int target = a[i][j] - 1;
			map[i][j] += 1;
		}
	}
}

bool isOnly()
{
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!map[i][j]) cnt++;
		}
	}
	return cnt == 1;
}
int transNYNX(int l)
{
	if (l < 0)
		return n - 1;
	if (l == n)
		return 0;
	return l; 
}
void goLazer(int y, int x) {
	if (y == v[cur].y && x == v[cur].x) {
		flag = true;
		return;
	}
	if (flag) return;

	for (int i = 3; i >= 0; i--) {
		int ny = transNYNX(y + dy[i]);
		int nx = transNYNX(x + dx[i]);
		if (a[ny][nx] == 0)continue;
		if (visited[ny][nx] != visited[y][x] - 1) continue;
		if (b[ny][nx]) continue;
		b[ny][nx] -= v[cur].attack / 2;
		goLazer(ny, nx);
		if (flag) return;
		else {
			b[ny][nx] = 0;
		}
	}
}
bool canGo()
{
	queue<pair<int, int>> q;
	memset(visited, 0, sizeof(visited));
	int y = v[cur].y;
	int x = v[cur].x;

	visited[y][x] = 1;
	flag = false;
	q.push({ y,x });



	while (q.size()) {
		y = q.front().first;
		x = q.front().second;
		q.pop();
		if (y == v[sub].y && x == v[sub].x) {
			flag = true;
			return flag;
		}
		for (int i = 0; i < 4; i++) {
			int ny = transNYNX(y + dy[i]);
			int nx = transNYNX(x + dx[i]);
			if (a[ny][nx] == 0)continue;
			if (visited[ny][nx]) continue;
			visited[ny][nx] = visited[y][x] + 1;
			q.push({ ny,nx });

		}
	}

	return flag;
}
void goPotan()
{
	int att = v[cur].attack;
	int y = v[sub].y;
	int x = v[sub].x;
	//v[sub].attack = max(0, v[sub].attack - att);

	for (int i = 0; i < 8; i++)
	{
		int ny = transNYNX(y + dy[i]);
		int nx = transNYNX(x + dx[i]);

		if (a[ny][nx] == 0)
			continue;
		//v[a[ny][nx]].attack = max(0, v[a[ny][nx]].attack - att / 2);
		b[ny][nx] -= att / 2;
	}
}
void getSub() {
	for (int i = v.size() - 1; i > 0; i--) {
		if (v[i].attack == 0) continue;
		sub = i;
		return;
	}
}
void resetAttack() {
	// 공격 반영
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] == 0 || b[i][j] == 0) continue;
			int target = a[i][j] - 1;
			int attack = map[i][j];
			int new_attack = max(0, attack + b[i][j]);
			map[i][j] = new_attack;
			v[target].attack = new_attack;
		}

	}
}
void resetMap() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] == 0) continue;
			int target = a[i][j] - 1;
			map[i][j] = v[target].attack;
		}
	}
}
void getCur() {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].attack == 0) continue;
		cur = i;
		return;
	}
}

void reVector() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!a[i][j]) continue;
			int target = a[i][j] - 1;
			v[target].attack = map[i][j];
			if (map[i][j] == 0) {
				a[i][j] = 0;
			}
		}
	}
}
void resetA() {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].attack == 0) continue;
		a[v[i].y][v[i].x] = i + 1;
	}
}
int main()
{	
	//freopen("data.txt", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> n >> m >> K;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
			if (map[i][j])
			{
				potab++;
				A temp;
				temp.attack = map[i][j];
				temp.y = i;
				temp.x = j;
				a[i][j] = potab;
				v.push_back(temp);
			}
		}
	}
	/*cout << "a" << "\n\n";
	print(a);
	cout << "\n";*/
	for (int k = 1; k <= K; k++)
	{
		// 1개 남았어?

		/*cout << "map" << "\n\n";
		print(map);*/
		// 공격자 선정

		sort(v.begin(), v.end(), cmp);
		resetA();

		
		getCur();


		v[cur].attack += n + m;
		v[cur].last = k;
		map[v[cur].y][v[cur].x] = v[cur].attack;

		//cout << "공격자 선정 : " <<cur <<"\t" << v[cur].y << " , " << v[cur].x << "\n";

	   // 피해자 선정
		getSub();
		//cout << "피해자 선정 : " << v[sub].y << " , " << v[sub].x << "\n";
		// 공격자 공격
		memset(b, 0, sizeof(b));

		b[v[sub].y][v[sub].x] = -v[cur].attack;
		if (canGo()) {
			/*cout << "CAN GO\n";
			cout << "visited" << "\n";*/
			//print(visited);
			flag = false;
			goLazer(v[sub].y, v[sub].x);
			b[v[cur].y][v[cur].x] = 0;
			/*cout << "b" << "\n\n";
			print(b);*/
		}
		else {
			//cout << "Can't GO\n";
			goPotan();
			b[v[cur].y][v[cur].x] = 0;
			/*cout << "b" << "\n\n";
			print(b);*/
		}
		resetAttack();

		//cout << "a" << "\n\n";
		//print(a);

		if (isOnly())
			break;

		// 무관애들 공격력 상승!
		b[v[cur].y][v[cur].x] = 1;

		plusAttack();
		
		reVector();

		
		/*cout << "map" << "\n";
		print(map);
		for (A a : v) {
			cout << "일치? " << (a.attack == map[a.y][a.x]) << " : " << a.attack << "\t" << map[a.y][a.x] << "\n";
		}*/
	}
	sort(v.begin(), v.end(), cmp);
	getSub();
	cout << v[sub].attack << "\n";
	
	return 0;
}