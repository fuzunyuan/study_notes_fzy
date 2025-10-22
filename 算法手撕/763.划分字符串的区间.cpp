/*
class Solution {
public:
    // 这一题的难点在与划分思想的区别
    // 就是保证遍历到当前的所有的字母都出现在当前区间，那么就可以添加到result中 
    vector<int> partitionLabels(string s) {
        int last[26] = {0};
        for(int i = 0; i < s.size(); i++) {
            last[s[i] - 'a'] = i;
        }

        vector<int> partition;
        int start = 0, end = 0;
        for (int  i = 0; i < s.size();i++) {
            end = max(end, last[s[i] - 'a']);
            if(end == i) {
                partition.push_back(end - start + 1);
                start = end + 1;
            }
        }

        return partition;
    }
};
*/