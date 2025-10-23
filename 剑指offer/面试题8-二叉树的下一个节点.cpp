#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *mParent;
    // 构造函数为了方便测试
    TreeNode(int v) : val(v), left(nullptr), right(nullptr), mParent(nullptr) {}
};

TreeNode *findNext(TreeNode *root) {
    TreeNode *p = root;
    if (p == nullptr) {
        return nullptr;
    }

    // 1. 如果当前节点的右子树不为空
    if (p->right != nullptr) {
        TreeNode* p_next = p->right;
        while (p_next->left != nullptr) {
            p_next = p_next->left;
        }

        return p_next;
    }
    else if (p->mParent != nullptr) { // 当前节点不存在右子树，那么就要向上找最顶层的节点，也就是root节点
        TreeNode* p_next = p;
        TreeNode* p_parent = p_next->mParent;
        while (p_parent->mParent != nullptr && p_parent->right == p_next) {
            p_next = p_parent;
            p_parent = p_parent->mParent;
        }
        return p_parent;
    }
}

// 辅助函数：打印节点信息
void printNode(const std::string& msg, TreeNode* node) {
    std::cout << msg;
    if (node != nullptr) {
        std::cout << node->val << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
}

void runTest(TreeNode* node) {
    if (node == nullptr) {
        std::cout << "Testing: null" << std::endl;
    } else {
        std::cout << "Testing: " << node->val << std::endl;
    }

    TreeNode* successor = findNext(node);

    std::cout << "  -> Successor is: ";
    if (successor != nullptr) {
        std::cout << successor->val << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

int main() {
    // 1. 构建树节点
    TreeNode* n8 = new TreeNode(8); // Root
    TreeNode* n6 = new TreeNode(6);
    TreeNode* n10 = new TreeNode(10);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n7 = new TreeNode(7);
    TreeNode* n9 = new TreeNode(9);
    TreeNode* n11 = new TreeNode(11);

    // 2. 链接左右子树
    n8->left = n6;
    n8->right = n10;

    n6->left = n5;
    n6->right = n7;

    n10->left = n9;
    n10->right = n11;

    // 3. 链接父指针 (mParent)
    n6->mParent = n8;
    n10->mParent = n8;

    n5->mParent = n6;
    n7->mParent = n6;

    n9->mParent = n10;
    n11->mParent = n10;

    // 中序遍历: 5, 6, 7, 8, 9, 10, 11

    std::cout << "Running In-order Successor Tests..." << std::endl;
    std::cout << "In-order traversal: 5, 6, 7, 8, 9, 10, 11" << std::endl;
    std::cout << "====================" << std::endl;

    // 测试用例
    runTest(n5);  // 预期: 6 (Case 2: 5是6的左孩子)
    runTest(n6);  // 预期: 7 (Case 1: 6有右子树，右子树的最左是7)
    runTest(n7);  // 预期: 8 (Case 2: 7是6的右孩子，6是8的左孩子 -> 8)
    runTest(n8);  // 预期: 9 (Case 1: 8有右子树，右子树的最左是9)
    runTest(n9);  // 预期: 10 (Case 2: 9是10的左孩子)
    runTest(n10); // 预期: 11 (Case 1: 10有右子树，右子树的最左是11)
    runTest(n11); // 预期: null (Case 2: 11是10的右孩子，10是8的右孩子，8是root -> null)
    runTest(nullptr); // 预期: null (Case: null input)


    // 4. 释放内存
    delete n5;
    delete n7;
    delete n9;
    delete n11;
    delete n6;
    delete n10;
    delete n8;

    return 0;
}