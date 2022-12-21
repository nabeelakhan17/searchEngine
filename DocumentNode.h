#ifndef ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_DOCUMENTNODE_H
#define ASSIGNMENT_4_SEARCH_ENGINE_NABEELA_KATHERINE_DOCUMENTNODE_H

#include <iostream>
#include <string.h>
using namespace std;

/*
DocumentNode is a class that incorporates the important/noteworthy aspects of the JSON file
*/
class DocumentNode
{
    private:
        string title;
        string publication;
        string author;
        string text;
        string uuid;
        string url;
    public:

        DocumentNode()
        {
            title = "";
            publication = "";
            author = "";
            text = "";
            uuid = "";
            url = "";
        }
        
        DocumentNode(string titleIn, string pubIn, string authIn, string txtIn, string uuidIn, string urlIn)
        {
            title = titleIn;
            publication = pubIn;
            author = authIn;
            text = txtIn;
            uuid = uuidIn;
            url = urlIn;
        }

        void setTitle(string titleIn)
        {
            title = titleIn;
        }
        void setPublication(string pub)
        {
            publication = pub;
        }
        void setAuthor(string auth)
        {
            author = auth;
        }
        void setText(string txt)
        {
            text = txt;
        }
        void setUuid(string uic)
        {
            uuid = uic;
        }
        void setUrl(string link)
        {
            url = link;
        }
        /*
        void addPerson(string pers) 
        {
            persons.push_back(pers);
        }
        void addOrg(string o) 
        {
            orgs.push_back(o);
        }*/
        string getTitle(){return title;}
        string getPublication(){return publication;}
        string getAuthor(){return author;}
        string getText(){return text;}
        string getUrl(){return url;}
        string getUuid(){return uuid;}
        //vector<string> getPersons(){return persons;}
        //vector<string> getOrgs(){return orgs;}

        bool operator==(const DocumentNode& rhs)
        {   
            //Since the uuid is the most unique aspect of a doc, if they are the same then the docs are identical
            if (rhs.uuid == uuid)
                return true;
            return false;
        }
};  

#endif
