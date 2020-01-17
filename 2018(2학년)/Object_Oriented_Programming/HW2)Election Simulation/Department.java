package assignment;
import java.util.ArrayList;
public class Department {
	//각각 기관의 정보x를 담는다.
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
		//가장 표수가 많은 후보자를 리턴해라
		return max_can;
	}
}
