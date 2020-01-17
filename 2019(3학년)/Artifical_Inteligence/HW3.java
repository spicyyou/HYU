package assignment3;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import java.util.*;



public class assignment3 {
	
	
	
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
	
	
	
	public static void main(String args[]) throws IOException{
		
	    String temp0 = args[0];
	    int n= Integer.parseInt(temp0);//n - queens
	    String path = args[1];
	    
	    
	    //파일 입출력
	    path=path+"\\"+"result"+n+".txt";
	    FileWriter fw = new FileWriter(path);
	    
	    String data = ">Genetic Algorithm\r\n";
	    fw.write(data);
	    //시간 체크
	    long starttime =  System.currentTimeMillis();

	    ArrayList<ArrayList<Integer>> nextgene = new ArrayList<ArrayList<Integer>>();
	    //처음 1000개의 population 생성
	    int generation =1;
	    for (int i=0;i<1000;i++) {
	    	Random random = new Random();
	    	ArrayList<Integer> temp = new ArrayList<Integer>();
	    	for (int j=0;j<n;j++) {
	    		int randnum = random.nextInt(n);
	    		temp.add(randnum);
	    	}
	    	int f = fitness(temp,n);
			if (f==0) { //n-queen을 찾음
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
	    	//-- tempgene에 100개의 parent생성
	    	//System.out.println("size: "+nextgene.size());
	    	//crossover한 값을 넣어준다. //crossover rate = 0.8 //mutation rate=0.1
	    	int cnt=0;
	    	int flag=0;
	    	//nextgene따로 저장해서 복붙하기
	    	//System.out.println("nowquene : "+nextgene.get(100));
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
	    		int mutation_idx = random.nextInt(900)+100; //생성된 자식중 랜덤으로 돌연변이될 자식을 뽑는다.
	    		ArrayList<Integer> mut = new ArrayList<Integer>();
	    		for (int m=0;m<n;m++) {
	    			int randnum = random.nextInt(n);
	    			mut.add(randnum);
	    		}
	    		tempgene.set(mutation_idx, mut);	    		
	    	}
	    	
	    	for (int i=0;i<1000;i++) {
	    		int f = fitness(tempgene.get(i),n);
    			if (f==0) { //n-queen을 찾음
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
	    	generation++; //세대 증가*/
	    }
	}
}
