FILE_NAME = 'input.txt'

# 2 seg -> 1
# 3 seg -> 7
# 4 seg -> 4
# 5 seg -> 2, 3, 5
# 6 seg -> 0, 6, 9
# 7 seg -> 8


def ansDecode(right, decoder):
    strNum = ''

    for digit in right:
        strNum = strNum + decoder[digit]
    return int(strNum)


def decode(left, right):
    decoder = {}
    decoder[left[0]] = '1'
    decoder[left[1]] = '7'
    decoder[left[2]] = '4'
    decoder[left[9]] = '8'

    # all set operation -> (intersection of 6,0,9) union (4 - 7) = 5
    fiveString = "".join(
        sorted(
            list(set(left[6]).intersection(left[7]).intersection(left[8])
                 .union(set(left[2]).difference(left[1]))
                 )
        )
    )
    decoder[fiveString] = '5'

    # (4 - 7) union (5 - 4) = 9
    nineString = ''.join(
        sorted(
            set(left[2]).union(left[1]).union(
                set(fiveString).difference(left[2])
            )
        )
    )
    decoder[nineString] = '9'

    # (8 - 4) union 5 = 6
    sixString = ''.join(
        sorted(
            set(left[9]).difference(left[2]).union(fiveString)
        )
    )
    decoder[sixString] = '6'

    # 8 - ((8 - inter(2,3,5)) - 1) = 3
    twoThreeFiveInter = set(left[3]).intersection(
        left[4]).intersection(left[5])
    verticals = set(left[9]) - twoThreeFiveInter
    leftVertical = verticals.difference(left[0])
    threeString = ''.join(sorted(set(left[9]).difference(leftVertical)))
    decoder[threeString] = '3'

    # 8 - (leftTop union rightTop) = 2
    rightVertical = verticals - leftVertical
    leftTop = leftVertical.intersection(fiveString)
    rightBottom = rightVertical.intersection(fiveString)
    notTwo = leftTop.union(rightBottom)
    twoString = ''.join(sorted(set(left[9]).difference(notTwo)))
    decoder[twoString] = '2'

    # (8 - (4 - 1)) union leftTop = 0
    zeroString = ''.join(
        sorted(
            set(left[9]).difference(
                set(left[2]).difference(left[0])
            ).union(leftTop)
        )
    )
    decoder[zeroString] = '0'

    return ansDecode(right, decoder)


left_data = []
right_data = []

for line in open(FILE_NAME):
    left, right = line.rstrip('\n').split('|')
    left_data.append(sorted([''.join(sorted(word))
                     for word in left.split()], key=len))
    right_data.append([''.join(sorted(word))
                      for word in right.split()])
sum = 0
for left, right in zip(left_data, right_data):
    sum += decode(left, right)

print(sum)
