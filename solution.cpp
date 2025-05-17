#include <bits/stdc++.h>
using namespace std;

struct Airport {
    string code;
    double x, y;
    int idx;
};

const int MAXN = 55;
const int MAXFUEL = 5000;

int N;
Airport airports[MAXN];
map<string,int> codeToIdx;
double distMat[MAXN][MAXN];
int F;
int startIdx, destIdx;

// Convert polar to Cartesian
pair<double,double> polarToCartesian(double dist, double angleDeg) {
    double rad = angleDeg * M_PI / 180.0;
    return {dist*cos(rad), dist*sin(rad)};
}

// Euclidean distance
double euclid(const Airport &a, const Airport &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

// State: current airport index, current fuel left
// We'll do a Dijkstra over states (airport, fuel left)
// At each airport, can refuel to full 5000
// Edges: travel to another airport if fuel left >= needed
// Cost: total fuel consumed (distance traveled)
// We want to minimize total fuel consumed
// If tie: lex smallest path (we can store path in parent and use lex order for tie-breaking)

struct State {
    int airport;
    int fuelLeft;
    double cost; // total fuel consumed so far
    string path;
    bool operator<(const State &o) const {
        if (cost != o.cost) return cost > o.cost; // min-heap by cost
        return path > o.path; // lex order tie-break
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    double thetaF;
    cin >> A >> B >> F >> thetaF;
    cin >> N;

    // origin airport at (0,0)
    airports[0] = {A, 0.0, 0.0, 0};
    codeToIdx[A] = 0;

    // Destination coordinates from origin using F and thetaF
    auto [dx, dy] = polarToCartesian(0, 0); // we'll overwrite below
    airports[N+1] = {B, 0, 0, N+1};
    codeToIdx[B] = N+1;

    // Read other airports (Xi Di θi)
    for (int i = 1; i <= N; i++) {
        string code; double dist, angle;
        cin >> code >> dist >> angle;
        auto [x, y] = polarToCartesian(dist, angle);
        airports[i] = {code, x, y, i};
        codeToIdx[code] = i;
    }

    // Destination airport's coordinates
    // The input format states destination is included with others, so we expect it in the N lines?
    // But your format has destination's distance + angle as thetaF (separate)
    // So let's overwrite the dest airport location using given thetaF and F as distance? 
    // Actually no, destination distance must be known from input N lines
    // So we assume the destination airport is part of the N airports list with code B.
    // To fix: destination airport should be included in N lines. 
    // We'll just find destIdx after input

    startIdx = 0;
    if (codeToIdx.find(B) == codeToIdx.end()) {
        cout << "NO PATH\n";
        return 0;
    }
    destIdx = codeToIdx[B];

    // Build distance matrix
    int totalAirports = N+1; // origin + N airports (including destination)
    for (int i = 0; i < totalAirports; i++) {
        for (int j = 0; j < totalAirports; j++) {
            distMat[i][j] = euclid(airports[i], airports[j]);
        }
    }

    // Dijkstra on state (airport, fuel left)
    // We'll keep dist[airport][fuel] = minimal fuel consumed so far
    // But fuel is from 0 to 5000, too large for exact
    // Optimization: only track fuelLeft in steps of 1 might be large
    // Instead, track dist[airport] = minimal fuel consumed to reach airport with any fuel left.
    // But fuelLeft affects possibility to go further.

    // So we do a priority queue storing State:
    // State: airport, fuelLeft, cost, path string
    // Whenever we reach an airport, we can refuel to 5000 if needed.

    vector<vector<double>> dist(totalAirports, vector<double>(MAXFUEL+1, 1e18));
    vector<vector<string>> paths(totalAirports, vector<string>(MAXFUEL+1, ""));
    priority_queue<State> pq;

    dist[startIdx][F] = 0.0;
    paths[startIdx][F] = A;
    pq.push({startIdx, F, 0.0, A});

    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();
        int u = cur.airport;
        int fuelLeft = cur.fuelLeft;
        double cost = cur.cost;
        string path = cur.path;

        if (u == destIdx) {
            cout << path << "\n";
            return 0;
        }

        if (dist[u][fuelLeft] < cost) continue;

        // Option 1: Refuel here if not already full
        if (fuelLeft < MAXFUEL) {
            int newFuel = MAXFUEL;
            if (dist[u][newFuel] > cost) {
                dist[u][newFuel] = cost;
                paths[u][newFuel] = path;
                pq.push({u, newFuel, cost, path});
            } else if (abs(dist[u][newFuel] - cost) < 1e-9 && paths[u][newFuel] > path) {
                // lex smaller path tie-break
                paths[u][newFuel] = path;
                pq.push({u, newFuel, cost, path});
            }
        }

        // Option 2: Fly to other airports if fuel permits
        for (int v = 0; v < totalAirports; v++) {
            if (v == u) continue;
            double d = distMat[u][v];
            if (d <= fuelLeft) {
                double newCost = cost + d;
                int newFuelLeft = fuelLeft - (int)ceil(d);
                string newPath = path + "->" + airports[v].code;

                if (dist[v][newFuelLeft] > newCost) {
                    dist[v][newFuelLeft] = newCost;
                    paths[v][newFuelLeft] = newPath;
                    pq.push({v, newFuelLeft, newCost, newPath});
                } else if (abs(dist[v][newFuelLeft] - newCost) < 1e-9 && paths[v][newFuelLeft] > newPath) {
                    paths[v][newFuelLeft] = newPath;
                    pq.push({v, newFuelLeft, newCost, newPath});
                }
            }
        }
    }

    cout << "NO PATH\n";
    return 0;
}
