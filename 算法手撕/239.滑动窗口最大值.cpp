/*
class Solution {
public:
// 这一道题的结题方法是，滑动窗口 + 单调队列
// 两个方法都要用到才能解题
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
         if (nums.size() == 0 || k == 0) return {};

        deque<int> deque;
        vector<int> res(nums.size() + 1 - k);

        for (int j = 0, i = 1 - k; j < nums.size(); i++, j++) {
            // 当窗口向右滑动时，判断之前的最大值（也就是队首元素 deque.front()）
            // 是否已经滑出窗口，如果滑出，就将其从队首移除。
            // 如果是，说明最大值已经过期，必须从队首 pop 掉，
            // 让队列中第二大的元素（如果存在）成为新的最大值。

            // 如果不是，说明滑出去的只是一个小值，
            // 真正的最大值（队首元素）仍然在窗口内，无需任何操作。
            if ( i > 0 && nums[i-1] == deque.front()) {
                deque.pop_front();
            }

            while(!deque.empty()&&nums[j] > deque.back()) {
                deque.pop_back();
            }

            deque.push_back(nums[j]);
            if(i >= 0) {
                res[i] = deque.front();
            }

        }

        return res;
    }
    
};
*/