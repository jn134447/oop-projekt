#ifndef INVENTORY_H
#define INVENTORY_H

#include <unordered_map>
#include <string>

class Inventory
{
private:
    std::unordered_map<std::string, int> items;

public:
    void AddItem(const std::string &itemId, const int quantity);
    void HasItem(const std::string &itemId, const int minQuantity = 1) const;
};

#endif