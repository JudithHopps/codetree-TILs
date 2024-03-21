#include <iostream>
#include <vector>

using namespace std;

const int MN = 100004;
const int MD = 22;

int n, q,cmd,c1,c2,pw;
int power[MN], parent[MN], ret[MN];
bool isOn[MN];
int cnt[MN][MD];

void init() {
	for (int i = 1; i <= n; i++) {
		cin >> parent[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> power[i];
		if (power[i] > 20) power[i] = 20;
	}

	for (int i = 1; i <= n; i++) {
		int cur = i;
		int pw = power[i];
		cnt[cur][pw]++;
		while (parent[cur] && pw) {
			cur = parent[cur];
			pw--;
			if (pw) cnt[cur][pw]++;
			ret[cur] ++;
		}
	}
}

void toggle_isOn(int c1) {
	if (isOn[c1]) {
		int cur = parent[c1];
		int num = 1;

		while (cur) {
			for (int i = num; i <= 21; i++) {
				ret[cur] += cnt[c1][i];
				if (i > num) cnt[cur][i - num] += cnt[c1][i];
			}
			if (isOn[cur]) break;
			cur = parent[cur];
			num++;
		}
		isOn[c1] = false;
	}
	else {
		int cur = parent[c1];
		int num = 1;
		while (cur) {
			for (int i = num; i <= 21; i++) {
				ret[cur] -= cnt[c1][i];
				if (i > num) cnt[cur][i - num] -= cnt[c1][i];
			}
			if (isOn[cur]) break;
			cur = parent[cur];
			num++;
		}
		isOn[c1] = true;
	}
}

void change_power(int c1, int pw) {
	int pre = power[c1];
	pw = (pw>20 ? 20 : pw);
	power[c1] = pw;

	cnt[c1][pre]--;
	if (!isOn[c1]) {
		int cur = parent[c1];
		int num = 1;
		while (cur) {
			if (pre >= num) ret[cur]--;
			if (pre > num) cnt[cur][pre - num]--;
			if (isOn[cur]) break;
			cur = parent[cur];
			num++;
		}
	}

	cnt[c1][pw]++;
	if (!isOn[c1]) {
		int cur = parent[c1];
		int num = 1;
		while (cur) {

			if (pw >= num) ret[cur]++;
			if (pw > num) cnt[cur][pw - num]++;
			if (isOn[cur]) break;
			cur = parent[cur];
			num++;
		
		}
	}
}

void change_parent(int c1, int c2) {
	bool bef1 = isOn[c1];
	bool bef2 = isOn[c2];
	// ctrl + d
	if (!bef1) toggle_isOn(c1);
	if (!bef2) toggle_isOn(c2);

	swap(parent[c1], parent[c2]);

	if (!bef1) toggle_isOn(c1);
	if (!bef2) toggle_isOn(c2);

}
int main() {

	cin >> n >> q;
	while (q--) {
		cin >> cmd;
		if (cmd == 100) {
			init();
		}
		else if (cmd == 200) {
			cin >> c1;
			toggle_isOn(c1);
		}
		else if (cmd == 300) {
			cin >> c1 >> pw;
			change_power(c1, pw);
		}
		else if (cmd == 400) {
			cin >> c1 >> c2;
			change_parent(c1, c2);
		}
		else if (cmd == 500) {
			cin >> c1;
			cout << ret[c1] << "\n";
		}
	}
	return 0;
}