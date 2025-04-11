#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "🌟 STL Set in C++ - Most Common Uses\n\n";

    // ✅ Declaration
    set<int> s;

    // ✅ Insertion (automatically sorted & unique)
    s.insert(10);
    s.insert(5);
    s.insert(20);
    s.insert(10);  // duplicate, will not be inserted

    // ✅ Traversal
    cout << "Set elements (auto-sorted, no duplicates):\n";
    for (int x : s)
        cout << x << " ";
    cout << "\n";

    // ✅ Size
    cout << "Size of set: " << s.size() << "\n";

    // ✅ Check if an element exists
    int target = 5;
    if (s.find(target) != s.end()) {
        cout << target << " is present in the set.\n";
    } else {
        cout << target << " is not in the set.\n";
    }

    // ✅ Erase an element
    s.erase(10);
    cout << "After erasing 10:\n";
    for (int x : s)
        cout << x << " ";
    cout << "\n";

    // ✅ Using count (returns 0 or 1, as elements are unique)
    cout << "Count of 5: " << s.count(5) << "\n";
    cout << "Count of 100: " << s.count(100) << "\n";

    // ✅ Clear set
    s.clear();
    cout << "After clearing, is set empty? " << (s.empty() ? "Yes" : "No") << "\n";

    // ✅ Set with custom comparator (Descending Order)
    set<int, greater<int>> ds;
    ds.insert(3);
    ds.insert(1);
    ds.insert(2);

    cout << "\nSet in descending order:\n";
    for (int x : ds)
        cout << x << " ";
    cout << "\n";

    // ✅ Set of strings
    set<string> fruits = {"apple", "banana", "cherry", "banana"};

    cout << "\nSet of strings:\n";
    for (auto fruit : fruits)
        cout << fruit << " ";
    cout << "\n";

    return 0;
}
