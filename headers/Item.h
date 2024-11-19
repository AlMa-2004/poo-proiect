#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>

class Item
{
    std::string itemName;
    int itemQuantity;

public:
    explicit Item(std::string n, int c);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] int getQuantity() const;
    void setQuantity(int c);
    friend std::ostream& operator<<(std::ostream& os, const Item& obj);
};
#endif //ITEM_H
