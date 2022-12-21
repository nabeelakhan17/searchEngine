## High-level Design of Solution

- UML class diagram, etc.
- High-level pseudo code for each component.

## Your Timeline to Finish the Project
Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task        | Planned completion | Actual completion | Time spent in hrs by KN | Time spent in hrs by NK |
| ----------- | :-----------------:| :---------------: | :--------------------:  |:-----------------------:|
| AVL         | Nov 7              | Nov 10            | 5                       |            5            |
| DocParser   | Nov 14             | Nov 12            | 5                       |            5            |
| IndexHandler| Nov 21             | Nov 23            | 10                      |            7            |
| QueryParser | Nov 21             | Nov 23            | 5                       |            6            |
| UI          | Nov 28             | Dec 1             | 4                       |            2            |        


## Used Data Structures
Explanation of what data structures are used where. For each, state
- time and space complexity (Big-Oh),
- Olog(n) and for a vector its  O(n)
- why it is the appropriate data structure and what other data structure could have been used.
vectors and a avl tree
## User Documentation
- How to use the software.
- First you habe to hit number 4, to parse the query and then search what query you want
- Some example queries with the results.

## Performance
- Statistics for indexing all documents and timing.
- 
## Automatic Tests and Memory Tests
You need to describe test cases for:
- Tests for your AVL tree's function
- Tests for your AVL tree for memory leaks (don't forget to test the persistence functions)
- Tests for indexer
- we printed out the avl tree after we entered the words from each 
- if the words are already contained inside the tree we push the vecotr of the dcoumetn node into the avl tree
- if it is a new word, we make a new node and we push the entire thing along with the node to the vector associated wiht the node and then add it to the avl tree
- Tests for the complete system
- if we input the word german with the sample data we get one index as an output, if we enter german and person powell we would still get the same document because it has the same
- created our json file 