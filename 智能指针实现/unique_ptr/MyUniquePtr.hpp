#ifndef MY_UNIQUE_PTR_HPP
#define MY_UNIQUE_PTR_HPP

#include <iostream>
#include <utility>

template<typename T>
class MyUniquePtr {
private:
    T* m_ptr;
public:
    // explicit 关键字防止隐式转换
    explicit MyUniquePtr(T* ptr = nullptr)
        : m_ptr(ptr) {}
    // RAII的核心：析构函数
    ~MyUniquePtr() {
        if (m_ptr) {
            delete m_ptr;
            m_ptr = nullptr;
        }
    }

    // 3. 独占所有权：禁止拷贝
    MyUniquePtr(const MyUniquePtr& rhs) = delete;
    MyUniquePtr& operator=(const MyUniquePtr& rhs) = delete;
    // 4. 独占所有权: 实现移动

    // 移动构造函数
    // 从other窃取steal指针的所有权
    // noexpect很重要，他告诉编译器不会抛出异常
    MyUniquePtr(MyUniquePtr&& other) noexcept
        :m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }
    // 移动赋值运算符
    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept {
        // 1. 检查自赋值
        if (this != &other) {
            // 2. 释放当前持有的资源
            if (m_ptr) {
                delete m_ptr;
            }
            // 3. 从other中窃取资源
            m_ptr = other.m_ptr;
            // 4. other放弃所有权
            other.m_ptr = nullptr;
        }
      return *this;
    }

    // 5. 模拟指针行为
    // 重载 * 运算符，解引用
    T& operator*() const {
        return *m_ptr;
    }
    // 重载 -> 运算符，成员访问
    T* operator->() const {
        return m_ptr;
    }
    // 6. 实用工具函数
    // get()， 返回裸指针
    T* get() const {
        return m_ptr;
    }
    // operator bool() const : 检查是否持有指针
    explicit operator bool() const {
        return m_ptr != nullptr;
    }
    // release(): 放弃所有权并返回裸指针
    // 调用者负责来管理这个指针的生命周期
    T* release() {
        T* tmp = m_ptr;
        m_ptr = nullptr;
        return tmp;
    }
    // reset() 释放旧指针，并获取一个新指针
    void reset(T* ptr = nullptr) {
        // 先保存旧的指针
        T* old_ptr = m_ptr;
        // 再获取指针
        m_ptr = ptr;
        // 最后释放旧指针
        if (old_ptr) {
            delete old_ptr;
        }
    }

};
#endif // MMY_UNIQUE_PTR_HPP