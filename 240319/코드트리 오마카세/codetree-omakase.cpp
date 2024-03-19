#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
unordered_map<string, int> visit;
unordered_map<string, int> position;
unordered_map<string, int> eat;

struct A {
    int cmd, t, x, cnt;
    string name;
};
vector<A> v;

int l, q, cmd, t, x, cnt,retP,retS;
string name;

bool cmp (A a , A b) {
    if(a.t == b.t){
        return a.cmd < b.cmd;
    }
    return a.t < b.t;
}

void input () {
    cin >> l >> q;
    for (int i = 0; i < q;i++){
        A a;
        cin >> a.cmd >> a.t;

        if(a.cmd==100){
            cin >> a.x >> a.name;
        }
        if(a.cmd==200){
            cin >> a.x >> a.name >> a.cnt;
            visit[a.name] = a.t;
            position[a.name] = a.x;
        }
        v.push_back(a);
    }
}

void calSushi () {
 for (int i = 0; i < q;i++){
        if(v[i].cmd != 100) continue;

        A temp = v[i];
        temp.cmd = v[i].cmd+1;
        string name = temp.name;
        int now_position = temp.x;
        int wait = 0;

        // 1. 초밥이 먼저 들어왔어! 
        if(temp.t <= visit[name]){
            int diff = visit[name] - temp.t;
            temp.t = visit[name];
            now_position = (now_position + diff) % l;
        }
        
        // 2. 사람이 초밥 기다리는 시간 
        // 초밥 < 사람 
        if(now_position <= position[name]){
            wait = position[name] - now_position;
        } 
        // 사람 > 초밥
        else {
            wait = (position[name] + l) - now_position;
        }

        temp.t += wait;

        v.push_back(temp);
    }

}
void go () {
    for (int i = 0; i < v.size();i++){
        if(v[i].cmd==100){
            retS++;
        }
        else if (v[i].cmd==101){
            retS--;
            eat[v[i].name]--;
            if(eat[v[i].name] <= 0)
                retP--;
        }
        else if (v[i].cmd==200){
            retP++;
            eat[v[i].name] = v[i].cnt;
        }
        else{
            cout << retP << " " << retS << "\n";
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    input();

    calSushi();

    sort(v.begin(), v.end(), cmp);

    go();

    return 0;
}