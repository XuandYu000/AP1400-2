#include "mocha.h"
#include <sub_ingredients.h>

void addMochaIngredients(std::vector<Ingredient*>& vec)
{
    vec.push_back(new Espresso{2});
    vec.push_back(new Milk{2});
    vec.push_back(new MilkFoam{1});
    vec.push_back(new Chocolate{1});
}

Mocha::Mocha()
{
    this->name = "Mocha";
    addMochaIngredients(ingredients);
}

Mocha::Mocha(const Mocha& cap) : side_items(cap.side_items)
{
    this->name = cap.name;
    this->ingredients = cap.ingredients;
}

Mocha::~Mocha()
{
    side_items.clear();
    std::vector<Ingredient*>().swap(side_items);
}

void Mocha::operator=(const Mocha& cap)
{
    if (this != &cap)
    {
        this->name = cap.name;
        this->ingredients = cap.ingredients;
        this->side_items = cap.side_items;
    }
}

std::string Mocha::get_name()
{

    return this->name;
}

double Mocha::price()
{
    double res = 0;
    for (const auto& ingredient:ingredients)
    {
        res += ingredient->price();
    }

    for (const auto& item : side_items)
    {
        res += item->price();
    }

    return res;
}

void Mocha::add_side_item(Ingredient* side)
{
    side_items.push_back(side);
}


std::vector<Ingredient*>& Mocha::get_side_items()
{
    return side_items;
}