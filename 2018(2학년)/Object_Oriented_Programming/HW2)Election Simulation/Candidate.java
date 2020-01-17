package assignment;

public class Candidate extends Student {
	//후보자의 정보를 담는다.
	int number_of_vote;
	//candidates must be compared based on the number of votes
	public int compareTo(Object arg0) {
		Candidate o = new Candidate();
		o=(Candidate)arg0;
		if(this.number_of_vote>o.number_of_vote) {return 1;}
		else if(this.number_of_vote==o.number_of_vote) {return 0;}
		else if (this.number_of_vote<o.number_of_vote) {return -1;}
		// TODO Auto-generated method stub
		return 0;
	}
	
}
