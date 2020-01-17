# Project2) N-queen: Local Search -Hill Climbing

## 알고리즘 및 objective function 설명

맨 처음 queen의 위치는 랜덤하게 지정한 후 지정된 퀸의 행 위치를 서로 바꾸며 n-queen을 성립시키는 퀸의 위치를 찾는다.

### 퀸 위치 지정 함수
```java
public static ArrayList<Integer> initial( int n){ //column을 초기화
		ArrayList<Integer> queen = new ArrayList<Integer>();
	    Random random = new Random();
		for (int i=0;i<n;i++) { 
	    	//int temp1 = random.nextInt(n);//0~n-1까지의 랜덤한 수를 처음 queen에 넣어준다.
	    	queen.add(i); //각 행에 중복을 없애기 위해 0~n을 넣어준다.
	    }
		Collections.shuffle(queen);//shuffle을 통해 랜덤하게 바꿔준다.
		return queen;
	}

```

0~n-1 column에 0~n-1의 row값을 넣어준다.  이때 각 열별로 중복되는 행은 존재하지 않게 구현했다. 만약 중복을 허용한다면 실행시간이 더 커질 것으로 예상된다. 
그 후 shuffle을 이용해 row의 위치를 랜덤하게 바꾼다.



### Heuristic value 찾기
```java
public static int Heuristic(ArrayList<Integer> queen, int n) { //Heuristic value를 지정한다.
		int cnt=0;
		for (int i = 0; i < n; i++) {
			for (int j=0; j<n ;j++) {
				if(i!=j) {
					if(queen.get(i)==queen.get(j)|Math.abs(queen.get(i) - queen.get(j)) == Math.abs(i - j)) { //대각선을 공격할수 있으면 cnt++
						cnt++;
					}
				}
			}
		}
	    return (cnt/2);//중복되므로 2를 나눈값을 추가한다.
	}
```

이중 for문을 돌며 서로 퀸을 먹을 수 있는 상황일때 cnt를 증가시킨다. 양방향이므로 마지막에 나누기 2를 해준다. return value가 좋을수록 더 좋은 상태로 올라가는 것이다.


### 실행 방법 코드

```java

while(true) {//Heuristic value가 0일때까지 실행
    	queen = initial(n);
    	int startH = Heuristic(queen,n); //시작 Heuristic value저장
    	int flag=0;
    	for (int i=0;i<n;i++) {
    		for (int j=0;j<n;j++) {
    			if(i==j) continue; 
    			ArrayList<Integer> temp1 = new ArrayList<Integer>();
    			for (int k=0;k<n;k++) { //temp1에 값 복사
    				temp1.add(queen.get(k));
    			}
    			temp1.set(i, queen.get(j));//원래 퀸에서 i,j column의 의 row를 바꾼 값을 temp1에 저장 
    			temp1.set(j, queen.get(i));
    			int nowH = Heuristic(temp1,n);
    			if(startH>nowH) { //바꾼 Heuristic value가 처음것보다 작을 때 queen을 temp1로 변경
    				queen=temp1;
    				startH=nowH;
    			}
    			if(startH==0) { //n-queen이 성립할때
    				flag=1;
    				for (int t=0;t<n;t++) {
    					data = queen.get(t)+" ";
    					fw.write(data);
    					//System.out.print(queen.get(t)+ " ");
    					
    				}
    				data="\r\n";
    				fw.write(data);
    				//System.out.println();
    				break;
    			}
    		}
    		if(flag==1) {//값을 찾았을 때 break
    			break;
    		}
    	}
		if(flag==1) {
			break;
		}
		restart++;//restart 횟수 세기
    }

```

temp1 리스트에 원래 queen리스트를 저장하고 i,j의 행 값을 바꾼다. 그래서 두 리스트의 Heuristic value를 확인한 후 더 작으면 queen과 현재의 Heuristic 값을 갱신한다.
Heristic value가 0이되면 서로 공격할수 있는 퀸의 쌍이 없는 것이므로 n-queen을 성립시킨다. 그 후 출력한 후 종료한다.


## 실행화면 출력
![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/81a96f8e050ca460d2aa8cfa3288a647/image.png]()

![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/81a96f8e050ca460d2aa8cfa3288a647/image.png]()

n이 30일때도 터지지않고 잘 실행된다.


## 결과에 대한 분석

for문을 돌려 실행을 여러번 반복하며 restart의 평균 횟수에 대해 계산해 보았다.

- n이 8일 때

![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/6bf4e2b375508fb211039a5a4e12751a/image.png]()

- n이 20일때
  ![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/20b0c77384c1cf874df584db6df0b4cb/image.png]()


그러나 반복을 몇번 하는지에 따라 랜덤하게 변한다.