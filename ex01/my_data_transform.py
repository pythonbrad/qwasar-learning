import datetime

def parse_age(age):
    if age < 21:
        return '1->20'
    elif age < 41:
        return '21->40'
    elif age < 66:
        return '41->65'
    elif age < 99:
        return '66->99'
    else:
        return '100->'

def parse_date(date_time_str):
    time = datetime.datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S')

    if time.hour >= 6 and time.hour <= 11:
        return 'morning'
    elif time.hour >= 12 and time.hour <= 17:
        return 'afternoon'
    elif time.hour >= 18 and time.hour <= 23:
        return 'evening'
    else:
        return '?'


"""
:type  param_1: {String}
:rtype: string[]
"""
def my_data_transform(data):
    out = []

    for i, row in enumerate(data.strip().split('\n')):
        cols = row.split(',')

        if not cols: continue

        out.append(','.join(
            [
                *cols[:4], cols[4].split('@')[1], parse_age(int(cols[5])),
                *cols[6:9], parse_date(cols[9])
            ] if i != 0 else cols
        ))

    return out
