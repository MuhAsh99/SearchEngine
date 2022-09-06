//
// Created by Ross Garrett on 4/20/22.
//

#include "catch.hpp"
#include "AVLtree.h"
#include "DocParser.h"

//TEST_CASE("AVLtree"){
//    AVLtree<std::string> test;
//    std::string a = "word";
//    std::string b = "word1";
//    std::string c = "word";
//    if(test.contains(a)){
//        test.find(a).push_back("a");
//    }
//    else{
//        test.insert(a);
//        test.find(a).push_back("a");
//    }
//    if(test.contains(b)){
//        test.find(b).push_back("b");
//    }
//    else{
//        test.insert(b);
//        test.find(b).push_back("b");
//    }
//    if(test.contains(c)){
//        test.find(c).push_back("c");
//    }
//    else{
//        test.insert(c);
//        test.find(c).push_back("c");
//    }
//    test.print();
//
//
//}
TEST_CASE("tokenize"){
    DocParser test;
    string totoken = "AND time computer";
    vector<string> toPrint = test.tokenize(totoken.c_str());
    for(int i =0; i< toPrint.size(); i++){
        cout << toPrint[i] << " ";
    }

}