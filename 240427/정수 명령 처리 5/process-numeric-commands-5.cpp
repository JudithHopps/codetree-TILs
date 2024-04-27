#include <iostream>
#include <string> 
#include <vector>

using namespace std;
vector<int> v;
int t, n;
string cmd; 

int main() {
    cin >> t;
    while(t--){
        cin >> cmd;
        if(cmd =="push_back"){
            cin >> n;
            v.push_back(n);
        }

        else if (cmd == "get"){
            cin >> n;
            cout << v[n-1] <<"\n";
        }

        else if (cmd =="size"){
            cout << v.size() <<"\n";
        }
        else if (cmd =="pop_back"){
            if(v.size()) v.pop_back();
        }
    }
    return 0;
}