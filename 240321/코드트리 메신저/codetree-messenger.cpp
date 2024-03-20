#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;
int n, q, cmd, c1, c2, parent[100004],onOff[100004], power[100004],visited[100004];
// vector<int> s[100004];
unordered_set<int> s[100004];

int bfs(int here){
    queue<int> q;
    visited[here] = 1;
    int cnt = 0;
    q.push(here);

    while(q.size()){
        int now = q.front();
        q.pop();
        for(int next : s[now]){
            if(onOff[next]==0) continue;
            if(visited[next]) continue;
            int dist = visited[now] + 1;
            if(power[next] >= visited[now]) {
                cnt++;
            }
            visited[next] = dist;
            q.push(next);
        }
    }

    return cnt;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    memset(onOff, 1, sizeof(onOff));
    cin >> n >> q;

    while(q--){
        cin >> cmd;

        //사내 메신저 준비
        if(cmd == 100){
            for (int i = 1; i <= n;i++){
                cin >> parent[i];
                s[parent[i]].insert(i);
            }
            for (int i = 1; i <= n;i++){
                cin >> power[i];
            }
        }
        //ON 상태라면 OFF
        else if (cmd== 200){
            cin >> c1;
            onOff[c1] = !onOff[c1];
        }

        //권한 세기 변경
        else if (cmd==300){
            cin >> c1 >> c2;
            power[c1] = c2;
        }

        // 부모 변경
        else if (cmd==400){
            cin >> c1 >> c2;

            int p1 = parent[c1];
            int p2 = parent[c2];

            // 부모 정보 변화
            parent[c1] = p2;
            parent[c2] = p1;

            // 부모에 현재 자식 제거
            s[p1].erase(find(s[p1].begin(), s[p1].end(), c1));
            s[p2].erase(find(s[p2].begin(), s[p2].end(), c2));
            

            // 부모에 바뀐 자식 push
            s[p1].insert(c2);
            s[p2].insert(c1);
        }

        // 채팅방 수 조회
        else if(cmd ==500){
            cin >> c1;
            memset(visited, 0, sizeof(visited));
            cout << bfs(c1) <<"\n";
        }
    }
    return 0;
}