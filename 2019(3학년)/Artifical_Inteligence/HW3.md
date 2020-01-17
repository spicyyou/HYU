# Project3) N-queen: Genetic Algorithm

## 기본 설정

- population : 1000
- parent : 0.1 (100 명)
- crossover rate : 0.9(900명)
- mutation rate : 1/9 (900 명 중 100명) //주석에는 0.1로 잘못 적혀있습니다.
- gene은 1차원배열 queen으로 인덱스는 그 열을 값은 행을 의미한다.

## parent select


```java
ArrayList<ArrayList<Integer>> tempgene = new ArrayList<ArrayList<Integer>>();
	    	for (int i=0;i<100;i++) {//population의 fitness 검사 후 pair로 리스트에 넣어줌 //parent생성
	    		int min=99999999;
	    		int idx=0;
	    		for (int j=0;j<10;j++) {//1000개중 10개의 랜덤수를 뽑은 후 가장 fiteness가 좋은 값을 parent로 넣어준다.
	    			Random random = new Random();
	    			int randnum = random.nextInt(1000); //0~999번지 중 랜덤한 수를 뽑는다.
	    			int f = fitness(nextgene.get(randnum),n);
	    			if(min>f) {
	    				min=f;
	    				idx=randnum;
	    			}
	    		}
	    		tempgene.add(nextgene.get(idx));
	    	}
```

전 generation과정에서 생성된 1000명 중 100명을 parent로 설정한다.
parent는 1000개중 10개의 랜덤 수를 뽑은 후 가장 fitness가 좋은 값을 parent로 설정한다. 이 과정을 100번 반복

## fitness

```java
public static int fitness(ArrayList<Integer> t, int n) { //인자로 들어온 ArrayList의 fitness 검사 //서로 몇개를 공격할 수 있는지
		int cnt=0;
		for (int i = 0; i < n; i++) {
			for (int j=0; j<n ;j++) {
				if(i!=j) {
					if(t.get(i)==t.get(j)|Math.abs(t.get(i) - t.get(j)) == Math.abs(i - j)) { //대각선을 공격할수 있으면 cnt++
						cnt++;
					}
				}
			}
		}
	    return (cnt/2);//중복되므로 2를 나눈값을 추가한다.
	}
```

서로 공격 가능한 수를 fitness수로 뒀다. 0일때 n-queen이 성립한다.
세대가 다 생성된 후 마지막에 생성된 1000개의 gene 의 fitness의 값을 찾아서 만족하는 것이 있는지 확인한다.

## cross-over algorithm

```java
for (int i=100;i<1000;i++) {
	    		Random random = new Random();
	    		//crossover할 father와 mother 선택
	    		int father = random.nextInt(100);
	    		int mother = random.nextInt(100);
	    		if(mother==father) {
	    			while(mother==father) {//mother와 father가 같지 않도록 해준다.
	    				mother=random.nextInt(100);
	    			}
	    		}
	    		
		    	int point = random.nextInt(n-2)+1;//1부터 n-2중 랜덤변수 생성 //어디에서 crossover point
		    	ArrayList<Integer> cross = new ArrayList<Integer>();
		    	//point기준으로 crossover
		    	for (int c=0;c<point;c++) {
		    		cross.add(tempgene.get(father).get(c));
		    	}
		    	for (int c = point;c<n;c++) {
		    		cross.add(tempgene.get(mother).get(c));
		    	}
		    	tempgene.add(cross);
	    	}
```
parent 100 개중 father와 mother로 고를 인덱스를 랜덤하게 고른다. 이때 같지 않도록 설정해준다.
그 후 cross over point또한 랜덤으로 정한후 father의 0-crossoverpoint-1번지까지의 값이랑 crossoverpoint -(n-1) 번지까지의 값을 합쳐서 gene으로 만든다.

## mutation oprater

```java
for (int i=0;i<100;i++) {//mutation rate = 0.1 // 100
	    		Random random = new Random();
	    		int mutation_idx = random.nextInt(900)+100; //생성된 자식중 랜덤으로 돌연변이될 자식을 뽑는다.
	    		ArrayList<Integer> mut = new ArrayList<Integer>();
	    		for (int m=0;m<n;m++) {
	    			int randnum = random.nextInt(n);
	    			mut.add(randnum);
	    		}
	    		tempgene.set(mutation_idx, mut);	    		
	    	}
```
자식의 번지 100~999까지의 랜덤인덱스를 뽑아 아이에 랜덤한 값으로 값을 변경해준다. 이 과정을 100번 반복한다. 
mutation rate는 900중 100개이다. 1/9 확률이다 .

## 실행 화면 출력

- n=10
  ![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/f7211223665b1594927c434a9edd61fd/image.png]()

- n=8
  ![https://hconnect.hanyang.ac.kr/2019_CSE4007_12853/2019_CSE4007_2017030519/uploads/e9cbd0bd1c3f9d8db0e72e27b09be987/image.png]()


## 결과에 대한 분석

- 장점:
  같은 n 값이어도 다양한 결과를 확인할 수 있다.
  번거로운 미분같은 연산이 필요없다.


- 단점:
  개체수 , 선택방법 등 결정해야할 요소가 많고 어떤 결정을 함에 따라 결과가 달라진다.
  같은 결과가 나와도 재현이 불가능하다.
  초기 값이 잘못설정되면 generation이 매우 커질 수 있다.
  계산이 많고 느릴 수 있다.