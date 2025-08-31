// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
// 示例1：
// 输入：head = [1,2,3,4,5], n = 2
// 输出：[1,2,3,5]
// 示例 2：

// 输入：head = [1], n = 1
// 输出：[]
// 示例 3：

// 输入：head = [1,2], n = 1
// 输出：[1]

// 思路：
// 1. 简单思路，使用栈，将所有的节点都入栈，然后依次出栈，找到第n个节点，那么就是倒数第n个节点
//    然后将其删除掉即可
// codes如下：
/*
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        stack <ListNode*> stack_list;
        ListNode* temp = head;
        int length = 0;
        while(temp!=nullptr) {
            cout << "temp->val = " << temp->val << endl;
            stack_list.push(temp);
            temp = temp-> next;
            length++;
        }
        if (n == length) {
            return head->next;
        }
        int t = 0;
        
        while(!stack_list.empty()) {
            t++;
            
            temp = stack_list.top();
            stack_list.pop();
            cout << "temp->val1 = " << temp->val << endl;
            if (n + 1 == t) {
               break; 
            }
        }

        if (temp != nullptr) {
            temp -> next  = temp  -> next -> next;
        }

 
        return head;
    }
};
*/
// 2. 解法可以采用双指针的方法，first节点和second节点，
//      让first节点，先向前遍历n个节点，这样first节点和second节点之间就相隔n个节点
//      然后first节点与second节点一起向后遍历，此时，当first节点遍历到最后的时候，
//      second节点就是倒数第n个节点
//      算法复杂度就是O(N)
/*
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        ListNode* firstNode   = head;
        ListNode* secondeNode = head;

        for (int i = 0 ; i < n;i++){
            firstNode = firstNode -> next;
        }
        // difficult: 这个地方是较难的一个点，就是含有的隐形条件就是
        //            整个列表的长度n = 倒数第n个
        if (firstNode == nullptr) {
            return secondeNode-> next;
        }
       

        while(firstNode -> next != nullptr) {
            firstNode   = firstNode -> next;
            secondeNode = secondeNode -> next;
        }


        secondeNode -> next = secondeNode -> next -> next;

        return head;
    
    }
       
};
*/