package projeck;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Vector;

//bfs, ��������� �Լ� ������ ����Ʈ, ���� �������
public class assignment {
	//��������¿� ����� ������
   public static String data_dfs;
   public static String data_bfs;
   public static String data_dfid;
   
	
	public static int isok;
   
   //��ȿ���� �Ǵ��ϴ� �Լ�
   //row[1]=2�� ���� 1��° ��� 2��° ���� ������ ������ �ǹ��Ѵ�.
   public static int possible(int[] row, int r) {//��ȿ���� �Ǵ��ϴ� �Լ�
      for (int i = 1; i < r; i++) {
         if (row[i] == row[r]) {//���� ��, ���� �ִ��� Ȯ��
            return -1;
         }
         else if (Math.abs(row[i] - row[r]) == Math.abs(i - r)) { //�밢�� Ȯ��
            return -1;
         }
      }
      return 1;//��ȿ�ϸ� 1�� return �Ѵ�.
   }

   //dfs
   public static void dfs(int[] row,int r, int n){
      if (r>n) {//������ ���� �� Ž��
         if (possible(row, r - 1) == 1) {
            for (int i = 1; i <= r - 1; i++) {//������ ���� ��� �������� Ȯ��
               if (possible(row, i) == -1) return;
            }
            if (isok == 0) {//���� ó���� ���� ������ Ȯ��
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
         for (int i = n; i >=1; i--) {//��� ���� Ž���Ѵ�. //LIFO������� �ڿ������� �־��ش�.
            row[r] = i;
            dfs(row, r + 1, n);
         }
      }      
   }
   
   //bfs

   public static int flag;
   
   public static void bfs(int row[], int now, int n) {
	   //Vector<Integer> members = new Vector<Integer>();
	   Queue<ArrayList> q = new LinkedList<ArrayList>();//queue<vector>�ڷᱸ���� �̿��ؼ� �湮�� ��� ���� ���� ����
	   ArrayList<Integer> v = new ArrayList<Integer>();
	   v.add(now);
	   q.offer(v);//���� col�� ��ġ�� �־��ش�.
	   row[now]=1;
	   while(!q.isEmpty()) {
		   ArrayList<Integer> r = q.poll();//�湮�� �� ���� ���� ����Ǿ��ִ�.
		  // q.poll();
		   if(r.size()<n) {//�湮�� ���� ������ n���� �۾ƾ��Ѵ�.
			   for (int i = 1; i <= n; i++) {//���� ���� ������ �����Ѵ�.		
				    r.add(i);
				    ArrayList<Integer> temp=new ArrayList<Integer>();
				    for (int j=0;j<r.size();j++) { //java�� shallow copy or deepcopy������ vector�� ���� queue�� �ִ� ���� ���� ���� ������
				    	int a = r.get(j);
				    	temp.add(a);
				    }
					q.offer(temp);
					r.remove(r.size()-1);//��� ������ ���� ���� ���ο� ���� ���� �ִ´�.
				}
		   }
		   if (r.size() == n) {//������ �湮���� ��
				for (int i = 0; i < n; i++) {
					row[i+1] = r.get(i);//row�迭�� ������� �湮�� ��,�� ������ �ִ´�.
				}
				for (int i = 1; i <= n; i++) {//�� ���� ���� �ڸ��� ��ȿ���� �Ǵ��Ѵ�.
					if (possible(row,i) == -1) {
						flag = -1;//�������� �ʴ�.
						break;
					}
				}
				if (flag == 0&&isok==0) {//������ //isok�� ó�� ���� �������� Ȯ���Ѵ�.
						data_bfs = "Location : ";
					for (int i = 1; i <= n; i++) { 
						data_bfs = data_bfs + (row[i]-1)+" ";//index�� 1�� �����ϹǷ� 1�� ���༭ print��.
					}
					data_bfs= data_bfs + "\r\n";
					isok++;
				}
				flag = 0;//flag�� �ʱ�ȭ ��Ų��.
		   }
	   }
   }
   
   
   
   
   
   
   //dfid
   public static void dfid(int row[], int r, int n, int depth) {
      if (r>depth) {//r�� depth���� Ŭ�� ��ȿ���� Ȯ���Ѵ�. 
         if (possible(row, r - 1) == 1) {//��ȿ���� Ȯ���Ѵ�.
            for (int i = 1; i <= r - 1; i++) {
               if (possible(row, i) == -1) return;//�ϳ��� ��ȿ���� ������ return gksek.
            }
            if (isok == 0&&r>n) {//depth�� n���� ���� ó�� ���� �� ����Ѵ�. 
            	data_dfid = "Location : ";
               for (int i = 1; i <= n; i++) {
            	   data_dfid = data_dfid + (row[i]-1)+" ";//��� ���� �ٲ㼭 ����ؾ���. ��� ����?
               }
               data_dfid= data_dfid + "\r\n";
               isok++;
            }
         }
      }
      else {
         for (int i = n; i >=1; i--) {//LIFO ������� �ڿ������� �־��ش�.
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
      
      int[] row= new int[20]; //row�迭 ����
      path=path+"\\"+"result"+n+".txt";
      FileWriter fw = new FileWriter(path);
      
      
      //dfs
      String data = ">DFS\r\n";
      fw.write(data);
      //fw.flush();
      int flag = 0; //flag ��������, ���� �ִ��� Ȯ��
      long starttime = System.currentTimeMillis(); //dfs���۽ð�
      
      for (int i = n; i >=1 ; i--) {
         row[1] = i;
         dfs(row,2, n);
      }
      
      long endtime = System.currentTimeMillis(); //dfs������ �ð�
      
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
      //row, isok �ʱ�ȭ 
      for (int i=0;i<20;i++) { 
         row[i]=0;
      }
      isok=0;
      
      
      
      //bfs

      data = ">BFS\r\n";
      fw.write(data);
      starttime = System.currentTimeMillis(); //bfs���۽ð�
      for (int i = 1; i <= n; i++) {
          bfs(row,i,n);
      } 
      endtime = System.currentTimeMillis(); //bfs������ �ð�
      
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
      //isok, row �ʱ�ȭ
      for (int i=0;i<20;i++) { 
         row[i]=0;
      }
      isok=0;
      
      
      
      //dfid
      data = ">DFID\r\n";
      fw.write(data);
      
      starttime = System.currentTimeMillis(); //dfid���۽ð�
      for (int i = n; i >=1; i--) {
         for (int d = 1; d <= n; d++) {
            row[1] = i;
            dfid(row, 2, n,d);
         }
      }
      endtime = System.currentTimeMillis(); //dfid������ �ð�
      
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