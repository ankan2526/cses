# author: ankan2526
 
import sys,math,heapq,bisect,random,itertools
input = sys.stdin.readline
sys.setrecursionlimit(10**5)
 
ints = lambda : list(map(int,input().split()))
def gprint(ans=''):global t;print(f"Case #{t+1}:",ans)
p = 10**9+7
inf = 10**20+7
adj = [[1, 0], [-1, 0], [0, 1], [0, -1]]
ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
alpha = "abcdefghijklmnopqrstuvwxyz"
ANS = []



'''
'''


n = int(input())
a = ints()


ans = 0

a.append(a[-1])

i, j = 0, 0

store = set()

while True:
    while a[j] not in store:
        store.add(a[j])
        j += 1
    
    while True:
        ans += j-i
        store.remove(a[i])
        i += 1
        if a[i-1] == a[j]:
            break
    
    if j == n:
        break

print(ans)
