from functools import reduce

def sum(a, b) :
    return a + b


operations = {
    'EQUAL': lambda a, b: a == b,
    'NOT_EQUAL': lambda a, b: a != b,
    'MORE_EQUAL': lambda a, b: a >= b,
    'LESS_EQUAL': lambda a, b: a <= b,
    'LESS': lambda a, b: a < b,
    'MORE': lambda a, b: a > b
}

function = {
    'AVG': lambda mas: reduce(sum, mas) / len(mas),
    'MAX': lambda mas: max(mas),
    'COUNT': lambda mas: len(mas)
}