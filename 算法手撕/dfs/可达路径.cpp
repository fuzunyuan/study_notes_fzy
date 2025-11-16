/***
*98. 可达路径
题目描述
给定一个有 n 个节点的有向无环图，节点编号从 1 到 n。请编写一个函数，找出并返回所有从节点 1 到节点 n 的路径。每条路径应以节点编号的列表形式表示。
输入描述
第一行包含两个整数 N，M，表示图中拥有 N 个节点，M 条边

后续 M 行，每行包含两个整数 s 和 t，表示图中的 s 节点与 t 节点中有一条路径

输出描述
输出所有的可达路径，路径中所有节点之间空格隔开，每条路径独占一行，存在多条路径，路径输出的顺序可任意。如果不存在任何一条路径，则输出 -1。

注意输出的序列中，最后一个节点后面没有空格！ 例如正确的答案是 `1 3 5`,而不是 `1 3 5 `， 5后面没有空格！
*/
#include <iostream>
#include <vector>

std::vector<std::vector<int>> results;
std::vector<int> path;

void dfs(std::vector<std::vector<int>>& points, int N, int target) {

    path.emplace_back(N);
    // 深搜结束条件
    if (N == target) {
        results.emplace_back(path);
        path.pop_back();
        return;
    }
    for(int i = 1; i <= target; i++) {
        if(points[N][i] == 1) {

            dfs(points, i, target);

        }

    }
    // 回溯
    path.pop_back();
}

int main() {
    int N, M;

    std::cin >> N >> M;
    std::vector<std::vector<int>> points(N + 1, std::vector<int>(N + 1,0));
    int i, j;
    while(M--) {
        std::cin >> i >> j;
        points[i][j] = 1;
    }

    dfs(points, 1, N);
    if (results.size() == 0) {
        std::cout << -1;
        return 0;
    }
    for(int t = 0; t < results.size(); t++) {
        for(int k = 0; k < results[t].size(); k++) {
            if (k != 0){
                std::cout << " ";
            }
            std::cout << results[t][k];

        }
        std::cout << std::endl;
    }
}