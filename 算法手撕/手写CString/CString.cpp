#include <iostream>
#include <cstring>
#include <utility>
#include <Windows.h>

class CString {
    private:
        char* m_data; // 指向动态分配的字符数组
        size_t m_size; // 字符串的长度，不包含末尾的'/0'
    public:
        // todo : 1. 构造函数
        CString(const char* str = nullptr) {
            if (str == nullptr) {
                m_size = 0;
                m_data = new char[1]; // 这个地方至少放一个字符，用来存放\0
                *m_data = '\0';
            } else {
                m_size = std::strlen(str);
                m_data = new char[m_size + 1];
                std::strcpy(m_data, str);
            }
            std::cout << "  [构造函数] CString(\"" << (m_data ? m_data : "null") << "\")" << std::endl;
        }
        //        2. 析构函数
        ~CString() {
            std::cout << "  [析构函数] ~CString(\"" << (m_data ? m_data : "null") << "\")" << std::endl;
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
        }
        //        3. 拷贝构造函数
        // CString s2 = s1;
        CString(const CString& other) {
            // 深拷贝：为新对象分配自己的内存
            m_size = other.m_size;
            m_data = new char[m_size + 1];
            std::strcpy(m_data, other.m_data);
            std::cout << "  [拷贝构造] CString(const CString& other = \"" << other.m_data << "\")" << std::endl;
        }
        //        4. 普通赋值函数
        // s2 = s1;
        CString& operator=(const CString& other) {
            std::cout << "  [拷贝赋值] operator=(\"" << other.m_data << "\")" << std::endl;
            // 1. 检查自身的赋值情况
            if (this == &other) {
                return *this;
            }
            // 2. 释放当前对象的旧资源
            delete[] m_data;
            // 3. 分配新资源并执行深拷贝
            m_size = other.m_size;
            m_data = new char[m_size + 1];
            std::strcpy(m_data, other.m_data);
            // 4. 返回对当前对象的引用
            return *this;
        }
        //        5. 移动构造函数
        // CString s3 = std::move(s1);
        // noexcept 告诉编译器此函数不会抛出异常，这对于标准库容器（如 std::vector）的性能优化很重要
        CString(CString&& other) noexcept {
            // "窃取"Steal other对象的资源
            m_data = other.m_data;
            m_size = other.m_size;

            std::cout << "  [移动构造] CString(CString&& other = \"" << m_data << "\")" << std::endl;
            // 将other对象置于一个有效的、可析构的状态
            other.m_data = nullptr;
            other.m_size = 0;
        }
        //        6. 右值引用赋值函数
        // s2 = std::move(s3);
        CString& operator=(CString&& other) noexcept {
            std::cout << "  [移动赋值] operator=(CString&& other = \"" << other.m_data << "\")" << std::endl;
            if (this == &other) {
                return *this;
            }

            delete[] m_data;

            m_data = other.m_data;
            m_size = other.m_size;

            other.m_data = nullptr;
            other.m_size = 0;

            return *this;
        }

        // 打印字符串的内容
        const char* c_str() const { return m_data; }
        // 获取长度
        size_t size() const { return m_size; }
        // 用于在main 中打印 CString 对象
        friend std::ostream& operator<<(std::ostream& os, const CString& s) {
            os << s.c_str();
            return os;
        }
};

CString createCString(const char* str) {
    std::cout << "--- 调用 createCString ---" << std::endl;
    CString temp(str);
    std::cout << "--- 结束 createCString ---" << std::endl;
    return temp;
}

int main() {
    SetConsoleOutputCP(65001); // 65001 是 UTF-8 在 Windows 上的代码页编号
    std::cout << "1. 构造函数测试:" << std::endl;
    CString s1("Hello");
    CString s_empty; // 测试默认构造
    std::cout << "s1: " << s1 << " (size: " << s1.size() << ")" << std::endl;
    std::cout << "s_empty: " << s_empty << " (size: " << s_empty.size() << ")" << std::endl;

    std::cout << "\n2. 拷贝构造函数测试:" << std::endl;
    CString s2 = s1;
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;

    std::cout << "\n3. 拷贝赋值函数测试:" << std::endl;
    CString s3("World");
    std::cout << "赋值前 s3: " << s3 << std::endl;
    s3 = s1;
    std::cout << "赋值后 s3: " << s3 << std::endl;
    s1 = s1; // 测试自赋值
    std::cout << "自赋值后 s1: " << s1 << std::endl;

    std::cout << "\n4. 移动构造函数测试 (使用 std::move):" << std::endl;
    std::cout << "移动前 s2: " << s2 << std::endl;
    CString s4 = std::move(s2);
    std::cout << "移动后 s4: " << s4 << std::endl;
    // std::cout << "移动后 s2 (应为空): " << s2 << " (size: " << s2.size() << ")" << std::endl;

    std::cout << "\n5. test" << std::endl;
    std::cout << "\n5. 移动构造函数测试 (使用函数返回值):" << std::endl;
    // C++ 编译器通常会执行 RVO (返回值优化)，这可能会跳过移动构造
    // 但如果 RVO 未发生，则会调用移动构造
    CString s5 = createCString("Temporary");
    std::cout << "s5: " << s5 << std::endl;

    std::cout << "\n6. 移动赋值函数测试:" << std::endl;
    std::cout << "移动前 s3: " << s3 << std::endl;
    s_empty = std::move(s3);
    std::cout << "移动后 s_empty: " << s_empty << std::endl;
    std::cout << "移动后 s3 (应为空): " << s3 << " (size: " << s3.size() << ")" << ", s3原内存已被s_empty接管并析构" << std::endl;


    std::cout << "\n7. 作用域结束，开始析构:" << std::endl;
    return 0;
}