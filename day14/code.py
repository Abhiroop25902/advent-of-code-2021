from collections import defaultdict


def getInput():
    FILE_NAME = "./input.txt"
    inputStringDone = False
    insertionRules = []
    for line in open(FILE_NAME):
        if not inputStringDone:
            inputStringDone = True
            template = line.rstrip('\n')
        elif line.rstrip('\n') != '':
            insertionRules.append(list(l.strip()
                                  for l in line.rstrip('\n').split("->")))

    rules = dict()

    for rule in insertionRules:
        rules[rule[0]] = rule[1]

    return template, rules


def makeTemplateDict(template):
    count = defaultdict(int)

    for i in range(len(template) - 1):
        count[template[i:i+2]] += 1

    return count


def updateTemplateDict(counts, insertionRules):
    newCounts = defaultdict(int)
    for key in counts:
        if key in insertionRules:
            newCounts[key[0] + insertionRules[key]] += counts[key]
            newCounts[insertionRules[key] + key[1]] += counts[key]
        else:
            newCounts[key] = counts[key]
    return newCounts


def maxCountMinusMinCount(counts, template):
    charCount = defaultdict(int)

    for key in counts:
        charCount[key[0]] += counts[key]

    charCount[template[-1]] += 1

    maxCount = max(charCount[char] for char in charCount)
    minCount = min(charCount[char] for char in charCount)

    return maxCount - minCount


template, insertionRules = getInput()
# print(template)
counts = makeTemplateDict(template)

# for rule in insertionRules:
#     print(rule)

# for key in counts:
#     print(f"{key}: {counts[key]}")
# print()

NUM_STEPS = 40

for _ in range(NUM_STEPS):
    counts = updateTemplateDict(counts, insertionRules)
    # for key in counts:
    #     print(f"{key}: {counts[key]}")
    # print()

print(maxCountMinusMinCount(counts, template))
