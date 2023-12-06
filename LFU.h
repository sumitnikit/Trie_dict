// #ifndef LFU_H
// #define LFU_H

// #include <string>
// #include <unordered_map>
// using namespace std;

// class LFUCache {
// private:
//     unordered_map<string, int> frequency;
//     int capacity;

// public:
//     LFUCache(int cap) : capacity(cap) {}
//     void put(string word) {
//         frequency[word]++;
//     }

//     string getLFUWord() {
//         string lfuWord;
//         int minFreq = INT_MAX;

//         for (const auto& pair : frequency) {
//             if (pair.second < minFreq) {
//                 minFreq = pair.second;
//                 lfuWord = pair.first;
//             }
//         }

//         return lfuWord;
//     }
// };

// #endif // LFU_H

#ifndef LFU_H
#define LFU_H

#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
using namespace std;

class LFUCache {
private:
    unordered_map<string, int> frequency;
    list<string> lfuList;
    int capacity;

public:
    LFUCache(int cap) : capacity(cap) {}

    void put(string word) {
        // Increment frequency
        frequency[word]++;
        
        // Update the list to reflect new frequency
        lfuList.remove(word);
        auto it = find_if(lfuList.begin(), lfuList.end(), 
                          [this, &word](const string& key) { return frequency[key] > frequency[word]; });
        lfuList.insert(it, word);

        // Evict if necessary
        if (lfuList.size() > capacity) {
            string leastFrequent = lfuList.back();
            lfuList.pop_back();
            frequency.erase(leastFrequent);
        }
    }

    string getLFUWord() {
        return lfuList.back();
    }
};

#endif // LFU_H

