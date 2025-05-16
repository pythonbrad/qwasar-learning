import sys


def my_roman_numerals_converter(value):
    out = ""
    symbols = ['I', 'V', 'X', 'L', 'C', 'D', 'M']
    text = str(value)
    n = len(text)

    for i in range(n):
        p = (n - i - 1) * 2
        
        d = int(text[i])

        if d < 4:
            out += d * symbols[p]
        elif d == 4:
            out += symbols[p] + symbols[p+1]
        elif d < 9:
            out += symbols[p+1] + (d - 5) * symbols[p]
        elif d == 9:
            out += symbols[p] + symbols[p+2]

    return out
