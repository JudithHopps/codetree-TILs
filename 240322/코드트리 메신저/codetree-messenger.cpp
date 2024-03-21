#include <iostream>
#include <vector>

using namespace std;

const int MN = 100004;
const int MD = 22;

int n, q,cmd,c1,c2,pw;
int power[MN], parent[MN], ret[MN];
bool isOff[MN];
int cnt[MN][MD];

void init() {
	for (int i = 1; i <= n; i++) {
		cin >> parent[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> power[i];
		if (power[i] > 20) power[i] = 20;
	}

    for (int i = 1; i <= n;i++){
        
        int cur = i;
        int pw = power[i];
        cnt[cur][pw]++;

        while(cur && pw){
            cur = parent[cur];
            ret[cur]++;
            pw--;
            if(pw)
                cnt[cur][pw]++;
        }
    }
}

void toggle_isOff(int c1) {
	// 켜져있어?
    if(!isOff[c1]){
        int num = 1;
        int cur = parent[c1];

        while(cur){
            for (int i = num; i <= 20;i++){
                ret[cur] -= cnt[c1][i];
                if(i > num)
                    cnt[cur][i - num] -= cnt[c1][i];
            }
            if(isOff[cur]) break;
            cur = parent[cur];
            num++;
        }
    } else {
        int cur = parent[c1];
        int step = 1;
        while(cur){
            for (int i = step; i <= 20;i++){
                ret[cur] += cnt[c1][i];
                if(i> step){
                    cnt[cur][i - step] += cnt[c1][i];
                }
            }
            if(isOff[cur]) break;
            cur = parent[cur];
            step++;
        }
    }
    isOff[c1] = !isOff[c1];
}

void cal(int c1 , int pw, int op ){
    int cur = parent[c1];
    int step = 1;
    while(cur){
        if(pw >= step)
            ret[cur] += op;
        if(pw > step){
            cnt[cur][pw - step] += op;
        }
        if(isOff[cur]) break;
        cur = parent[cur];
        step++;
    }
}
void change_power(int c1, int pw) {
    int pre = power[c1];
    power[c1] = pw > 20 ? 20 : pw;
    cnt[c1][pre]--;
    if(!isOff[c1]){
        cal(c1, pre, -1);
    }
    cnt[c1][pw]++;

    if(!isOff[c1]){
        cal(c1, pw, 1);
    }
}

void change_parent(int c1, int c2) {
    bool bef1 = isOff[c1];
    bool bef2 = isOff[c2];

    if(!bef1)
        toggle_isOff(c1);
    if(!bef2)
        toggle_isOff(c2);

    swap(parent[c1], parent[c2]);

    if(!bef1)
        toggle_isOff(c1);
    if(!bef2)
        toggle_isOff(c2);

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
			toggle_isOff(c1);
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