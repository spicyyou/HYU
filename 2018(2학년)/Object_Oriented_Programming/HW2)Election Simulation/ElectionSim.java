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
			/*department Ŭ������ �ν��Ͻ��� name_department�� department�� ��ü �ְ�
			 * �� ��ü�� ElectionSim�� �ν��Ͻ��� de arraylist�� �߰��ߴ�.
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
		//��ǥ�ڼ���
		for (int i=0;i<de.size();i++) {
			 can.add(de.get(i).most(de.get(i),i));
		}
		saveData();
		//���ͷ���Ʈ�� ���� ��� �л��� �����ؾ��Ѵ�.
		//�� ���� ��ǥ�ڸ� �����Ѵ�.
	}
	public void saveData() {
		//�����ĺ��ڵ��� ��Ʈ //department������
		//�ƿ�ǲ���Ͽ� ����Ʈ
		PrintWriter print=null;
		try {
			print=new PrintWriter(new FileOutputStream(outfilepath));
		}
		catch(FileNotFoundException e3) {
			e3.printStackTrace();
		}
		//�� �ݺ��ؼ� ����ؾ���
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