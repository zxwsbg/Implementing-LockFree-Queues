import os

f = open("./build/1.out")
line = f.readline()

dict_produce = {}
dict_consume = {}

while line:
    a = line.split()
    key = a[0]
    if key == "produce":
        val = int(a[1])
        if dict_produce.get(val, 0) == 1:
            print("LockFree error: ", key, val)
            # exit()
        dict_produce[val] = 1
    elif key == "consume":
        val = int(a[1])
        if dict_consume.get(val, 0) == 1:
            print("Lockfree error: ", key, val)
            # exit()
        dict_consume[val] = 1
    line = f.readline()
f.close()

print("LockFree correctness test pass!")