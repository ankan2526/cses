# author: ankan2526
 
import math, bisect, heapq, random, sys, itertools
#sys.setrecursionlimit(10**6)
input=sys.stdin.readline
 
ints = lambda : list(map(int,input().split()))
alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
p2 = [1]
for i in range(30):p2.append(p2[-1]*2)
p = 10**9+7
ANS=[]
A = 0
 
 
n,m,k = ints()
a = ints()
b = ints()
a.sort()
b.sort()
ind1,ind2 = 0,0
ans = 0
while ind1<n and ind2<m:
    if a[ind1]-k<=b[ind2]<=a[ind1]+k:
        ind1+=1
        ind2+=1
        ans+=1
    elif a[ind1]-k>b[ind2]:
        ind2+=1
    else:
        ind1+=1
print(ans)
