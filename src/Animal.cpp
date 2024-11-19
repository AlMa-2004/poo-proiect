#include "../headers/Animal.h"

// Constructor for Animal class
Animal::Animal(std::string name, int production_time, bool fed_status, bool product_status)
    : animalName(std::move(name)), productionTime(production_time), fedStatus(fed_status), productStatus(product_status)
{
}

std::ostream& operator<<(std::ostream& os, const Animal& obj)
{
    os << "animalName: " << obj.animalName
        << " | Is Fed: " << obj.fedStatus
        << " | Is Produced: " << obj.productStatus;
    return os;
}
