// 背景：
/*
我在面试的时候，遇到这样一个问题：
给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点
路径总和等于给定目标和的路径。
叶子节点 是指没有子节点的节点。
输入：root=[5,4,8,11,null,13,4,7,2,null,null,5,1],targetSum=22 输出：[[5,4,11,2],[5,8,4,5]] ，
输入：root=[1,2,3],targetSum=5 输出：[]
输入：root=[1,2],targetSum=0输出：[]，
但是我遇到的题目更难，是这样描述的，不要求起点从根节点出发，不要求终点在叶子节点，找到所有的路径
*/
// 题目初步解法：双重DFS + 回溯
#include<vector>
#include<iostream>
#include <windows.h> // 1. 包含这个 Windows.h 头文件

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    private:
        // 用于存储所有找到的路径
        std::vector<std::vector<int>> allPaths;

    /***
     *
     * 内层DFS
     * 从node节点开始，查找所有和为targetNum的路径
     * currentSum是从startNode(外层循环的节点) 到 node 的父节点的路径和
     * currentPath 存储了startNode 到当前 node 的路径
     */
    void findPath(TreeNode* node, long long currentSum, int targetSum, std::vector<int>& currentPath) {
        if (node == NULL) {
            return;
        }

        currentSum += node->val;
        currentPath.push_back(node->val);

        if (currentSum == targetSum) {
            allPaths.push_back(currentPath);
        }

        findPath(node->left, currentSum, targetSum, currentPath);
        findPath(node->right, currentSum, targetSum, currentPath);

        // 回溯
        currentPath.pop_back();
    }

    /**
     * 外层DFS
     * 遍历树中的每一个节点，并且以它为起点启动内层DFS
     */
    void traverse(TreeNode* node, int targetSum) {
        if (node == NULL) {
            return;
        }

        std::vector<int> currentPath;
        findPath(node, 0, targetSum, currentPath);

        traverse(node->left, targetSum);
        traverse(node->right, targetSum);
    }

    public:
        std::vector<std::vector<int>> pathSum(TreeNode* root, int target) {
            allPaths.clear();
            traverse(root, target);
            return allPaths;
        }

};
// 3. ------------------------------------------
//    辅助函数：打印结果
// ---------------------------------------------
void printResult(const std::vector<std::vector<int>>& result, int targetSum) {
    std::cout << "--- 目标和 (TargetSum): " << targetSum << " ---" << std::endl;
    if (result.empty()) {
        std::cout << "未找到任何路径。" << std::endl;
        return;
    }

    std::cout << "找到了 " << result.size() << " 条路径:" << std::endl;
    for (const auto& path : result) {
        std::cout << "[ ";
        for (int i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i < path.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " ]" << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}

// 辅助函数：清理二叉树内存
void deleteTree(TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}


// 4. ------------------------------------------
//    主函数 (main) - 测试入口
// ---------------------------------------------
int main() {
    // 构建测试树
    //       10
    //      /  \
    //     5    -3
    //    / \    \
    //   3   2    11
    //  / \   \
    // 3  -2   1
    SetConsoleOutputCP(CP_UTF8);
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(-3);

    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    root->right->right = new TreeNode(11);

    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(-2);
    root->left->right->right = new TreeNode(1);

    // 创建 Solution 实例
    Solution solution;

    // --- 测试 1 ---
    int targetSum1 = 8;
    std::vector<std::vector<int>> result1 = solution.pathSum(root, targetSum1);
    printResult(result1, targetSum1);

    // --- 测试 2 (测试空路径) ---
    int targetSum2 = 100;
    std::vector<std::vector<int>> result2 = solution.pathSum(root, targetSum2);
    printResult(result2, targetSum2);

    // --- 测试 3 (测试单个节点) ---
    int targetSum3 = 11;
    std::vector<std::vector<int>> result3 = solution.pathSum(root, targetSum3);
    printResult(result3, targetSum3);


    // 清理内存
    deleteTree(root);

    return 0;
}