package assignment;
import java.util.ArrayList;
import java.util.Random;

public class Student implements Voter {
//�л��� ���� ������ ����ִ�.
	public String student_name;
	public int id_num;
	public int student_grade;
	public int student_department;

	
	public void vote(int size_,Object o,int now) {
		// TODO Auto-generated method stub
		//Department candepart= new Department();
		Random random = new Random();
		int n;
		n = random.nextInt(size_);//�̰ų��߿� sizeȮ���ϱ�
		((ArrayList<Department>) o).get(now).candidate.get(n).number_of_vote++;
		//random.������ ����ؼ� 0~candidate��ŭ�� ���� ����;
		//department�� candidate�� ���ڸ� �����Ѵ�. randomnumberlocation��
	}

	@Override
	public int compareTo(Object arg0) {
		// TODO Auto-generated method stub
		
		return 0;
	}
	
	
}