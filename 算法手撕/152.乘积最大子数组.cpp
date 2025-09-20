// 传统的做法，使用两个数组的辅助空间
// code1:
/*
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // 1. 这行代码创建了一个名为 MaxF 的 long 类型向量，并用 nums 向量中的所有元素来初始化它。
        // 简单来说，就是创建了一个 nums 的完整拷贝，并将其命名为 MaxF。
        vector<long> MaxF(nums.begin(), nums.end()), MinF(nums.begin(), nums.end());
        for(int i = 1; i < nums.size(); i++) {
            MaxF[i] = max(nums[i]*MaxF[i - 1], max(nums[i] * MinF[i - 1], (long)nums[i]));
            MinF[i] = min(nums[i]*MaxF[i - 1], min(nums[i] * MinF[i - 1], (long)nums[i]));
            if (MinF[i] < INT_MIN) {
                MinF[i] = nums[i];
            }
        }

        // 2. max_element(MaxF.begin(), MaxF.end())

        max_element: 这是 C++ 标准库 <algorithm> 中的一个函数。

        作用: 它的作用是在一个给定的范围内查找最大的元素。

        参数: 它接收两个迭代器作为参数，定义了查找的范围，这里是 MaxF.begin() 和 MaxF.end()，代表查找整个 MaxF 向量。

        返回值: 这一点非常重要！ max_element 函数返回的不是最大值本身，而是指向那个最大值元素的迭代器（也就是一个指向内存地址的“指针”）。

        b) * (星号)

        *: 在这里是“解引用运算符”（Dereference Operator）。

        作用: 当你有一个指向某个内存地址的迭代器或指针时，在它前面加上 * 就可以获取到存储在该地址的实际值。
        return *max_element(MaxF.begin(), MaxF.end());
    }
};
*/
// 2. 解法二：一般在面试的过程中会对一个问题进行升级提问：
// 直接借用中间变量来记录，大大减小空间复杂度
/*
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxF = nums[0], minF = nums[0],ans = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int temp_max = maxF, temp_min = minF; 
            maxF = max(nums[i] * temp_max, max(nums[i] * temp_min, nums[i]));
            minF = min(nums[i] * temp_min, min(nums[i] * temp_max, nums[i]));
            if (minF < INT_MIN) {
                minF = INT_MIN;
            }
            ans = max(maxF, ans);
        }

        return ans;
    }
};

*/