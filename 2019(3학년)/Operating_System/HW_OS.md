# HW_OS

## Project1) Shell

### 함수 설명

#### main()
 명령인자를 통해 batch mode와 interactive mode를 구분한다.
 인자 개수가 1개이면 interactive mode를 수행하고 2개이면 batch mode를 수행한다.
 그 외의 개수가 나오면 에러 메시지를 출력한다.

#### Interactive_mode()
 While문을 통해 prompt를 실행할 수 있도록 한다. Fgets로 명령어를 입력받고 quit이면 종료한다. Check_semi함수를 실행해 명령어 개수를 리턴받아 run을 실행한다.

#### batch_mode(char file_name[])
 File_name[]인자는 main문에서 받은 명령인자의 인덱스 1번지의 문자를 받아온다.
 파일스트림을 통해 file을 open하여 안에 내용을 fgets로 읽어들인다. 이 때 quit가 나오면 quit를 읽은 후 출력한 후 종료한다. Check_semi함수를 실행해 명령어 개수를 리턴받아 run을 실행한다.

#### check_semi()
 Strtok를 이용해 명령어의 개수를 return한다. 즉 ls ; pwd ; ls -al 이 입력되면 3을 return한다.
그리고 전역변수인 arr배열에 ;을 기준으로 나눈 명령어들을 저장한다.
 명령어 개수만큼 for문을 돌려 check_option함수에 arr에 저장된 명령어를 인자로 넣어 실행시킨다. 이 작업이 끝나고 나면 명령어가 구분되어 있다.

#### check_option(char com[], int idx)
 Stortok를 이용해 명령어의 옵션을 구분한다. 즉 ls -al에서 ls와 al을 구분한다. 인자로 명령어와 명령어의 개수를 받아 실행한다. 그래서 전역변수로 선언된 cmd_arr이차원 배열을 통해 저장한다. 이때 행은 index이고 열은 명령어를 띄어쓰기로 구분한 것들이 각각 들어가있다.

#### run(int cmd_num)
 : shell에서 가장 중요한 역할을 하는 함수이다. 명령어의 개수를 인자로 받아 실행한다. Pid[cmd_num]만큼 선언한다.
 명령어 개수만큼 for문을 돌며 pid[i]에 folk를 수행한다. 이때 fork가 실패하면 에러처리를 해준다. 그리고 만약 pid[i]가 0이면 자식프로세스 이므로 execvp를 이용해 exec을 실행한다. 이때도 에러가 나면 에러메세지를 출력하고 kill을 통해 child process를 종료한다. for문을 종료한 후 마지막으로 한 번더 for문을 돌면서 pid[i]별로 waitpid를 실행한다.



## Project2) FCFS & MLFQ

## FCFS

### 기본 이론 및 구현

FCFS는 First Come First Served라는 뜻으로 먼저 프로세서를 요청한 프로세스부터 CPU를 할당해주는 알고리즘입니다.

따라서 가장 먼저 요청된 프로세스를 찾아 스케쥴링 해주는 것이 프로젝의 핵심이었습니다.
proc.c의 scheduler함수를 수정해 프로젝트를 진행했습니다.

우리는 먼저 생성된 프로세스를 가장 먼저 스케쥴링 해주기 때문에 ptable의 프로세스를 다 돌면서 pid가 가장 작은 프로세스를 찾아 저장합니다.
왜냐하면 먼저 생성된 프로세스의 pid가 더 작기 때문입니다.
이것을 fcfs라는 프로세스에 저장을 해준 후 기존의 방식대로 swtch switchuvm등의 함수를 통해 스위치 해줍니다.



#### 100ticks가 지날 때

tick은 trap.c코드 중 타이머 인터럽트가 발생할 때 증가됩니다. 따라서 프로세스의 tick값을 저장해주기 위해 proc.h에 proc struct에 pticks라는 변수를 추가했습니다.

또한 proc.c 마지막에 fcfs_ticks_adder(void)라는 pticks를 증가시키는 함수를 만들었고 이 함수를 trap.c에서 사용할 수 있도록 defs.h에 함수를 추가하였습니다.

trap.c 에

![https://hconnect.hanyang.ac.kr/2019_ELE3021_12310/2019_ELE3021_2017030519/uploads/dcf864d582878abc3012dfbe67cd362c/11111111111111.PNG](https://hconnect.hanyang.ac.kr/2019_ELE3021_12310/2019_ELE3021_2017030519/uploads/dcf864d582878abc3012dfbe67cd362c/11111111111111.PNG)
이 if문 안에서 fcfs_ticks_adder()함수를 실행시켰고 그 후 myproc()->pticks값이 100보다 크다면 myproc()->killed=1로 바꾸어 주어 프로세스를 강제종료시킵니다.

### 실행 결과

![https://hconnect.hanyang.ac.kr/2019_ELE3021_12310/2019_ELE3021_2017030519/uploads/e4497df4d3f80db65ba266252c65cd6d/ans2.PNG]()

![https://hconnect.hanyang.ac.kr/2019_ELE3021_12310/2019_ELE3021_2017030519/uploads/87a197a3cafc6b47e140222e529d01a3/ans1.PNG]()

![https://hconnect.hanyang.ac.kr/2019_ELE3021_12310/2019_ELE3021_2017030519/uploads/f9ff6419a5dcfb8ba20b6eb533a1dc7f/ans3.PNG]()



##### test1

먼저 생성된 프로세스가 먼저 cpu에 할당되므로 pid가 작은 프로세스의 모든 출력이 끝난 후 그다음으로 큰 pid를 가진 프로세스의 출력을 해야한다.

##### test2

yield를 하더라도 먼저 생성된 프로세스가 먼저 cpu에 할당되므로 test1과 실행결과가 같습니다.

##### test3

잠들다가 깨어난 프로세스의 pid가 더 작으면 그 pid의 모든 출력을 한 후 원래 프로세스가 다시 수행되어야한다.

##### test4

![https://hconnect.hanyang.ac.kr/2019_ELE3021_12310/2019_ELE3021_2017030519/uploads/3dd49b5b44e87d76e44406751439123b/image.png]()

모든 자식프로세스를 종료시킨다.



### 트러블슈팅

#### panic : trap

 스위치 문 중 인터럽트가 발생하는 부분에 fcfs_tick_adder를 실행시켰더니 예상치 못한 trap이라는 에러가 많이 떴습니다. 그래서 함수를 아래쪽에 이동시키므로써 해결할 수 있었습니다.
위쪽에서 증가하는 기존의 ticks과의 충돌이 발생하여 trap error가 뜬 것이라고 추측했습니다.

#### zombie, init panic

 프로세스를 킬하는 과정에서 test2에서부터 zombie에러가 떠 결과 값이 나오지 않은 에러를 겪었습니다. 종료할 때 exit이나 kill을 사용하면 패닉이 떴고 프로세스의 killed값을 바꿔주며 해결할 수 있었습니다. 

## MLFQ

### 기본 이론

MLFQ는 multilevel feedback queue로 여러개의 레벨을 가지고 있다. 우리 프로젝트에서는 2개의 레벨이 있으며 우선순위가 높은 레벨인 L0는 RR알고리즘을 따라고 ticks가 4주기이다. L1은 pirority queue로 setpriority 시스템콜을 이용해 우선순위를 정해줄 수도 있다. 주기는 8ticks이다.



### 구현

#### 큐 구현

전체적인 큐 구현은 struct proc에 level과 prior변수를 추가해줬다. level이 0이면 L0큐이고 1이면 L1큐로 생각했다. allocproc에서 level과 prior을 0으로 설정하며 프로세스를 만든다.

#### 스케쥴러

proc.c의 스케쥴러 함수를 수정했다.
페이지 테이블을 돌면서 runnable인 level이 0인 프로세스가 있으면 그 프로세스를 RR알고리즘으로 스위치한다.
만약에 그렇지 않으면 priority queue에 대한 구현을 해야한다. 사실 FCFS에서 부호만 바꾸면된다. 페이지테이블을 다시돌면서 prior가 가장 큰 프로세스를 찾아 스케쥴링 해준다.

#### time quantum

trap.c의 코드를 고친다.
타이머 인터럽트가 발생하는 if문 내에서 struct proc의 pticks값을 증가시킨다.
 그리고 만약 전체 ticks의 값이 100이되면 priority boost를 실행한다.
그리고 레벨이 0일 때는 pticks가 4의 배수가 되면 level을 1로 바꾸고 pticks를 초기화한다.
레벨이 1일 때는 pticks가 8의 배수가 되면 myproc의 prior값을 하나 감소한다. 이때 0보다 클때만 감소시킨다. 그 후 pticks를 초기화한다.

그 후 yield를 실행한다.
이렇게 하면 time quantum이 지날 때마다 레벨을 변경하거나 우선순위를 변경할 수 있다.

#### prior_boost

페이지 테이블을 돌면서 프로세스가 있으면 프로세스의 레벨과 prior을 0으로 초기화하고 pticks의 값도 0으로 바꾼다.

#### getlev 시스템콜

 myproc()->level을 리턴한다.

#### setpriority 시스템콜

페이지 테이블을 돌면서 인자로 받은 pid가 같은 프로세스가 있으면 그 프로세스의 prior를 인자로 받은 prior로 설정한다.

#### yield시스템콜

myproc()->pticks가 0이아니면 myproc()->pticks를 --해야한다. (for prevent gaming the scheduler)

### 실행 결과

![https://hconnect.hanyang.ac.kr/2019_ELE3021_12310/2019_ELE3021_2017030519/uploads/da2f6fc908ed5b2123f6441be8d601d1/%EC%99%84%EC%84%B1.PNG]()

#### test1

: pid가 큰 우선순위 값이 크기 때문에 pid가 큰 프로세스먼저 실행되고 종료됩니다.

#### test2

: 우선순위가 모두 같으므로 pid가 작은순위 먼저 fcfs처럼 동작하여 실행되고 종료됩니다.

#### test3

: yield호출이 잘되어 L0에서만 실행된다.



### 트러블 슈팅

1. ticks이 4이상 증가하지 않아 아이에 쉘조차 실행되지 않은 에러가 발생했습니다. 그 이유를 찾아본 결과 L1의 스케쥴러의 동작이 제대로 되지않아 무한루프로 인한 것이었습니다.
2. pticks를 초기화하지 않아 ticks의 계산이 이상하게 되서 초기화하여 수정했습니다. 
  3 test3에서  yield의 역할이 제대로 되지않아. L0에만 머물러있지 않고 L1에도 갔습니다.
3. 프로세스가 먼저죽지않습니다.
4. set priority 시스템콜을 잘못 설정하여 우선순위가 큰 프로세스가 들어오지 못했습니다. 조건문을 수정한 후 해결했습니다.
5. yield의 게이밍에 관련된 부분을 처리하지않아 test3가 잘 되지않았지만 처리후 해결했습니다.



## Project3) LWP

### LWP란?

LWP는 Light Weight Process의 약자로 경량 프로세스 라는 뜻이고 xv6에서는 pthread로 사용가능한다.
그리고 쓰레드라고 불리어진다.

주요 특징은 다른 LWP와 자원과 주소 공간을 공유해 유저레벨에서의 멀티태스킹을 가능하게 해준다.

### 코드 설명

#### struct proc
int is_thread;
void* retval;
이란 변수를 추가한다. retval은 반환값을 의미하고 is_thread는 thread인지 아닌지 판단해준다.


#### thread_create
기존의 fork와 exec코드를 이용하였습니다. 

#### allocproc()
is_thread =0;으로 초기화 해줍니다.

우선 allocproc으로 프로세스(쓰레드)를 할당받습니다. 
그 후is_thread =1 로 바꾸어 쓰레드임을 설정합니다.

그리고 allocuvm함수를 통해 힙 영역에 메로리를 할당합니다. 

그 후 스택에 값을 저장후 복사해줍니다.
이때 esp는 프로세스 사이즈(np->size) 를 가리켜야 하며 eip는 start_routine을 가리켜야 합니다.

*thread에는 np->pid값을 저장해줍니다.
따로 thread id를 만들어주지 않고 기존의 pid값을 이용했습니다.


#### thread_exit
기존의 exit()함수를 이용했습니다.
기존의 exit함수와 다른 것은 retval의 값을 curproc->retval에 저장해줍니다.


#### thread_join

기존의 wait()함수를 이용했습니다.
기존의 함수와 다른점은 p->pid가 인자로 들어온 thread와 같은지 아닌지를 확인해주어야합니다.
그리고 page table을 돌면서 p가 is_thread인지 아닌지도 확인해 주어야합니다.
 이 때 프로세스가 쓰레드가 아니거나 인자로 받은 쓰레드와 프로세스의 pid값이 같지않으면 continue해주어야 합니다.

그 후 알맞은 p를 찾으면 자원을 정리해주는데 유의할점은 기존의 코드와 달리 freevm(p->pgdir)을 하면 안된다는 것입니다. 이 코드를 실행하면 xv6가 재부팅되는 오류가 발생할 수 있습니다. 왜냐하면 참조하고 있는 pgdir을 프리하면 사용하고 있던 다른 프로세스(쓰레드)들이 사용하지 못하기 때문입니다. 
그리고 *retval 의 값을 p->retval에 저장되어있는 값으로 저장해주어야합니다. 그리고 잘 저장해줬다면 return 0을 통해 함수를 마무리 합니다.

#### fork

기존의 함수를 유지했습니다.



## Project4) Indirect

### fs.h

~~~c
#define NDIRECT 11

struct dinode {
  short type;           // File type
  short major;          // Major device number (T_DEV only)
  short minor;          // Minor device number (T_DEV only)
  short nlink;          // Number of links to inode in file system
  uint size;            // Size of file (bytes)
  uint addrs[NDIRECT+2];   // Data block addresses
};
~~~

: dinode의 addrs배열에 NDIRECT+2로 변경한다.



### fs.c
~~~c
bn -=NINDIRECT;
  if(bn<NINDIRECT*NINDIRECT){
    int s_idx = bn/NINDIRECT;
	int d_idx = bn%NINDIRECT;
	if((addr = ip->addrs[NDIRECT+1])==0)
		ip->addrs[NDIRECT+1]=addr=balloc(ip->dev);
	bp = bread(ip->dev, addr);
	s_idr = (uint*)bp->data;
	if((addr = s_idr[s_idx])==0){
		s_idr[s_idx] =addr = balloc(ip->dev);
		log_write(bp);
	}
	brelse(bp);
	bp2 = bread(ip->dev, addr);
	d_idr = (uint*)bp2->data;
	if((addr = d_idr[d_idx])==0){
		d_idr[d_idx] = addr = balloc(ip->dev);
		log_write(bp2);
	}
	brelse(bp2);
	return addr;	
  }
~~~
부분을 추가하였다.

  if(bn<NINDIRECT*NINDIRECT){
: double indirection인지 체크한다.


```c
bp = bread(ip->dev, addr);
s_idr = (uint*)bp->data;
```
: double indirect table을 get한다.(first level)

  int s_idx = bn/NINDIRECT;
int d_idx = bn%NINDIRECT;

: 엔트리 number와 index를 계산


bp2 = bread(ip->dev, addr);
d_idr = (uint*)bp2->data;

: double indirect table을 get한다.(second level)

```c
if((addr = d_idr[d_idx])==0){
	d_idr[d_idx] = addr = balloc(ip->dev);
	log_write(bp2);
}
```


### 함수 설명

##### log_write
: 로그 헤더에 수정한 블록 번호 추가

##### bread
: blockno에 해당하는 block을 할당받고 빈 블록을 할당받은 경우 disk에서 data를 읽어온다.(idrew_

##### beget
: bcache를 순회하며 해당 블록이 캐시에 있는지 확인해 있으면 블록을 리턴한다.



각각의 함수를 이해하는 부분이 힘들었다. 대부분의 과정은 single indirect를 구현하는 방법과 비슷했다.

