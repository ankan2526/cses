n=int(input())
a=[int(i) for i in input().split()]
store=[0 for i in range(n)]
for i in a:
    store[i-1]=1
for i in range(n):
    if store[i]==0:
        print(i+1)
        break