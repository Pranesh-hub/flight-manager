import random
import math

# Airport codes list (15 Indian + others)
all_airports = [
    "DEL", "BLR", "MUM", "HYD", "CCU", "PNQ", "GOI", "BOM", "AMD", "COK",
    "JAI", "LKO", "MAA", "IXR", "PAT",  # 15 Indian
    "JFK", "LAX", "ORD", "ATL", "DFW", "DEN", "SFO", "SEA", "MIA", "BOS",
    "CDG", "LHR", "FRA", "AMS", "MAD", "BCN", "ROM", "VIE", "ZRH", "CPH",
    "HND", "PEK", "SIN", "SYD", "DXB", "CPT", "GRU", "YVR", "EZE", "MEX"
]

def random_angle():
    return round(random.uniform(0, 360), 2)

def random_dist():
    return random.randint(100, 30000)

def generate():
    # Pick origin and destination distinct
    origin = random.choice(all_airports)
    destination = random.choice(all_airports)
    while destination == origin:
        destination = random.choice(all_airports)

    # Initial fuel 0 to 5000
    initial_fuel = random.randint(0, 5000)

    # Number of airports N: 1 to 10
    N = random.randint(1, 10)

    # Airports to include: destination + N-1 others unique and excluding origin
    used = {origin, destination}
    other_airports = [destination]

    while len(other_airports) < N:
        a = random.choice(all_airports)
        if a not in used:
            used.add(a)
            other_airports.append(a)

    # Print input as per format
    print(f"{origin} {destination} {initial_fuel}")
    print(N)
    for code in other_airports:
        d = random_dist()
        theta = random_angle()
        print(f"{code} {d} {theta}")

if __name__ == "__main__":
    generate()
