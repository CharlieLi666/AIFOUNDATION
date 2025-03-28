#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

// 目标状态（即解决后的正确排列）
const string target = "12345678x";

// 方向数组：上、右、下、左（对应二维坐标变化）
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

// 移动方向对应的字符表示
const char dir[] = {'u', 'r', 'd', 'l'};

// 定义状态结构体
struct State {
    string board;  // 当前棋盘状态（用字符串表示，如"123x46758"）
    int g;         // 从起始状态到当前状态的实际步数
    int h;         // 当前状态到目标状态的启发式估计值（曼哈顿距离）
    string path;   // 从起始状态到当前状态的移动路径（如"uldr"）
    
    // 重载>运算符，用于优先队列排序（小根堆）
    bool operator>(const State& other) const {
        return (g + h) > (other.g + other.h);  // 按f(n)=g(n)+h(n)排序
    }
};

// 计算曼哈顿距离（启发式函数）
int manhattan(const string& board) {
    int distance = 0;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 'x') continue;  // 空格不计算距离
        int num = board[i] - '1';      // 将字符'1'-'8'转换为数字0-7
        // 累加每个数字当前位置与目标位置的曼哈顿距离
        distance += abs(i / 3 - num / 3) + abs(i % 3 - num % 3);
    }
    return distance;
}

// A*算法实现
string astar(string start) {
    // 优先队列（小根堆），按f(n)=g(n)+h(n)排序
    priority_queue<State, vector<State>, greater<>> pq;
    // 记录已访问状态及其对应的最小步数
    unordered_map<string, int> visited;
    
    // 初始状态计算启发式值
    int h = manhattan(start);
    // 初始状态入队：步数0，路径为空
    pq.push({start, 0, h, ""});
    visited[start] = 0;  // 记录初始状态
    
    while (!pq.empty()) {
        // 取出当前最优状态
        State current = pq.top();
        pq.pop();
        
        // 找到目标状态，返回路径
        if (current.board == target) {
            return current.path;
        }
        
        // 如果当前步数大于已记录的最小步数，跳过
        if (current.g > visited[current.board]) {
            continue;
        }
        
        // 找到空格'x'的位置
        int pos = current.board.find('x');
        // 将一维位置转换为二维坐标
        int x = pos / 3, y = pos % 3;
        
        // 尝试四个方向的移动
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];  // 计算新坐标
            // 检查新坐标是否合法
            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                string next_board = current.board;
                // 交换空格和相邻数字
                swap(next_board[pos], next_board[nx * 3 + ny]);
                
                int new_g = current.g + 1;  // 新状态的步数
                // 如果新状态未被访问过，或者找到更优路径
                if (!visited.count(next_board) || new_g < visited[next_board]) {
                    int new_h = manhattan(next_board);  // 计算新启发式值
                    string new_path = current.path + dir[i];  // 更新路径
                    // 新状态入队
                    pq.push({next_board, new_g, new_h, new_path});
                    visited[next_board] = new_g;  // 更新访问记录
                }
            }
        }
    }
    
    // 无解情况
    return "unsolvable";
}

int main() {
    string start;
    char c;
    // 读取输入，共9个字符（8个数字和1个'x'）
    for (int i = 0; i < 9; ++i) {
        cin >> c;
        start += c;
    }
    
    // 调用A*算法并输出结果
    cout << astar(start) << endl;
    return 0;
}