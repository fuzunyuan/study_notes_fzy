#ifndef MY_SHARED_PTR_HPP
#define MY_SHARED_PTR_HPP

#include <iostream>
#include <utility>

// 辅助类 : 控制块
struct ControlBlock {
    // 强引用计数: 有多少个MySharedPtr 实例在拥有这个对象
    // 当 strong_count降到0时，必须delete这个资源
    int strong_count ;

    // 弱引用计数: 有多少个MyWeakPtr实例在 “观察”这个对象
    // 当 weak_count降到0(并且 强引用本身也为0)
    // 必须 delete 这个 ControlBlock本身
    int weak_count ;

    ControlBlock() : strong_count(0), weak_count(0) {}
};

template<typename  T>
class MyWeakPtr;

template<typename T>
class MySharedPtr_simple {
    private:
        T* m_ptr; // 指向被管理资源的裸指针
        ControlBlock* m_block; // 指向共享控制块的指针

        // 内部清理函数
        void cleanup() {

            if (!m_ptr) {
                return;
            }

            // 1. 减少强引用计数
            m_block->strong_count--;
            std::cout << "[Debug] MySharedPtr cleanup: strong_count = "
                  << m_block->strong_count << std::endl;
            // 2. 检查强引用是否为0
                // 3. 检查弱引用是否为0
            if (m_block->strong_count == 0) {
                std::cout <<"[Debug] MySharedPtr: Deleting resource..."<< std::endl;
                delete m_ptr;
                m_ptr = nullptr;

                if (m_block->weak_count == 0) {
                    std::cout <<"[Debug] MySharedPtr: Deleting control block..."<< std::endl;
                    delete m_block;
                    m_block = nullptr;
                }
            }
        }

    // 允许MyWeakPtr 访问我们的私有成员
    friend class MyWeakPtr<T>;
    public:

        // 1. 构造函数
        explicit MySharedPtr_simple(T* ptr = nullptr)
            : m_ptr(ptr) {
            if (m_ptr) {
                // 分配控制块
                m_block = new ControlBlock();
                // 初始化强引用为 1
                m_block->strong_count = 1;
                m_block->weak_count = 0;
                std::cout << "[Debug] MySharedPtr(T*): Created. strong=1, weak=0" << std::endl;
            } else {
                m_block = nullptr;
                std::cout << "[Debug] MySharedPtr(nullptr): Created empty." << std::endl;
            }
        }
        // 2. 拷贝构造函数 -- 这个就是共享所有权的核心
        MySharedPtr_simple(const MySharedPtr_simple& other)
            : m_ptr(other.m_ptr), m_block(other.m_block) {
            if (m_block) {
                m_block->strong_count++;
                std::cout << "[Debug] MySharedPtr(Copy Ctor): strong="
                      << m_block->strong_count << std::endl;
            }
        }
        // 3. 拷贝赋值运算符
        MySharedPtr_simple& operator=(const MySharedPtr_simple& other) {
            // 1. 检查自赋值
            if (this == &other) {
                return *this;
            }

            // 2. 先释放当前持有的资源
            cleanup();

            // 3. 复制other的数据
            m_ptr = other.m_ptr;
            m_block = other.m_block;

            // 4. 增加新资源的引用计数
            if (m_block) {
                m_block->strong_count++;
                std::cout << "[Debug] MySharedPtr(Copy Assign): strong="
                      << m_block->strong_count << std::endl;
            }

            return *this;
        }
        // 4. 移动构造函数
        MySharedPtr_simple(MySharedPtr_simple&& other) noexcept
            : m_ptr(other.m_ptr), m_block(other.m_block) {
            // other 放弃所有权
            other.m_ptr = nullptr;
            other.m_block = nullptr;

            std::cout << "[Debug] MySharedPtr(Move Ctor)" << std::endl;
        }
        // 5. 移动赋值运算符
        MySharedPtr_simple& operator=(MySharedPtr_simple&& other) noexcept {
            // 1. 检查自赋值
            if (this == &other) {
                return *this;
            }
            // 2. 释放当前持有的资源
            cleanup();
            // 3. 从 'other'窃取资源
            m_ptr = other.m_ptr;
            m_block = other.m_block;
            // 4. 'other' 放弃所有权
            other.m_ptr = nullptr;
            other.m_block = nullptr;
            std::cout << "[Debug] MySharedPtr(Move Assign)" << std::endl;
            return *this;
        }
        // 6. 析构函数
        ~MySharedPtr_simple() {
            std::cout << "[Debug] MySharedPtr Destructor..." << std::endl;
            cleanup();
        }
        // 7. 模拟指针行为
        T& operator*() const {return *m_ptr;}
        T* operator->() const {return m_ptr;}
        // 8. 实用工具函数
        T* get() const {return m_ptr;}
        int use_count() const {
            return m_block ? m_block->strong_count : 0;
        }
        explicit operator bool() const {
            return m_ptr != nullptr;
        }
};

// 简化版的辅助函数
template<typename T, typename... Args>
MySharedPtr_simple<T> MakeShared(Args&&... args) {
    // 效率比较低的 make_shared版本：它分配两次
    // 1. new T(args...)
    // 2. new ControlBlock()
    return MySharedPtr_simple<T>(new T(std::forward<Args>(args)...));
}

#endif