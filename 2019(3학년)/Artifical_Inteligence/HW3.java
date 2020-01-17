package assignment3;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import java.util.*;



public class assignment3 {
	
	
	
	public static int fitness(ArrayList<Integer> t, int n) { //���ڷ� ���� ArrayList�� fitness �˻� //���� ��� ������ �� �ִ���
		int cnt=0;
		for (int i = 0; i < n; i++) {
			for (int j=0; j<n ;j++) {
				if(i!=j) {
					if(t.get(i)==t.get(j)|Math.abs(t.get(i) - t.get(j)) == Math.abs(i - j)) { //�밢���� �����Ҽ� ������ cnt++
						cnt++;
					}
				}
			}
		}
	    return (cnt/2);//�ߺ��ǹǷ� 2�� �������� �߰��Ѵ�.
	}
	
	
	
	public static void main(String args[]) throws IOException{
		
	    String temp0 = args[0];
	    int n= Integer.parseInt(temp0);//n - queens
	    String path = args[1];
	    
	    
	    //���� �����
	    path=path+"\\"+"result"+n+".txt";
	    FileWriter fw = new FileWriter(path);
	    
	    String data = ">Genetic Algorithm\r\n";
	    fw.write(data);
	    //�ð� üũ
	    long starttime =  System.currentTimeMillis();

	    ArrayList<ArrayList<Integer>> nextgene = new ArrayList<ArrayList<Integer>>();
	    //ó�� 1000���� population ����
	    int generation =1;
	    for (int i=0;i<1000;i++) {
	    	Random random = new Random();
	    	ArrayList<Integer> temp = new ArrayList<Integer>();
	    	for (int j=0;j<n;j++) {
	    		int randnum = random.nextInt(n);
	    		temp.add(randnum);
	    	}
	    	int f = fitness(temp,n);
			if (f==0) { //n-queen�� ã��
			for (int t=0;t<n;t++) {
				data = temp.get(t)+" ";
				fw.write(data);
				//System.out.print(temp.get(t)+" ");
			}
			//System.out.println();
			//System.out.println("generation : "+generation);
			data="\r\n";
			fw.write(data);
			long endtime =  System.currentTimeMillis();
    	    data="Total Elasped Time : "+((endtime - starttime)/100.0);
    	    fw.write(data);
    	    fw.flush();
    	    return;
			}
	    	nextgene.add(temp);
	    }
	    
	    
	    while(true) {
	    	//System.out.println(generation);
		    ArrayList<ArrayList<Integer>> tempgene = new ArrayList<ArrayList<Integer>>();
	    	for (int i=0;i<100;i++) {//population�� fitness �˻� �� pair�� ����Ʈ�� �־��� //parent����
	    		int min=99999999;
	    		int idx=0;
	    		for (int j=0;j<10;j++) {//1000���� 10���� �������� ���� �� ���� fiteness�� ���� ���� parent�� �־��ش�.
	    			Random random = new Random();
	    			int randnum = random.nextInt(1000); //0~999���� �� ������ ���� �̴´�.
	    			int f = fitness(nextgene.get(randnum),n);
	    			if(min>f) {
	    				min=f;
	    				idx=randnum;
	    			}
	    		}
	    		tempgene.add(nextgene.get(idx));
	    	}
	    	//-- tempgene�� 100���� parent����
	    	//System.out.println("size: "+nextgene.size());
	    	//crossover�� ���� �־��ش�. //crossover rate = 0.8 //mutation rate=0.1
	    	int cnt=0;
	    	int flag=0;
	    	//nextgene���� �����ؼ� �����ϱ�
	    	//System.out.println("nowquene : "+nextgene.get(100));
	    	for (int i=100;i<1000;i++) {
	    		Random random = new Random();
	    		//crossover�� father�� mother ����
	    		int father = random.nextInt(100);
	    		int mother = random.nextInt(100);
	    		if(mother==father) {
	    			while(mother==father) {//mother�� father�� ���� �ʵ��� ���ش�.
	    				mother=random.nextInt(100);
	    			}
	    		}
	    		
		    	int point = random.nextInt(n-2)+1;//1���� n-2�� �������� ���� //��𿡼� crossover point
		    	ArrayList<Integer> cross = new ArrayList<Integer>();
		    	//point�������� crossover
		    	for (int c=0;c<point;c++) {
		    		cross.add(tempgene.get(father).get(c));
		    	}
		    	for (int c = point;c<n;c++) {
		    		cross.add(tempgene.get(mother).get(c));
		    	}
		    	//System.out.println("fater : "+tempgene.get(father)+"fidx : "+father);
		    	//System.out.println("mother: "+tempgene.get(mother)+"midx : "+mother);
		    	//System.out.println("point : "+point);
		    	//System.out.println("cross : "+cross);
		    	//System.out.println("----------------------");
		    	tempgene.add(cross);
	    	}
	    	
	    	//mutation
	    	for (int i=0;i<100;i++) {//mutation rate = 1/9 // 100/900
	    		Random random = new Random();
	    		int mutation_idx = random.nextInt(900)+100; //������ �ڽ��� �������� �������̵� �ڽ��� �̴´�.
	    		ArrayList<Integer> mut = new ArrayList<Integer>();
	    		for (int m=0;m<n;m++) {
	    			int randnum = random.nextInt(n);
	    			mut.add(randnum);
	    		}
	    		tempgene.set(mutation_idx, mut);	    		
	    	}
	    	
	    	for (int i=0;i<1000;i++) {
	    		int f = fitness(tempgene.get(i),n);
    			if (f==0) { //n-queen�� ã��
    				for (int t=0;t<n;t++) {
    					data = tempgene.get(i).get(t)+" ";
    					fw.write(data);
    					//System.out.print(tempgene.get(i).get(t)+" ");
    				}
    				//System.out.println();
    				//System.out.println("generation : "+generation);
    				data="\r\n";
    				fw.write(data);
    				long endtime =  System.currentTimeMillis();
    				//System.out.println("generationg : "+generation);
		    	    data="Total Elasped Time : "+((endtime - starttime)/100.0);
		    	    fw.write(data);
		    	    fw.flush();
		    	    return;
    			}
	    	}
	    	nextgene.clear();
	    	nextgene=tempgene;
	    	generation++; //���� ����*/
	    }
	}
}
