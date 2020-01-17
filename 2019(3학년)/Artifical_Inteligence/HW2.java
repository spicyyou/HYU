package assignment2;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class assignment2 {
	
	//queen의 초기위치 설정
	public static ArrayList<Integer> initial( int n){ //column을 초기화
		ArrayList<Integer> queen = new ArrayList<Integer>();
	    Random random = new Random();
		for (int i=0;i<n;i++) { 
	    	//int temp1 = random.nextInt(n);//0~n-1까지의 랜덤한 수를 처음 queen에 넣어준다.
	    	//queen.add(temp1);
	    	queen.add(i); //각 행에 중복을 없애기 위해 0~n을 넣어준다.
	    }
		Collections.shuffle(queen);//shuffle을 통해 랜덤하게 바꿔준다.
		return queen;
	}
	
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
	
	
	//main
	public static void main(String args[]) throws IOException{
		
    String temp0 = args[0];
    int n= Integer.parseInt(temp0);//n - queens
    String path = args[1];
    
    
    //파일 입출력
    path=path+"\\"+"result"+n+".txt";
    FileWriter fw = new FileWriter(path);
    
    String data = ">Hill Climbing \r\n";
    fw.write(data);
    fw.flush();
    ArrayList<Integer> queen = new ArrayList<Integer>();    
    
    
    long starttime =  System.currentTimeMillis();
    int restart=0;
    //for (int T=0;T<100;T++) {
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
    //}
    long endtime = System.currentTimeMillis();
      //time evaluation
    data = "Total Elapsed Time: "+(endtime-starttime)/100.0+"\r\n";
    fw.write(data);
    //System.out.println(" n이 "+n+"이고 10000번 실행했을 때 restart의 평균 횟수"+restart/10000.0+"번");
    
    fw.flush();
	}
}
