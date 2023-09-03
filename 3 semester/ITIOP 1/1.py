def decimal_to_r(num, r, decimal_places = 5):
    res = ''
    decimal_part = float('0.' + str(num).split('.')[1])
    num = int(num)
    while num > 0:
        temp = num % r
        if temp < 10:
            res += str(temp)
        else:
            res += chr(ord('A') + temp - 10)
        num //= r
    res = res[::-1]
    res += '.'
    for i in range(decimal_places):
        temp = decimal_part * r
        res += str(temp).split('.')[0] 
        decimal_part = float('0.' + str(temp).split('.')[1])
    return res

def r_to_decimal(num, r):
    res = 0
    power = len(num.split('.'))
    num = num.replace('.','')
    for i in range(len(num)):
        if num[i].isdigit():
            res += int(num[i]) * (r ** (power-i))
        else:
            res += (ord(num[i]) - ord('A') + 10) * (r ** (power-i))
    return res

def r_sum(num1, num2, r):
    nums_sum = r_to_decimal(num1, r) + r_to_decimal(num2, r)
    return decimal_to_r(nums_sum, r)


def r_mul(num1, num2, r):
    nums_prod = r_to_decimal(num1, r) * r_to_decimal(num2, r)
    return decimal_to_r(nums_prod, r)


with open('test.txt') as f:
    for i in f:
        line = i.readline()
        print(line)
