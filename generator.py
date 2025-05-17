import math
import random

# List of 15 Indian airports (IATA codes)
indian_airports = [
    "DEL", "BLR", "BOM", "MAA", "HYD", "CCU", "PNQ", "COK", "GOI", "IXC",
    "LKO", "AMD", "JAI", "SXR", "TRV"
]

# List of 35 foreign airports (example codes)
foreign_airports = [
    "JFK", "LHR", "CDG", "FRA", "HND", "SYD", "DXB", "SIN", "YYZ", "GRU",
    "ATL", "PEK", "ORD", "MAD", "BCN", "MEX", "MUC", "AMS", "SFO", "IST",
    "NRT", "DUB", "CPT", "KUL", "AKL", "ZRH", "BKK", "SVO", "MEL", "EWR",
    "LGW", "FCO", "SHA", "VIE", "CPH", "MNL", "SEA"
]

# Shuffle and pick 15 Indian and 35 foreign
random.shuffle(indian_airports)
random.shuffle(foreign_airports)

airports = indian_airports[:15] + foreign_airports[:35]

# Origin and Destination chosen randomly from the airports
origin = random.choice(airports)
destination = random.choice(airports)
while destination == origin:
    destination = random.choice(airports)

# Fuel between 0 and 5000
fuel = random.randint(1000, 5000)

# Destination angle θF in degrees (0 to 359)
thetaF = random.uniform(0, 360)

# Number of other airports N (excluding origin)
N = len(airports) - 1

print(f"{origin} {destination} {fuel} {thetaF:.2f}")
print(N)

for code in airports:
    if code == origin:
        continue
    # Random distance 100 to 30000
    dist = random.randint(100, 30000)
    angle = random.uniform(0, 360)
    print(f"{code} {dist} {angle:.2f}")
