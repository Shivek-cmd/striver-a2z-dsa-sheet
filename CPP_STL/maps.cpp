#include <bits/stdc++.h>
using namespace std;

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
    // for (auto [id, name] : idName) {
    //     cout << id << " -> " << name << "\n";
    // }

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
