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
vector<A> commend, v;

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
        a.name = "", a.cnt = -1, a.x = -1;

        if(a.cmd==100){
            cin >> a.x >> a.name;
        }
        if(a.cmd==200){
            cin >> a.x >> a.name >> a.cnt;
            visit[a.name] = a.t;
            position[a.name] = a.x;
            eat[a.name] = a.cnt;
        }
        commend.push_back(a);
    }
}

void calSushi () {
     for (int i = 0; i < commend.size();i++){
        if(commend[i].cmd != 100) continue;

        A temp = commend[i];
        temp.cmd = commend[i].cmd+1;
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
    for (int i = 0; i < commend.size();i++){
        if(commend[i].cmd==100){
            retS++;
        }
        else if (commend[i].cmd==101){
            retS--;
            eat[commend[i].name]= eat[commend[i].name] - 1;
            if(eat[commend[i].name] <= 0){
                retP--;
            }
        }
        else if (commend[i].cmd==200){
            retP++;
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

    commend.insert(commend.end(), v.begin(), v.end());
    sort(commend.begin(), commend.end(), cmp);

    go();

    return 0;
}