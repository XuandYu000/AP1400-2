#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <string>

class Ingredient
{
public:
    double get_price_unit() const
    {
        return price_unit;
    }
    size_t get_units() const
    {
        return units;
    }
    /*
     * virtual 声明虚函数实现动态多态，即让基类的指针或引用能够根据实际指向的对象类型来调用相应的成员函数。
     */
    virtual std::string get_name() = 0;

    double price()
    {
        return price_unit * units;
    }

/*
 * protected 定义可以使该类衍生的函数访问， 使用private后不能再修改成员变量
 */
protected:
    Ingredient(double price_unit, size_t units) : price_unit(price_unit),  units(units) {}

    double price_unit;
    size_t units;
    std::string name;
};

#endif // INGREDIENT_H