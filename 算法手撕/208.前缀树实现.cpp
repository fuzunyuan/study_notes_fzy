// 请你实现 Trie 类：
// Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。
// Trie() 初始化前缀树对象。
// void insert(String word) 向前缀树中插入字符串 word 。
// boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
// boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。
 

// 示例：

// 输入
// ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
// [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
// 输出
// [null, null, true, false, true, null, true]

// 解释
// Trie trie = new Trie();
// trie.insert("apple");
// trie.search("apple");   // 返回 True
// trie.search("app");     // 返回 False
// trie.startsWith("app"); // 返回 True
// trie.insert("app");
// trie.search("app");     // 返回 True
 

// 提示：

// 1 <= word.length, prefix.length <= 2000
// word 和 prefix 仅由小写英文字母组成
// insert、search 和 startsWith 调用次数 总计 不超过 3 * 104 次

// 解题思路： 这个题目的难点就在于怎么把单词给抽象成节点
//           重点的思路就是，一个单词的每一位是26位字母中的一个，所以可以看作是“26叉树，并且这个26叉树，可以使用一个相邻的
//                         数组来存储，那么这样就可以很快的搜索到子节点是否存在”
//           这三个方法中insert的难点在于怎么讲单词给拆开来插入
//              search在于怎么和startWith给区分开来，然后，记得是返回标志位，也就是isEnd,而不是单纯的返回false     
/*
class Trie {
private:
	struct TireNode{
		TireNode* children[26];
		bool isEnd;
		TireNode():isEnd(false) {
			
			for (int i = 0; i< 26;i++){
				children[i] = nullptr;
			}
		}
		
	};
    TireNode* root;
public:
    Trie() {
        root = new TireNode();
    }
    
    void insert(string word) {
        TireNode* cur = root;
		for ( char ch : word) {
			int idx = ch - 'a';
			if(!cur->children[idx]){
				cur->children[idx] = new TireNode();
			}
			cur = cur->children[idx];
		}
		cur->isEnd = true;
    }
    
    bool search(string word) {
        TireNode* cur = root;
		for (char ch : word) {
			int idx = ch - 'a';
			if (!cur->children[idx]) return false;
			cur = cur->children[idx];
		}
		return cur->isEnd;
    }
    
    bool startsWith(string prefix) {
       TireNode* cur = root;
		for (char ch : prefix) {
			int idx = ch - 'a';
			if (!cur->children[idx]) return false;
			cur = cur->children[idx];
		}
		return true;
    }
};
*/

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */