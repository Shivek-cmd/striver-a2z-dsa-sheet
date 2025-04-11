#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "🌟 STL Queue in C++ - Most Common Uses\n\n";

    queue<string> q;

    // ✅ Pushing elements
    q.push("Alice");
    q.push("Bob");
    q.push("Charlie");

    // ✅ Front and back
    cout << "Front: " << q.front() << "\n";
    cout << "Back: " << q.back() << "\n";

    // ✅ Popping front
    q.pop();
    cout << "After pop, front: " << q.front() << "\n";

    // ✅ Size
    cout << "Size: " << q.size() << "\n";

    // ✅ Empty check
    cout << "Is empty? " << (q.empty() ? "Yes" : "No") << "\n";

    // ✅ Traversing the queue (via pop)
    cout << "\nQueue elements (FIFO): ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "\n";

    return 0;
}
