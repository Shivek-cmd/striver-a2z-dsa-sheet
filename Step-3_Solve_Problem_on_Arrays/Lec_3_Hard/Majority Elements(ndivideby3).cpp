#include <bits/stdc++.h>
using namespace std;

/*
INTUITION:-  MAX 2 ELEMENTS CAN BE MAJORITY ONLY(THINK ABOUT IT)
    Problem Statement:
    Given an integer array, find all the elements that appear more than n/3 times in the array.
    Note: The majority elements are those that appear more than n/3 times.

    Example 1:
    Input Format: N = 5, array[] = {1,2,2,3,2}
    Result: 2
    Explanation: Here we can see that the Count(1) = 1, Count(2) = 3, and Count(3) = 1.
    Therefore, the count of 2 is greater than N/3 times. Hence, 2 is the answer.

    Example 2:
    Input Format: N = 6, array[] = {11,33,33,11,33,11}
    Result: 11 33
    Explanation: Here we can see that the Count(11) = 3 and Count(33) = 3.
    Therefore, the count of both 11 and 33 is greater than N/3 times. Hence, 11 and 33 are the answer.
*/
/*
-----------------------------------------------------
Approach 1: Brute Force
-----------------------------------------------------
    - Traverse the array and for each element, count its occurrences using nested loops. 
    - If its count is greater than n/3, add it to the result.
    - Time Complexity: O(n^2)
    - Space Complexity: O(1)


    -----------------------------------------------------
Approach 2: Better Approach (Using HashMap)
-----------------------------------------------------
    - Use a hash map to store the count of each element in the array.
    - Once we've counted the occurrences, we check which elements have a count greater than n/3.
    - Time Complexity: O(2n) One pass to count occurrences (O(n)) Another pass through the hash map to check which elements have a count greater than n/3
    - Space Complexity: O(n)

        -----------------------------------------------------
Approach 3: Efficient Approach (Using HashMap)
-----------------------------------------------------
    - This approach utilizes an unordered map (hash map) to count occurrences of each element in the array.
    - We increment the count for each element, and as soon as an element's count reaches `n/3 + 1`, we add it to the result vector.
    - The logic behind the threshold is that we are looking for elements that appear more than `n/3` times.
    - If at any point, more than two elements are found, we return the result early to avoid unnecessary processing.
    - This approach ensures we do not unnecessarily count elements that exceed the threshold, making it slightly more efficient.
    - Early Exit Optimization:(as compare to approach 2)
    Time Complexity:
    - The time complexity of this approach is `O(n)` because we are iterating through the array only once and performing constant-time operations for each element.

    Space Complexity:
    - The space complexity is `O(n)` because we are using a hash map to store the count of each element.


    -----------------------------------------------------
Approach 4: Optimal Approach (Boyer-Moore Voting Algorithm)
-----------------------------------------------------
    - Use the Boyer-Moore voting algorithm to find at most two majority elements.
    - In the first pass, we select candidates, and in the second pass, we confirm their counts.
    - Time Complexity: O(n)
    - Space Complexity: O(1)
*/
vector<int> majorityElementBruteForce(vector<int>& nums) {
    vector<int> v;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        int count = 0;
        // Count occurrences of nums[i] in the nums array
        for (int j = 0; j < n; j++) {
            if (nums[j] == nums[i]) {
                count++;
            }
        }

        // If the count is greater than n/3, add it to the result
        if (count > n / 3 && find(v.begin(), v.end(), nums[i]) == v.end()) {
            v.push_back(nums[i]);
        }
    }
    return v;
}

// Approach 2: Better Approach (Hash Map)
vector<int> majorityElementBetter(vector<int>& nums) {
    unordered_map<int, int> mp;
    vector<int> v;
    int n = nums.size();

    // Count occurrences of each element
    for (int num : nums) {
        mp[num]++;
    }

    // Find the elements that appear more than n/3 times
    for (auto it : mp) {
        if (it.second > n / 3) {
            v.push_back(it.first);
        }
    }

    return v;
}

vector<int> majorityElementBetterBetter(vector<int>& nums) {
    unordered_map<int, int> mp;
    vector<int> v;
    int n = nums.size();
    
    for (int num : nums) {
        mp[num]++;
        
        // If we reach the threshold, add the element to the result vector
        if (mp[num] == (n / 3) + 1) {
            v.push_back(num);
        }
        
        // If we have more than two majority elements, return early
        if (v.size() > 2) {
            break;
        }
    }
    
    return v;
}

// Approach 3: Optimal Approach (Boyer-Moore Voting Algorithm)
vector<int> majorityElementOptimal(vector<int>& nums) {
    int count1 = 0, count2 = 0, ele1, ele2;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        if (count1 == 0 && nums[i] != ele2) {
            count1 = 1;
            ele1 = nums[i];
        } else if (count2 == 0 && nums[i] != ele1) {
            count2 = 1;
            ele2 = nums[i];
        } else if (ele1 == nums[i]) {
            count1++;
        } else if (ele2 == nums[i]) {
            count2++;
        } else {
            count1--;
            count2--;
        }
    }

    vector<int> ls;
    count1 = 0, count2 = 0;
    // Second pass to confirm the elements and their counts
    for (int i = 0; i < n; i++) {
        if (ele1 == nums[i]) {
            count1++;
        }
        if (ele2 == nums[i]) {
            count2++;
        }
    }

    int mini = n / 3 + 1;
    if (count1 >= mini) ls.push_back(ele1);
    if (count2 >= mini) ls.push_back(ele2);

    sort(ls.begin(), ls.end());
    return ls;
}

int main() {
    vector<int> arr = {11, 33, 33, 11, 33, 11};

    // Test Brute Force Approach
    vector<int> ansBrute = majorityElementBruteForce(arr);
    cout << "Brute Force Majority Elements: ";
    for (auto it : ansBrute) {
        cout << it << " ";
    }
    cout << "\n";

    // Test Better Approach (HashMap)
    vector<int> ansBetter = majorityElementBetter(arr);
    cout << "Better Approach Majority Elements: ";
    for (auto it : ansBetter) {
        cout << it << " ";
    }
    cout << "\n";
      // Test Better BETTER Approach (HashMap)
    vector<int> ansOptimal = majorityElementBetterBetter(arr);
    cout << "Optimal Approach Majority Elements: ";
    for (auto it : ansOptimal) {
        cout << it << " ";
    }
    cout << "\n";
    // Test Optimal Approach (Boyer-Moore Voting)
    vector<int> ansOptimal = majorityElementOptimal(arr);
    cout << "Optimal Approach Majority Elements: ";
    for (auto it : ansOptimal) {
        cout << it << " ";
    }
    cout << "\n";

    return 0;
}

/*
-----------------------------------------------------
Problem Statement:
-----------------------------------------------------
    - Given an integer array, find all the elements that appear more than n/3 times in the array.
    - Majority elements are those that appear more than n/3 times in the array.

-----------------------------------------------------
Approach 1: Brute Force
-----------------------------------------------------
    - Traverse the array and for each element, count its occurrences.
    - Compare its count with n/3 and push the element into the result vector if it satisfies the condition.
    - Time Complexity: O(n^2)
    - Space Complexity: O(1)

-----------------------------------------------------
Approach 2: Better Approach (Using HashMap)
-----------------------------------------------------
    - Use a hash map to count occurrences of each element.
    - Iterate through the map and check if any element has a count greater than n/3.
    - Time Complexity: O(n)
    - Space Complexity: O(n)

-----------------------------------------------------
Approach 3: Optimal Approach (Boyer-Moore Voting Algorithm)
-----------------------------------------------------
    - Use the Boyer-Moore voting algorithm to find at most two majority elements.
    - In the first pass, select two potential majority elements. In the second pass, count their occurrences.
    - Time Complexity: O(n)
    - Space Complexity: O(1)
*/
