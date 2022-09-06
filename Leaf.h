//
// Created by Muhammad Ashraf on 4/20/22.
//

#ifndef INC_22S_FINAL_PROJ_LEAF_H
#define INC_22S_FINAL_PROJ_LEAF_H
#include <string>
#include <vector>
#include "ostream"

class Leaf{

public:
    Leaf();
    Leaf(std::string, std::string);
    bool operator ==(const std::string& s);
    bool operator <(const std::string& s);
    bool operator >(const std::string& s);
     bool operator ==(Leaf) const;
     bool operator <(Leaf) const;
    Leaf(std::string);

    std::string key;
    std::vector<std::string> locations;

    friend std::ostream& operator<< (std::ostream&, Leaf&);

private:



};



#endif //INC_22S_FINAL_PROJ_LEAF_H
