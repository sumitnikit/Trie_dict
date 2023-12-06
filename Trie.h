// #ifndef TRIE_H
// #define TRIE_H

// #include <string>
// using namespace std;

// #define ALPHABETS 26

// class TrieNode {
// public:
//     string meaning;
//     TrieNode* children[ALPHABETS];

//     TrieNode() : meaning("") {
//         for (int i = 0; i < ALPHABETS; i++) {
//             children[i] = NULL;
//         }
//     }


// };

// #endif // TRIE_H

#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
using namespace std;

#define ALPHABETS 26

class TrieNode {
public:
    string meaning;
    TrieNode* children[ALPHABETS];

    TrieNode() : meaning("") {
        for (int i = 0; i < ALPHABETS; i++) {
            children[i] = NULL;
        }
    }

    void collectAllWords(string prefix, vector<string>& words) {
        if (!meaning.empty()) {
            words.push_back(prefix);
        }
        for (int i = 0; i < ALPHABETS; i++) {
            if (children[i] != NULL) {
                children[i]->collectAllWords(prefix + char(i + 'a'), words);
            }
        }
    }
};

#endif // TRIE_H

