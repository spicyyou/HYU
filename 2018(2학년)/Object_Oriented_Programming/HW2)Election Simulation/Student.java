package assignment;
import java.util.ArrayList;
import java.util.Random;

public class Student implements Voter {
//학생에 대한 정보를 담고있다.
	public String student_name;
	public int id_num;
	public int student_grade;
	public int student_department;

	
	public void vote(int size_,Object o,int now) {
		// TODO Auto-generated method stub
		//Department candepart= new Department();
		Random random = new Random();
		int n;
		n = random.nextInt(size_);//이거나중에 size확인하기
		((ArrayList<Department>) o).get(now).candidate.get(n).number_of_vote++;
		//random.무엇을 사용해서 0~candidate만큼의 난수 생성;
		//department의 candidate의 숫자를 증가한다. randomnumberlocation에
	}

	@Override
	public int compareTo(Object arg0) {
		// TODO Auto-generated method stub
		
		return 0;
	}
	
	
}