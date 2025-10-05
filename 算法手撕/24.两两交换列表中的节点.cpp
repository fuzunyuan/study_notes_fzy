/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// 这一题其实用的就是递推的算法
// 核心点1，添加一个头结点的实现，以及将当前节点作为头结点的下一个节点
//         ListNode dummy(0, head);
// 核心点2，将两两节点交换得的顺序
            // node_2 = node_1->next
            // node_3 = node_2->next;

            // node_0->next = node_2
            // node_2->next = node_1
            // node_1->next = node_3

            // 最后修改node_0 和 node_1的指向即可
            // node_0 = node_1
            // node_1 = node_3

/*
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0, head);
        ListNode* node_0 = &dummy;
        ListNode* node_1 = head;

        while(node_1 && node_1 -> next) {
            ListNode* node_2 = node_1->next;
            ListNode* node_3 = node_2->next;

            node_0->next = node_2;
            node_2->next = node_1;
            node_1->next = node_3;

            node_0 = node_1;
            node_1 = node_3;
        }

        return dummy.next;
    }
};*/