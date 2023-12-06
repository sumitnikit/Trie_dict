#include "Trie.h"
#include "LFU.h"
#include "LRU.h"
#include <iostream>
#include <fstream>
vector<string> suggestions;
class Dictionary {
private:
    TrieNode* root;
    LFUCache lfuCache;
    LRUCache lruCache;

public:
    Dictionary(int cacheCapacity) : lfuCache(cacheCapacity), lruCache(cacheCapacity) {
        root = new TrieNode();
    }

    void insert(string word, string meaning) {
        TrieNode* temp = root;
        for (char c : word) {
            int index = c - 'a';
            if (!temp->children[index]) {
                temp->children[index] = new TrieNode();
            }
            temp = temp->children[index];
        }
        temp->meaning = meaning;
    }

    void autoComplete(string prefix, vector<string>& suggestions) {
        TrieNode* temp = root;
        for (char c : prefix) {
            int index = c - 'a';
            if (!temp->children[index]) {
                return;  // Prefix not found
            }
            temp = temp->children[index];
        }
        temp->collectAllWords(prefix, suggestions);
    }

    void search(string word) {
        TrieNode* temp = root;
        for (char c : word) {
            int index = c - 'a';
            if (!temp->children[index]) {
                cout << "Word not found." << endl;
                return;
            }
            temp = temp->children[index];
        }

        if (!temp->meaning.empty()) {
            cout << "Meaning of " << word << ": " << temp->meaning << endl;
            lfuCache.put(word);
            lruCache.put(word);
        } else {
            cout << "Word not found. Did you mean" <<endl;
            autoComplete(word,suggestions);
            for(string& word: suggestions)
                cout<<word<<endl;
            suggestions.clear();
        }
    }

    bool remove(string word) {
        return removeUtil(root, word, 0);
    }

    bool removeUtil(TrieNode* node, const string& word, int depth) {
        if (!node) {
            return false;
        }

        if (depth == word.size()) {
            // End of the word reached
            if (!node->meaning.empty()) {
                node->meaning = ""; // Clear the meaning, effectively deleting the word
                // Check if node can be deleted
                return isLeafNode(node);
            }
            return false;
        }

        int index = word[depth] - 'a';
        if (removeUtil(node->children[index], word, depth + 1) && node->children[index]) {
            delete node->children[index];
            node->children[index] = nullptr;
            return (!node->meaning.empty() || !isLeafNode(node));
        }
        return false;
    }

    bool isLeafNode(TrieNode* node) {
        for (int i = 0; i < ALPHABETS; i++) {
            if (node->children[i]) {
                return false;
            }
        }
        return true;
    }

    

    string getLFUWord() {
        return lfuCache.getLFUWord();
    }

    string getLRUWord() {
        return lruCache.getLRUWord();
    }

    void clearMemory(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < ALPHABETS; i++) {
            if (node->children[i]) {
                clearMemory(node->children[i]);
            }
        }
        delete node;
    }
    // Destructor to free Trie memory
    //~Dictionary() {}
};

int main() {
    Dictionary dict(5); // Cache capacity set to 5
    

    // Example usage
    dict.insert("hello", "a greeting");
    dict.insert("world", "the earth");
    string words[]={"prodigious","potent","sway","corrosive","propaganda","drag","cart","card","carrot","carrom","carton"};
	string meanings[]={"very large in size","very strong in chemical or medicinal way","control","having the ability to wear down or destroy","information","pass slowly and tediously","a strong open vehicle with two or four wheels, typically used for carrying loads and pulled by a horse","a piece of thick, stiff paper or thin pasteboard, in particular one used for writing or printing on","a tapering orange-coloured root eaten as a vegetable","any strike and rebound, as a ball striking a wall and glancing off","a box"};
	int n=sizeof(words)/sizeof(words[0]);

	for(int i=0;i<n;i++)
		dict.insert(words[i],meanings[i]);

    dict.search("potent");
    dict.search("cart");
    dict.search("sway");
    dict.search("drag");
    dict.search("sway");
    dict.search("drag");
    dict.search("drag");
    

    cout << "LFU Word: " << dict.getLFUWord() << endl;
    cout << "LRU Word: " << dict.getLRUWord() << endl;

    dict.autoComplete("carr",suggestions);
    

    dict.remove("cart");

    dict.search("cart");
    dict.search("carrom");
    return 0;
}
