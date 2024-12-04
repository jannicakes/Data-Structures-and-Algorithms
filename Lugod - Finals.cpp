#include <bits/stdc++.h>
using namespace std;

vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
    vector<bool> knowsSecret(n, false);
    knowsSecret[0] = true;
    knowsSecret[firstPerson] = true;

    map<int, vector<pair<int, int>>> timeMeetings;
    for (auto& meeting : meetings) {
        timeMeetings[meeting[2]].push_back({meeting[0], meeting[1]});
    }

    for (auto& [time, meetingList] : timeMeetings) {
        unordered_set<int> tempKnowsSecret;
        unordered_map<int, vector<int>> graph;
  
        for (auto& [u, v] : meetingList) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
   
        for (auto& [person, _] : graph) {
            if (knowsSecret[person] && tempKnowsSecret.find(person) == tempKnowsSecret.end()) {
                queue<int> q;
                q.push(person);

                while (!q.empty()) {
                    int current = q.front();
                    q.pop();
                    if (tempKnowsSecret.count(current)) continue;

                    tempKnowsSecret.insert(current);
                    for (int neighbor : graph[current]) {
                        if (!tempKnowsSecret.count(neighbor)) {
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        for (int person : tempKnowsSecret) {
            knowsSecret[person] = true;
        }
    }

    vector<int> result;
    for (int i = 0; i < n; ++i) {
        if (knowsSecret[i]) {
            result.push_back(i);
        }
    }
    return result;
}

int main() {
    cout << endl;
    int n1 = 6;
    vector<vector<int>> meetings1 = {{1, 2, 5}, {2, 3, 8}, {1, 5, 10}};
    int firstPerson1 = 1;
    vector<int> result1 = findAllPeople(n1, meetings1, firstPerson1);
    for (int person : result1) {
        cout << person << " ";
    }
    cout << endl;

    cout  << endl;
    int n2 = 4;
    vector<vector<int>> meetings2 = {{3, 1, 3}, {1, 2, 2}, {0, 3, 3}};
    int firstPerson2 = 3;
    vector<int> result2 = findAllPeople(n2, meetings2, firstPerson2);
    for (int person : result2) {
        cout << person << " ";
    }
    cout << endl;

    cout << endl;
    int n3 = 5;
    vector<vector<int>> meetings3 = {{3, 4, 2}, {1, 2, 1}, {2, 3, 1}};
    int firstPerson3 = 1;
    vector<int> result3 = findAllPeople(n3, meetings3, firstPerson3);
    for (int person : result3) {
        cout << person << " ";
    }
    cout << endl;

    return 0;
}
 