#include <bits/stdc++.h>
using namespace std;
/*
    ✅ Insertion (set.insert() or set[key] = value):        O(log N)
    ✅ Access (set.find()):                                  O(log N)
    ✅ Deletion (set.erase()):                               O(log N)
    ✅ Search (set.find() or set.count()):                   O(log N)
    ✅ Traversal (using for-loop):                           O(N)
    ✅ Size (size()):                                        O(1)
    ✅ Empty check (empty()):                                O(1)
    ✅ Clearing entire set (clear()):                        O(N)
    
    🔹 **Notes**:
    - `set` is an ordered collection of unique keys.
    - Operations like insert, delete, and search are logarithmic due to the underlying Red-Black tree structure.
    - Traversal is linear (`O(N)`), as it needs to visit each element in the set.
    - `set` is slower than `unordered_set` for search and insertion on average because of the tree structure but maintains a sorted order.
    - `find()` and `count()` return the same result and are used for checking if an element exists.


    /*
    ✅ Insertion (unordered_set.insert()):       O(1) average, O(N) worst case
    ✅ Access (unordered_set.find()):            O(1) average, O(N) worst case
    ✅ Deletion (unordered_set.erase()):         O(1) average, O(N) worst case
    ✅ Search (unordered_set.find() or unordered_set.count()): O(1) average, O(N) worst case
    ✅ Traversal (using for-loop):               O(N)
    ✅ Size (size()):                            O(1)
    ✅ Empty check (empty()):                    O(1)
    ✅ Clearing entire unordered_set (clear()):  O(N)

    🔹 **Notes**:
    - `unordered_set` does not maintain any order of keys.
    - Insertion, deletion, and search are **faster** on average compared to `set` because of hash-based implementation.
    - **Worst-case** time complexity can be O(N) due to hash collisions, but this is uncommon in practice.
    - If the order of elements is not important, `unordered_set` is preferred as it generally provides better performance.

*/

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
