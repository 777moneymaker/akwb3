//    _____ _____ _____                                                 _
//   |___  |___  |___  | __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
//      / /   / /   / / '_ ` _ \ / _ \| '_ \ / _ \ | | | '_ ` _ \ / _` | |/ / _ \ '__|
//     / /   / /   / /| | | | | | (_) | | | |  __/ |_| | | | | | | (_| |   <  __/ |
//    /_/   /_/   /_/ |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
//                                                |___/

#include <iostream>
#include "Libs/Map.hpp"

using namespace std;

int main() {
    bool found = false;
    auto *M = new Map;
    M->readLengths();

    cout << endl << "Searching for solution..." << endl << endl;

    // Time measure and main function.
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    M->assembleMap(0, found);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    // Print time.
    cout << "Time: " << endl
         << chrono::duration_cast<chrono::seconds>(end - begin).count() << "[s]" << endl
         << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl
         << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "[ns]" << endl;

    return 0;
}