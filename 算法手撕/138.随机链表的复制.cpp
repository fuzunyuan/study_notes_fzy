/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
/*
class Solution {
public:
    Node* copyRandomList(Node* head) {
        // 这一题的难点就在于：想到使用unorder_map来做一个 新 旧 节点之间的映射
        if (head == nullptr) return nullptr;
        Node* cur = head;
        // 难点1，这个地方的初始化，要注意unordered_map的初始化
        unordered_map<Node*, Node*> map;

        while(cur != nullptr) {
            map[cur] = new Node(cur->val);
            cur = cur -> next;
        }

        cur = head;

        while(cur!=nullptr) {
            // 整个题目的难点所在，使用unordered_map可以快速找到下一个节点与随机节点
            map[cur] -> next = map[cur->next];
            map[cur] -> random = map[cur -> random];
            cur = cur -> next;
        }

        return map[head];
    }
};
*/