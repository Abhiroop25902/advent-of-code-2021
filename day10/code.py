import statistics

FILE_NAME = 'input.txt'
START_BRACKETS = ('(', '[', '{', '<')
END_BRACKETS = (')', ']', '}', '>')
ERROR_COST = {
    ')': 3,
    ']': 57,
    '}': 1197,
    '>': 25137
}
ADD_COST = {
    ')': 1,
    ']': 2,
    '}': 3,
    '>': 4
}


def get_end_bracket(char: str):
    return END_BRACKETS[START_BRACKETS.index(char)]


# part 1
def find_syntax_error_cost(chunk: str):
    stack = list()
    for char in chunk:
        if char in START_BRACKETS:
            stack.append(char)
        elif char in END_BRACKETS:
            if get_end_bracket(stack[-1]) != char:
                return ERROR_COST[char]
            else:
                stack.pop()
        else:
            raise ValueError('unknown symbol found')
    return 0


# part 2
def find_completion_cost(chunk: str):
    stack = list()
    for char in chunk:
        if char in START_BRACKETS:
            stack.append(char)
        elif char in END_BRACKETS:
            if get_end_bracket(stack[-1]) != char:
                return 0
            else:
                stack.pop()
        else:
            raise ValueError('unknown symbol found')

    cost = 0
    while len(stack) > 0:
        cost *= 5
        cost += ADD_COST[get_end_bracket(stack.pop())]

    return cost


chunks = [line.rstrip("\n") for line in open(FILE_NAME)]

print(
    f"error cost = {sum([find_syntax_error_cost(chunk) for chunk in chunks])}"
)

completion_costs = list(filter(
    lambda a: a != 0,
    [find_completion_cost(chunk) for chunk in chunks]
))
print(f"completion cost = {statistics.median(completion_costs)}")
