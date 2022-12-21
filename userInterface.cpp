//
// Created by nabee on 11/28/2022.
//

#include "UserInterface.h"

/**
 * @brief called from the main method. Starts running the program
 * 
 */
void UserInterface::run()
{
    string fileName = "";
    int userIn = 4;

    while (userIn != 0)
    {
        cout << endl << "Enter a number for the following:" << endl << "\t1. Enter query" << endl
            << "\t2. Save current index" << endl << "\t3. Load current index" << endl
            << "\t4. Create index" << endl << "\t0. quit" << endl;
        cin >> userIn;
        getline(cin, fileName);

        if (userIn == 1)
        {
            enterQuery();
        }
        else if (userIn == 2)
        {
            writeIndex();
        }
        else if (userIn == 3)
        {
            loadIndex();
        }
        else if (userIn == 4)
        {
            cout << "Enter the file path name to create the index: " << endl;
            getline(cin, fileName);

            createIndex(fileName);
        }
    }
}

/**
 * @brief Reads in the documents and assigns words into the AVL Tree
 * 
 */
void UserInterface::createIndex(const string &path)
{
    dp.browseDirectory(path, ih);   
}

/**
 * @brief loads the persistence so that each of the AVL trees are filled out without 
 * having to read each file individually
 */
void UserInterface::loadIndex()
{
    ih.loadPersistence();
}

/**
 * @brief writes to the persistence and saves what has already been added in the tree?
 * 
 */
void UserInterface::writeIndex()
{
    ih.createPersistence();
}

/**
 * @brief Ask user for query, run the search engine
 * 
 */
void UserInterface::enterQuery()
{
    //ih.printTrees();
    string userQu = "";
    cout << "Enter query: ";
    getline(cin, userQu);
    transform(userQu.begin(), userQu.end(), userQu.begin(), ::tolower); //Convert query to lowercase

    outputStats(qe.parseQuery(userQu, ih));
}

/**
 * @brief given a vector of Document Nodes, print out the results to the user so that
 * they can see their relevant docs
 */
void UserInterface::outputStats(vector<DocumentNode> docs)
{
    for (size_t i = 0; i < docs.size(); i++)
    {
        cout << endl << docs[i].getTitle() << " by " << docs[i].getAuthor() << endl << docs[i].getUrl() << endl;
    }
    cout << endl;
}

