
# ✈️ Optimal Air Route

You are the operations manager at a busy airline. With the growth of air travel, the number of flights has risen rapidly. Manual route planning has become infeasible. You're tasked with developing a system to **find the most fuel-efficient route** between two airports.

Given:
- The origin and destination airports.
- Initial fuel in the plane.
- A list of other available airports including the destination airport with their positions defined relative to the origin.

Design a system that **finds the route from the origin to the destination** (possibly via other airports) that consumes the **minimum total fuel**. 

Planes can **refuel to full capacity (5000 units)** at any airport.

Fuel consumption is **1 unit per 1 unit of distance** traveled.

---

## Input

```
A B F θD 
N  
X1 D1 θ1  
X2 D2 θ2  
...  
XN DN θN
```

- `A`: Three-letter origin airport code (e.g., `DEL`)
- `B`: Three-letter destination airport code (e.g., `NYC`)
- `F`: Integer (0 ≤ F ≤ 5000) — initial fuel available in the plane
- `θD`: Angle (in degrees) with respect to the x-axis (0 ≤ θF < 360) (for destination airport)
- `N`: Number of other airports (1 ≤ N ≤ 10)
- Each of the next `N` lines contains:
  - `Xi`: Three-letter airport code
  - `Di`: Distance from `A` (100 ≤ Di ≤ 30000)
  - `θi`: Angle (in degrees) with respect to the x-axis (0 ≤ θi < 360)

---

## Output

```
A->Xk->Xj->...->B
```

Print the route (including intermediate airports) from origin `A` to destination `B` such that the **total fuel consumed is minimized**. If multiple paths have the same fuel usage, output the **lexicographically smallest** one.

If no valid path exists, output:
```
NO PATH
```

---

## Notes

- All positions are in a 2D plane with `A` located at coordinates (0, 0).  
- Use polar to Cartesian conversion to compute coordinates of each airport:
  - `x = D × cos(θ in radians)`
  - `y = D × sin(θ in radians)`
- You may refuel the plane to full capacity (5000 units) at **any airport**, including the origin.
- You may visit an airport multiple times if required.
- Each airport has a unique code.

---

## Example

### Input
```
DEL NYC 2000  
3  
BLR 1800 0  
DXB 1000 90  
NYC 3200 0
```

### Output
```
DEL->BLR->NYC
```

---

## Explanation

- From DEL to BLR: 1800 units of fuel used → 200 left  
- Refuel at BLR to 5000  
- From BLR to NYC: 1400 units used  
- Total fuel used: 3200  
- This is the most fuel-efficient path.

---

## Constraints

- 1 ≤ N ≤ 10  
- 0 ≤ F ≤ 5000  
- 100 ≤ D ≤ 30000  
- 0 ≤ θ < 360  
