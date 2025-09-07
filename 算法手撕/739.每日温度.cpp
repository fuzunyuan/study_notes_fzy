/*
739. 每日温度
已解答
中等
相关标签
premium lock icon
相关企业
提示
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，
下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

示例 1:
输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]

示例 2:
输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]

示例 3:
输入: temperatures = [30,60,90]
输出: [1,1,0]
*/

#include <vector>
#include <stack>
using std::vector;
using std::stack;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);
		stack<int> stack_temp;
		
		for(int i = temperatures.size() - 1; i >= 0; i--) {
			
			while(!stack_temp.empty() && temperatures[stack_temp.top()] <= temperatures[i]) {
				stack_temp.pop();
			}
			
			result[i] = stack_temp.empty()? 0:stack_temp.top() - i;
			stack_temp.push(i);
		
		}
		return result;
    }
};