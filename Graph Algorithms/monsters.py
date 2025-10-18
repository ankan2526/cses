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

n, m = ints()

a = [input().strip() for i in range(n)]

monster_time = [[inf]*m for _ in range(n)]
queue = []
for i in range(n):
    for j in range(m):
        if a[i][j] == 'M':
            monster_time[i][j] = 0
            queue.append((i, j))

while queue:
    q = []
    for x, y in queue:
        for dx, dy in adj:
            nx, ny = x+dx, y+dy
            if 0 <= nx < n and 0 <= ny < m and a[nx][ny] != '#' and monster_time[nx][ny] == inf:
                monster_time[nx][ny] = monster_time[x][y] + 1
                q.append((nx, ny))
    queue = q



player_time = [[inf]*m for _ in range(n)]
prev_cell = [[None]*m for _ in range(n)]
queue = []
for i in range(n):
    for j in range(m):
        if a[i][j] == 'A':
            player_time[i][j] = 0
            queue.append((i, j))

prev_cell[queue[0][0]][queue[0][1]] = "Start"

while queue:
    q = []
    for x, y in queue:
        for dx, dy in adj:
            nx, ny = x+dx, y+dy
            if 0 <= nx < n and 0 <= ny < m and a[nx][ny] != '#' and player_time[nx][ny] == inf:
                if player_time[x][y] + 1 < monster_time[nx][ny]:
                    player_time[nx][ny] = player_time[x][y] + 1
                    prev_cell[nx][ny] = (x, y)
                    q.append((nx, ny))
    queue = q


x, y = -1, -1
for i in range(n):
    if prev_cell[i][0] != None:
        x, y = i, 0
        break
    if prev_cell[i][m-1] != None:
        x, y = i, m-1
        break

for j in range(m):
    if prev_cell[0][j] != None:
        x, y = 0, j
        break
    if prev_cell[n-1][j] != None:
        x, y = n-1, j
        break


if x == -1 and y == -1:
    print("NO")

else:
    print("YES")
    path = []
    while prev_cell[x][y] != "Start":
        px, py = prev_cell[x][y]
        if px == x-1:
            path.append('D')
        elif px == x+1:
            path.append('U')
        elif py == y-1:
            path.append('R')
        else:
            path.append('L')
        x, y = px, py
    path.reverse()
    print(len(path))
    print(''.join(path))