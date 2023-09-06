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

    return res.rstrip('0')

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

def normalize_number(num_str):
    if '.' not in num_str:
        return num_str, 0

    dot_pos = num_str.find('.')
    exponent = dot_pos - 1
    num_str = num_str.replace('.','')
    num_str = num_str[:1] + '.' + num_str[1:]
    return num_str, exponent

def decimal_to_byte(num):
    decimal_num = decimal_to_r(abs(num),2) # могут быть баги с тем, что недостаточно знаков после запятой!
    normalize_num, exponent = normalize_number(decimal_num)
    offset = decimal_to_r(float(exponent + 1023),2)

    bin_num = str(int(num <= 0)) + offset[:-1] + normalize_num[2:]
    while len(bin_num) != 32:
        bin_num+='0'
    fourbyte = bin_num
    while len(bin_num) != 64:
        bin_num+='0'
    eightbyte = bin_num

    hex_comp = hex(int(bin_num,2))[2:].upper() # может быть тоже самое, что в bin отрезает первые нули
    return hex_comp,eightbyte,fourbyte

def byte_to_decimal(num,byte_type):
    if byte_type == 1:
        num = hex(int(num,2))[2:].upper()
    while len(num) != 16:
       num += num

    binary_string = bin(int(num,16))[2:]
    while len(binary_string) != 64:
        binary_string = '0' + binary_string
    sign_bit = int(binary_string[0], 2)
    exponent_bits = binary_string[1:12]
    fraction_bits = binary_string[12:]

    exponent = int(exponent_bits, 2) - 1023 
    fraction = 1.0  # Начинаем с мантиссы равной 1

    for i in range(52):
        fraction += int(fraction_bits[i], 2) * 2**(-(i + 1))
    value = (-1)**sign_bit * 2**exponent *r_to_decimal('1.'+fraction_bits,2)
    return value 

num_test = -312.3125
num1 = -75.5625
num2 = 483.5
num3 = -33.0781
num4 = 223.352
print(decimal_to_byte(num_test))
print(decimal_to_byte(num1))
print(decimal_to_byte(num2))
print(decimal_to_byte(num3))
print(decimal_to_byte(num4))
hex_test = '3FEC600000000000'
hex_num1 = 'C3F8C800' 
hex_num2 = '438E5000' 
hex_num3 = 'C07D83E000000000' 
hex_num4 = '403F400000000000' 
print(byte_to_decimal(hex_test,0))
print(byte_to_decimal(hex_num1,0))
print(byte_to_decimal(hex_num2,0))
print(byte_to_decimal(hex_num3,0))
print(byte_to_decimal(hex_num4,0))
