#include "IndexHandler.h"

IndexHandler::IndexHandler()
{

}

void IndexHandler::addDoc(const DocumentNode &dn)
{
    docs.push_back(dn);
}

void IndexHandler::addWord(string word, DocumentNode &docToAdd)
{
    Node search;
    search.word = word;

    if (words.contains(search)) //If the AVL tree already contains word, just add the doc to the vector
    {
        bool sameDoc = false;
        for (size_t j = 0; j < search.document.size(); j++) //Check if the doc is already inside the vector
        {
            if (search.document[j] == docToAdd)
                sameDoc = true;
        }

        if (!sameDoc)   //If its not a repeat doc
        {
            search = words.find(search);
            words.remove(words.find(search)); //remove the node from the tree then readd the updated node
            search.document.push_back(docToAdd);   
            words.insert(search);
        }
    }
    else    //Otherwise, add the doc then add the Node to the tree entirely
    {
        search.document.push_back(docToAdd);
        words.insert(search);
    }

}
void IndexHandler::addOrg(string word, DocumentNode &docToAdd )
{
    Node search;
    search.word = word;

    if (words.contains(search)) //If the AVL tree already contains word, just add the doc to the vector
    {
        bool sameDoc = false;
        if (search.document.size() > 0) //Need to check if theres a repeat doc
        {
            for (size_t j = 0; j < search.document.size(); j++)
            {
                if (search.document[j] == docToAdd)
                    sameDoc = true;
            }
        }

        if (!sameDoc)   //If its not a repeat doc
        {
            search = orgs.find(search);
            orgs.remove(orgs.find(search)); //remove the node from the tree then readd the updated node
            search.document.push_back(docToAdd);   
            orgs.insert(search);
        }
    }
    else    //Otherwise, add the doc then add the Node to the tree entirely
    {
        search.document.push_back(docToAdd);
        orgs.insert(search);
    }

    /*
    Node search;
    search.word = org;
    Node temp = orgs.find(search);
    temp.docs.push_back(docs.size() - 1);   
    orgs.insert(temp);*/

/*
    cout << "org tree: " << endl;
    orgs.prettyPrintTree();
    cout << endl;*/
}
void IndexHandler::addPerson(string word, DocumentNode &docToAdd )
{
    Node search;
    search.word = word;

    if (words.contains(search)) //If the AVL tree already contains word, just add the doc to the vector
    {
        bool sameDoc = false;
        if (search.document.size() > 0) //Need to check if theres a repeat doc
        {
            for (size_t j = 0; j < search.document.size(); j++)
            {
                if (search.document[j] == docToAdd)
                    sameDoc = true;
            }
        }

        if (!sameDoc)   //If its not a repeat doc
        {
            search = people.find(search);
            people.remove(people.find(search)); //remove the node from the tree then readd the updated node
            search.document.push_back(docToAdd);   
            people.insert(search);
        }
    }
    else    //Otherwise, add the doc then add the Node to the tree entirely
    {
        search.document.push_back(docToAdd);
        people.insert(search);
    }

    /*
    Node search;
    search.word = ppl;
    Node temp = people.find(search);
    temp.docs.push_back(docs.size() - 1);
    people.insert(temp);*/

    /*
    cout << "ppl tree:\n";
    people.prettyPrintTree();
    cout << endl;*/
}

vector<DocumentNode> IndexHandler::getWord(string word) {
    Node search;
    search.word = word;
    Node result = words.find(search);
    vector<DocumentNode> docList;
    for (size_t i = 0; i < result.document.size(); i++) {

        //Gonna be real, the only reason why this is here again is because it didnt work in the add section
        bool sameDoc = false;
        for (size_t j = 0; j < docList.size(); j++) //Check if the doc is already inside the vector
        {
            if (result.document[i] == docList[j])
                sameDoc = true;
        }

        if (!sameDoc)   //If its not a repeat doc
        {
            docList.push_back(result.document[i]);
        } 
    }
    return docList;
}
vector<DocumentNode> IndexHandler::getPerson(string ppl) {
    Node search;
    search.word = ppl;
    Node result = people.find(search);
    vector<DocumentNode> docList;
    for (size_t i = 0; i < result.document.size(); i++) {
        //Gonna be real, the only reason why this is here again is because it didnt work in the add section
        bool sameDoc = false;
        for (size_t j = 0; j < docList.size(); j++) //Check if the doc is already inside the vector
        {
            if (result.document[i] == docList[j])
                sameDoc = true;
        }

        if (!sameDoc)   //If its not a repeat doc
        {
            docList.push_back(result.document[i]);
        } 
    }
    return docList;
}
vector<DocumentNode> IndexHandler::getOrg(string o) {
    Node search;
    search.word = o;
    Node result = orgs.find(search);
    vector<DocumentNode> docList;
    for (size_t i = 0; i < result.document.size(); i++) {
        //Gonna be real, the only reason why this is here again is because it didnt work in the add section
        bool sameDoc = false;
        for (size_t j = 0; j < docList.size(); j++) //Check if the doc is already inside the vector
        {
            if (result.document[i] == docList[j])
                sameDoc = true;
        }

        if (!sameDoc)   //If its not a repeat doc
        {
            docList.push_back(result.document[i]);
        } 
    }
    return docList;
}

vector<DocumentNode> IndexHandler::getDoc()
{
    return docs;
}

int IndexHandler::getNumDocs()
{
    return docs.size();
}

int IndexHandler::getNumWords()
{
    return words.getSize();
}

bool IndexHandler::createPersistence()
{
    ofstream outWord;
    outWord.open("PersistenceWord.txt");
    ofstream outPpl;
    outPpl.open("PersistencePpl.txt");
    ofstream outOrg;
    outOrg.open("PersistenceOrg.txt");

    if (!outWord || !outPpl || !outOrg)
    {
        cout << "Error: Failed to open file";
        return false;
    }

    outWord << words.getSize() << endl;
    words.printTreeByLevel(outWord);

    outPpl << people.getSize() << endl;
    people.printTreeByLevel(outPpl);

    outOrg << orgs.getSize() << endl;
    orgs.printTreeByLevel(outOrg);

    outWord.close();
    outPpl.close();
    outOrg.close();
    clear();
    return true;
}

bool IndexHandler::loadPersistence()
{

    ifstream inWord;
    inWord.open("PersistenceWord.txt");
    ifstream inPpl;
    inPpl.open("PersistencePpl.txt");
    ifstream inOrg;
    inOrg.open("PersistenceOrg.txt");

    if (!inWord || !inPpl || !inOrg)
    {
        cout << "Error: Failed to open file";
        return false;
    }

    string count;
    getline(inWord, count);
   
    int size = stoi(count); 
    for (int i = 0; i < size; i++) {
        string word;
        int numOfDocs;

        getline(inWord, word);  //had an issue where there would be a space in front of the word, so just substr it if thats the case
        if (word[0] == ' ')
            word = word.substr(1);

        Node newNode;
        newNode.word = word;
        getline(inWord, word);
        numOfDocs = stoi(word);

        for (int j = 0; j < numOfDocs; j++)
        {
            string title, pub, author, text, uuid, url;

            getline(inWord, title);
            getline(inWord, pub);
            getline(inWord, author);
            getline(inWord, uuid);
            getline(inWord, url);
            //Create the document node with all the info and add it to the node
            DocumentNode newDoc(title, pub, author, text, uuid, url);
            newNode.document.push_back(newDoc);
        }
        words.insert(newNode);  //insert into tree
    }
    //Repeat for the ppl and org trees
    getline(inPpl, count);
    size = stoi(count);
    for (int i = 0; i < size; i++) {
        string word;
        int numOfDocs;

        getline(inPpl, word);
        if (word[0] == ' ')
            word = word.substr(1);

        Node newNode;
        newNode.word = word;

        getline(inPpl, word);
        numOfDocs = stoi(word);
        for (int j = 0; j < numOfDocs; j++)
        {
            string title, pub, author, text, uuid, url;

            getline(inPpl, title);
            getline(inPpl, pub);
            getline(inPpl, author);
            getline(inPpl, uuid);
            getline(inPpl, url);

            DocumentNode newDoc(title, pub, author, text, uuid, url);
            newNode.document.push_back(newDoc);
        }
        people.insert(newNode);
    }

    getline(inOrg, count);
    size = stoi(count);
    for (int i = 0; i < size; i++) {
        string word;
        int numOfDocs;

        getline(inOrg, word);
        if (word[0] == ' ')
            word = word.substr(1);

        Node newNode;
        newNode.word = word;

        getline(inOrg, word);
        numOfDocs = stoi(word);
        for (int j = 0; j < numOfDocs; j++)
        {
            string title, pub, author, text, uuid, url;

            getline(inOrg, title);
            getline(inOrg, pub);
            getline(inOrg, author);
            getline(inOrg, uuid);
            getline(inOrg, url);

            DocumentNode newDoc(title, pub, author, text, uuid, url);
            newNode.document.push_back(newDoc);
        }
        orgs.insert(newNode);
    }

    inWord.close();
    inPpl.close();
    inOrg.close();

    //printTrees();

    return true;
}

void IndexHandler::clear()
{
    words.makeEmpty();
    people.makeEmpty();
    orgs.makeEmpty();
}

