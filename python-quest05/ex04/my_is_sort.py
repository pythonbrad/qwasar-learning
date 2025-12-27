"""
:type  param_1: {Integer[]}
:rtype: boolean
"""
def my_is_sort(param_1):
    size = len(param_1);

    if size < 1:
        return 1

    asc = 1 if param_1[0] < param_1[-1] else 0

    for i in range(size-1):
        if param_1[i] > param_1[i+1] == asc:
            return 0

    return 1
