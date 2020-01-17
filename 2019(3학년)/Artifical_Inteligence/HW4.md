# Project4) Sat Solver 

## 정의
Symbol : 일차원 배열, 배열 i번째는 column을 그 값은 row를 의미한다.
formula : 각 변수에 할당 될 수 있는 값. 0~N-1에 해당
Model : Constraints를 모두 만족시키는 상태(대각성 , 행, 열에 겹치지않는다.)

## 실행 화면 (NqueensOpt)

### N=20
![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/66154aa4a46d9aecf9b6b7ee31bbdc5e/image.png]()

### N = 15

![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/df615cb86611db1718328be29dc3f747/image.png]()

### N=10

![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/c90dedcbc95e0f1a044821d101c2ab0e/image.png]()

### N=5

![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/76e617d458cbbb59f343e47003397505/image.png]()

### N=2

![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/ca8eee9d1c6415522479e9ef6668dfcc/image.png]()

만족하는게 없을땐 아무것도 출력하지 않는다.


### 코드

``` python
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

```

변수 선언후 제약조건을 설정해준다.

## 결과 분석

Optimization 방법 : 
1. 이차원 배열 대신 일차원 배열을 선언한다.
2. for문을 두 번돌아 모두 확인하지 않고 현재 col에 대해 col보다 작은 곳의 위치만 확인 

### 실행 결과 비교 (NqueensNaive와 NqueenOpt)

#### NqueensNaive

##### N= 10
![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/243afb10e488ac38c803ec58c2dfffae/image.png]()

##### N= 15
![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/5c5de938a9c07da46072486b5385aa3a/image.png]()

##### N = 20
![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/7df676cc356b15cbacb4621354ac4fac/image.png]()

![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/dd8562d20ad69faded909619b57a95ff/image.png]()

성능계산식 (naive-opt)/naive

성능이 매우 향상된 것을 확인할 수 있다.