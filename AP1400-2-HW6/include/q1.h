#ifndef Q1_H
#define Q1_H
#include <cmath>
#include <functional>

/*
 * 梯度下降的思想是在梯度的方向上函数变化最快
 * 每次将init值每次变化梯度*步长来逐步逼近最小值
 */

namespace q1
{
    template <typename T, typename Func>
    T gradient_descent(const T& init, const T& step, Func func = Func{})
    {
        T value = init;
        auto accuracy = step * 1e-3;
        auto gradient = [&func, &accuracy](T& value) {return (func(value + accuracy)-func(value)) / accuracy; };
        while (abs(gradient(value)) > accuracy)
        {
            value = value - step * gradient(value);
        }
        return value;
    }

    template <typename T>
    T gradient_descent(const T& init, const T& step, T func(T))
    {
        return gradient_descent<T, T(T)>(init, step,func);
    }
};

#endif //Q1_H
