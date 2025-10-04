a=input()
maxx=0
c=1
for i in range(1,len(a)):
    if a[i]==a[i-1]:
        c+=1
    else:
        if c>maxx:
            maxx=c
        c=1
print(max(maxx,c))
