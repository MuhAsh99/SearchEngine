//
// Created by Muhammad Ashraf on 4/18/22.
//

#include "DocInfo.h"


void DocInfo::setDocId(std::string Id) {
        docID = Id;
}


std::string DocInfo::getDocId() {
    return docID;
}


void DocInfo::setText(std::string fileText) {
        text.push_back(fileText);
}


std::vector<std::string>& DocInfo::getFileText() {
    return text;
}

DocInfo::DocInfo(std::string IDP, std::vector<std::string> textP, std::vector<std::string> personP,
                 std::vector<std::string> organizationP) {
    docID = IDP;
    text = textP;
    persons = personP;
    organization = organizationP;
}

bool DocInfo::operator==(std::string d) const {
    return docID == d;
}

bool DocInfo::operator>(std::string d) const {
    return docID > d;
}

bool DocInfo::operator<(std::string d) const {
    return docID < d;
}

DocInfo& DocInfo::operator=(DocInfo d) {
    docID = d.docID;
    persons = d.persons;
    organization = d.organization;
    text = d.text;
    return *this;
}








