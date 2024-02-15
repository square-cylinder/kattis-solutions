t,a,d=0,0,1;m=10**9+7
for c in input():t,a,d={"1":(t,(a+d)%m,d),"0":((t+a)%m,a,d),"?":((t*2+a)%m,(a*2+d)%m,(d*2)%m)}[c]
print(t)