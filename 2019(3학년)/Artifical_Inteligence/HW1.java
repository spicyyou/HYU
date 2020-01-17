package projeck;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Vector;

//bfs, 파일입출력 함수 내에서 프린트, 띄어쓰기 어떻게할지
public class assignment {
	//파일입출력에 출력할 변수들
   public static String data_dfs;
   public static String data_bfs;
   public static String data_dfid;
   
	
	public static int isok;
   
   //유효성을 판단하는 함수
   //row[1]=2의 뜻은 1번째 행과 2번째 열에 놓아져 있음을 의미한다.
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

   //dfs
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
   }
   
   //bfs

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
   
   
   
   
   
   
   //dfid
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
   
   
   
   //main
   public static void main(String args[]) throws IOException{
      String temp = args[0];
      int n= Integer.parseInt(temp);
      String path = args[1];
      
      int[] row= new int[20]; //row배열 선언
      path=path+"\\"+"result"+n+".txt";
      FileWriter fw = new FileWriter(path);
      
      
      //dfs
      String data = ">DFS\r\n";
      fw.write(data);
      //fw.flush();
      int flag = 0; //flag 전역변수, 답이 있는지 확인
      long starttime = System.currentTimeMillis(); //dfs시작시간
      
      for (int i = n; i >=1 ; i--) {
         row[1] = i;
         dfs(row,2, n);
      }
      
      long endtime = System.currentTimeMillis(); //dfs끝나는 시간
      
      if(data_dfs!=null && !data_dfs.isEmpty()) {
    	  fw.write(data_dfs);
      }
      if(isok == 0) { //No solution
         data = "No solution\r\nTime : 0.0\r\n";
         fw.write(data);
      }
      else { 
         data = "Time : "+((endtime-starttime)/1000.0)+"\r\n";
         fw.write(data);
      }
      
      fw.write("\r\n");
      //row, isok 초기화 
      for (int i=0;i<20;i++) { 
         row[i]=0;
      }
      isok=0;
      
      
      
      //bfs

      data = ">BFS\r\n";
      fw.write(data);
      starttime = System.currentTimeMillis(); //bfs시작시간
      for (int i = 1; i <= n; i++) {
          bfs(row,i,n);
      } 
      endtime = System.currentTimeMillis(); //bfs끝나는 시간
      
      if(data_bfs!=null && !data_bfs.isEmpty()) {
    	  fw.write(data_bfs);
      }
      if(isok == 0) { //No solution
          data = "No solution\r\nTime : 0.0\r\n";
          fw.write(data);
       }
       else { 
          data = "Time : "+((endtime-starttime)/1000)+"\r\n";
          fw.write(data);
       }
      fw.write("\r\n");
      //isok, row 초기화
      for (int i=0;i<20;i++) { 
         row[i]=0;
      }
      isok=0;
      
      
      
      //dfid
      data = ">DFID\r\n";
      fw.write(data);
      
      starttime = System.currentTimeMillis(); //dfid시작시간
      for (int i = n; i >=1; i--) {
         for (int d = 1; d <= n; d++) {
            row[1] = i;
            dfid(row, 2, n,d);
         }
      }
      endtime = System.currentTimeMillis(); //dfid끝나는 시간
      
      if(data_dfid!=null && !data_dfid.isEmpty()) {
    	  fw.write(data_dfid);
      }
      if(isok == 0) { //No solution
         data = "No solution\r\nTime : 0.0\r\n";
         fw.write(data);
      }
      else { 
         data = "Time : "+((endtime-starttime)/1000)+"\r\n";
         fw.write(data);
      }
      fw.flush();
      fw.close();
   }

}