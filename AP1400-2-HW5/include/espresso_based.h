#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include "ingredient.h"
#include <vector>
#include <string>

class EspressoBased
{
public:
    // virtual 声明虚函数实现动态多态
    // 在其后加上 = 0 则为纯虚函数(pure virtual function), 包含纯虚函数的类成为抽象类
    virtual std::string get_name() = 0;
    virtual double price() = 0;

    void brew();
    /*
     * std::vector<Ingredient*>&：
     * 这表示函数返回一个指向 std::vector<Ingredient*> 类型的引用。换句话说，函数返回的是一个指针，指向某个 std::vector 对象，
     * 而不是返回一个新的 std::vector 对象的副本。这种方式可以有效地避免在返回时进行副本构造，提高了效率，
     * 并且允许调用者对返回的向量进行修改。
     *
     * std::vector<Ingredient*>：
     * 这表示函数返回一个 std::vector<Ingredient*> 类型的对象。
     * 这意味着函数返回一个新创建的 std::vector 对象的副本，而不是原始的 std::vector 对象。
     * 在这种情况下，调用者得到的是一个新的向量对象，对它的修改不会影响到函数内部使用的原始向量。
     *
     * std::vector<Ingredient*>& 表示返回一个指向 std::vector<Ingredient*> 的引用，
     * 而 std::vector<Ingredient*> 表示返回一个新的 std::vector<Ingredient*> 对象的副本。
     * 选择使用哪种方式取决于函数的设计目的和对返回值的操作需求。
     * 通常情况下，如果需要返回一个向量并且希望调用者能够对其进行修改，那么使用引用返回更为方便和高效。
     */
    std::vector<Ingredient*>& get_ingredients();

    /*
     * 这里析构函数如果按照要求for(const auto& i : ingredients) delete i;那么会将同一块空间重复释放报错
     * 此时可以先clear后std::vector<Ingredient*>().swap(ingredients);
     * 这种方式可以有效地释放内存空间，并且将容器恢复为初始状态。因为在使用 swap() 函数时，
     * 创建了一个新的匿名 std::vector<Ingredient*> 对象，然后将其与 ingredients 容器交换，最后匿名对象会在结束时自动销毁，
     * 释放内存空间。
     */

    /*
     * 如果将析构函数声明为protected那么限制只有该类和衍生类可以调用
     * 如果在外界对象生命周期结束时无法调用析构函数从而无法释放内存。
     */
    virtual ~EspressoBased();

protected:
    EspressoBased();
    EspressoBased(const EspressoBased& esp);
    /*
     * 之前重载'='运算符会声明函数为typename&作为返回
     * 声明为void时通常会先比较两个地址是否相等(避免重复)
     * 然后再将参数全部复制
     */
    void operator=(const EspressoBased& esp);

    std::vector<Ingredient*> ingredients;
    std::string name;

};
#endif // ESPRESSO_BASED_H