## High-level Design of Solution

- UML class diagram, etc.
- ![](../../umlDiagram.png)
- High-level pseudo code for each component.
  - Node:
    - vars:
      - string word
      - vector<DocumentNode> documents
-  DocumentNode
    - vars:
      - string title
      - string publication;
        string author;
        string text;
        string uuid;
        string url;
- Document Parser:
  - vars:
    - vector<string> stopWords; 
    - IndexHandler* 
  -Functions: 
    - browseDirectory()
      - loops through all the enteries
      - parses files that end in json
      - calls the read file function
    - readFile()
      - Creating a RapidJSON IStreamWrapper using the file input stream above.
      - adding the relevant information to the document node
      - changing the whole text to lowercase
      - tokening title based on delimeters
      - stemming the words and adding to the vector if a stop word is found
- IndexHandler
  - vars:
    - AvlTree<Node> words;
    - AvlTree<Node> people;
    - AvlTree<Node> orgs;
  - Functions:
    - addWord()
      - Given a word and a DocumentNode, add the word to the Word AVL Tree. If it 
        already exists in the tree, simply push the DocumentNode to the associated Node in the tree.
        Otherwise, add the entire word into the tree
    - addPerson()
      - Same as addWord() but with the people AVL tree. 
    - addOrg()
      - Same as addWord() but with the orgs AVL Tree
    - getNumDocs()
      - return how many docs are inside a specific Node
    - getNumWords()
      - return how many words are inside the AVL Tree
    - createPersistence()
      - create an output file for all 3 AVL trees. Print each tree by level into the associated file.
    - loadPersistence()
      - Read from the three files and create the 3 trees for the Query portion
- Query Engine
  - vars: 
    - IndexHandler*
-Functions: 
- vector<DocumentNode> parseQuery(string query, IndexHandler &ih);
  - creates a c-string depending on the query length
  - copies it into the data 
  - tokensizes the data by a ' '
  - pushes the tokenization into the vector
- vector<DocumentNode> intersect(vector<DocumentNode> one, vector<DocumentNode> two);
  - given two vectors, return a vector of DocumentNodes in which the two share in common
- vector<DocumentNode> removeNot(vector<DocumentNode> one, vector<DocumentNode> two); 
   - same as intersect, but return the docs that appear in one but do not appear in two
- int getRelevance();
   - Not implemented

## Your Timeline to Finish the Project
Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task        | Planned completion | Actual completion | Time spent in hrs by KN | Time spent in hrs by NK |
| ----------- | :-----------------:| :---------------: | :--------------------:  |:-----------------------:|
| AVL         | Nov 7              | Nov 10            | 5                       |            5            |
| DocParser   | Nov 14             | Nov 12            | 5                       |            5            |
| IndexHandler| Nov 21             | Nov 23            | 10                      |            7            |
| QueryParser | Nov 21             | Nov 23            | 5                       |            6            |
| UI          | Nov 28             | Dec 1             | 4                       |            5            |        


## Used Data Structures
Explanation of what data structures are used where. For each, state 
- time and space complexity (Big-Oh), why it is the appropriate data structure and what other data structure could have been used.
-We used the vector structure in DocumentParser, Index Handler, and the AVL Node. 
- The vector had a time complexity of O(n). We believed that vectors were the best in these following situations because the Index Handler could store a vector of documents. 
- Along with that, we used a doc vector in the AVl node section to store docs as a node and then push it into the AVl tree. 
- Also, in the Doc Parser we used a vector to store all the stop words. The other data structure we mainly used was the AVl tree. This stored the documents with pairs to word, persons, and organizations. The 
time complexity of this was O(log(n)) and the space complexity if O(n) where n is the depth of the tree. 
We couldve used a hash map if we wanted to instead of the AVl tree or vector to reduce runtime. 
## User Documentation
- How to use the software.
- If you want to load the trees with an index, hit 4. If you want to load the previously created trees, hit 3. Then hit 1 and enter your query.
  PERSON: and ORG: require the : and no space before the word, and only accepts one word in the search. Queries, in general, can be in any case and in any order
   <img width="682" alt="ExampleQuery" src="https://user-images.githubusercontent.com/111790464/205590416-cc967946-29b2-4d0f-8aa3-0422102059c9.png">

## Performance
- Statistics for indexing all documents and timing.
- creating index: .02 seconds
- saving persistence: 10 seconds
## Automatic Tests and Memory Tests
You need to describe test cases for:
- Tests for your AVL tree's function
  - we tested our AVL tree with the use of Catch test cases to make sure each method was mainly working. 
- Tests for your AVL tree for memory leaks (don't forget to test the persistence functions)
  -We ran val grind and made sure everything was working smoothly through that. 
- ![](../../valgrindProof.png)
- Tests for indexer
  - we printed out the avl tree after we entered the words from each 
  - if the words were already contained inside the tree we pushed the vector of the dcoument node into the avl tree
  - if it is a new word, we make a new node and we push the entire thing along with the node to the vector associated with the node and then add it to the avl tree
- Tests for the complete system
  - if we input the word german with the sample data we get one index as an output, if we enter german and person powell we would still get the same document because it has the same name associated it with as well
  - we created our two jsons files that shared the similar word dog to see after we created the index with the two files and entered a query with the word dog, both of those json files was outputted

 
