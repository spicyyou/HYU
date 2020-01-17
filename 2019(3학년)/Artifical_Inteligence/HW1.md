# Project1) DFS, BFS, DFID

## N-qeens란?

 N x N 체스판에서 N개의 Queen이 서로 공격하지 않도록 N개의 퀸을 놓는 문제다.
과제는 첫 번째로 찾아진 퀸이 놓여진 위치를 dfs, bfs, dfid 세가지의 방법으로 해결하는 것이다.
단, 기존의 백준에서 풀어보았던 문제와는 다르게 prunning하지않고 expand하는 것이 특징이다.


모든 알고리즘은 n이 20보다 작을때까지라고 가정하고 배열을 선언했다.

## dfs

: row[1] 배열은 1번째 행에 *col이 놓이는 것을 의미한다. 과제를 보면 column의 있는 queen의 row를 출력해야하는데 row를 col이라고 생각하고 퀸을 놓는 방법을 썼다고 바꿔서 생각하면 출력은 무의미하다고 볼 수 있다.


### 함수 설명 
그리고 재귀를 쓰면 (1,1,1,1)이 먼저 찾아지는데 수업시간에 배운 dfs는 stack의 방식으로 LIFO방식을 사용하므로
퀸을 4번째 열에서부터 넣어주는 것으로 for문을 대체했다. 다음은 main문에 있는 dfs를 사용하는 코드이다.

```java
      for (int i = n; i >=1 ; i--) {
         row[1] = i;
         dfs(row,2, n);
      }
```

 맨처음 행은 1로 설정해두고 다음행으로 바로 들어가며 dfs를 시작한다. dfs의 인자는 dfs(int[] row, int row, int n)으로 들어가고 int row는 현재의 row , int n은 n*n의 n이다. 다음은 dfs함수에 관한 코드이다. 

```java
public static void dfs(int[] row,int r, int n){
      if (r>n) {//마지막 행일 때 탐색
         if (possible(row, r - 1) == 1) {
            for (int i = 1; i <= r - 1; i++) {//높아진 열이 모두 가능한지 확인
               if (possible(row, i) == -1) return;
            }
            if (isok == 0) {//제일 처음에 나온 답인지 확인
            	data_dfs = "Location : ";
               for (int i = 1; i <= n; i++) {
            	   data_dfs = data_dfs + (row[i]-1)+" ";
               }
               data_dfs= data_dfs + "\r\n";
               isok++;
            }
         }
      }
      else {
         for (int i = n; i >=1; i--) {//모든 열을 탐색한다. //LIFO방법으로 뒤에서부터 넣어준다.
            row[r] = i;
            dfs(row, r + 1, n);
         }
}
```

possible함수는 현재들어가는 row의 col위치가 유효한지 확인해준다. expand하는 방식이므로 마지막 행에 도착했을 때 row함수를 돌며 유효성을 확인해준다. data_dfs변수는 전역변수로서 main문에서 파일입출력을 위해 이용되는 String변수로 답을 저장한다. isok변수는 제일 처음 나온 답인지 확인해준다. 

```java
 long starttime = System.currentTimeMillis(); //dfs시작시간
      
      for (int i = n; i >=1 ; i--) {
         row[1] = i;
         dfs(row,2, n);
      }
      
      long endtime = System.currentTimeMillis(); //dfs끝나는 시간
```
java에 내장되어있는 System.currentTimeMillis();를 사용한다. 그래서 main문에서 dfs가 시작하기 전 타임과 후타임의 차이를 이용해 시간을 체크한다. 

(endtime-starttime)/1000.0)으로 계산하며 /1000으로 나누는 바람에 가끔 0으로 출력되는 경우가 있다.

## BFS

: bfs는 첫번째 행에서도 모든 열을 넣고 시작하지않고 dfs와 마찬가지로 첫번째 행의 첫번째 열을 기준으로 너비 탐색으로 진행된다. 

### 함수 설명



```java
public static int flag;
   
   public static void bfs(int row[], int now, int n) {
	   //Vector<Integer> members = new Vector<Integer>();
	   Queue<ArrayList> q = new LinkedList<ArrayList>();//queue<vector>자료구조를 이용해서 방문한 모든 행의 열을 저장
	   ArrayList<Integer> v = new ArrayList<Integer>();
	   v.add(now);
	   q.offer(v);//현재 col의 위치를 넣어준다.
	   row[now]=1;
	   while(!q.isEmpty()) {
		   ArrayList<Integer> r = q.poll();//방문한 각 행의 열이 저장되어있다.
		  // q.poll();
		   if(r.size()<n) {//방문한 행의 개수가 n보다 작아야한다.
			   for (int i = 1; i <= n; i++) {//다음 행의 열들을 저장한다.		
				    r.add(i);
				    ArrayList<Integer> temp=new ArrayList<Integer>();
				    for (int j=0;j<r.size();j++) { //java는 shallow copy or deepcopy때문에 vector를 빼면 queue에 있는 값도 빠져 따로 저장함
				    	int a = r.get(j);
				    	temp.add(a);
				    }
					q.offer(temp);
					r.remove(r.size()-1);//방금 저장한 열을 빼고 새로운 열을 집어 넣는다.
				}
		   }
		   if (r.size() == n) {//끝까지 방문했을 때
				for (int i = 0; i < n; i++) {
					row[i+1] = r.get(i);//row배열에 현재까지 방문한 행,열 정보를 넣는다.
				}
				for (int i = 1; i <= n; i++) {//각 퀸이 놓인 자리가 유효한지 판단한다.
					if (possible(row,i) == -1) {
						flag = -1;//가능하지 않다.
						break;
					}
				}
				if (flag == 0&&isok==0) {//가능함 //isok는 처음 나온 값인지를 확인한다.
						data_bfs = "Location : ";
					for (int i = 1; i <= n; i++) { 
						data_bfs = data_bfs + (row[i]-1)+" ";//index가 1로 시작하므로 1을 빼줘서 print함.
					}
					data_bfs= data_bfs + "\r\n";
					isok++;
				}
				flag = 0;//flag를 초기화 시킨다.
		   }
	   }
   }
}
```
row배열과 현재 now와 n을 인자로 받는다. flag 전역변수를 사용해 답을 출력해도 되는지 안되는지 결정한다.
bfs로 탐색해야하므로 모든 열을 저장해줄 스테이너가 따로 필요했다. 그래서 Queue<ArrayList>라는 자료구조를 사용해 행이 늘어날때마다 (1,1) , (1,1,1) 이렇게 vector에 하나씩 추가해 push해준다. 

하지만 문제점이 하나있다.

```java
 if(r.size()<n) {//방문한 행의 개수가 n보다 작아야한다.
			   for (int i = 1; i <= n; i++) {//다음 행의 열들을 저장한다.		
				    r.add(i);
				    ArrayList<Integer> temp=new ArrayList<Integer>();
				    for (int j=0;j<r.size();j++) { //java는 shallow copy or deepcopy때문에 vector를 빼면 queue에 있는 값도 빠져 따로 저장함
				    	int a = r.get(j);
				    	temp.add(a);
				    }
					q.offer(temp);
					r.remove(r.size()-1);//방금 저장한 열을 빼고 새로운 열을 집어 넣는다.
				}
		   }
```

이것은 bfs를 돌면서 마지막 행을 도착하지 않았다면 다음 행에 있는 열을 for문으로 돌면서 push해주는 부분이다.
그러나 만약 여기서 원래 사용하던 어레이리스트인 r을 사용한후 r에 있는 값을 remove해주면 카피되어 큐에 들어있는 것또한 삭제되는 문제점이 있었다. 그래서 어쩔 수 없이 temp라는 어레이리스트를 선언해 for문을 돌면서 r의 있는값을 새롭게 add해주는 방법을 사용했다.

그리고 마지막 행에 도착하면 벡터에 저장했던 열의 정보를 row배열에 저장해 유효한지 확인했다.

시간은 dfs와 마찬가지로 코딩했고  /1000으로 인해 가끔 0으로 출력되는 경우가 있다. 그리고 세 알고리즘 중 가장 시간을 많이 차지했다.


## DFID

: DFID는 dfs와 거의 같은 방식을 사용했다. depth를 하나씩 증가하며 코드를 진행했다.

###함수 설명


```java
for (int i = n; i >=1; i--) {
         for (int d = 1; d <= n; d++) {
            row[1] = i;
            dfid(row, 2, n,d);
         }
      }
```

dfs와 다른점은 원래 for문 안쪽에 d 변수를 이용한 for문을 하나더 만들고 dfid함수의 인자로 넣어줬다.
```java
public static void dfid(int row[], int r, int n, int depth) {
      if (r>depth) {//r이 depth보다 클때 유효성을 확인한다. 
         if (possible(row, r - 1) == 1) {//유효성을 확인한다.
            for (int i = 1; i <= r - 1; i++) {
               if (possible(row, i) == -1) return;//하나라도 유효하지 않으면 return gksek.
            }
            if (isok == 0&&r>n) {//depth가 n까지 가고 처음 답일 때 출력한다. 
            	data_dfid = "Location : ";
               for (int i = 1; i <= n; i++) {
            	   data_dfid = data_dfid + (row[i]-1)+" ";//행과 열을 바꿔서 출력해야함. 어떠헤 하지?
               }
               data_dfid= data_dfid + "\r\n";
               isok++;
            }
         }
      }
      else {
         for (int i = n; i >=1; i--) {//LIFO 방식으로 뒤에서부터 넣어준다.
            row[r] = i;
            dfid(row, r + 1,  n,depth);
         }
      }
   }
```
dfs와 다른점은 첫번째 줄에서  if (r>depth)부분인데 dfs에서는 if(r>n)일때 유효함을 확인했다. 그리고 답을 출력할 때 r>n이라는 조건을 추가로 넣어주어 마지막행까지 도착했을때 결과값을 추가할수 있도록 했다.

시간은 dfs와 bfs를 한 방법과 동일하다. dfs보다 실행시간이 더 오래걸린다. 


## possible 함수

```java
public static int possible(int[] row, int r) {//유효성을 판단하는 함수
      for (int i = 1; i < r; i++) {
         if (row[i] == row[r]) {//같은 행, 열에 있는지 확인
            return -1;
         }
         else if (Math.abs(row[i] - row[r]) == Math.abs(i - r)) { //대각선 확인
            return -1;
         }
      }
      return 1;//유효하면 1을 return 한다.
   }
```
유효하면 1을 유효하지않으면 -1을 리턴해 판단했다.

## 파일 입출력

```java
 String temp = args[0];
      int n= Integer.parseInt(temp);
      String path = args[1];
      
 path=path+"\\"+"result"+n+".txt";
      FileWriter fw = new FileWriter(path);
```
agrs는 명령인수이다. 첫번째 인자로 n을 입력받고 두번째 인자로 path를 입력받는다. 
그러나 과제에서 원한것은 출력파일을 resultn.txt로 만드는 것이므로 path에 스트링을 추가해 FileWriter에 넣는다.


## 출력
출력할때는 답이 없으면 No solution와 Time 0.0을 전역변수인 isok변수를 통해 체크해줬다.
