import heapq

# 创建一个小顶堆
min_heap = []

# 推入元素
heapq.heappush(min_heap, 10)
heapq.heappush(min_heap, 3)
heapq.heappush(min_heap, 8)
heapq.heappush(min_heap, 5)

print(f"小顶堆: {min_heap}")  # 输出的列表不一定是完全排序的，但 heap[0] 永远是最小值

# 查看最小元素
print(f"最小元素: {min_heap[0]}")

# 弹出最小元素
smallest = heapq.heappop(min_heap)
print(f"弹出的最小元素: {smallest}")
print(f"弹出后的堆: {min_heap}")

# 从一个现有列表创建堆
data = [19, 9, 4, 11, 6, 21]
heapq.heapify(data)
print(f"通过 heapify 创建的堆: {data}")