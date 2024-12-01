#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

// Function to simulate boiling water
void boilWater(int& waterTemp) {
    cout << "Boiling water..." << endl;
    this_thread::sleep_for(chrono::seconds(3)); // Simulate boiling time
    waterTemp = 100; // Simulate water reaching boiling temperature
}

// Function to simulate checking water temperature
void checkWaterTemp(int waterTemp, int requiredTemp) {
    if (waterTemp >= requiredTemp) {
        cout << "Water is ready to pour!" << endl;
    } else {
        cout << "Water is not ready yet." << endl;
    }
}

// Function to simulate heating a pan
void heatPan() {
    cout << "Heating the pan..." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Simulate heating time
    cout << "Pan is heated." << endl;
}

// Function to cook eggs based on type
void cookEggs(string eggType) {
    if (eggType == "fried") {
        cout << "Adding oil or butter to the pan..." << endl;
        this_thread::sleep_for(chrono::seconds(2)); // Simulate adding oil or butter
        cout << "Cooking fried eggs..." << endl;
    } else if (eggType == "scrambled") {
        cout << "Beating eggs..." << endl;
        this_thread::sleep_for(chrono::seconds(2)); // Simulate beating eggs
        cout << "Cooking scrambled eggs..." << endl;
    }
    this_thread::sleep_for(chrono::seconds(3)); // Simulate cooking time
    cout << "Eggs are ready!" << endl;
}

// Main function
int main() {
    int waterTemp = 0;
    int requiredWaterTemp = 90;

    // Step 1: Boil water
    cout << "Step 1: Boil water for coffee." << endl;
    boilWater(waterTemp);

    // Step 2: Check water temperature
    cout << "Step 2: Check water temperature." << endl;
    checkWaterTemp(waterTemp, requiredWaterTemp);

    // Step 3: Heat pan and choose egg type
    cout << "Step 3: Heat pan and prepare eggs." << endl;
    heatPan();

    string eggType;
    cout << "Do you want scrambled or fried eggs? ";
    cin >> eggType;

    // Step 4: Cook eggs
    cout << "Step 4: Cooking eggs." << endl;
    cookEggs(eggType);

    // Step 5: Prepare coffee
    cout << "Step 5: Preparing coffee..." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simulate setting aside coffee
    cout << "Coffee is ready and in the cup." << endl;

    // Step 6: Plate eggs
    cout << "Step 6: Plating eggs..." << endl;
    this_thread::sleep_for(chrono::seconds(1)); // Simulate plating eggs
    cout << "Eggs are on the plate." << endl;

    // Step 7: Enjoy breakfast
    cout << "Step 7: Enjoy your breakfast!" << endl;

    return 0;
}
