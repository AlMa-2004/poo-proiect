#include "../headers/Item.h"

Item::Item(std::string n,const int c = 1) : itemName(std::move(n)), itemQuantity(c)
{
    std::cout << "Item constructor\n";
}

[[nodiscard]] std::string Item::getName() const { return itemName; }
[[nodiscard]] int Item::getQuantity() const { return itemQuantity; }
void Item::setQuantity(const int c) { itemQuantity = c; }

std::ostream& operator<<(std::ostream& os, const Item& obj)
{
    return os << "Item " << obj.itemName << " ( " << obj.itemQuantity << "pcs )\n";
}
