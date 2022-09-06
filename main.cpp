// rapidjson/example/simpledom/simpledom.cpp`
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
#include <unordered_set>
#include "include/rapidjson/document.h"

using namespace std;

#include "DocParser.h"
#include "AVLtree.h"
#include "UserInterface.h"

#include "catch_setup.h"
#include "porter2_stemmer.h"

using namespace rapidjson;


int main(int argc, char** argv) {

    UserInterface Dr_Fontenot;
    Dr_Fontenot.Menu();

    return 0;
}
