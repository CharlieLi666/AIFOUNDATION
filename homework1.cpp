#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    // 输入处理
    int n, m;
    scanf("%d%d", &n, &m);
    // 创建邻接表来存储图
    vector<vector<int>> adj(n + 1);

    // 输入图的节点
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
    }
    // 距离数组，-1表示未访问
    vector<int> dist(n + 1, -1);
    // 创建BFS队列
    queue<int> q;
    // 1到自己的距离为0
    dist[1] = 0;
    // 初始放入1，从1开始BFS
    q.push(1);


    // BFS遍历原理
    while (!q.empty()) {
        // 取出首节点
        int u = q.front();
        // 弹出首节点
        q.pop();
        // 遍历u的邻居，如果v未被访问就更新v的距离并把v加入队列
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    // 在无权图中，BFS 按层遍历，先访问距离1的节点，再访问距离2的节点，依此类推。第一次访问n时，dist[n]就是最短距离。
    // 在此直接打印dist「n」
    printf("%d\n", dist[n]);
    return 0;
}