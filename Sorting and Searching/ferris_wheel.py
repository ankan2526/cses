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
 
 
n,k = ints()
a = ints()
a.sort()
left,right = 0,n-1
ans = 0
while left<=right:
    if left==right:
        ans+=1
        break
    if a[left]+a[right]<=k:
        left+=1
        right-=1
        ans+=1
    else:
        right-=1
        ans+=1
 
print(ans)
