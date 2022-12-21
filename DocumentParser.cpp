#include "DocumentParser.h"

DocumentParser::DocumentParser()
{
   //heyyy
}

/**
 * @brief code used from rapidJSONExample.cpp - given the name of the directory
 * read the subdirectories contained inside, and isolate the JSON filenames. 
 * Send each JSON file to the DocumentParser
 * 
 * @param path - name of director
 */
void DocumentParser::browseDirectory(const string &path, IndexHandler &ih)
{
    auto it = filesystem::recursive_directory_iterator(path);

    // loop over all the entries.
    for (const auto &entry : it)
    {
        //cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;

        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
        {
            readFile(entry.path().string(), ih);
            //testReadJsonFile(entry.path().string());
        }
    }

}

void DocumentParser::readFile(const string &fileName, IndexHandler &ih)
{
    ifstream input(fileName);
    if (!input.is_open())
    {
        cerr << "cannot open file: " << fileName << endl;
        return;
    }

    DocumentNode newDoc;

    // Create a RapidJSON IStreamWrapper using the file input stream above.
    IStreamWrapper isw(input);

    // Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    Document d;
    d.ParseStream(isw);

    // Now that the document is parsed, we can access different elements the JSON using
    // familiar subscript notation.

    // This accesses the -title- element in the JSON. Since the value
    //  associated with title is a string (rather than
    //  an array or something else), we call the GetString()
    //  function to return the actual title of the article
    //  as a c-string.
    string word;

    //Adding relevant info into Document Node
    auto val = d["title"].GetString();
    char *title = NULL;
    title = (char *)val;
    newDoc.setTitle(title);

    val = d["url"].GetString();
    title = (char*) val;     
    newDoc.setUrl(title);

    val = d["uuid"].GetString();
    title = (char*) val;
    newDoc.setUuid(title);

    val = d["author"].GetString();
    title = (char*) val;
    newDoc.setAuthor(title);

    val = d["published"].GetString();
    title = (char*) val;   

    newDoc.setPublication(title);

    char delimeters[] = " ,.!?\n";
    val = d["text"].GetString();
    string wholeText = val;
//changing the whole text to lowercase and copying it into the title
    transform(wholeText.begin(), wholeText.end(), wholeText.begin(), ::tolower);
    strcpy(title, wholeText.c_str());

    newDoc.setText(title);
    //tokenizing the title based on the delimeters
    char* token = strtok(title, delimeters);
    //steming the words and then checking if the stop words are found
    while (token != nullptr) {
        word= token;
        trim(word);
        stem(word);
        if (find(stopWords.begin(), stopWords.end(), word) == stopWords.end()) {
            //if they are equal to the stop words and done words, it is added
            ih.addWord(word, newDoc);
        }
        token = strtok(nullptr, delimeters);

    }

    // The Persons entity for which you're building a specific
    //  inverted index is contained in top level -entities- element.
    //  So that's why we subscript with ["entities"]["persons"].
    //  The value associated with entities>persons is an array.
    //  So we call GetArray() to get an iterable collection of elements
    auto persons = d["entities"]["persons"].GetArray();

    for (auto &p : persons)
    {
        ih.addPerson( p["name"].GetString(), newDoc);
    }

    cout << endl;

    auto orgs = d["entities"]["organizations"].GetArray();
    for (auto &o : orgs)
    {
        ih.addOrg(o["name"].GetString(), newDoc);
    }
    //ih.printTrees();
    input.close();
}

