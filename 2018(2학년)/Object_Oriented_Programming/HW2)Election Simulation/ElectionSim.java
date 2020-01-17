package assignment;

import java.io.PrintWriter;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.Iterator;
import java.util.Collections;
public class ElectionSim 
{
	/*private static final String DEPARTMENT_INPUT_FILE_PATH = "input1.csv";
	private static final String STUDENT_INPUT_FILE_PATH = "input2.csv";
	private static final String OUTPUT_FILE_PATH = "ouput_file.txt";*/
	ArrayList<Department> de= new ArrayList<Department>();
	ArrayList<Candidate> can = new ArrayList<Candidate>();
	public String outfilepath;
	public ElectionSim(String departmentInputFilePath, String studentInputFilePath, String outputFilePath) {
		Scanner file1 = null;
		Scanner file2 = null;
		outfilepath=outputFilePath;
		try {
			file1 = new Scanner(new FileInputStream(departmentInputFilePath));
		}catch(FileNotFoundException e) {
			e.printStackTrace();
		}
		file1.nextLine();
		while(file1.hasNextLine()) {
			Department name = new Department();
			String str = file1.nextLine();
			StringTokenizer st = new StringTokenizer(str,",");
			st.nextToken();
			String dep=st.nextToken();
			name.name_department=dep;
			de.add(name);
			//department_num++;
			/*department 클래스의 인스턴스인 name_department를 department의 객체 넣고
			 * 그 객체를 ElectionSim의 인스턴스인 de arraylist에 추가했다.
			*/
		}
		try {
			file2 = new Scanner(new FileInputStream(studentInputFilePath));
		}
		catch(FileNotFoundException e) {
			e.printStackTrace();
		}
		file2.nextLine();
		Department depStu =new Department();
		Student A = new Student();
		while(file2.hasNextLine()) {
			int school;
			String str = file2.nextLine();
			StringTokenizer st = new StringTokenizer(str,",");
			A.id_num=Integer.parseInt(st.nextToken());
			A.student_department=Integer.parseInt(st.nextToken())-1;
			school=A.student_department;
			A.student_name=st.nextToken();
			String elected = st.nextToken();//candidate
			de.get(school).student.add(A);
			if(elected.equals("TRUE")) {
				Candidate canStu = new Candidate();
				canStu.id_num=A.id_num;
				canStu.student_department=A.student_department;
				canStu.student_name=A.student_name;
				de.get(school).candidate.add(canStu);
			}
		}
		
		file1.close();
		file2.close();
	}
	
	/*public static void main(String[] args) {
		ElectionSim eSim = new ElectionSim(DEPARTMENT_INPUT_FILE_PATH,STUDENT_INPUT_FILE_PATH,OUTPUT_FILE_PATH);
		eSim.runSimulation();
	}
	*/
	public void runSimulation() {
		// TODO Auto-generated method stub
		Department elec = new Department();
		Student student_elec = new Student();
		//System.out.println(de.size());
		Iterator<Student> iter;
		for (int i=0;i<de.size();i++){
			int n=de.get(i).student.size();
			iter = de.get(i).student.iterator();
			while(iter.hasNext()) {
				iter.next().vote(de.get(i).candidate.size(), de,i);
			}
		}
		//대표자선출
		for (int i=0;i<de.size();i++) {
			 can.add(de.get(i).most(de.get(i),i));
		}
		saveData();
		//이터레이트를 통해 모든 학생이 선거해야한다.
		//각 과는 대표자를 선출한다.
	}
	public void saveData() {
		//선거후보자들을 솔트 //department순으로
		//아웃풋파일에 라이트
		PrintWriter print=null;
		try {
			print=new PrintWriter(new FileOutputStream(outfilepath));
		}
		catch(FileNotFoundException e3) {
			e3.printStackTrace();
		}
		//거 반복해서 출력해야함
		Collections.sort(can);
		
		for (int i=0;i<de.size();i++) {
		print.println("======== Elected Candidate ========");
		print.println("Department name: "+de.get(can.get(i).student_department).name_department);
		print.println("name: "+can.get(i).student_name);
		print.println("Student_id: "+can.get(i).id_num);
		print.println("Votes: "+can.get(i).number_of_vote);
		print.println("===================================");
		}
		print.close();
	}
}