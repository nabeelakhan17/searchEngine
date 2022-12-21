//
// Created by nabee on 11/21/2022.
//

#include "Node.h"
//creates operators for the nodes because it is not a double stacked AVL tree
bool Node::operator<(const Node& rhs) {
    return word < rhs.word;
}

bool Node:: operator>(const Node& rhs)
{
    return word> rhs.word;
}
bool Node:: operator==(const Node& rhs)
{
    return word==rhs.word;
}
void Node::operator=(const Node& rhs)
{
    word = rhs.word;
    document.clear();

    for (size_t i = 0; i < rhs.document.size(); i++)
        document.push_back(rhs.document[i]);  
}
//prints out the title, publication, author, text, Uuid, and url for each document
ostream &operator<<(ostream &out, Node& rhs)
{
    out << rhs.word << endl;
    out << rhs.document.size() << endl; //How many douments are associated with the word

    for (int i = 0; i < rhs.document.size(); i++) 
    {
        out << rhs.document[i].getTitle() << endl;
        out << rhs.document[i].getPublication() << endl;
        out << rhs.document[i].getAuthor() << endl;
        out << rhs.document[i].getUuid() << endl;
        out << rhs.document[i].getUrl() << endl;
    }
    return out;
}

