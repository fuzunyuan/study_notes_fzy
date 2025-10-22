#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <funcitonal>
#include <shared_mutex>
#include <utility>

// 注册式工厂
// CtorArgs... 代表将来创建派生对象时，构造函数需要哪些实参
template <typename Base, typename... CtorArgs>
class RegistryFactory {
    public:
        // 用std::function 函数包装模板，方便把lambda、函数指针、std::bind 结果都塞到同一个容器里
        using Crearor = std::function<std::unique_ptr<Base>(CtorArgs&&...)>;

        // 单例入口，只有第一次调用的时候，才会走到这里
        static RegistryFactory& instance() {
            static RegistryFactory f;
            return f;
        }

        // 注册派生类，自动用其构造函数（CtorArgs... ）构造
        // 函数的入参通常是用于标识要创建的类型
        // 在emplace 中是一个闭包的写法
        // 它接受一个参数包CtorArgs，并使用万能引用&&和可变参数模板...来实现完美转发。
        // 它调用std::make_unique来构造一个**Derived类型的对象，
        // 然后用std::forward**将传入的参数args完美转发给Derived的构造函数。
        // std::forward确保了参数的原始左值/右值属性得以保留
        // 避免了不必要的拷贝或移动。最后，它将创建的std::unique_ptr返回。
        template <typename Derived>
        bool register_type(const std::string& key) {
            std::unique_lock lock(mu_);
            auto [it, ok] = creators_.emplace(
                key,
                [](CtorArgs&&... args ) -> std::unique_ptr<Base> {
                    return std::make_unique<Derived>(std::forward<CtorArgs>(args)...);
                }
            );
            return ok;
        }

        // 手动注册
        bool register_creator(const std::string& key, Creator creator) {
            std::unique_lock lock(mu_);
            auto[it, ok] = creators_.emplace(key, std::move(creator));

            return ok;
        }

        // 根据 key 创建对象，找不到返回 nullptr
        std::unique_ptr<Base> create(const std::string& key, CtorArgs... args) const {
             
            std::shared_lock lock(mu_);
            auto it = creators_.find(key);
            if (it == creators_.end()) return nullptr;
            return (it->second)(std::forward<CtorArgs>(args)...);
        }

    private:
        RegistryFactory() = default;
        RegistryFactory(const RegistryFactory&) = delete;
        RegistryFactory& operator = (const RegistryFactory&) = delete;

        mutable std::shared_mutex mu_;
        std::unordered_map<std::string, Creator> creators_;

};

// 使用示例
struct Vehicle {
    virtual ~Vehicle() = default;
    virtual std::string spec() const = 0;
}

struct Car : Vehicle {
    int hp;
    explicit Car(int hp_) : hp(hp_) {}
    std::string spec() const override { return "Car(" + std::to_string(hp) + "hp)"; }
};

struct Bike : Vehicle {
    int gears;
    explicit Bike(int g) : gears(g) {}
    std::string spec() const override { return "Bike(" + std::to_string(gears) + "g)"; }
};

using VehicleFactory = RegistryFactory<Vehicle, int>;

int main() {
    auto& fac  = VehicleFactory::instance();

    fac.register_type<Car>("car");
    fac.register_type<Bike>("bike");

    auto v1 = fac.create("car", 150);
    auto v2 = fac.create("bike", 21);
    auto v3 = fac.create("unknown", 0);

    if (v1) std::cout << v1->spec() << "\n";
    if (v2) std::cout << v2->spec() << "\n";
    if (!v3) std::cout << "unknown not registered\n";

    return 0;
}