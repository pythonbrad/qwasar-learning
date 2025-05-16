"""
:type  param_1: {String[]}
:rtype: integer[]
"""
def my_count_on_it(param_1):
    return list(map(lambda x: len(x), param_1))
