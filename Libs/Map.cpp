//    _____ _____ _____                                                 _
//   |___  |___  |___  | __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
//      / /   / /   / / '_ ` _ \ / _ \| '_ \ / _ \ | | | '_ ` _ \ / _` | |/ / _ \ '__|
//     / /   / /   / /| | | | | | (_) | | | |  __/ |_| | | | | | | (_| |   <  __/ |
//    /_/   /_/   /_/ |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
//                                                |___/

#include "Map.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>

using namespace std;

vector<int*> Map::getLengths(){
    return this->lengths;
}

vector<int*> Map::getSolution(){
    return this->solution;
}

void Map::assembleMap(int iteration, bool &found){
    bool sum_found = false;

    auto *used = new vector<bool>;
    for(int i = 0; i < this->lengths.size(); i++)
        used->push_back(false);

    for(auto v : this->solution){
        if(v == nullptr)
            cout << 0 << " ";
        else
            cout << *v << " ";
    }
    cout<< endl;
    for(int i = 0; i < this->lengths.size(); i++){
        bool num_belongs = (bool)count(this->solution.begin(), this->solution.end(), this->lengths[i]);
        if(num_belongs and not((*used)[i])){
            (*used)[i] = true;
        }
    }

    if(iteration == this->map_size - 1){
        bool temp_solution = true;
        vector<int> sums;

        for(int i = 0; i < this->map_size; i++){
            int tmp = *this->solution[i];
            sums.push_back(tmp);
            for(int j = i + 1; j < this->map_size; j++){
                int sum = tmp + *this->solution[j];
                tmp += *this->solution[j];
                sums.push_back(sum);
            }
        }
        vector<int> comparsion;
        for(auto v : this->lengths){
            comparsion.push_back(*v);
        }
        sort(sums.begin(), sums.end());
        sort(comparsion.begin(), comparsion.end());

        if(sums.size() not_eq comparsion.size()){
            temp_solution = false;
        }else{
            for(int k = 0; k < sums.size(); k++){
                if(sums[k] not_eq comparsion[k]){
                    temp_solution = false;
                    break;
                }
            }
        }

        if(temp_solution){
            cout <<endl<< "Solution found: " << endl;
            for(auto v : this->solution)
                cout << *v << " ";
            cout << endl << endl;
            found = true;
            return;
        }else{
            for(int i = 1; i < this->solution.size(); i++){
                if(this->solution[i] == nullptr){
                    this->solution[i-1] = nullptr;
                    (*used)[i-1] = false;
                    break;
                }
            }
        }
    }else{
        for(int i = 0; i < this->lengths.size(); i++){
            bool worth = true;

            // if element is not used
            if(not (*used)[i]){
                this->solution[iteration + 1] = this->lengths[i];
                for(int j = 0; j < this->map_size; j++){

                    int assembly = this->solution[j] == nullptr ? 0 : *this->solution[j];

                    for(int k = j + 1; k < this->map_size; k++){
                        int sum = this->solution[k] == nullptr ? assembly + 0 : assembly + *this->solution[k];
                        assembly += this->solution[k] == nullptr ? 0 : *this->solution[k];
//                        if(this->solution[k] == nullptr){
//                            sum = assembly + 0;
//                            assembly += 0;
//                        }else{
//                            sum = assembly + *this->solution[k];
//                            assembly += *this->solution[k];
//                        }
                        sum_found = false;
                        if(sum == 0)
                            sum_found = true;
                        else
                            for(auto val : this->lengths){
                                if(sum == *val){
                                    sum_found = true;
                                    break;
                                }
                            }
                        worth = sum_found;
                    }
                    if(not sum_found)
                        break;
                }
                if(worth){
                    assembleMap(iteration + 1, found);
                }else{
                    for(int l = iteration+1; l < this->solution.size(); l++){
                        this->solution[l] = nullptr;
                        (*used)[l] = false;
                    }
                }
            }
            if(found){
                break;
            }
        }
        delete used;
    }
}

void Map::readLengths(){
    // Read
    fstream file("input.txt", ios::in);
    if(not file.good()){
        cout << "Bad file!" << endl;
        return;
    }else{
        while(not file.eof()){
            int *len = new int;
            file >> *len;
            this->lengths.push_back(len);
        }
    }

    this->isValid();

    // Assign length and start value

    int *max1, *max2;
    if(*this->lengths[0] > *this->lengths[1]) {
        max2 = this->lengths[1];
        max1 = this->lengths[0];
    } else {
        max2 = this->lengths[0];
        max1 = this->lengths[1];
    }
    for(int i = 2; i < this->lengths.size(); i++){
        // use >= n not just > as max and second_max can hav same value. Ex:{1,2,3,3}
        if(*this->lengths[i] >= *max1){
            max2 = max1;
            max1 = this->lengths[i];
        }
        else if(*this->lengths[i] > *max2){
            max2 = this->lengths[i];
        }
    }
    this->start_chop = *max1 - *max2;
    this->seq_length = *max1;
    this->solution.resize(this->map_size);
    for(int i = 0; i < this->lengths.size(); i++){
        if(*this->lengths[i] == this->start_chop){
            this->solution[0] = this->lengths[i];
            break;
        }
    }
    shuffle(this->lengths.begin(), this->lengths.end(), std::random_device());
    //reverse(this->lengths.begin(), this->lengths.end());

    return void();
}

void Map::isValid(){
    bool valid_size = false;
    for(int i = 1; i <= this->lengths.size(); i++){
        if((i+1) * (i+2) / 2 == this->lengths.size() and *this->lengths[i-1] > 0){
            this->map_size = i + 1;
            valid_size = true;
            break;
        }else{
            continue;
        }
    }
    if(not valid_size){
        cerr << "Instance is not valid" << endl;
        exit(EXIT_FAILURE);
    }
    return void();
}