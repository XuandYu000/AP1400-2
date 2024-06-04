#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

/*
 * Micro 宏定义可以将DEFCLASS表示符替换为函数或对象
 * 同时有两个运算符#和##
 * # ： 将运算符后的参数变为字符串
 * 详见 https://en.cppreference.com/w/cpp/preprocessor/replace
 */
/*
 * 当子类继承父类并将父类声明为 public 时，
 * 父类中的 public 成员（包括成员函数和成员变量）会在子类中继承并保持其 public 访问权限。
 */
#define DEFCLASS(Name, Price) class Name : public Ingredient {  \
public:                                                         \
    Name(size_t units) : Ingredient{Price, units}       \
    {                                                           \
        this->name = #Name;                                     \
    }                                                           \
    virtual std::string get_name()                              \
    {                                                           \
        return this->name;                                      \
    }                                                           \
}                                                               \



DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);


#endif // SUB_INGREDIENTS_H