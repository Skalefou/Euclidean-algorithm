def shor(n):
    if n == 4:
        return 0
    a = 2
    while a < n**(0.5):
       if n % a == 0:
           return 0
       a += 1
    return 1

print("Calculate the sequence of prime numbers")
limit = int(input("Please put a limit : "))
a = 2
while a < limit:
    if shor(a) == 1:
        print(a)
    a += 1