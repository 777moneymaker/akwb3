//    _____ _____ _____                                                 _
//   |___  |___  |___  | __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
//      / /   / /   / / '_ ` _ \ / _ \| '_ \ / _ \ | | | '_ ` _ \ / _` | |/ / _ \ '__|
//     / /   / /   / /| | | | | | (_) | | | |  __/ |_| | | | | | | (_| |   <  __/ |
//    /_/   /_/   /_/ |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
//                                                |___/

#ifndef AKWB3_MAP_HPP
#define AKWB3_MAP_HPP

#include <iostream>
#include <vector>

class Map{
private:
    int seq_length, map_size, start_chop;
    std::vector<int> lengths;
    std::vector<int> solution;

    void isValid();

public:
    void readLengths();

    void assembleMap(int iteration, bool &found);

    std::vector<int> getSolution();
    std::vector<int> getLengths();
};


#endif //AKWB3_MAP_HPP
