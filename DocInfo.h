//
// Created by Muhammad Ashraf on 4/18/22.
//

#ifndef INC_22S_FINAL_PROJ_DOCINFO_H
#define INC_22S_FINAL_PROJ_DOCINFO_H
#include <string>
#include <vector>


class DocInfo {
    //for id
    //-in node, word, vector of doc id,
    //when insert word, search tree to see if it exists in tree, if no exist create defualt node with
    // string being word and doc id being length 1
    //if node does exist
    //

public:
    DocInfo() {}
    DocInfo(std::string IDP, std::vector<std::string> textP, std::vector<std::string> authorP, std::vector<std::string> organizationP);
    bool operator ==(std::string d) const;
    void setDocId(std::string Id);
    std::string getDocId();

    void setText(std::string fileText);
    std::vector<std::string>& getFileText();
    DocInfo& operator=(DocInfo d);
    bool operator>(std::string d) const;
    bool operator<(std::string d) const;



private:
    std::string docID;
    std::vector<std::string> text;
    std::vector<std::string> persons;
    std::vector<std::string> organization;




};


#endif //INC_22S_FINAL_PROJ_DOCINFO_H
