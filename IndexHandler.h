#ifndef ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_INDEXHANDLER_H
#define ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_INDEXHANDLER_H

#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include "AVLTree.h"
#include "Node.h"

using namespace std;

class IndexHandler
{
private:
    AvlTree<Node> words;
    AvlTree<Node> people;
    AvlTree<Node> orgs;
    vector<DocumentNode> docs;
    
public:
    IndexHandler();
    void addDoc(const DocumentNode &dn);

    vector<DocumentNode> getWord(string);
    vector<DocumentNode> getPerson(string);
    vector<DocumentNode> getOrg(string);
    vector<DocumentNode> getDoc();

    void addWord(string, DocumentNode &docToAdd);
    void addPerson(string, DocumentNode &docToAdd);
    void addOrg(string, DocumentNode &docToAdd);

    int getNumDocs();
    int getNumWords();
    bool createPersistence();
    bool loadPersistence();
    void clear();
    void printTrees()
    {
        cout << "Word\n";
        words.prettyPrintTree();
        cout <<"ppl"<< endl;
        people.prettyPrintTree();
        cout <<"org"<< endl;
        orgs.prettyPrintTree();
        cout << endl;
    }
};

#endif
