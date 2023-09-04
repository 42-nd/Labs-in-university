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
        if temp < 10:
            res += str(int(temp))
        else:
            res += chr(ord('A') + int(temp) - 10)
        decimal_part = float('0.' + str(temp).split('.')[1])

    return res

def r_to_decimal(num, r):
    res = 0
    try:
        numeric,decimal = num.split('.')
        for i in range(len(numeric)):
            if numeric[i].isdigit():
                res += int(numeric[i]) * (r ** (len(numeric) - i - 1))
            else:
                res += (ord(numeric[i]) - ord('A') + 10) * (r **(len(numeric) - i - 1))
        for i in range(len(decimal)):
            if decimal[i].isdigit():
                res += int(decimal[i]) * (r ** -(i+1))
            else:
                res += (ord(decimal[i]) - ord('A') + 10) * (r **-(i+1))
    except:
        for i in range(len(num)):
            if num[i].isdigit():
                res += int(num[i]) * (r ** (len(num) - i - 1))
            else:
                res += (ord(num[i]) - ord('A') + 10) * (r **(len(num) - i - 1))
    return res

def r_sum(num1, num2, r):
    nums_sum = r_to_decimal(num1, r) + r_to_decimal(num2, r)
    print(nums_sum)
    return decimal_to_r(nums_sum, r)


def r_mul(num1, num2, r):
    nums_prod = r_to_decimal(num1, r) * r_to_decimal(num2, r)
    return decimal_to_r(nums_prod, r)


with open('test.txt') as f:
    lines = [line.rstrip() for line in f]
    for i in range(5):
        print(lines[i],"|",decimal_to_r(float(lines[i]),6))
    for i in range(5,10):
        num,base = lines[i].split(' ')
        print(num,base,"|",r_to_decimal(num,int(base)))   
    print(lines)
num1,num2,base = input().split()
base = int(base)
print(r_sum(num1,num2,base),"|",r_sum(num1,num2,base))