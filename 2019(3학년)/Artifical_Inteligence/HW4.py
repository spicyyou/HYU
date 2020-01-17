from z3 import *
import time

# Number of Queens
print("N: ")
N = int(input())

start = time.time()
#variables
X = [Int("x_%s" % (row)) for row in range(N)]

s = Solver()

#formula
s.add([And(X[i]>=0, X[i]<=N-1) for i in range(N)])

#같은 row, 대각선에 존재하지 않는 것을 의미
for i in range(N):
    for j in range(i):
        s.add(X[i] != X[j], X[i]+i != X[j]+j, X[i]-i != X[j]-j)

if s.check() == sat:
    m = s.model()
    #순서대로 출력
    r = [m.evaluate(X[i]) for i in range(N)]
    print(r)

print("elapsed time: ", time.time() - start, " sec")
