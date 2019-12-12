//
// Created by moneymaker on 12.12.2019.
//

#ifndef AKWB3_MAP_H
#define AKWB3_MAP_H

#include <iostream>
#include <vector>

using boolean = bool;


class Map{
private:
   std::vector<int> lengths;
   boolean isValid();
public:
   void readLengths();
};


#endif //AKWB3_MAP_H
