"""
:type  param_1: {String}
:type  param_2: {String}
:rtype: string[][]
"""
def my_csv_parser(text, sep):
    return [line.split(',') for line in text.strip().split('\n')]
