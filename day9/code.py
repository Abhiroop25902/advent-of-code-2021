from functools import reduce

FILE_NAME = 'input.txt'
#up, right, down, left
DX = (0, 1, 0, -1)
DY = (-1, 0, 1, 0)


def findBasinSize(heightMap, i, j, visited):
    # print(visited)
    visited.add((i, j))
    for dx, dy in zip(DX, DY):
        if (i + dy >= 0) and (i + dy < len(heightMap)) and (j + dx >= 0) and (j + dx < len(row)) and (heightMap[i+dy][j+dx] != 9) and ((i+dy, j+dx) not in visited):
            findBasinSize(heightMap, i+dy, j+dx, visited)


basinSizes = []

heightMap = [[int(char) for char in line.rstrip('\n')]
             for line in open(FILE_NAME)]

for i, row in enumerate(heightMap):
    for j, elem in enumerate(row):
        isValley = True
        for dx, dy in zip(DX, DY):
            if (0 <= i + dy < len(heightMap)) and (0 <= j + dx < len(row)) and (elem >= heightMap[i+dy][j+dx]):
                isValley = False
                break
        if isValley == True:
            visited = set()
            findBasinSize(heightMap, i, j, visited)
            basinSizes.append(len(visited))
            basinSizes.sort(reverse=True)
            if len(basinSizes) == 4:
                basinSizes.pop()

print(reduce(lambda x, y: x*y, basinSizes))
