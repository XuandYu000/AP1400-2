#include "cappuccino.h"

void addIngredients(std::vector<Ingredient*>& vec)
{
    vec.push_back(new Espresso{2});
    vec.push_back(new Milk{2});
    vec.push_back(new MilkFoam{1});
}

Cappuccino::Cappuccino()
{
    this->name = "Cappuccino";
    addIngredients(ingredients);
}

Cappuccino::Cappuccino(const Cappuccino& cap) : side_items(cap.side_items)
{
    this->name = cap.name;
    this->ingredients = cap.ingredients;
}

Cappuccino::~Cappuccino()
{
    // for (const auto& i : side_items)
    // {
    //     delete i;
    // }
    side_items.clear();
    std::vector<Ingredient*>().swap(side_items);
}

void Cappuccino::operator=(const Cappuccino& cap)
{
    if (this != &cap)
    {
        this->name = cap.name;
        this->ingredients = cap.ingredients;
        this->side_items = cap.side_items;
    }
}

std::string Cappuccino::get_name()
{

    return this->name;
}

double Cappuccino::price()
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

void Cappuccino::add_side_item(Ingredient* side)
{
    side_items.push_back(side);
}


std::vector<Ingredient*>& Cappuccino::get_side_items()
{
    return side_items;
}




