/*
45. 跳跃游戏 II
中等

给定一个长度为 n 的 0 索引整数数组 nums。初始位置在下标 0。

每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在索引 i 处，你可以跳转到任意 (i + j) 处：

0 <= j <= nums[i] 且
i + j < n
返回到达 n - 1 的最小跳跃次数。测试用例保证可以到达 n - 1。

 

示例 1:

输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
示例 2:

输入: nums = [2,3,0,1,4]
输出: 2
 

提示:

1 <= nums.length <= 104
0 <= nums[i] <= 1000
题目保证可以到达 n - 1
*/
/*
class Solution {
public:
    int jump(vector<int>& nums) {
        int steps = 0;
		// 分别设置两个下表，一个代表当前可达的步数
		// 第二个代表下一层可达的步数
		int end = 0;
		int next_end = 0;
		int length = nums.size() - 1;
		
		for (int i = 0; i < length; i++) {
			// 谈心算法体现的部分
			next_end = max(next_end, nums[i]+i);
			if (end == i) {
				steps++;
				end = next_end;
			}
			if (end >= length){
				break;
			}
		
		}
		
		return steps;
    }
};
*/