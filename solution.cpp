#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

struct Airport {
    string code;
    double x, y;
};

struct Edge {
    int to;
    double cost;
};

int findIndex(const vector<Airport>& airports, const string& code) {
    for (int i = 0; i < airports.size(); ++i) {
        if (airports[i].code == code) return i;
    }
    return -1;
}

vector<string> dijkstra(const vector<vector<Edge>>& graph, int start, int end, int maxFuel) {
    int n = graph.size();
    vector<double> dist(n, numeric_limits<double>::infinity());
    vector<int> prev(n, -1);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            if (edge.cost > maxFuel) continue; // can't travel if fuel is insufficient

            int v = edge.to;
            double newDist = dist[u] + edge.cost;

            if (newDist < dist[v]) {
                dist[v] = newDist;
                prev[v] = u;
                pq.push({newDist, v});
            }
        }
    }

    vector<string> path;
    if (dist[end] == numeric_limits<double>::infinity()) return path;

    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(graph[at].empty() ? "" : to_string(at));
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    string originCode, destinationCode;
    int fuelAvailable, n;
    cin >> originCode >> destinationCode >> fuelAvailable;
    cin >> n;

    vector<Airport> airports;
    unordered_map<string, int> codeToIndex;

    // Origin is at (0, 0)
    airports.push_back({originCode, 0, 0});
    codeToIndex[originCode] = 0;

    for (int i = 0; i < n; ++i) {
        string code;
        double dist, angle;
        cin >> code >> dist >> angle;
        double rad = angle * M_PI / 180.0;
        double x = dist * cos(rad);
        double y = dist * sin(rad);
        codeToIndex[code] = airports.size();
        airports.push_back({code, x, y});
    }

    // Build graph
    int totalAirports = airports.size();
    vector<vector<Edge>> graph(totalAirports);

    for (int i = 0; i < totalAirports; ++i) {
        for (int j = 0; j < totalAirports; ++j) {
            if (i == j) continue;
            double dx = airports[i].x - airports[j].x;
            double dy = airports[i].y - airports[j].y;
            double dist = sqrt(dx * dx + dy * dy);
            if (dist <= 5000) { // max range between refuels
                graph[i].push_back({j, dist});
            }
        }
    }

    int start = codeToIndex[originCode];
    int end = codeToIndex[destinationCode];

    vector<string> pathIndices = dijkstra(graph, start, end, fuelAvailable);

    if (pathIndices.empty()) {
        cout << "No valid path found" << endl;
    } else {
        for (int i = 0; i < pathIndices.size(); ++i) {
            if (i > 0) cout << "->";
            cout << airports[stoi(pathIndices[i])].code;
        }
        cout << endl;
    }

    return 0;
}