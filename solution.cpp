#include <bits/stdc++.h>
using namespace std;

struct Airport {
    string code;
    double x, y;
};

double toRadians(double deg) {
    return deg * M_PI / 180.0;
}

double dist(const Airport &a, const Airport &b) {
    return hypot(a.x - b.x, a.y - b.y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string originCode, destCode;
    int F; // initial fuel
    cin >> originCode >> destCode >> F;

    int N; cin >> N;

    vector<Airport> airports;
    airports.push_back({originCode, 0.0, 0.0}); // origin at (0,0)

    // Read other airports including destination
    for (int i = 0; i < N; i++) {
        string code; double D, theta;
        cin >> code >> D >> theta;
        double x = D * cos(toRadians(theta));
        double y = D * sin(toRadians(theta));
        airports.push_back({code, x, y});
    }

    // Find index of destination in airports
    int destIndex = -1;
    for (int i = 0; i < (int)airports.size(); i++) {
        if (airports[i].code == destCode) {
            destIndex = i;
            break;
        }
    }
    if (destIndex == -1) {
        cout << "NO PATH\n";
        return 0;
    }

    int n = airports.size();

    // Build graph with distances
    vector<vector<double>> graph(n, vector<double>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                graph[i][j] = dist(airports[i], airports[j]);
            }
        }
    }

    // State: (totalFuelUsed, currentAirport, fuelLeft)
    using State = tuple<int, int, int>;
    // dist[u][fuelLeft] = minimal total fuel used to reach u with fuelLeft fuel
    vector<vector<int>> dist(n, vector<int>(5001, INT_MAX));
    vector<vector<int>> parent(n, vector<int>(5001, -1));
    vector<vector<int>> fuelParent(n, vector<int>(5001, -1));

    priority_queue<State, vector<State>, greater<State>> pq;

    dist[0][F] = 0;
    pq.push({0, 0, F});

    while (!pq.empty()) {
        auto [totalUsed, u, fuelLeft] = pq.top();
        pq.pop();
        if (dist[u][fuelLeft] < totalUsed) continue;
        if (u == destIndex) break;

        // Refuel at u (if not already full)
        if (fuelLeft < 5000) {
            if (dist[u][5000] > totalUsed) {
                dist[u][5000] = totalUsed;
                parent[u][5000] = parent[u][fuelLeft];
                fuelParent[u][5000] = fuelLeft;
                pq.push({totalUsed, u, 5000});
            }
        }

        // Try moving to next airports
        for (int v = 0; v < n; v++) {
            if (v == u) continue;
            int needed = (int)round(graph[u][v]);
            if (needed <= fuelLeft) {
                int newTotal = totalUsed + needed;
                int newFuelLeft = fuelLeft - needed;
                if (dist[v][newFuelLeft] > newTotal) {
                    dist[v][newFuelLeft] = newTotal;
                    parent[v][newFuelLeft] = u;
                    fuelParent[v][newFuelLeft] = fuelLeft;
                    pq.push({newTotal, v, newFuelLeft});
                }
            }
        }
    }

    // Find minimal dist at destIndex
    int bestFuelUsed = INT_MAX;
    int bestFuelLeft = -1;
    for (int f = 0; f <= 5000; f++) {
        if (dist[destIndex][f] < bestFuelUsed) {
            bestFuelUsed = dist[destIndex][f];
            bestFuelLeft = f;
        }
    }

    if (bestFuelUsed == INT_MAX) {
        cout << "NO PATH\n";
        return 0;
    }

    // Reconstruct path
    vector<int> path;
    int curNode = destIndex, curFuel = bestFuelLeft;
    while (curNode != -1) {
        path.push_back(curNode);
        int p = parent[curNode][curFuel];
        int pf = fuelParent[curNode][curFuel];
        curNode = p;
        curFuel = pf;
    }
    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); i++) {
        cout << airports[path[i]].code;
        if (i + 1 < path.size()) cout << "->";
    }
    cout << "\n";

    return 0;
}
