#include "espresso_based.h"

EspressoBased::EspressoBased() {}

EspressoBased::EspressoBased(const EspressoBased& esp) : ingredients(esp.ingredients), name(esp.name){}

EspressoBased::~EspressoBased()
{
    // for (const auto& i : ingredients)
    // {
    //     delete i;
    // }
    ingredients.clear();
    std::vector<Ingredient*>().swap(ingredients);
}

void EspressoBased::operator=(const EspressoBased& esp)
{
    if (this != &esp)
    {
        this->name = esp.name;
        this->ingredients = esp.ingredients;
    }
}

std::vector<Ingredient*>& EspressoBased::get_ingredients()
{
    return this->ingredients;
}

void EspressoBased::brew()
{
    return;
}

