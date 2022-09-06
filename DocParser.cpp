//
// Created by Muhammad Ashraf on 4/6/22.
//

#include "DocParser.h"
#include "porter2_stemmer.h"
#include <string>
#include <utility>
#include <set>

DocParser::DocParser(){

}
void DocParser::Parser(std::string& filename) {
  
    std::ifstream ifs(filename);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document document;
    document.ParseStream(isw);

    std::string id = document["uuid"].GetString();
    std::string titleName = document["title"].GetString();
    std::string bodyText = document["text"].GetString();
    std::string author = document["author"].GetString();
//do we need these still after map??
    //need to create map of uuid to filepath instead and reparse the document to print for the GUI output
    docsUUID.insert(make_pair(id, filename));
    //populate trees for people
    const rapidjson::Value& persons = document["entities"]["persons"];
    vector<string> p;
    for (int i = 0; i < persons.Size(); i++) {
        string name = persons[i]["name"].GetString();
        //std::cout<<name<<std::endl;
        Leaf temp(name);
        p.push_back(name);
        if(personTree.contains(temp)){
            try{
                if (find(personTree.find(temp).locations.begin(), personTree.find(temp).locations.end(), id) == personTree.find(temp).locations.end()) {
                    personTree.find(temp).locations.push_back(id);
                }
            }
            catch(exception e){cout << temp.key <<endl;}


        }
        else{
            Leaf temp(name, id);
            personTree.insert(temp);
        }
    }

    //populate tree for orgs
    vector<string> o;
     const rapidjson::Value& organizations = document["entities"]["organizations"];
     for(int i = 0; i < organizations.Size(); i++) {
         string orgs = organizations[i]["name"].GetString();
          //std::cout<<orgs<<std::endl;
          //we need only the first word from the org i think he said in class
         Leaf temp(orgs);
         o.push_back(orgs);
         if(orgTree.contains(temp)){
            try{
                if (find(orgTree.find(temp).locations.begin(), orgTree.find(temp).locations.end(), id) == orgTree.find(temp).locations.end()) {
                    orgTree.find(temp).locations.push_back(id);
                }
            }
            catch(exception e){cout << temp.key <<endl;}


        }
        else{
            Leaf temp(orgs, id);
            orgTree.insert(temp);
        }
    }




   // tree for text that removes stop words, stems, and inserts into tree
    std::vector<std::string> tokens = tokenize(bodyText.c_str());
    stripStopWordsAndCompact(tokens);
    //populate docs
    vector<string> words;
    for(int i = 0; i< tokens.size(); i++){
        Porter2Stemmer::stem(tokens[i]);
        words.push_back(tokens[i]);
        Leaf temp(tokens[i]);
        if(tree.contains(temp)){
            try{
                if (find(tree.find(temp).locations.begin(), tree.find(temp).locations.end(), id) == tree.find(temp).locations.end()) {
                    tree.find(temp).locations.push_back(id);
                }
            }
            catch(exception e){cout << temp.key <<endl;}


        }
        else{
            Leaf temp(tokens[i], id);
            tree.insert(temp);
        }
    }
    //Docs[id] = words;
    ifs.close();


}



void DocParser::open_dir_using_dirent(const std::string &directory) {
    using namespace std;
    string filepath;
    DIR *dp;
    struct dirent *dirp; // the directory file
    struct stat filestat;
    dp = opendir(directory.c_str()); // open the directory
    if (dp == nullptr) // check and see if there was an error opening a given directory
    {
        cout << "Error(" << errno << ") opening " << directory << endl;
    }

    int i = 0;
    while ((dirp = readdir(dp)) != nullptr) // while files exist in the directory
    {
        if(i == 1 || i == 0) { // this is necessary because the first 2 lines that it tries to read are <directory>/. and <directory>/..
            i++;
            continue;
        }

        filepath = directory + "/" + dirp->d_name;

        // If the file is a directory (or is in some way invalid) we'll skip it
        if (stat(filepath.c_str(), &filestat)) continue;
        if (S_ISDIR(filestat.st_mode))  { //If the file is a directory, recursive call to this function
            open_dir_using_dirent(filepath);
        } else {
            if(this->endsWith(filepath, ".json")){
//                cout  <<"Parsing..."<< filepath <<" ";
                Parser(filepath);
//                cout << " Finished" <<endl; //else print out the name of the file
            }
            else{
                cout<<"Invalid file: "<<filepath<<endl;
            }
        }
    }
    closedir(dp); // closing the director
}

// https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
bool DocParser::endsWith(const string& a, const string& b) {
    if (b.size() > a.size()) return false;
    return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

void DocParser::stripStopWordsAndCompact( std::vector<std::string>& words )
{
    static std::ifstream sw_file( "../include/StopWords.txt" ) ;
    static std::istream_iterator<std::string> begin(sw_file), end ;
    static const std::unordered_set<std::string> stopwords( begin, end ) ;
    static const auto empty_or_stopword = []( const std::string& word )
    { return ( word.size() < 2U ) || ( stopwords.find(word) != stopwords.end() ) ; } ;

    words.erase( std::remove_if( words.begin(), words.end(), empty_or_stopword ), words.end() ) ;
}

std::vector<std::string> DocParser::tokenize(const char* input) {
    char * temp;
    char copy[100000];
    strcpy(copy, input);
    vector<string> tokens; //how to fix???
    temp = strtok(copy, " ,.-!_");
    while(temp != nullptr){
        tokens.push_back(temp);
        temp = strtok(nullptr, " ,._");
    }
    return tokens;
}

set<string> DocParser::reportQuery(std::string passed) {
    Leaf query(std::move(passed));
    set<string> ids;
    //variable for relevancy
    int relevancy;
    std::vector<std::string> toPrint;
    if(tree.contains(query)){
        toPrint = tree.find(query).locations;
        //need to stem query before using this function
        //cout << "Query for 'war' contained in:" << endl; //need to fix
    }

    //for loop to add relevancies
    for(int i = 0; i< toPrint.size(); i++ ){
        relevancy = Relevency(toPrint.at(i), query.key);
       // std::cout<<relevancy<<" "<<toPrint.at(i) << endl;
        ids.insert(toPrint.at(i));
    }
    return ids;
}

set<string> DocParser::reportQuery2(std::string passed) {
    Leaf query(std::move(passed));
    set<string> ids;
    std::vector<std::string> toPrint;
    if(personTree.contains(query)){
        toPrint = personTree.find(query).locations;
       // cout << "Query for 'sheeran' contained in:" << endl; //need to fix
    }
    for(int i = 0; i< toPrint.size(); i++ ){
       // cout << toPrint[i] << endl;
        ids.insert(toPrint.at(i));
    }
  //  Relevency(filename, query);
    return ids;
}

set<string> DocParser::reportQuery3(std::string passed) {
    Leaf query(std::move(passed));
    set<string> ids;
    std::vector<std::string> toPrint;
    if(orgTree.contains(query)){
        toPrint = orgTree.find(query).locations;
       // cout << "Query for 'nasa' contained in:" << endl; //need to fix
    }
    for(int i = 0; i< toPrint.size(); i++ ){
       // cout << toPrint[i] << endl;
        ids.insert(toPrint.at(i));
    }
    return ids;
}

int DocParser::Relevency(std::string id, std::string& query) {
    //take in the query
//    for(int i = 0; i < lo)
    //go through docs and find freq
    //rank docs with highest freq of word
    //sort based on freq in docs
    if (Docs.find(id) != Docs.end()) {
        return std::count(Docs[id].getFileText().begin(), Docs[id].getFileText().end(), query);
    } else {
        return 0;
    }

}

void DocParser::queryProcessor(std::string fullQuery) {
    using namespace std;
    AVLtree<string> boolean;
    boolean.insert("AND");
    boolean.insert("OR");
    boolean.insert("NOT");
    boolean.insert("ORG");
    boolean.insert("PERSON");


    vector<string> byWord = tokenize(fullQuery.c_str());
    //vector that is used to iterate through term that is queried, used for relevancy
    vector<string> searchTerms;
    if(byWord.size() == 1){
        Porter2Stemmer::stem(fullQuery);
        //push back the query into searchTerm vec
        searchTerms.push_back(fullQuery);
        matches = reportQuery(fullQuery);
    }
    else{
        for(int i = 0; i< byWord.size(); i++){
            if(byWord[i] == "AND"){
                if(i+1 == byWord.size()){return;}
                i++;
                do{
                    Porter2Stemmer::stem(byWord[i]);
                    //push back index of byWord into searchTerms
                    searchTerms.push_back(byWord[i]);
                    if(matches.empty()){
                        matches = reportQuery(byWord[i]);
                    }
                    else{
                        set<string> temp = reportQuery(byWord[i]);
                        set<string> dest;
                        //iterator from first and sec and gives iterator of intersection
                        set_intersection(matches.begin(),matches.end(), temp.begin(),temp.end(), inserter(dest, dest.begin()) );
                        matches = dest;
                        //matches = matches && reportQuery(byWord[i]);
                    }
                    if(i+1 == byWord.size()){return;}
                    //if no other word quit
                    i++;
                }
                while(!boolean.contains(byWord[i]));
                //take mult words
                //for rel- logic that increases counter when try
                i--;
            }
            else if(byWord[i] == "OR"){
                if(i+1 == byWord.size()){return;}
                i++;
                do{
                    Porter2Stemmer::stem(byWord[i]);
                    //push back index of byWord into searchTerms
                    searchTerms.push_back(byWord[i]);
                    if(matches.empty()){
                        matches = reportQuery(byWord[i]);
                    }
                    else{
                        set<string> temp = reportQuery(byWord[i]);
                        set<string> dest;
                        set_union(matches.begin(),matches.end(), temp.begin(),temp.end(), inserter(dest, dest.begin()) );
                        matches = dest;
                        //matches = matches || reportQuery(byWord[i]);
                    }
                    if(i+1 == byWord.size()){return;}
                    i++;
                }
                while(!boolean.contains(byWord[i]));
                i--;
            }
            else if(byWord[i] == "NOT"){
                if(i+1 == byWord.size()){return;}
                i++;
                do{
                    Porter2Stemmer::stem(byWord[i]);
                    set<string> temp = reportQuery(byWord[i]);
                    set<string> dest;
                    set_difference(matches.begin(),matches.end(), temp.begin(),temp.end(), inserter(dest, dest.begin()) );
                    matches = dest;
                    //matches = matches - reportQuery(byWord[i]);
                    if(i+1 == byWord.size()){return;}
                    i++;
                }
                while(!boolean.contains(byWord[i]));
                i--;
            }
            else if(byWord[i] == "ORG"){
                if(i+1 == byWord.size()){return;}
                i++;
                Porter2Stemmer::stem(byWord[i]);
                if(matches.empty()){
                    matches = reportQuery3(byWord[i]);
                }
                else{
                    set<string> temp = reportQuery3(byWord[i]);
                    set<string> dest;
                    set_intersection(matches.begin(),matches.end(), temp.begin(),temp.end(), inserter(dest, dest.begin()) );
                    matches = dest;
                    //matches = matches && reportQuery3(byWord[i]);
                }
            }
            else if(byWord[i] == "PERSON"){
                if(i+1 == byWord.size()){return;}
                i++;
                Porter2Stemmer::stem(byWord[i]);
                if(matches.empty()){
                    matches = reportQuery2(byWord[i]);
                }
                else{
                    set<string> temp = reportQuery2(byWord[i]);
                    set<string> dest;
                    set_intersection(matches.begin(),matches.end(), temp.begin(),temp.end(), inserter(dest, dest.begin()) );
                    matches = dest;
                    //matches = matches && reportQuery2(byWord[i]);
                }
            }
            else{
                Porter2Stemmer::stem(byWord[i]);
                matches = reportQuery(byWord[i]);//this is when only one search word is present( no AND || OR)
            }
        }
    }

    //clear vector
    relevancies.clear();
    //iterate through set
    for (auto it=matches.begin(); it != matches.end(); ++it) {
        int rel = 0;
        //add relevancy with function, i think the Relevancy function is where the issue is
        for (int i = 0; i < searchTerms.size(); i++) {
            rel += Relevency(*it, searchTerms.at(i));
        }
        relevancies.push_back(rel);
    }
}

void DocParser::showMatches() {
    cout << "Matches: " << endl;
    int index = 0;
    //outputs 0 instead of num of relevancy
    for (auto it=matches.begin(); it != matches.end(); ++it) {
        cout << ' ' << *it<< " "<< relevancies.at(index) << endl;
        index++;
    }

}

void DocParser::showDocMap() {
    std::cout << endl << "{" << "uuid" << ": " << "filepath" << "}\n";
    for (auto const &pair: docsUUID) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";

    }
}















