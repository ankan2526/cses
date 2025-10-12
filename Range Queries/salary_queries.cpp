#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
 
// Sets up fast input/output for C++
void setup_fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}
 
/**
 * @brief A Fenwick Tree (or Binary Indexed Tree) class.
 * It supports point updates and prefix sum queries in O(log n) time.
 */
class FenwickTree {
private:
    std::vector<int> bit; // The internal array for the Fenwick tree
    int size;             // The number of elements the tree can handle
 
public:
    /**
     * @brief Constructs a Fenwick Tree for 'n' elements.
     * @param n The number of elements.
     */
    FenwickTree(int n) : size(n), bit(n + 1, 0) {}
 
    /**
     * @brief Adds a 'delta' value to the element at a given index.
     * @param idx The 0-based index of the element to update.
     * @param delta The value to add.
     */
    void update(int idx, int delta) {
        idx++; // Convert to 1-based index for internal logic
        while (idx <= size) {
            bit[idx] += delta;
            idx += idx & (-idx); // Move to the next relevant index
        }
    }
 
    /**
     * @brief Calculates the cumulative sum from the start up to a given index.
     * @param idx The 0-based index.
     * @return The sum of elements from index 0 to idx.
     */
    int get_sum(int idx) {
        idx++; // Convert to 1-based index
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & (-idx); // Move to the parent index
        }
        return sum;
    }
 
    /**
     * @brief Calculates the sum of elements within a given range [l, r].
     * @param l The 0-based starting index of the range.
     * @param r The 0-based ending index of the range.
     * @return The sum of elements in the range.
     */
    int query(int l, int r) {
        if (l > r) {
            return 0;
        }
        // The sum of [l, r] is (sum up to r) - (sum up to l-1)
        return get_sum(r) - get_sum(l - 1);
    }
};
 
// A simple structure to hold the details of each query
struct Query {
    char type;
    int x, y;
};
 
int main() {
    setup_fast_io();
 
    int n, q;
    std::cin >> n >> q;
 
    std::vector<int> salary(n);
    std::set<int> unique_values; // Use a set to automatically handle unique values
 
    // Read initial salaries and add them to the set for coordinate compression
    for (int i = 0; i < n; ++i) {
        std::cin >> salary[i];
        unique_values.insert(salary[i]);
    }
 
    std::vector<Query> queries(q);
    // Read all queries and collect salary values that will be used
    for (int i = 0; i < q; ++i) {
        std::cin >> queries[i].type >> queries[i].x >> queries[i].y;
        if (queries[i].type == '!') {
            unique_values.insert(queries[i].y);
        } else { // type == '?'
            unique_values.insert(queries[i].x);
            unique_values.insert(queries[i].y);
        }
    }
 
    // --- Coordinate Compression ---
    // Create a sorted vector from the set of unique values. The index in this
    // vector will be the "compressed" value.
    std::vector<int> compressed_map(unique_values.begin(), unique_values.end());
    
    // A helper function to find the compressed index of any salary value
    auto get_compressed_index = [&](int val) {
        // std::lower_bound efficiently finds the position of 'val' in the sorted map
        return std::lower_bound(compressed_map.begin(), compressed_map.end(), val) - compressed_map.begin();
    };
 
    // --- Fenwick Tree Initialization ---
    FenwickTree ft(compressed_map.size());
    // Populate the Fenwick tree based on the initial salaries' frequencies
    for (int s : salary) {
        ft.update(get_compressed_index(s), 1);
    }
 
    // --- Process Queries ---
    for (const auto& query : queries) {
        if (query.type == '!') {
            // Update query: salary[k] = new_salary
            int k = query.x - 1; // Convert to 0-based employee index
            int new_salary = query.y;
 
            // Decrement the count for the old salary
            ft.update(get_compressed_index(salary[k]), -1);
            
            // Increment the count for the new salary
            ft.update(get_compressed_index(new_salary), 1);
 
            // Update the actual salary in our array
            salary[k] = new_salary;
        } else { // type == '?'
            // Range query: count employees with salary in [a, b]
            int a = query.x;
            int b = query.y;
 
            // Find the compressed indices for the salary range [a, b]
            int l_idx = get_compressed_index(a);
            int r_idx = get_compressed_index(b);
 
            // Perform the query on the Fenwick tree and print the result
            std::cout << ft.query(l_idx, r_idx) << "\n";
        }
    }
 
    return 0;
}