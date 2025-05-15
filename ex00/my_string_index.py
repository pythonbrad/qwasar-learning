"""
:type  param_1: {String}
:type  param_2: {Character}
:rtype: integer
"""
def my_string_index(param_1, param_2):
    for i in range(len(param_1)):
        if param_1[i] == param_2:
            return i
    
    return 0
