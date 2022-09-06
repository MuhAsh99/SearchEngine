//
// Created by Muhammad Ashraf on 4/20/22.
//
#include "Leaf.h"

Leaf::Leaf() {
}
Leaf::Leaf(std::string s1, std::string s2) {
    key = s1;
    locations.push_back(s2);
}
bool Leaf::operator==(const std::string &s) {
    if(key == s){
        return true;
    }
}

bool Leaf::operator<(const std::string &s) {
    if(key < s){
        return true;
    }
}

bool Leaf::operator>(const std::string &s) {
    if(key > s){
        return true;
    }
}

Leaf::Leaf(std::string passed) {
    key = passed;
}

bool Leaf::operator<( Leaf passed) const {
    if(key < passed.key){
        return true;
    }
}

bool Leaf::operator==(Leaf passed) const {
    if(key == passed.key){
        return true;
    }
}

std::ostream &operator<<(std::ostream &out , Leaf &passed) {
    out << passed.key << " can be found at:" << std::endl;
    for(int i = 0; i<passed.locations.size(); i++){
        out << passed.locations[i] << ", ";
    }
    return out;
}

