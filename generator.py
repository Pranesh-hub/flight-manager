import random
import math

# Fixed airport list with (code, country)
airports_list = [
    # 15 Indian airports (example)
    ("DEL", "India"), ("BOM", "India"), ("BLR", "India"), ("HYD", "India"), ("MAA", "India"),
    ("CCU", "India"), ("GOI", "India"), ("PNQ", "India"), ("COK", "India"), ("AMD", "India"),
    ("LKO", "India"), ("IXZ", "India"), ("JAI", "India"), ("TRV", "India"), ("PAT", "India"),
    # 35 International airports (example)
    ("JFK", "USA"), ("LHR", "UK"), ("CDG", "France"), ("DXB", "UAE"), ("HND", "Japan"),
    ("FRA", "Germany"), ("SIN", "Singapore"), ("SYD", "Australia"), ("GRU", "Brazil"), ("YYZ", "Canada"),
    ("AMS", "Netherlands"), ("MEX", "Mexico"), ("ICN", "South Korea"), ("MAD", "Spain"), ("FCO", "Italy"),
    ("SVO", "Russia"), ("BKK", "Thailand"), ("ZRH", "Switzerland"), ("EWR", "USA"), ("MUC", "Germany"),
    ("KUL", "Malaysia"), ("BOM", "India"), ("CPT", "South Africa"), ("DME", "Russia"), ("LAX", "USA"),
    ("PHX", "USA"), ("IAD", "USA"), ("SFO", "USA"), ("ATL", "USA"), ("ORD", "USA"),
    ("DEL", "India"), ("LIS", "Portugal"), ("BRU", "Belgium"), ("VIE", "Austria"), ("MAN", "UK"),
    ("ARN", "Sweden"), ("CPH", "Denmark"), ("HEL", "Finland"), ("OSL", "Norway"), ("WAW", "Poland"),
]

def generate_polar_coords():
    # Distance: 100 to 30000 units
    dist = random.randint(100, 30000)
    # Angle in degrees 0-359
    angle = random.randint(0, 359)
    return dist, angle

def generate_test_case():
    # Select origin and destination distinct
    origin = random.choice(airports_list)[0]
    dest = origin
    while dest == origin:
        dest = random.choice(airports_list)[0]

    # N between 3 and 10
    N = random.randint(3, 10)

    # Pick N-1 other airports (excluding origin but including destination)
    candidates = [a[0] for a in airports_list if a[0] != origin]
    selected = set()
    selected.add(dest)

    while len(selected) < N:
        c = random.choice(candidates)
        selected.add(c)

    # initial fuel between 1000 and 4999 so refuel needed (some airports > initial fuel distance)
    initial_fuel = random.randint(1000, 4999)

    print(f"{origin} {dest} {initial_fuel}")
    print(N)

    # For each airport, generate random dist and angle
    # Make sure destination distance > initial fuel to force refuel
    airport_data = []
    for code in selected:
        if code == dest:
            dist = random.randint(initial_fuel + 100, 30000)
        else:
            dist, _ = generate_polar_coords()
        angle = random.randint(0, 359)
        airport_data.append((code, dist, angle))

    # Shuffle except destination last (optional)
    airport_data_sorted = [a for a in airport_data if a[0] != dest]
    random.shuffle(airport_data_sorted)
    airport_data_sorted.append([a for a in airport_data if a[0] == dest][0])

    for code, dist, angle in airport_data_sorted:
        print(f"{code} {dist} {angle}")

if __name__ == "__main__":
    generate_test_case()
