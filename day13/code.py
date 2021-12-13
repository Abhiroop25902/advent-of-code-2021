from multipledispatch import dispatch  # for constructor overloading


def getInput():
    FILE_NAME = "./input.txt"
    coordinates = []
    instructions = []
    coordinateDone = False
    for line in open(FILE_NAME):
        if line == '\n':
            coordinateDone = True
            continue

        if not coordinateDone:
            coordinates.append(list(map(int, line.rstrip('\n').split(","))))
        else:
            inst = line.rstrip('\n').split("=")
            instructions.append([inst[0][-1], int(inst[1])])

    return coordinates, instructions


class Table:
    @dispatch(list)
    def __init__(self, coordinates: list):
        maxX = 0
        maxY = 0

        for cooordinate in coordinates:
            maxX = max(maxX, cooordinate[0])
            maxY = max(maxY, cooordinate[1])

        self.table = [["." for _ in range(maxX + 1)] for _ in range(maxY + 1)]

        for cooordinate in coordinates:
            self.setPos(cooordinate[1], cooordinate[0])

    @dispatch(int, int)
    def __init__(self, height, width):
        self.table = [["." for _ in range(width)] for _ in range(height)]

    def setPos(self, i, j):
        self.table[i][j] = '#'

    def getTable(self):
        return self.table

    def printTable(self):
        for row in self.table:
            string = ""
            for elem in row:
                string += elem
            print(string)
        print()

    def dotVisible(self) -> int:
        count = 0

        for row in self.table:
            for elem in row:
                if elem == "#":
                    count += 1
        return count

    def __foldUpBigger(self, idx):
        # upward part is bigger or equal to downward part
        newTable = Table(idx, len(self.table[0]))

        for i in range(idx):
            for j in range(len(self.table[i])):
                if self.table[i][j] == '#':
                    newTable.setPos(i, j)
                elif 2*idx - i < len(self.table) and self.table[2*idx - i][j] == '#':
                    newTable.setPos(i, j)
        return newTable

    def __foldUpSmaller(self, idx):
        # upward part is smaller to downward part
        newTable = Table(len(self.table) - idx - 1, len(self.table[0]))
        newTableI = 0
        for i in range(len(self.table) - 1, idx, -1):
            for j in range(len(self.table[i])):
                if self.table[i][j] == '#':
                    newTable.setPos(newTableI, j)
                elif 2*idx - i >= 0 and self.table[2*idx - i][j] == '#':
                    newTable.setPos(newTableI, j)
            newTableI += 1
        return newTable

    def foldUp(self, idx):
        if idx <= len(self.table)/2:
            return self.__foldUpSmaller(idx)
        else:
            return self.__foldUpBigger(idx)

    def __foldLeftBigger(self, idx):
        # left part is bigger or equal to right part
        newTable = Table(len(self.table), idx)

        for j in range(idx):
            for i in range(len(self.table)):
                if self.table[i][j] == '#':
                    newTable.setPos(i, j)
                elif 2*idx - j < len(self.table[i]) and self.table[i][2*idx - j] == '#':
                    newTable.setPos(i, j)
        return newTable

    def __foldLeftSmaller(self, idx):
        # left part is smaller to right part
        newTable = Table(len(self.table), len(self.table[0]) - idx - 1)
        newTableJ = 0
        for j in range(len(self.table[0]) - 1, idx, -1):
            for i in range(len(self.table)):
                if self.table[i][j] == '#':
                    newTable.setPos(i, newTableJ)
                elif 2*idx - j >= 0 and self.table[i][2*idx - j] == '#':
                    newTable.setPos(i, newTableJ)
            newTableJ += 1
        return newTable

    def foldLeft(self, idx):
        if idx <= len(self.table)/2:
            return self.__foldLeftSmaller(idx)
        else:
            return self.__foldLeftBigger(idx)


coordinates, instructions = getInput()

sheet = Table(coordinates)

for inst in instructions:
    if inst[0] == 'y':
        sheet = sheet.foldUp(inst[1])
    else:
        sheet = sheet.foldLeft(inst[1])
#     break

# print(sheet.dotVisible())
sheet.printTable()
