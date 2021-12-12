from collections import defaultdict

FILE_NAME = "./input.txt"

edges = [line.rstrip('\n').split("-") for line in open(FILE_NAME)]
adjacencyList = defaultdict(list)
nodes = set()

for edge in edges:
    for node in edge:
        nodes.add(node)
    adjacencyList[edge[0]].append(edge[1])
    adjacencyList[edge[1]].append(edge[0])


def dfs(adjacencyList, nodeName: str, visitsRemaining, currPath: list[str], paths: set):
    if nodeName == "end":
        paths.add(str(currPath))
        return

    for val in adjacencyList[nodeName]:
        if visitsRemaining[val] > 0:
            currPath.append(val)
            visitsRemaining[val] -= 1
            dfs(adjacencyList, val, visitsRemaining, currPath, paths)
            visitsRemaining[val] += 1
            currPath.pop()


def createVisitedCountDict(nodes, doubleNode=""):
    visitsRemaining = dict()
    for node in nodes:
        if node == doubleNode:
            visitsRemaining[node] = 2
        elif node[0].islower():
            visitsRemaining[node] = 1
        else:
            visitsRemaining[node] = 1000000000000000
    
    visitsRemaining['start'] = 0
    return visitsRemaining

print(f"filename: {FILE_NAME}")
# Part 1
paths = set()
visitsRemaining = createVisitedCountDict(nodes)
currPath = ['start']
dfs(adjacencyList, 'start', visitsRemaining, currPath, paths)
print("number of paths for part 1: " + str(len(paths)))

# Part 2
paths = set()
for doubleNode in nodes:
    visitsRemaining = createVisitedCountDict(nodes, doubleNode)
    currPath = ['start']
    dfs(adjacencyList, 'start', visitsRemaining, currPath, paths)
print("number of paths for part 2: " + str(len(paths)))
