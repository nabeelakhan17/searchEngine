//
// Created by nabee on 11/15/2022.
//
///ds
#include "QueryEngine.h"

QueryEngine:: QueryEngine()
{

}

vector<DocumentNode> QueryEngine::parseQuery(string query, IndexHandler &ih) {
    //Separate the query into separate search terms, add them into the terms vector
    vector<string> terms;
    char delimeters[] = " ";
    char *data = new char[query.length()];
    strcpy(data, query.c_str());
    char* token = strtok(data, delimeters);
    while (token != nullptr) {
        terms.push_back(token);
        token = strtok(nullptr, delimeters);
    }  
    delete[] data;
    vector<DocumentNode> results;   //Holds the documents that are related to the query
    
    for(int i = 0; i<terms.size(); i++)
    {
        vector<DocumentNode> temp;  //Holds docs temporarily to see if they are relavent to the overall search
        bool notTerm = false;

        if(terms[i].find("person:")!= string::npos)
        {
            string remove = terms[i].substr(7, (terms[i].length() - 7)); 
          //  temp = temp documents for remove in persons
          temp = ih.getPerson(remove);
        }
        else if(terms[i].find("org:")!= string::npos )
        {
            string remove = terms[i].substr(4, (terms[i].length() - 4));
            temp = ih.getOrg(remove);
        }
        else if (terms[i][0] == '-')
        {
            string remove = terms[i].substr(1, (terms[i].length() - 1));
            temp = ih.getWord(remove);
            notTerm = true;
        }
        else    //If the word is on its own (no PERSON, ORG or -) collect it 
        {
            temp = ih.getWord(terms[i]);


            if (i == 0)
                for (size_t i = 0; i < temp.size(); i++)
                    results.push_back(temp[i]);
            else
                results = intersect(results, temp);
        }

        if (notTerm)
        {
             results = removeNot(results, temp);
             notTerm = false;
        }
        else if (i > 0) //intersect the documents if there are two or more terms
        {
             results = intersect(results, temp);
        }
    }
    delete[]token;

    return results;    
}

vector<DocumentNode> QueryEngine::intersect(vector<DocumentNode> one, vector<DocumentNode> two)
{
    vector<DocumentNode> combined;
    for(int i = 0; i< one.size(); i++)
    {
        for(int j =0; j< two.size(); j++)
        {
            if(one[i] == two[j])    //If the docs are the same in both vectors, add it
            {
                combined.push_back(two[j]);
            }
        }
    }
    return combined;
}

int QueryEngine::getRelevance()
{
    return -1;
}

vector<DocumentNode> QueryEngine::removeNot(vector<DocumentNode> one, vector<DocumentNode> two)
{
    vector<DocumentNode> combined;
    for(int i = 0; i< one.size(); i++)
    {
        bool found = false;
        for(int j =0; j< two.size(); j++)
        {
            if(one[i] == two[j])
            {
                found = true;
                break;
            }
        }
        if (!found) {   //Only add vectors that are not included in vector two
            combined.push_back(one[i]);
        }
    }
    return combined;
}

