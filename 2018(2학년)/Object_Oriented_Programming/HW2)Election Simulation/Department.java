package assignment;
import java.util.ArrayList;
public class Department {
	//���� ����� ����x�� ��´�.
	String name_department;
	ArrayList<Candidate> candidate = new ArrayList<Candidate>();
	ArrayList<Student> student = new ArrayList<Student>();
	Candidate most(Department o,int now) {
		int max=0;
		Candidate max_can = new Candidate();
		//o.candidate.get(now);
		for (Candidate e : o.candidate) {
			if(e.number_of_vote>max) {
				max=e.number_of_vote;
				max_can=e;
			}
		}
		//���� ǥ���� ���� �ĺ��ڸ� �����ض�
		return max_can;
	}
}
