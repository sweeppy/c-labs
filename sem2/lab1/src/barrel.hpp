#include <iostream>

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"

class Barrel
{
private:
    double volume;
    double alcohol;
    double water;

public:
    Barrel(double initialVolume, double initialAlcohol, double initialWater);

    void pour_into(Barrel &other, double amount);

    double get_alc_concentration();

    double get_total_volume();
};
