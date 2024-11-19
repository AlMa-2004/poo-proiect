#include <iostream>
#include <ostream>
#include <chrono>
#include <thread>
//#include <SFML/Graphics.hpp>
#include "headers/Player.h"
#include "headers/Time.h"
using namespace std;
using namespace std::chrono;

int main() {

    // TEST TIME CLASS
    Time gameTime;
    this_thread::sleep_for(seconds(2));
    cout << "Elapsed: " << gameTime.elapsed(steady_clock::now()) << "\n";

    // TEST ANIMAL CLASS
    Animal cow("Marioara", 10, true, false);
    cout << cow << endl;

    // TEST CROP CLASS
    Crop wheat("Wheat", 3, gameTime.elapsed(steady_clock::now()), false, true);
    this_thread::sleep_for(seconds(4));
    wheat.Grow(gameTime.elapsed(steady_clock::now()));

    Crop corn("Corn", 4, gameTime.elapsed(steady_clock::now()), false, true);
    this_thread::sleep_for(seconds(2));
    corn.Grow(gameTime.elapsed(steady_clock::now()));

    // TEST ITEM CLASS
    Item i1("Wheat", 5);
    cout << i1 << endl;

    // TEST PLAYER CLASS
    Item wheatSeeds("Wheat Seeds", 20);
    // I will continue working with Item-derived functions, specifically modifying the planting functions in the player class
    Item sunflower("Sunflower", 15);
    Player player("Ana", 100, {wheatSeeds, sunflower}, {});
    cout << player << endl;

    player.addItem(Item("Wheat Seeds", 5));
    player.addItem(Item("Potato", 7));
    cout << "Inventory after adding items: \n" << player << endl;

    player.Plant("Corn Seeds", 300);
    player.Plant("Wheat Seeds", 3);  // Attempt to plant 3 seeds
    cout << "Player status after they've planted the seeds: \n" << player << endl;

    this_thread::sleep_for(seconds(3));
    cout << "Seed statuses after we've planted them: \n";
    for (auto& i : player.getField()) {
        if (!i.getName().empty()) {
            i.Grow(gameTime.elapsed(steady_clock::now()));
        }
    }

    player.Harvest();
    cout << "Player status after they've harvested the seeds: \n" << player << endl;

    Player p2(player);
    Player p3 = player;
    cout << p2 << endl << p3;

    return 0;


}