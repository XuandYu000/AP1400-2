#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include <utility>

/*
 * UniquePtr主要是限制指针只能被一个对象拥有
 * 这就说明取消'='运算符和copy构造函数
 */
template<typename T>
class UniquePtr
{
public:
    // 动态对象创建直接资源转移
    UniquePtr(T* obj) : _p(std::move(obj)){}
    UniquePtr() : _p(nullptr) {}
    ~UniquePtr()
    {
        if (!_p)
        {
            delete _p;
            _p = nullptr;
        }
    }
    // '='运算符和copy构造函数直接禁用
    UniquePtr(const UniquePtr& obj) = delete;
    T& operator=(const UniquePtr* ptr) = delete;
    T* get() const
    {
      return _p;
    }
    T& operator*() const
    {
        if (_p)
        {
            return  *_p;
        }
        else
        {
            throw std::runtime_error("Cannot dereference a nullptr.");
        }
    }
    T* operator->()
    {
        return _p;
    }
    void reset()
    {
        if (!_p)
        {
            delete _p;
            _p = nullptr;
        }
        _p = nullptr;
    }
    void reset(T* obj)
    {
        if (!_p)
        {
            delete _p;
            _p = nullptr;
        }
        _p = std::move(obj);
    }
    T* release()
    {
        T* tmp = _p;
        _p = nullptr;
        return tmp;
    }
    /*
     * 这个函数是一个显式转换运算符，用于将类对象转换为布尔值。这种显式转换通常被用来实现对象的布尔上下文转换，使得该对象可以被用于条件
     * 判断或者布尔运算。
     */
    explicit operator bool()
    {
        return _p != nullptr;
    }

private:
    T* _p;
};

/*
 * class... Args 参数包用于处理可变数量的模板参数。
 * std::forward实现完美转发，。完美转发是指，在模板函数中将参数以原始的值类别（value category）和引用属性（reference qualifiers）
 * 转发给另一个函数，从而保留参数的完整类型信息。
 */
template<typename T, class... Args>
auto make_unique(Args&&... args)
{
    return UniquePtr<T>{new T(std::forward<Args>(args)...)};
}

#endif //UNIQUE_PTR
