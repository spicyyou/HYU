package assignment2;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class assignment2 {
	
	//queen�� �ʱ���ġ ����
	public static ArrayList<Integer> initial( int n){ //column�� �ʱ�ȭ
		ArrayList<Integer> queen = new ArrayList<Integer>();
	    Random random = new Random();
		for (int i=0;i<n;i++) { 
	    	//int temp1 = random.nextInt(n);//0~n-1������ ������ ���� ó�� queen�� �־��ش�.
	    	//queen.add(temp1);
	    	queen.add(i); //�� �࿡ �ߺ��� ���ֱ� ���� 0~n�� �־��ش�.
	    }
		Collections.shuffle(queen);//shuffle�� ���� �����ϰ� �ٲ��ش�.
		return queen;
	}
	
	public static int Heuristic(ArrayList<Integer> queen, int n) { //Heuristic value�� �����Ѵ�.
		int cnt=0;
		for (int i = 0; i < n; i++) {
			for (int j=0; j<n ;j++) {
				if(i!=j) {
					if(queen.get(i)==queen.get(j)|Math.abs(queen.get(i) - queen.get(j)) == Math.abs(i - j)) { //�밢���� �����Ҽ� ������ cnt++
						cnt++;
					}
				}
			}
		}
	    return (cnt/2);//�ߺ��ǹǷ� 2�� �������� �߰��Ѵ�.
	}
	
	
	//main
	public static void main(String args[]) throws IOException{
		
    String temp0 = args[0];
    int n= Integer.parseInt(temp0);//n - queens
    String path = args[1];
    
    
    //���� �����
    path=path+"\\"+"result"+n+".txt";
    FileWriter fw = new FileWriter(path);
    
    String data = ">Hill Climbing \r\n";
    fw.write(data);
    fw.flush();
    ArrayList<Integer> queen = new ArrayList<Integer>();    
    
    
    long starttime =  System.currentTimeMillis();
    int restart=0;
    //for (int T=0;T<100;T++) {
    while(true) {//Heuristic value�� 0�϶����� ����
    	queen = initial(n);
    	int startH = Heuristic(queen,n); //���� Heuristic value����
    	int flag=0;
    	for (int i=0;i<n;i++) {
    		for (int j=0;j<n;j++) {
    			if(i==j) continue; 
    			ArrayList<Integer> temp1 = new ArrayList<Integer>();
    			for (int k=0;k<n;k++) { //temp1�� �� ����
    				temp1.add(queen.get(k));
    			}
    			temp1.set(i, queen.get(j));//���� ������ i,j column�� �� row�� �ٲ� ���� temp1�� ���� 
    			temp1.set(j, queen.get(i));
    			int nowH = Heuristic(temp1,n);
    			if(startH>nowH) { //�ٲ� Heuristic value�� ó���ͺ��� ���� �� queen�� temp1�� ����
    				queen=temp1;
    				startH=nowH;
    			}
    			if(startH==0) { //n-queen�� �����Ҷ�
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
    		if(flag==1) {//���� ã���� �� break
    			break;
    		}
    	}
		if(flag==1) {
			break;
		}
		restart++;//restart Ƚ�� ����
    }
    //}
    long endtime = System.currentTimeMillis();
      //time evaluation
    data = "Total Elapsed Time: "+(endtime-starttime)/100.0+"\r\n";
    fw.write(data);
    //System.out.println(" n�� "+n+"�̰� 10000�� �������� �� restart�� ��� Ƚ��"+restart/10000.0+"��");
    
    fw.flush();
	}
}
