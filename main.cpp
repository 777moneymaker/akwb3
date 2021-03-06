//    _____ _____ _____                                                 _
//   |___  |___  |___  | __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
//      / /   / /   / / '_ ` _ \ / _ \| '_ \ / _ \ | | | '_ ` _ \ / _` | |/ / _ \ '__|
//     / /   / /   / /| | | | | | (_) | | | |  __/ |_| | | | | | | (_| |   <  __/ |
//    /_/   /_/   /_/ |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
//                                                |___/

#include <iostream>
#include <fstream>
#include "Libs/Map.hpp"
#include <chrono>
#include <algorithm>

using namespace std;

int main() {
    bool found = false;
    Map *M = new Map;
    M->readLengths();
    cout << endl << "Searching for solution..." << endl << endl;
    // 1, 1, 1, 1, 1, 1, 9, 4, 7, 2, 8
    // Time measure and main function.
    auto begin = chrono::high_resolution_clock::now();

    M->assembleMap(0, found);

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> time_sec = end - begin;
    chrono::duration<double, milli> time_micro = end - begin;

    auto solution = M->getSolution();
    auto lengths = M->getLengths();
    if(not found){
        cerr << "Instance has no solution - it contains error(s)." << endl;
    }

    // Print time.
    cout << "Time: " << endl
        << time_sec.count() << "[s]" << endl
        << time_micro.count() << "[ms]" << endl << endl;

    delete M;
    return 0;
}