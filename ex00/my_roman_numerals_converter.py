import sys


if len(sys.argv) < 2:
    exit(0)

text = sys.argv[1]
out = ""
n = len(text)

symbols = ['I', 'V', 'X', 'L', 'C', 'D', 'M']

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
        out += symbols[p] + symbols[p+1]

print(out)
