//
// Created by Muhammad Ashraf on 4/6/22.
//

#ifndef INC_22S_FINAL_PROJ_DOCPARSER_H
#define INC_22S_FINAL_PROJ_DOCPARSER_H
#include "include/rapidjson/document.h"
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/istreamwrapper.h"
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include "dirent.h"
#include "unordered_set"
#include "AVLtree.h"
#include <iterator>
#include <algorithm>
#include "DocInfo.h"
#include "sys/stat.h"
#include "Leaf.h"
#include <map>
#include <set>

using namespace std;
class DocParser{
public:

    DocParser();
    void Parser(std::string& filename);
    void open_dir_using_dirent(const std::string& directory);
    std::vector<std::string> tokenize(const char*);
//    void addStopWords();
    void stripStopWordsAndCompact( std::vector<std::string>& words );
    bool endsWith(const string& s, const string& suffix);
    //void removeStopWords(std::vector<std::string>& words);
    set<string> reportQuery(std::string passed);
    set<string> reportQuery2(std::string passed);
    set<string> reportQuery3(std::string passed);

    int  Relevency(std::string filename, std::string& query);

    void queryProcessor(std::string fullQuery);
    void showMatches();
    void showDocMap();


    //for persistence file
    //to get data from pers
    //-has nums a top, use getline
    //need two nums for stats
    //while loop until end of persi file, getting word and num of docs it is in
    //getline of temp words with delim for word and num
    //put word into the tree, vec of strings for docs
    //getline of delim that gets num
    //for loop of i < numFiles
    //keep running until gets all files and pushed back into document vector
    //maybe do same for people and orgs, 3 peristece files
    //




private:
    AVLtree<Leaf> tree;
    AVLtree<Leaf> personTree;
    AVLtree<Leaf> orgTree;
    map<string, string> docsUUID;
    set<string> matches;
    map<string, DocInfo> Docs;
    vector<int> relevancies;
};

#endif //INC_22S_FINAL_PROJ_DOCPARSER_H



// SOlution 1: Create a Word class and overload the comparision operators (==)(<)
// solution 2: Create a set() to store the words that you already inserted into the tree, so you do the search on the vector instead of the tree to see if it exisits