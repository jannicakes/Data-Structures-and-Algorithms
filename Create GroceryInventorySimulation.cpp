#include <iostream>
#include <vector>
#include <string>

using namespace std;


string vectorToString(const vector<string>& vec, const string& label) {
    string result = label + "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        result += "\"" + vec[i] + "\"";
        if (i < vec.size() - 1) result += ", ";
    }
    result += "]\n";
    return result;
}


void mergeInventory(vector<string>& inventory, const vector<string>& shipment) {
    for (const auto& item : shipment) {
        bool found = false;
        for (const auto& invItem : inventory) {
            if (item == invItem) {
                found = true;
                break;
            }
        }
        if (!found) {
            inventory.push_back(item);
        }
    }
}

void removeSoldOutItems(vector<string>& inventory, const vector<string>& soldoutItems) {
    for (const auto& soldItem : soldoutItems) {
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i] == soldItem) {
                inventory.erase(inventory.begin() + i);
                break;
            }
        }
    }
}

int main() {
    vector<string> inventory = {"apples", "bananas", "oranges", "pears"};
    vector<string> shipment = {"kiwis", "bananas", "grapes"};
    vector<string> soldoutItems = {"apples", "oranges"};

    cout << vectorToString(inventory, "Current Inventory: ");
    cout << vectorToString(shipment, "Shipment: ");

    mergeInventory(inventory, shipment);

    removeSoldOutItems(inventory, soldoutItems);

    cout << vectorToString(soldoutItems, "Sold-out items: ");
    cout << vectorToString(inventory, "Updated Inventory: ");

    return 0;
}
