#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "🌟 STL Stack in C++ - Most Common Uses\n\n";

    stack<int> st;

    // ✅ Pushing elements
    st.push(10);
    st.push(20);
    st.push(30);

    // ✅ Top element
    cout << "Top element: " << st.top() << "\n";

    // ✅ Popping the top
    st.pop();
    cout << "After pop, top: " << st.top() << "\n";

    // ✅ Size of stack
    cout << "Size: " << st.size() << "\n";

    // ✅ Is stack empty?
    cout << "Is empty? " << (st.empty() ? "Yes" : "No") << "\n";

    // ✅ Printing all elements (by popping)
    cout << "\nStack elements (LIFO): ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << "\n";

    return 0;
}
