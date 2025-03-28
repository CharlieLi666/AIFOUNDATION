#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    // 用邻接矩阵处理
    vector<vector<int>> g(n + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 0; i < m; ++i) {
        int a, b, z;
        scanf("%d%d%d", &a, &b, &z);
        // 如果有重边，取最短的
        g[a][b] = min(g[a][b], z);
    }

    // 距离
    vector<int> dist(n + 1, INT_MAX); 
    // 标记是否已访问
    vector<bool> visited(n + 1, false); 
    // 起点到自己的距离为 0
    dist[1] = 0;  

    // dijkstra的处理：外层循环
    for (int i = 0; i < n; ++i) { 
        int u = -1;
        // 找到未访问的、距离起点最近的点
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (u == -1) break;  // 所有可达点都已处理
        visited[u] = true;  // 标记为已访问

        // 用 u 更新其他点的距离
        for (int v = 1; v <= n; ++v) {
            if (g[u][v] != INT_MAX) {  // 如果 u→v 有边
                dist[v] = min(dist[v], dist[u] + g[u][v]);
            }
        }
    }

    if (dist[n] == INT_MAX) printf("-1\n");  // 无法到达
    else printf("%d\n", dist[n]);

    return 0;
}