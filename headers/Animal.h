#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>
#include <iostream>

class Animal
{
    std::string animalName;
    const int productionTime;
    bool fedStatus, productStatus;

public:
    explicit Animal(std::string name, int production_time, bool fed_status, bool product_status);

    friend std::ostream& operator<<(std::ostream& os, const Animal& obj);
};

#endif // ANIMAL_H
