#include "barrel.hpp"

Barrel::Barrel(double initialVolume, double initialAlcohol, double initialWater)
{
    this->volume = initialVolume;
    this->alcohol = initialAlcohol;
    this->water = initialWater;
}

void Barrel::pour_into(Barrel &other, double amount)
{
    double actualAmount = std::min(amount, other.get_total_volume());

    if (actualAmount <= 0)
    {
        std::cout << RED << "No volume in barrel" << RESET;
        return;
    }

    double alcoholToPour = (alcohol / get_total_volume()) * actualAmount;
    double waterToPour = (water / get_total_volume()) * actualAmount;

    alcohol -= alcoholToPour;
    water -= waterToPour;

    other.alcohol += alcoholToPour;
    other.water += waterToPour;
}

double Barrel::get_alc_concentration()
{
    double totalVolume = get_total_volume();
    if (totalVolume == 0)
        return 0;
    return (alcohol / totalVolume) * 100.0;
}

double Barrel::get_total_volume()
{
    return alcohol + water;
}
