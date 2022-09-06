//
// Created by Muhammad Ashraf on 4/26/22.
//

#include "UserInterface.h"



void UserInterface::Menu() {
    //cout << "query:" << query;
    DocParser fontenot;
    cout<<"Welcome to our Search Engine! Please select an option: "<<endl;
    while (true) {
        cout<<endl;
        cout<<"1. Parse information"<<endl;
        cout<<"2. Enter a query"<<endl;
        cout<<"3. Exit"<<endl;
        getline(cin, choice);
        switch (choice[0]) {
            case '1':
                cout<<"Enter directory path: "<<endl;
                getline(cin, helpMe);
                cout<<"Parsing..."<<std::endl;
                fontenot.open_dir_using_dirent(helpMe);
                break;
            case '2':
                cout<<"Enter a query: "<<endl;
                getline(cin, query);
                fontenot.queryProcessor(query);
                fontenot.showDocMap();
                fontenot.showMatches();
                //need to get it to ask for other options after querying
                break;
            case '3':
                cout<<"Bye bye, i miss you already, come back soon. "<<endl;
                return;
            default:
                cout<<"Not a valid choice, please try again."<<endl;
                break;
        }
    }




}
