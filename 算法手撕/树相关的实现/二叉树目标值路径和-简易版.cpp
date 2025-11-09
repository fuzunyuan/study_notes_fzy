// 这一题相较于二叉树的目标值路径和相比：整体的逻辑会简单一些，因为只需要一条完整的路径
// 起点必须是根节点，终点必须是叶子节点
// 所以只需要 深搜 + 回溯 即可解决问题

/**
* Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> pathTarget(TreeNode* root, int target) {
        pathFind(root, target);

        return result;
    }
private:
    // 这道题目用的是递归 + 回溯
    vector<vector<int>> result;
    vector<int> path;

    void pathFind(TreeNode* currentNode, int targetNum) {
        if (currentNode == nullptr) {
            return;
        }

        targetNum -= currentNode->val;
        path.push_back(currentNode->val);
        if(targetNum == 0 && currentNode->left == nullptr && currentNode->right == nullptr) {
            result.push_back(path);
        }

        pathFind(currentNode->left, targetNum);
        pathFind(currentNode->right, targetNum);

        path.pop_back();
    }
};