FILE_NAME = './input.txt'
energy_levels = [list(map(int, list(line.rstrip("\n"))))
                 for line in open(FILE_NAME)]
# top, topright, right, bottomright, bottom, bottomleft, left, topleft
Dy = (-1, -1, 0, 1, 1, 1, 0, -1)
Dx = (0, 1, 1, 1, 0, -1, -1, -1)


def chainReaction(i, j, add_map, energy_levels, count_flash):
    energy_levels[i][j] = 0
    add_map[i][j] = 0
    count_flash[0] += 1
    for dx, dy in zip(Dx, Dy):
        if 0 <= i + dy < len(energy_levels) and 0 <= j + dx < len(energy_levels[i]) and energy_levels[i+dy][j + dx] != 0:
            if energy_levels[i + dy][j + dx] == 9:
                energy_levels[i + dy][j + dx] = 0
                add_map[i+dy][j + dx] = 0
                chainReaction(i + dy, j + dx, add_map,
                              energy_levels, count_flash)
            else:
                energy_levels[i+dy][j + dx] += 1
                add_map[i + dy][j + dx] += 1


def all_zeros(energy_levels):
    for row in energy_levels:
        for elem in row:
            if elem != 0:
                return False

    return True


count_flash = [0]
num_steps = 0
while not all_zeros(energy_levels):
    for i, row in enumerate(energy_levels):
        for j, elem in enumerate(row):
            energy_levels[i][j] += 1

    add_map = [[0] * len(energy_levels)
               for _ in range(len(energy_levels[0]))]
    for i, row in enumerate(energy_levels):
        for j, elem in enumerate(row):
            if elem >= 10:
                chainReaction(i, j,  add_map, energy_levels, count_flash)

    for i, row in enumerate(energy_levels):
        for j, elem in enumerate(row):
            if elem != 0 and add_map[i][j] >= 9:
                chainReaction(i, j,  add_map, energy_levels, count_flash)

    num_steps += 1

for row in energy_levels:
    print(row)
print()

print(count_flash)
print(num_steps)
