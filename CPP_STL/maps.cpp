#include <bits/stdc++.h>
using namespace std;



/*
    🔸 STL Map in C++ - Time Complexities
    (for ordered map<Key, T> → implemented as Red-Black Tree)

    ✅ Insertion (mp[key] = value or insert()):       O(log N)
    ✅ Access (mp[key] or find()):                    O(log N)
    ✅ Deletion (erase()):                            O(log N)
    ✅ Search (find(), count()):                      O(log N)
    ✅ Traversal (using for-loop):                    O(N)
    ✅ Size (size()), Empty check (empty()):          O(1)
    ✅ Clearing entire map (clear()):                 O(N)
*/

/*
    🔸 STL Unordered Map in C++ - Time Complexities
    (for unordered_map<Key, T> → implemented using Hash Table)

    ✅ Insertion (ump[key] = value or insert()):       O(1) average, O(N) worst case
    ✅ Access (ump[key] or find()):                    O(1) average, O(N) worst case
    ✅ Deletion (erase()):                             O(1) average, O(N) worst case
    ✅ Search (find(), count()):                       O(1) average, O(N) worst case
    ✅ Traversal (using for-loop):                     O(N)
    ✅ Size (size()), Empty check (empty()):           O(1)
    ✅ Clearing entire unordered_map (clear()):        O(N)

    ⚠️ Note:
    - Worst-case time occurs due to hash collisions.
    - unordered_map does NOT maintain any order of keys.
    - For large datasets where ordering is not needed, unordered_map is generally faster.
*/

int main() {
    cout << "🌟 STL Map in C++ - Most Common Uses\n\n";

    // ✅ Declaration
    map<string, int> mp;

    // ✅ Insertion
    mp["apple"] = 3;
    mp["banana"] = 5;
    mp["orange"] = 2;

    // ✅ Using insert()
    mp.insert(make_pair("grape", 7));

    // ✅ Traversing a map
    cout << "Contents of map:\n";
    for (auto it : mp) {
        cout << it.first << " -> " << it.second << "\n";
    }

    // ✅ Accessing Elements
    cout << "\nValue for 'banana': " << mp["banana"] << "\n";

    // ✅ Checking existence
    if (mp.find("apple") != mp.end()) {
        cout << "'apple' exists in the map.\n";
    }

    // ✅ Erasing a key
    mp.erase("orange");
    cout << "\nAfter erasing 'orange':\n";
    for (auto it : mp) {
        cout << it.first << " -> " << it.second << "\n";
    }

    // ✅ Size of map
    cout << "\nSize of map: " << mp.size() << "\n";

    // ✅ Clear map
    mp.clear();
    cout << "Map cleared. Is it empty? " << (mp.empty() ? "Yes" : "No") << "\n";

    // ✅ Map with integer keys
    map<int, string> idName;
    idName[101] = "Alice";
    idName[102] = "Bob";
    idName[103] = "Charlie";

    cout << "\nMap with integer keys:\n";
    for (auto it : idName) {
        cout << it.first << " -> " << it.second << "\n";
    }

    // ✅ Custom Sorting (Descending Order by Key)
    map<int, string, greater<int>> descMap;
    descMap[1] = "A";
    descMap[3] = "C";
    descMap[2] = "B";

    cout << "\nMap sorted in descending order:\n";
    for (auto it : descMap) {
        cout << it.first << " -> " << it.second << "\n";
    }

    return 0;
}
