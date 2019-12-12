//
// Created by moneymaker on 12.12.2019.
//

#include "Map.h++"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

void Map::readLengths(){
    int len;
    std::fstream file("map.txt", std::ios::in);
    if(not(file.good())){
        std::cout << "Bad file!" << std::endl;
        return;
    }else{
        while(not(file.eof())){
            file >> len;
            this->lengths.push_back(len);
        }
    }
    for(auto &c : this->lengths){
        std::cout << c << std::endl;
    }
    this->isValid();
    return void();
}

boolean Map::isValid(){
    std::vector<int> tmp;
    sort(tmp.begin(), tmp.end());

    for(auto &c : this->lengths){
        if(not(count(tmp.begin(), tmp.end(), c))){
            tmp.push_back(c);
        }
    }
    // TODO Check If values are valid.
    return true;
}