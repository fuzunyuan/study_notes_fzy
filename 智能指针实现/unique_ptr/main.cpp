#include <iostream>
#include "MyUniquePtr.hpp"

using namespace std;

struct Widget {
    int id;
    Widget(int i) : id(i) {
        cout << "Widget " << id << " created." << endl;
    }

    ~Widget() {
        cout << "Widget " << id << " destroyed." << endl;
    }

    void doSomething() {
        cout << "Widget " << id << " is doing something." << endl;
    }
};

// 移动语义，函数返回
MyUniquePtr<Widget> createWidget(int id) {
    cout << "--- Entering createWidget ---" << endl;
    MyUniquePtr<Widget> w(new Widget(id));
    cout << "--- Exiting createWidget ---" << endl;
    return w;
}

// 演示移动语义，函数参数
void takeOwnership(MyUniquePtr<Widget> p) {
    cout << "--- Entering takeOwnership ---" << endl;
    if (p) {
        p->doSomething();
    }
    cout << "--- Exiting takeOwnership ---" << endl;
}

int main() {
    cout << "===== 1. Basic RAII Test =====" << endl;
    {
        MyUniquePtr<Widget> ptr1(new Widget(1));
        ptr1->doSomething();
        (*ptr1).doSomething();
    }
    cout << "============================\n" << std::endl;

    cout << "===== 2. Move Constructor Test (Return from function) =====" << endl;
    MyUniquePtr<Widget > ptr = createWidget(2);
    cout << "Widget 2 is now owned by ptr2 in main." << endl;
    cout << "============================\n" << std::endl;

    cout << "===== 3. Move Assignment Test =====" << endl;
    MyUniquePtr<Widget > ptr3(new Widget(3));
    MyUniquePtr<Widget > ptr4(new Widget(4));

    cout << "Before move assignment..." << endl;
    ptr3 = move(ptr4);
    std::cout << "After move assignment..." << std::endl;
    std::cout << "ptr4.get() is now: " << (ptr4.get() ? "not null" : "null") << std::endl;
    std::cout << "============================\n" << std::endl;

    std::cout << "===== 4. Move to Function Test =====" << std::endl;
    MyUniquePtr<Widget> ptr5(new Widget(5));
    takeOwnership(std::move(ptr5)); // 转移所有权给函数
    std::cout << "ptr5.get() is now: " << (ptr5.get() ? "not null" : "null") << std::endl;
    std::cout << "============================\n" << std::endl;

    std::cout << "===== 5. Reset and Release Test =====" << std::endl;
    MyUniquePtr<Widget> ptr6(new Widget(6));
    ptr6->doSomething();
    ptr6.reset(new Widget(7)); // Widget 6 被销毁，ptr6 接管 Widget 7
    std::cout << "After reset..." << std::endl;
    Widget* raw_ptr = ptr6.release(); // ptr6 放弃所有权
    std::cout << "After release, ptr6.get() is: " << (ptr6.get() ? "not null" : "null") << std::endl;
    raw_ptr->doSomething();
    delete raw_ptr; // 我们现在必须手动删除它
    std::cout << "============================\n" << std::endl;

    std::cout << "===== 6. Copy Test (Compile Error) =====" << std::endl;
    // 下面的代码如果取消注释，将会编译失败，这正是我们想要的！
    // MyUniquePtr<Widget> ptr8(new Widget(8));
    // MyUniquePtr<Widget> ptr9 = ptr8; // 错误：拷贝构造函数被 delete
    // MyUniquePtr<Widget> ptr10;
    // ptr10 = ptr8; // 错误：拷贝赋值运算符被 delete
    std::cout << "(Copy tests are commented out, compile fails as expected)" << std::endl;
    std::cout << "============================\n" << std::endl;

    std::cout << "End of main. ptr2, ptr3 will be destroyed." << std::endl;
    return 0;
}
