//
// Created by alexa on 19.11.2024.
//

#include "../headers/Player.h"

Player::Player(): playerName("Player"), playerMoney(0), Field({})
{
    Inventory.emplace_back("Seeds",1);
    std::cout << "Default player constructor\n";
}

Player::Player(std::string name="Player", const int money=0, const std::vector<Item>& items={},
               const std::array<Crop, 5>& field={}) : playerName(std::move(name)),
                                                        playerMoney(money), Inventory(items),
                                                        Field(field)
{
    std::cout << "Parameterised player constructor\n";
}

Player::Player(const Player& p):
    playerName(p.playerName),
    playerMoney(p.playerMoney),
    Inventory(p.Inventory),
    Field(p.Field)
{
    std::cout << "Copy player constructor\n";
}

Player::~Player() = default;

//OPERATOR OVERLOADING
Player& Player::operator=(const Player& p)
{
    this->playerName = p.playerName;
    this->playerMoney = p.playerMoney;
    this->Inventory = p.Inventory;
    std::cout << "Player assignment\n";
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << "PlayerName: " << player.playerName
        << " Money: " << player.playerMoney
        << " Inventory: ";
    for (auto& i : player.Inventory)
        os << i << " ";
    os << "Field:\n";
    for (auto& j : player.Field)
    {
        os << j << " ";
    }
    os << "\n";
    return os;
}

//INVENTORY MANAGEMENT
void Player::addItem(const Item& i)
{
    for (auto& item : Inventory)
    {
        if (item.getName() == i.getName())
        {
            item.setQuantity(item.getQuantity() + i.getQuantity());
            return;
        }
    }
    Inventory.push_back(i);
}

//FIELD MANAGEMENT
void Player::Plant(const std::string& s, int no)
{
    bool exists = false;
    for (auto& invItem : Inventory)
    {
        if (invItem.getName() == s)
        {
            exists = true;
            if (invItem.getQuantity() < no)
            {
                std::cout << "You don't have that many seeds for planting! Planting " << invItem.getQuantity() <<
                    " seeds.\n";
                no = invItem.getQuantity();
                invItem.setQuantity(0);
            }
            else
                invItem.setQuantity(invItem.getQuantity() - no);
            break;
        }
    }
    if (exists == false)
    {
        std::cout << "You don't have this kind of item in your inventory!\n";
        return;
    }

    std::cout << "Planting...\n";

    int noPlanted = 0;
    for (auto& lot : Field)
    {
        if (noPlanted >= no) break;
        if (lot.getName().empty())
        {
            lot = Crop(s, 0, 0, true, true);
            std::cout << "The following type of seed: " << s << " has been planted on an empty lot.\n";
            noPlanted++;
        }
    }
    if (noPlanted < no)
    {
        std::cout << "You don't have enough free lots for planting those seeds.\n";
    }
}

void Player::Harvest()
{
    for (auto& lot : Field)
    {
        if (lot.getGrowthStatus())
        {
            std::cout << "The " << lot.getName() << " crop is ready for collection!\n";
            addItem(Item(lot.getName().substr(8), 1));
            lot = Crop(); /// Resetting the lot after collecting the crops with an "anonymous" plant.
        }
    }
}

[[nodiscard]] std::array<Crop, 5>& Player::getField() { return Field; }
