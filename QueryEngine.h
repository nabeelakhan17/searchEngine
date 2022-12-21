//
// Created by nabee on 11/15/2022.
//
//dsds
#ifndef ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_QUERYENGINE_H
#define ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_QUERYENGINE_H

#include "IndexHandler.h"
#include <vector>

class QueryEngine {
private:

public:
    QueryEngine();
    vector<DocumentNode> parseQuery(string query, IndexHandler &ih);
    vector<DocumentNode> intersect(vector<DocumentNode> one, vector<DocumentNode> two);
    vector<DocumentNode> removeNot(vector<DocumentNode> one, vector<DocumentNode> two);
    int getRelevance();
};


#endif //ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_QUERYENGINE_H
