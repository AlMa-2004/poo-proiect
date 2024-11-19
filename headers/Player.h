#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include "../headers/Crop.h"
#include "../headers/Item.h"
#include "../headers/Animal.h"

class Player
{
    std::string playerName;
    int playerMoney;

    //REPLACE WITH SMART POINTERS & MODIFY SIZE OF FIELD - POSSIBLE LOTS WHERE CROPS CAN BE PLANTED
    std::vector<Item> Inventory;
    std::array<Crop, 5> Field;
    //vector<Animal> Barn;

public:
    //CONSTRUCTORS & DESTRUCTORS
    Player();
    explicit Player(std::string name, int money, const std::vector<Item>& items,
                    const std::array<Crop, 5>& field);
    Player(const Player& p);

    ~Player();

    //OPERATOR OVERLOADING
    Player& operator=(const Player& p);
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

    //INVENTORY MANAGEMENT
    void addItem(const Item& i);

    //FIELD MANAGEMENT
    void Plant(const std::string& s, int nr);
    void Harvest();
    std::array<Crop, 5>& getField();
};


#endif //PLAYER_H
