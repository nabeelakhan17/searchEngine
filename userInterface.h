//
// Created by nabee on 11/28/2022.
//

#ifndef ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_USERINTERFACE_H
#define ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_USERINTERFACE_H

#include "DocumentParser.h"
#include "IndexHandler.h"
#include "QueryEngine.h"

class UserInterface {
private:
    IndexHandler ih;
    DocumentParser dp;
    QueryEngine qe;

public:
    void run();
    void createIndex(const string &path);
    void loadIndex();
    void writeIndex();
    void enterQuery();
    void outputStats(vector<DocumentNode>);
};


#endif //ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_USERINTERFACE_H
