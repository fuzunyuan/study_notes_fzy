# 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

# 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

# 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

# 这个是找第K大的元素，那么可以从两个角度来考虑
# 1. 使用python中的小顶堆，然后，将所有元素的相反数加入堆中即可，然后，依次将K个元素给输出出来即可

# class Solution:
#     def findKthLargest(self, nums: List[int], k: int) -> int:
#         min_heap = []
#         import heapq
#         for t in nums:
#             heapq.heappush(min_heap, -1 * t)
#         print(f"小顶堆元素：{min_heap}")
#         for i in range(0,k - 1):
#             heapq.heappop(min_heap)
#         return -1 * heapq.heappop(min_heap)
        
# 2. 同样使用python中的小顶堆，输出第N-k个元素
