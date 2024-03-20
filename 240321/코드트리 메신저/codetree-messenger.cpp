#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
int n, q, cmd, c1, c2, parent[100004],onOff[100004], power[100004],visited[100004];
vector<int> adj[100004],temp;

// int dfs(int here,int dist){
//     visited[here] = 1;
//     int cnt = (dist <= power[here]) ? 1 : 0;

//     for(int there : adj[here]){
//         if(visited[there]) continue;
//         if(onOff[there]==0) continue;
//         // if(dist > power[there]) continue;
//         cnt += dfs(there,dist+1);
//     }
//     return cnt;
// }
int bfs(int here){
    queue<int> q;
    visited[here] = 1;
    int cnt = 0;
    q.push(here);

    while(q.size()){
        int now = q.front();
        q.pop();
        for(int next : adj[now]){
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
                adj[parent[i]].push_back(i);
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

            // cout << cmd << "  : " << p1 << " " << p2 << "\n";

            // 부모 정보 변화
            parent[c1] = p2;
            parent[c2] = p1;

            // 부모에 현재 자식 제거
            adj[p1].erase(find(adj[p1].begin(), adj[p1].end(), c1));
            adj[p2].erase(find(adj[p2].begin(), adj[p2].end(), c2));
            
            // int flag = false;
            // for (int vv : adj[p1]){
            //     if(vv==c1)
            //         flag = true;
            // }
            // cout << (flag ? "삭제 안됐는데??" : "삭제됨!!")
            //      << "\n";
            
            // for (int vv : adj[p2]){
            //     if(vv==c1)
            //         flag = true;
            // }
            // cout << (flag ? "삭제 안됐는데??" : "삭제됨!!")
            //      << "\n";


            // 부모에 바뀐 자식 push
            adj[p1].push_back(c2);
            adj[p2].push_back(c1);

            // flag = false;
            // for (int vv : adj[p2]){
            //     if(vv==c1)
            //         flag = true;
            // }
            // cout << (flag ? "들어감!!" : "안들어감!!")
            //      << "\n";

            // flag = false;
            // for (int vv : adj[p1]){
            //     if(vv==c2)
            //         flag = true;
            // }

            // cout << (flag ? "들어감!!" : "안들어감!!")
            //      << "\n";

            // cout << cmd << "  : " << parent[c1] << " " << parent[c2] << "\n";

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