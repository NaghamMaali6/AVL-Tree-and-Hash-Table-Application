# AVL-Tree-and-Hash-Table-Application
This C project implements an application for efficiently indexing words found in a text file using two powerful data structures: AVL Tree and Hash Table. The application reads words from a text file, inserts them into an AVL tree for sorted order and efficient retrieval, and stores them in a hash table for quick access by their hash values. It also supports operations like inserting, deleting, searching, and retrieving statistics for word frequencies.

# Features:
1. Input Data: The application reads a text file (input.txt) containing text data that may have multiple lines.

2. Reading Data: It reads the words from the file, ignoring anything other than alphabetical characters (e.g., punctuation, digits) and treats "Hello" and "hello" as the same word.

3. AVL Tree: An AVL Tree is a self-balancing binary search tree where the difference between the heights of the left and right subtrees (balance factor) is at most 1 for all nodes. It ensures efficient insertion, deletion, and searching operations in O(log n) time.
* Building the AVL Tree: Each word is inserted into the AVL tree with a frequency of 1. If the word already exists, its frequency is updated.
* Insert a Word: Insert new words or update the frequency of existing words.
* Delete a Word: Search for a word in the AVL tree and delete it. A message is shown if the word does not exist.
* Display Words: The words and their frequencies are printed using an in-order traversal of the AVL tree, which guarantees sorted order.

4. Hash Table: A table used for fast word frequency retrieval via direct access through the hash of the word.
* Creation: After the AVL tree is built, the tree is traversed, and each word along with its frequency is inserted into the hash table for fast retrieval.
* Collision Handling: The application implements collision handling using an appropriate method (e.g., separate chaining or linear probing).
* Search: The hash table allows users to search for a word and retrieve its frequency directly.
* Insert a Word: Insert a new word or update the frequency of an existing word in the hash table.
* Delete a Word: Search for a word in the hash table and delete it. A message is shown if the word does not exist.

5. Word Count Statistics:
* Statistics: Provides useful statistics, such as the total number of unique words and the most frequent word in the hash table.

