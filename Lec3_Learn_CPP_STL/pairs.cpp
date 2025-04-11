#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "🌟 STL Pairs in C++ - Most Common Uses\n\n";

    // ✅ Basic Declaration
    pair<int, int> p1 = {10, 20};
    cout << "p1: (" << p1.first << ", " << p1.second << ")\n";

    // ✅ Using make_pair()
    pair<string, int> p2 = make_pair("Alice", 100);
    cout << "p2: (" << p2.first << ", " << p2.second << ")\n";

    // ✅ Nested Pair
    pair<int, pair<int, int>> nested = {1, {2, 3}};
    cout << "nested: (" << nested.first << ", " << nested.second.first << ", " << nested.second.second << ")\n";

    // ✅ Swapping pairs
    pair<int, int> a = {5, 6}, b = {7, 8};
    swap(a, b);
    cout << "After swap: a = (" << a.first << ", " << a.second << "), b = (" << b.first << ", " << b.second << ")\n";

    // ✅ Pair Array (commonly used in sorting problems)
    pair<int, int> arr[] = {{3, 4}, {1, 2}, {5, 0}};
    int n = 3;

    cout << "\nBefore sorting:\n";
    for (int i = 0; i < n; i++)
        cout << "(" << arr[i].first << ", " << arr[i].second << ") ";

    // ✅ Sort array of pairs by first (default behavior)
    sort(arr, arr + n);

    cout << "\nAfter sorting by first element:\n";
    for (int i = 0; i < n; i++)
        cout << "(" << arr[i].first << ", " << arr[i].second << ") ";

    // ✅ Vector of Pairs
    vector<pair<int, int>> vp;
    vp.push_back({1, 100});
    vp.push_back({2, 50});
    vp.push_back({3, 75});

    cout << "\n\nVector of pairs:\n";
    for (auto p : vp)
        cout << "(" << p.first << ", " << p.second << ") ";

    // ✅ Custom Sorting using Comparator
    sort(vp.begin(), vp.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;  // sort by second value
    });

    cout << "\n\nAfter sorting vector by second element:\n";
    for (auto p : vp)
        cout << "(" << p.first << ", " << p.second << ") ";

    cout << "\n";

    return 0;
}
