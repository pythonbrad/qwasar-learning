"""
:type  param_1: {String[]}
:rtype: string
"""
def my_data_process(data):
    out = {
        'Gender': {},
        'Email': {},
        'Age': {},
        'City': {},
        'Device': {},
        'Order At': {},
    }

    for row in data[1:]:
        cols = row.split(',')
        gender = cols[0]
        email = cols[4]
        age = cols[5]
        city = cols[6]
        device = cols[7]
        order_at = cols[9]

        out['Gender'][gender] = out['Gender'].get(gender, 0) + 1
        out['Email'][email] = out['Email'].get(email, 0) + 1
        out['Age'][age] = out['Age'].get(age, 0) + 1
        out['City'][city] = out['City'].get(city, 0) + 1
        out['Device'][device] = out['Device'].get(device, 0) + 1
        out['Order At'][order_at] = out['Order At'].get(order_at, 0) + 1

    return str(out).replace(", ", ",").replace(": ",":").replace("'", '"')
