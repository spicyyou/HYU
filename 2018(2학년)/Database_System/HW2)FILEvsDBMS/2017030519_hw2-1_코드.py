import csv
from random import *
import numpy as np
import pandas as pd
print("======LOGIN======\n")
inputid = input("ID : ")
password = input("password : ")
print("=================\n")
personal_contact = {} # dictionary 사용
if inputid =="admin":
    #관리자 모드 
    print(">>>>>>>>관리자 모드<<<<<<<<<<")
    while 1:
        print("=====어떤 명령을 수행하시겠습니까?=======\n")
        print("a. 새학생 추가\nb. 연락처 추가기능\nc. 학생 데이터 변경\nd. 학생 정보 삭제\ne.도메인별 도수분포표 보기\nf. 종료\n=================================")
        com = input("원하는 명령을 입력하시오 : ")
        if com == 'f':
            break
        elif com == 'a':
            #새학생 추가기능
            print("새로운 학생의 정보를 입력하세요 : ")
            new_student = input()
            new_student = new_student.split(',')
            f = open ( 'students.csv','a',encoding = 'utf-8',newline = '')
            wr = csv.writer(f)
            wr.writerow(new_student)
            f.close()
        elif com == 'b':
            #연락처 추가기능
            addcontact = input()
            addcontact = addcontact.split(',')
            f = open ( '한양인 주소록.csv','a',encoding = 'utf-8',newline = '')
            wr = csv.writer(f)
            wr.writerow(addcontact)
            f.close()
        elif com == 'c':
            #연락처 변경기능
            print("학생이름을 입력하시요\n")
            stu_name = input()
            print("변경할 email을 입력하시오\n")
            new_email = input()
            f = open ( 'students.csv','r',encoding = 'utf-8',newline = '')
            rdr = csv.reader(f)
            for line in rdr: # 이름을 통해 stu_id 찾기
                if line[2]==stu_name:
                    stu_id = line[0]
                    break
            f.close()
            stu_id = ''.join(stu_id.split()) 
            #stu_id(학번) 통해서 email 바꿔 temp파일에 적는다.
            with open ('한양인 주소록.csv','r',encoding = 'utf-8',newline='') as fi:
                with open ('temp.csv','w',encoding = 'utf-8',newline='')as fo:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        row[0]=''.join(row[0].split())
                        if row[0]==stu_id:
                            row[2]=new_email
                            fw.writerow(row)
                        else :
                            fw.writerow(row)
            #한양인 주소록 비우기
            with open ('한양인 주소록.csv','w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')
            #temp파일에 있는내용을 한양인 주소록에 복사
            with open ('한양인 주소록.csv','w',encoding = 'utf-8',newline='') as fo:
                with open ('temp.csv','r',encoding = 'utf-8',newline='')as fi:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        fw.writerow(row)
            #temp파일 비우기
            with open ('temp.csv','w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')
        elif com == 'd':
            #연락처 삭제
            print("학생이름을 입력하시요\n")
            stu_name = input()
            f = open ( 'students.csv','r',encoding = 'utf-8',newline = '')
            rdr = csv.reader(f)
            #이름을 통해 stu_id찾기
            for line in rdr:
                if line[2]==stu_name:
                    stu_id = line[0]
                    break
            f.close()
            stu_id = ''.join(stu_id.split()) 
            with open ('한양인 주소록.csv','r',encoding = 'utf-8',newline='') as fi:
                with open ('temp.csv','w',encoding = 'utf-8',newline='')as fo:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        row[0]=''.join(row[0].split())
                        if row[0]!=stu_id:
                            fw.writerow(row)
            with open ('한양인 주소록.csv','w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')
            with open ('한양인 주소록.csv','w',encoding = 'utf-8',newline='') as fo:
                with open ('temp.csv','r',encoding = 'utf-8',newline='')as fi:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        fw.writerow(row)
            with open ('temp.csv','w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')
            #밑에 과정은 c와 같다.
        elif com =='e':
            #도메인별 도수분포표
            f = open ( '한양인 주소록.csv','r',encoding = 'utf-8',newline = '')
            rdr = csv.reader(f)
            #이름을 통해 stu_id찾기
            finddomain=[]#locale part 와 domain 구분
            count=0
            for line in rdr:
                if count!=0:
                    finddomain.append(line[2].split('@'))
                count=count+1
            f.close()
            domain ={}
            for row in finddomain:
                #print(row)
                n=0
                for col in row:
                    if n==1:
                        domain[col]=0
                    n=n+1    
            for row in finddomain:
                n=0
                for col in row:
                    if n==1:
                        domain[col]=domain[col]+1
                    n=n+1    
            #domain에는 각 domain별 분포도가 나타나있다.
            d=pd.Series(domain)
            print(d) #도수분포표 보기

        else:
            print("다시 입력해 주세요\n")
else:
    #학생모드
    while 1:
        ok=0
        f = open ('students.csv','r',encoding = 'utf-8',newline = '') 
        rdr = csv.reader(f)
        for line in rdr: #비밀번호와 맞는지 비교하기
            iddel = ''.join(line[0].split()) #학번 공백제거
            if iddel==inputid: # id가 students.csv파일에 있을 때
                passdel = ''.join(line[1].split())  # password공백제거
                if password ==passdel: #비밀번호가 같은게 있는지 확인
                    ok=1
                    break
        f.close()
        if ok==0:
            print("존재하지 않거나 비밀번호가 틀렸습니다.")
            break
        print("=====어떤 명령을 수행하시겠습니까?=======\n")
        print("a. 메일보내기 기능\nb. 개인주소록 파일 추가\nc. 개인주소록 업데이트\nd. 개인주소록 연락처 삭제\ne. 종료\n=================================")
        print("원하는 명령을 입력하시오 : ")
        com_stu = input()
        if com_stu == 'e':
            break
        elif com_stu =='a':
            #####personal contact 있을 때 어떻게 되는지 확인하기

            #메일보내기 한양인주소록과 개인주소록을 모두 출력
            print("메일을 보냅니다. 주소록을 확인하세요")
            print("========주소록 ==============") 
            #input id와 개인주소록을 연동해야함
            f = open ( 'personal_contact_list.csv','r',encoding = 'utf-8',newline = '') 
            rdr = csv.reader(f)
            personal=''
            for line in rdr: # personal에 sid를 통한 개인주소록을 받아온다.
                if line[0] ==inputid:
                    personal = line[1]
                    break
            f.close()

            #한양인 주소록 출력
            print(">>>>>>>>>한양인 주소록 <<<<<<<<<<<<")
            f = open ( '한양인 주소록.csv','r',encoding = 'utf-8',newline = '') 
            rdr = csv.reader(f)
            for line in rdr: 
                print(line)
            f.close()
            print("=================================")
            if personal != '':#개인주소록이 있을 때
                print(">>>>>>>>>>>개인주소록<<<<<<<<<<<<<") #개인주소록 출력
                f = open ( personal,'r',encoding = 'utf-8',newline = '') 
                rdr = csv.reader(f)
                for line in rdr: 
                    print(line)
                f.close()
                print("==================================")

        elif com_stu =='b' :
            #학번으로 로그인한다. id를 찾는다.
            print("추가할 파일을 입력하시오 : ")
            addfilename = input()
            c =inputid+','+addfilename
            c = c.split(',')
            f = open ( 'personal_contact_list.csv','a',encoding = 'utf-8',newline = '') 
            wr = csv.writer(f)
            wr.writerow(c)
            f.close()
        elif com_stu =='c' :
            #정보를 업데이트 전화번호가 다른것만
            #id를 통해 개인주소록 파일에 접근해 업데이트하자
            f = open ( 'personal_contact_list.csv','r',encoding = 'utf-8',newline = '') 
            rdr = csv.reader(f)
            for line in rdr: # updatefile에 sid를 통한 개인주소록을 받아온다.
                if line[0] ==inputid:
                    updatefilename = line[1]
                    break
            f.close()
            #업데이트 파일로 원래파일을 변경할때
            #temp 에 업데이트된 파일을 적음
            u = 'business_cards_updated/'+updatefilename
            with open (u,'r',encoding = 'utf-8',newline='') as fi:
                with open ('temp.csv','w',encoding = 'utf-8',newline='')as fo:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        fw.writerow(row) 
            #원래파일 초기화
            with open (updatefilename,'w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')

            #temp에 있는 내용을 원래파일에 적는다.
            with open (updatefilename,'w',encoding = 'utf-8',newline='') as fo:
                with open ('temp.csv','r',encoding = 'utf-8',newline='')as fi:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        fw.writerow(row)
            #temp.csv초기화
            with open ('temp.csv','w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')            
            #아래코드는 만약 업데이트에서 추가되고 변경된 내용을 원래 파일에 추가한다고할때            
            '''
            u = 'business_cards_updated/'+updatefilename
            with open (u,'r',encoding = 'utf-8',newline='') as fi:
                with open ('temp.csv','w',encoding = 'utf-8',newline='')as fo:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        fw.writerow(row) 
            addnum=[]
            with open ('임시주소록 업데이트.csv','w',encoding = 'utf-8',newline='')as fo:
                with open ('temp.csv','r',encoding = 'utf-8',newline='')as tempi:
                    fw = csv.writer(fo,delimiter=',')
                    tempr = csv.reader(tempi,delimiter=',')
                    for row in tempr:
                        numberexist =0
                        f = open ( updatefilename,'r',encoding = 'utf-8',newline = '') 
                        fr = csv.reader(f)
                        for col in fr:
                            if(row[1]==col[1]): #업데이트 된 전화번호와 원래 전화번호가 같을 때
                                fw.writerow(row)
                                numberexist=1
                                break
                        f.close()
                        if numberexist==0:
                            print("전화번호 없음 : "+row[1]+col[1])
                            addnum.append(row)# 업데이트 된 전화번호가 원래 파일에 없을때 리스트에 추가

            #원래파일 초기화
            with open (updatefilename,'w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')
            #임시주소록 업데이트.csv파일을 원래파일에 적기
            with open (updatefilename,'w',encoding = 'utf-8',newline='') as fo:
                with open ('임시주소록 업데이트.csv','r',encoding = 'utf-8',newline='')as fi:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        fw.writerow(row)

            #리스트에 있는 내용을 원래파일에 추가로 적기
            with open (updatefilename,'a',encoding = 'utf-8',newline='') as fo:
                fw = csv.writer(fo,delimiter=',')
                for row in addnum:
                    fw.writerow(row)
            print(addnum)
            #temp.csv초기화
            with open ('temp.csv','w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')
            #임시주소록 업데이트.csv초기화
            with open ('임시주소록 업데이트.csv','w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')'''

        elif com_stu =='d':
            #input id와 개인주소록을 연동해야함
            f = open ( 'personal_contact_list.csv','r',encoding = 'utf-8',newline = '') 
            rdr = csv.reader(f)
            for line in rdr: # deletefile에 sid를 통한 개인주소록을 받아온다.
                if line[0] ==inputid:
                    deletefile = line[1]
                    break
            f.close()
            #temp에 옮겨적음
            with open (deletefile,'r',encoding = 'utf-8',newline='') as fi:
                with open ('temp.csv','w',encoding = 'utf-8',newline='')as fo:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        fw.writerow(row)
            #원래 파일 초기화
            with open (deletefile,'w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')
            #temp에 옮긴것을 통해 행갯수 찾기
            rowcnt=0 
            with open ('temp.csv','r',encoding = 'utf-8',newline='')as fi:
                fr = csv.reader(fi, delimiter=',')
                for row in fr:
                    rowcnt=rowcnt+1 #행갯수세기
            random = randint(0,rowcnt) # 지울 임의의 난수 생성
            #temp에 옮긴것을 원래파일에 다시 적기
            i=0
            with open (deletefile,'w',encoding = 'utf-8',newline='') as fo:
                with open ('temp.csv','r',encoding = 'utf-8',newline='')as fi:
                    fr = csv.reader(fi, delimiter=',')
                    fw = csv.writer(fo,delimiter=',')
                    for row in fr:
                        if(i!=random):
                            fw.writerow(row)
                        i=i+1
            #temp 파일 초기화
            with open ('temp.csv','w',encoding = 'utf-8',newline='') as f:
                fw = csv.writer(f,delimiter=',')
        else: 
            print("다시 입력해주세요")