//
// Created by nabee on 11/21/2022.
//

#ifndef ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_NODE_H
#define ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_NODE_H
#include "DocumentNode.h"
#include <vector>

using namespace std;

/*
Node is a class that consists of a string and a vector of Document Nodes. It is
used in the creation of the AVL Tree so that we can keep the list of documents attached to the words
*/
class Node {
public:
    string word;
    vector<int> docs;
    vector<DocumentNode> document;

    vector<DocumentNode> getDocuments()
    {
        return document;
    }

    bool operator<(const Node&);
    bool operator>(const Node&);
    bool operator==(const Node&);
    void operator=(const Node&);

    friend ostream &operator<<(ostream &, Node&);
};


#endif //ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_NODE_H
