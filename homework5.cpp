#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 目标状态
const string target = "12345678x";

// 方向数组：上、右、下、左
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int bfs(string start) {
    queue<string> q;
    unordered_map<string, int> dist;  // 记录每个状态的最短步数
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        auto t = q.front();
        q.pop();

        if (t == target) return dist[t];  // 找到目标状态

        int distance = dist[t];
        int pos = t.find('x');  // 找到 'x' 的位置
        int x = pos / 3, y = pos % 3;  // 转换为二维坐标

        for (int i = 0; i < 4; ++i) {  // 尝试四个方向
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {  // 判断是否越界
                int new_pos = nx * 3 + ny;
                string new_state = t;
                swap(new_state[pos], new_state[new_pos]);  // 交换 'x' 和相邻数字

                if (!dist.count(new_state)) {  // 如果新状态未访问过
                    dist[new_state] = distance + 1;
                    q.push(new_state);
                }
            }
        }
    }

    return -1;  // 无解
}

int main() {
    string start;
    char c;
    for (int i = 0; i < 9; ++i) {
        cin >> c;
        start += c;
    }

    cout << bfs(start) << endl;
    return 0;
}