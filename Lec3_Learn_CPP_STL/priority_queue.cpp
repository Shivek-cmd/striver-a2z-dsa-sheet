#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "🌟 STL Priority Queue in C++ - Most Common Uses\n\n";

    // ✅ Max Heap (default)
    priority_queue<int> pq;

    pq.push(5);
    pq.push(2);
    pq.push(8);
    pq.push(10);

    cout << "Top (max): " << pq.top() << "\n";

    // ✅ Popping elements
    pq.pop();
    cout << "After pop, top: " << pq.top() << "\n";

    // ✅ Size
    cout << "Size: " << pq.size() << "\n";

    // ✅ Traversing (via pop)
    cout << "\nMax-Heap elements (descending): ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }

    // ✅ Min Heap
    priority_queue<int, vector<int>, greater<int>> minpq;
    minpq.push(5);
    minpq.push(2);
    minpq.push(8);
    minpq.push(1);

    cout << "\n\nMin-Heap elements (ascending): ";
    while (!minpq.empty()) {
        cout << minpq.top() << " ";
        minpq.pop();
    }

    return 0;
}
