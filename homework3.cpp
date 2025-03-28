// 堆优化版dijkstra
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = 0x3f3f3f3f;  // 定义无穷大

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<pair<int, int>>> adj(n + 1);  // 邻接表存图

    // 读入边并构建邻接表
    for (int i = 0; i < m; ++i) {
        int a, b, z;
        scanf("%d%d%d", &a, &b, &z);
        adj[a].emplace_back(b, z);  // 允许重边，算法会自动处理
    }

    vector<int> dist(n + 1, INF);  // 存储最短路长度
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;  // 小根堆
    
    dist[1] = 0;          // 起点距离为0
    pq.emplace(0, 1);     // 初始将起点入队

    while (!pq.empty()) {
        auto [d, u] = pq.top();  // 取出当前距离最小的点
        pq.pop();

        if (d > dist[u]) continue;  // 跳过已处理的旧数据

        // 遍历所有邻接边
        for (auto [v, z] : adj[u]) {   // C++17结构化绑定
            if (dist[v] > dist[u] + z) {
                dist[v] = dist[u] + z;  // 松弛操作
                pq.emplace(dist[v], v); // 新状态入队
            }
        }
    }

    // 输出结果
    if (dist[n] == INF) printf("-1\n");  // 不可达
    else printf("%d\n", dist[n]);

    return 0;
}