#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple> // For std::pair
#include <algorithm> // For std::reverse

using namespace std;

// Define infinity for time grid
const int INF = 1e9;

// Directions: {row_change, col_change}
// (1, 0) -> Down
// (-1, 0) -> Up
// (0, 1) -> Right
// (0, -1) -> Left
int adj[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
// Corresponding moves for backtracking
char moves[4] = {'D', 'U', 'R', 'L'};

int main() {
    // --- Fast I/O Setup ---
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // -----------------------

    int n, m;
    cin >> n >> m;

    vector<string> a(n);
    pair<int, int> start_pos = {-1, -1};
    queue<pair<int, int>> q_monster;
    
    // Grid for monster distances
    vector<vector<int>> monster_time(n, vector<int>(m, INF));

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'M') {
                monster_time[i][j] = 0;
                q_monster.push({i, j});
            } else if (a[i][j] == 'A') {
                start_pos = {i, j};
            }
        }
    }

    // --- Monster BFS (Multi-source) ---
    // Calculates the minimum time for *any* monster to reach each cell
    while (!q_monster.empty()) {
        pair<int, int> curr = q_monster.front();
        q_monster.pop();
        int x = curr.first;
        int y = curr.second;

        for (int i = 0; i < 4; ++i) {
            int nx = x + adj[i][0];
            int ny = y + adj[i][1];

            // Check bounds and if cell is valid (not a wall and not visited)
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && 
                a[nx][ny] != '#' && monster_time[nx][ny] == INF) {
                
                monster_time[nx][ny] = monster_time[x][y] + 1;
                q_monster.push({nx, ny});
            }
        }
    }

    // --- Player BFS ---
    // Grid for player distances
    vector<vector<int>> player_time(n, vector<int>(m, INF));
    // Grid to store the *move* taken to reach a cell (for path reconstruction)
    // 0 = unvisited, 'S' = start, 'U'/'D'/'L'/'R' = move from parent
    vector<vector<char>> prev_move(n, vector<char>(m, 0));
    queue<pair<int, int>> q_player;

    if (start_pos.first != -1) {
        player_time[start_pos.first][start_pos.second] = 0;
        prev_move[start_pos.first][start_pos.second] = 'S'; // Mark start
        q_player.push(start_pos);
    }

    int end_x = -1, end_y = -1; // To store the exit cell

    while (!q_player.empty()) {
        pair<int, int> curr = q_player.front();
        q_player.pop();
        int x = curr.first;
        int y = curr.second;

        // Check if this is a border cell (an exit)
        if (end_x == -1 && (x == 0 || x == n - 1 || y == 0 || y == m - 1)) {
            end_x = x;
            end_y = y;
            // We found the shortest path to *an* exit, so we can stop the BFS.
            break; 
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + adj[i][0];
            int ny = y + adj[i][1];

            // Check bounds, valid cell, and if player hasn't visited it
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && 
                a[nx][ny] != '#' && player_time[nx][ny] == INF) {
                
                // CRUCIAL CHECK: Player must arrive *before* the monster
                if (player_time[x][y] + 1 < monster_time[nx][ny]) {
                    player_time[nx][ny] = player_time[x][y] + 1;
                    prev_move[nx][ny] = moves[i]; // Store the move
                    q_player.push({nx, ny});
                }
            }
        }
    }

    // --- Output ---
    if (end_x == -1) {
        // No exit found. Check if the start pos was *already* an exit.
        // This is a special case if 'A' starts on the border.
        if (start_pos.first != -1 && (start_pos.first == 0 || start_pos.first == n - 1 || start_pos.second == 0 || start_pos.second == m - 1)) {
             cout << "YES\n";
             cout << 0 << "\n"; // Path length is 0
             cout << "" << "\n"; // Empty path
        } else {
             cout << "NO\n";
        }
    } else {
        cout << "YES\n";
        string path = "";
        int cx = end_x, cy = end_y;

        // Backtrack from the exit cell to the start
        while (prev_move[cx][cy] != 'S') {
            char move = prev_move[cx][cy];
            path += move;
            // Move to the parent cell
            if (move == 'D') cx--;      // Came from Up
            else if (move == 'U') cx++; // Came from Down
            else if (move == 'R') cy--; // Came from Left
            else if (move == 'L') cy++; // Came from Right
        }
        
        // The path was built from end to start, so reverse it
        reverse(path.begin(), path.end());

        cout << path.length() << "\n";
        cout << path << "\n";
    }

    return 0;
}