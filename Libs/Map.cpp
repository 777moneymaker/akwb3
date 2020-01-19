//    _____ _____ _____                                                 _
//   |___  |___  |___  | __ ___   ___  _ __   ___ _   _ _ __ ___   __ _| | _____ _ __
//      / /   / /   / / '_ ` _ \ / _ \| '_ \ / _ \ | | | '_ ` _ \ / _` | |/ / _ \ '__|
//     / /   / /   / /| | | | | | (_) | | | |  __/ |_| | | | | | | (_| |   <  __/ |
//    /_/   /_/   /_/ |_| |_| |_|\___/|_| |_|\___|\__, |_| |_| |_|\__,_|_|\_\___|_|
//                                                |___/

#include "Map.hpp"
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

vector<int> Map::getLengths(){
    return this->lengths;
}

vector<int> Map::getSolution(){
    return this->solution;
}

void Map::assembleMap(int iteration, bool &found){
    int number;
    bool sum_found = false;

    auto *used = new vector<bool>;

    for(int i = 0; i < this->lengths.size(); i++)
        (*used).push_back(false);

    for(int i = 0; i < this->lengths.size(); i++){
        if(count(this->solution.begin(), this->solution.end(), this->lengths[i])){
            if(not(*used)[i]){
                (*used)[i] = true;
                break;
            }
        }
    }

    if(iteration == this->map_size - 1){
        bool temp_solution = true;
        vector<int> sums;

        for(int i = 0; i < this->map_size; i++){
            int tmp = this->solution[i];
            sums.push_back(tmp);
            for(int j = i + 1; j < this->map_size; j++){
                int sum = tmp + this->solution[j];
                tmp += this->solution[j];
                sums.push_back(sum);
            }
        }
        auto *comparsion = new vector<int>;
        *comparsion = this->lengths;
        sort(sums.begin(), sums.end());
        sort(comparsion->begin(), comparsion->end());

        if(sums.size() not_eq comparsion->size()){
            temp_solution = false;
            delete comparsion;
        }else{
            for(int k = 0; k < sums.size(); k++){
                if(sums[k] not_eq (*comparsion)[k]){
                    temp_solution = false;
                    delete comparsion;
                    break;
                }
            }
        }

        if(temp_solution){
            cout <<endl<< "Solution found: " << endl;
            sort(this->solution.begin(), this->solution.end());
            for(auto &v : this->solution)
                cout << v << " ";
            cout << endl << endl;
            found = true;
            return;
        }else{
            int wrong_num = this->solution[iteration];
            for(int i = 0; i < this->lengths.size(); i++){
                if(wrong_num == this->lengths[i]){
                    for(int j = i; j < this->solution.size(); j++){
                        this->solution[j] = 0;
                        (*used)[j] = false;
                    }
                    break;
                }
            }
        }
    }else{
        // for every element
        for(int i = 0; i < this->lengths.size(); i++){
            bool worth = true;

            // if element is not used
            if(not(*used)[i]){
                number = this->lengths[i];
                this->solution[iteration + 1] = number;
                for(int j = 0; j < this->map_size; j++){
                    int assembly = this->solution[j];
                    for(int k = j + 1; k < this->map_size; k++){
                        int sum = assembly + this->solution[k];
                        assembly += this->solution[k];
                        sum_found = false;
                        if(sum == 0)
                            sum_found = true;
                        else
                            for(auto &val : this->lengths){
                                if(sum == val){
                                    sum_found = true;
                                    break;
                                }
                            }
                        if(not sum_found){
                            worth = false;
                        }else{
                            worth = true;
                        }
                    }
                    if(not(sum_found))
                    break;
                }
                if(worth){
                    assembleMap(iteration + 1, found);
                }else{
                    for(int i = iteration+1; i < this->solution.size(); i++){
                        this->solution[i] = 0;
                    }
                }
            }
            if(found){
                break;
            }
        }
    }
}

void Map::readLengths(){
    // Read
    int len;
    fstream file("input.txt", ios::in);
    if(not file.good()){
        cout << "Bad file!" << endl;
        return;
    }else{
        while(not file.eof()){
            file >> len;
            this->lengths.push_back(len);
        }
    }

    this->isValid();

    // Assign length and start value
    auto *tmp = new vector<int>;
    *tmp = this->lengths;

    this->seq_length = *max_element(tmp->begin(), tmp->end());
    tmp->erase(find(tmp->begin(), tmp->end(), this->seq_length));
    this->start_chop = this->seq_length - *max_element(tmp->begin(), tmp->end());
    this->solution.resize(this->map_size);
    this->solution[0] = this->start_chop;
    //shuffle(this->lengths.begin(), this->lengths.end(), std::random_device());
    //reverse(this->lengths.begin(), this->lengths.end());
    delete tmp;

    return void();
}

void Map::isValid(){
    bool valid_size = false;
    for(int i = 1; i <= this->lengths.size(); i++){
        if((i+1) * (i+2) / 2 == this->lengths.size() and this->lengths[i-1] > 0){
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