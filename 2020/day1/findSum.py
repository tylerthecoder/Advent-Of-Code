

f = open("data.txt", "r")

seenSet = set();

for line in f:
    num = int(line)
    if num in seenSet:
        print("Found it")
        print(num, 2020-num)
        print(num * (2020-num))
    else: 
        seenSet.add(2020 - num)

