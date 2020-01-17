# HW1) Letter Transformation Program



## 과제 설명



- Form Letter를 Letter로 변환해주는 프로그램을 작성한다.
- From Leetter는 template을 통해 작성된 편지이다. 
- template에 특정 수신자 또는 발신자의 정보를 적어야 하다면 중괄호 { }안에 properties key 이름을 적어 놓고 변환하는 과정을 거친다.
- properties는 별도의 파일에 key=value 쌍으로 저장해놓는다.



## 요구조건

- key와 value 
- KeyValue class
  - properties 정보를 갖고 있다.
  - properties의 key 와 value를 저장할 private 필드 key, value.
  - 두 개의 생성자.
    - ‘key=value’ 와 같은 형식으로 이루어진 한 개의 String을 매개변수로 하는 생성자. 이 생성자에서는 StringTokenizer 클래스를 사용하여 key와 vlaue 값을 파싱한다.
    - key와 value 2개의 String을 매개변수로 하는 생성자
  - private 필드인 key 값을 return 해주는 getKey() 메소드
  - private 필드인 value 값을 return 해주는 getValue() 메소드
- LetterTransformator 클래스
  - 한 개의 main 함수를 갖고 있고 main 함수안에서 KeyValue 클래스를 이용하여 Form Letter를 변형해야 한다.
    - template_file.txt 파일로부터 Form Letter의 템플릿을 read 한다.
    - properties.txt 파일로부터 Form Letter의 템플릿을 read 한다.
    - output_file.txt 파일에 알맞게 변형된 텍스트 결과를 write 한다.
    - File I/O를 수행하기 위해 어떤 클래스를 사용해도 무방하며, File I/O를 위한 예외처리는 되어있어야 한다.




# HW2) Election Simulation

## 과제 설명

부서 대표를위한 가상 선거 결과를 시뮬레이션한다. 후보자 중에서 가장 많은 표를 얻은 후보자가 부서별로 선정된다.  선거 시뮬레이션은 SimTest, ElectionSim, Student, Candidate 및 Department Class로구성된다.



## 요구 조건

### Voter interface

- This interface will be used for student class.
-  This interface declares a method named “vote”.
-  This interface extends Comparable Interface.

### Student Class

- This class will be used to store information about student.
-  This class has three instance variables.
  -  String - The name of the student.
  -  Integer - The identification number of the student.
  -  Integer - The grade of the student.
  -  Department - The department of the student.
- This class implements the Vote interface and define the method named “vote”. Thismethod do the following tasks.
  - Select a number randomly between 0 and the number of Candidates of the department of the student.
  - Increase the number of votes of the candidate of the department in the ArrayList at the random number location.

### Candidate Class

-  This class is used to store information about candidate.
- This class extends the student class.
- This class have one instance variable.
  - Integer - Number of votes
- Candidates must be compared based on the number of votes.



### Department Class

- This class is used to store information about each department.
- This class have four instance variables.
  - String name - The name of the department.
  - ArrayList&lt;Candidate&gt; - The collection of candidates that the department contains.
  - ArrayList&lt;Student&gt; - The collection of students that the department contains.
- This class have a method that return candidate with the most votes in the department.



### ElectionSim Class

- This class will be used as the election simulator. This class must read input data from a text files, run the simulation and then write the output to another text file.
- This class has five instance variables.
  - String - The path of input file about departments.
  - String - The path of input file about students.
  - String - The path of the output file.
  - ArrayList&lt;Department&gt; - The collection of all departments.
  - ArrayList&lt;Candidate&gt; - The collection of elected candidates.
- The body of the constructor must carry out the following tasks.
  - Read data from the input file named “input_department.csv”.
  - Add them into the Collection of Department.
  - Read data from the input file named “input_student.csv”.
  - Add them into the Collection of Student by department.
- This class have a method named saveData and this method do the following tasks.
  - Sort the collection of elected candidates.
  - Write the information in the collection of candidates to the output file.
- This class have a method named runSimulation. This method carries out the following tasks.
  - All students will vote by using iterator.
  - Each department elects representative.
  - Then call saveData method to save the simulation results to the outputfile.