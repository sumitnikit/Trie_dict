// #ifndef LRU_H
// #define LRU_H

// #include <string>
// #include <list>
// #include <unordered_map>
// using namespace std;

// class LRUCache {
// private:
//     list<string> lruList;
//     unordered_map<string, list<string>::iterator> lruMap;

// public:
//     void put(string word) {
//         if (lruMap.find(word) != lruMap.end()) {
//             lruList.erase(lruMap[word]);
//         }
//         lruList.push_front(word);
//         lruMap[word] = lruList.begin();
//     }

//     string getLRUWord() {
//         return lruList.back();
//     }
// };

// #endif // LRU_H

#ifndef LRU_H
#define LRU_H

#include <string>
#include <list>
#include <unordered_map>
using namespace std;

class LRUCache {
private:
    list<string> lruList;
    unordered_map<string, list<string>::iterator> lruMap;
    int capacity;

public:
    LRUCache(int cap) : capacity(cap) {}

    void put(string word) {
        if (lruMap.find(word) != lruMap.end()) {
            lruList.erase(lruMap[word]);
        } else if (lruList.size() == capacity) {
            string leastRecent = lruList.back();
            lruList.pop_back();
            lruMap.erase(leastRecent);
        }
        lruList.push_front(word);
        lruMap[word] = lruList.begin();
    }

    string getLRUWord() {
        return lruList.back();
    }
};

#endif // LRU_H
