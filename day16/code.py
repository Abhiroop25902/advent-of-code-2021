HEX_TO_BIN = {
    '0': '0000',
    '1': '0001',
    '2': '0010',
    '3': '0011',
    '4': '0100',
    '5': '0101',
    '6': '0110',
    '7': '0111',
    '8': '1000',
    '9': '1001',
    'A': '1010',
    'B': '1011',
    'C': '1100',
    'D': '1101',
    'E': '1110',
    'F': '1111',
}

def letterwiseHexToBin(hexStr):
    binStr = ''

    for char in hexStr:
        binStr += HEX_TO_BIN[char]

    return binStr


versions = []


def processLiteralValue(binary_sequence):
    result = ""
    LITERAL_LEN = 5
    keepGoing = True
    while keepGoing and len(binary_sequence) > 0:
        if binary_sequence[0] == '0':
            keepGoing = False

        result += hex(int(binary_sequence[1:LITERAL_LEN], 2))[2:]
        binary_sequence = binary_sequence[LITERAL_LEN:]

    print(int(result, 16))

    return binary_sequence


def processOperator(binary_sequence):
    if(binary_sequence[0] == '0'):
        binary_sequence = binary_sequence[1:]
        I_LEN = 15
        string_len = int(binary_sequence[:I_LEN], 2)
        binary_sequence = binary_sequence[I_LEN:]
        extractMultiplePacket(binary_sequence[:string_len])
        binary_sequence = binary_sequence[string_len:]
    else:
        binary_sequence = binary_sequence[1:]
        I_LEN = 11
        string_len = int(binary_sequence[:I_LEN], 2)
        binary_sequence = binary_sequence[I_LEN:]

        for _ in range(string_len):
            if len(binary_sequence) > 0 and int(binary_sequence, 2) > 0:
                binary_sequence = extractSinglePacket(binary_sequence)

    return binary_sequence


def extractMultiplePacket(binary_sequence):
    while len(binary_sequence) > 0 and int(binary_sequence, 2) > 0:
        binary_sequence = extractSinglePacket(binary_sequence)


def extractSinglePacket(binary_sequence):
    # [2:] done to ignore '0x' is start
    STATUS_LEN = 3
    version = int(binary_sequence[:STATUS_LEN], 2)
    # print(version)
    global versions
    versions.append(version)
    binary_sequence = binary_sequence[STATUS_LEN:]
    type_ID = hex(int(binary_sequence[: STATUS_LEN], 2))[2:]
    binary_sequence = binary_sequence[STATUS_LEN:]

    if type_ID == '4':
        binary_sequence = processLiteralValue(binary_sequence)
        return binary_sequence
    else:
        return processOperator(binary_sequence)


# binary_sequence = "110100101111111000101000"
# binary_sequence = "00111000000000000110111101000101001010010001001000000000"
# binary_sequence = "11101110000000001101010000001100100000100011000001100000"

# hexStr = "8A004A801A8002F478"
# hexStr = "620080001611562C8802118E34"
# hexStr = "C0015000016115A2E0802F182340"
# hexStr = "A0016C880162017C3686B18A3D4780"

# hexStr = open('./input.txt').read()
# print(hexStr)

hexStr = "C200B40A82"

binStr = letterwiseHexToBin(hexStr)
# print(binStr)

extractMultiplePacket(binStr)
# print(sum(versions))
