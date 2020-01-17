import psycopg2
import csv
import json
import ast
from time import sleep
from datetime import datetime
from pprint import pprint
def execute_data(query):
    try :
        conn.execute(query)
    except:
        return "fail"
    return conn.fetchall()

def admin_table(query):
    try :
        conn.execute(query)
    except:
        print("fail")
    
    product.commit()

def es_add(j):
    i=0
    while i<len(line[j]):
        if line[j][i]=="'":
            st = line[j]
            line[j]=st[:i+1]+"'"+st[i+1:]
            i=i+2
        else:
            i=i+1
#tfalkc@smh.com.au,8mf3trl
def login(table, login_ID,login_passwrd):
    login_suceess="0"
    sql = "select s.local"+" from "+table+" s where s.local = "+"'"+login_ID[0]+"'and s.domain = "+"'"+login_ID[1]+"'"
    result = execute_data(sql)
    if  not result : #이거 부분 고치기
        garbage=1
        #print("회원등록이 되지 않았습니다. 회원가입을 부탁드립니다")
    else :
    #비밀번호 확인
        sql = "select passwd from "+table+" s where s.passwd = " +"'"+ login_passwrd+"'"
        result = execute_data(sql)
        if not result: #비밀번호 틀렸을 때
            login_suceess = "0"
        else:
            print("화면을 로딩중입니다. 잠시만 기다려 주십시오.")
            if table == "seller":
                login_suceess="1"
            elif table == "customer":
                login_suceess="2"
            elif table == "delivery":
                login_suceess = "3"
    return login_suceess
    #1 : seller, 2: customer, 3. delivery 0: 실패



user = 'postgres'
password = 'wkdwnd7827'
host_product = '127.0.0.1'
dbname = 'deliveryapp'
port = '5432'

product_connection_string = "dbname={dbname} user={user} host={host} password={password} port={port}"\
                            .format(dbname=dbname,
                                    user=user,
                                    host=host_product,
                                    password=password,
                                    port=port)    

try : 
    product =psycopg2.connect(product_connection_string)
except:
    print("I am unable to connect to the database")

conn = product.cursor()

#앱 실행

print("\n\n\n 배달의 한양에 오신걸 환영합니다. \n\n\n")
#|-----------------------------앱실행--------------------------------|

#로그인
while 1:
    print("원하는 기능을 선택하여 주십시오.")
    print("1. Login \n0. 프로그램 종료")
    com  = input("입력 : ")
    if(com == "0"):
        exit()

    print(">>>>>>>>>>배달의 한양<<<<<<<<<<<<<")
    print("             Login               ")
    print("ID : ")
    #seller는 seller_id로 로그인customers는 이름으로 로그인
    ID = input()
    #ID = "bfiile@yale.edu" #판매자 
    #ID = "tfalkc@smh.com.au" #구매자
    #ID = "nolivmt@reverbnation.com" #구매자2
    #ID = "wbac@nydailynews.com" #배달자
    ID = ID.split("@")
    print("password : ")
    password = input()
    #password = "amobzpdb8" #판매자
    #password = "newpassword" #판매자 새로운 비밀번호
    #password = "newpassword" #구매자
    #password = "z2hj1ptrp"#구매자2
    #password = "q7etd2n1w"#배달자
    print("=================================")

#id와 password가 일치하는지 확인
    while 1:
        result = login("seller",ID,password) #판매자인지 검사
        if result=="0":
            result = login("customer",ID,password)
            if result =="0":
                result=login("delivery",ID,password)
        #구매자인지 검사
        #배달자인지 검사
        if(result!="0") :
            break
        else :
            print("로그인에 실패하였습니다. 아이디나 비밀번호를 확인해주십시오. 앱을 종료합니다.")
            exit()
#판매자로 로그인할때
    print("로그인에 성공하셨습니다.")
#|-----------------------------판매자 시작--------------------------------|
    #로그인 성공시
    if result =="1": #판매자 일 때 #가게태그 #현재 주문내역 추가하기
        print("회원님은 배달의 한양의 판매자로 등록되어 있습니다.")
        print("==============================================")

#|-----------------------------로그인실행 후 연결성공 --------------------------------|
        print(">>>>>>>>>>>>>>배달의 한양<<<<<<<<<<<<<<<<<<<<<<")
        while 1:
            print("원하는 기능을 선택하여 주십시오.")
            print("1. 내 소유 가게 보기\n2. 개인정보 변경\n0. 나가기 ")
            print("입력 : ")
            com= input()

            if com == "0":
                break
                #판매자 기능 종료
            elif com =="1":
                #내 소유 가게 보기
                
                sql = "select sname from store st, seller s where s.seller_id =st.seller_id and s.local = "+"'"+ID[0]+"'and s.domain = "+"'"+ID[1]+"'"
                result = execute_data(sql)
                for i in range(0,len(result)):
                    print(i+1,": ",result[i][0])
                print("가게 정보를 확인하시겠습니까? [Y?N]")
                store_name = result
                com = input()
                if com =="Y":
                    print("확인할 가게의 번호를 입력하세요 : ")
                    com = input()
                    store_index = (str)(int(com)-1)
                    str_idx = (int(com)-1)
                    
                    sql = "select sid from store, seller where store.sname = "+"'"+store_name[str_idx][0]+"'"+" and seller.local = "+"'"+ID[0]+"'and seller.domain = "+"'"+ID[1]+"'"+"and seller.seller_id = store.seller_id"
                    result = execute_data(sql)
                    sid = result
                    order_sid = sid
                    #가게 선택했음, 가게에 대한 정보 보기
                    while 1:
                        print("1. 가게정보 보기\n2. 현재메뉴관리\n3. 현재주문관리\n0. 나가기")
                        com = input()
                        if com =="0":
                            break
                        elif com == "1":
                            #가게 정보보기
                            print("1. 가게 설명 보기\n2. 가게 태그 보기")
                            com = input()
                            if com =="1":
                                #가게 설명보기
                                print("가게 이름 : "+store_name[str_idx][0])
                                sql = "select address from store where store.sid ="+"'"+ store_index+"'"
                                result = execute_data(sql)

                                print("가게 주소 : "+result[0][0])
                                sql = "select phone_nums from store where store.sid ="+"'"+ store_index+"'"
                                result = execute_data(sql)
                                store_phone = result[0][0]
                                store_phone = store_phone[1:-1]
                                print("가게 번호 : "+store_phone)

                                sql = "select schedules from store where store.sid ="+"'"+ store_index+"'"
                                result = execute_data(sql)
                                store_schedules = result[0][0]
                                store_schedules = store_schedules[1:-1]
                                print("가게 스케쥴 : "+store_schedules) #jasnon이 되면 jason으로 출력하기
                                
                                sql = "select lat from store where store.sid ="+"'"+ store_index+"'"
                                result = execute_data(sql)
                                store_latitude = result[0][0]
                                print("가게 latitude : "+store_latitude) #jasnon이 되면 jason으로 출력하기
                                
                                sql = "select lng from store where store.sid ="+"'"+ store_index+"'"
                                result = execute_data(sql)
                                store_longitude = result[0][0]
                                print("가게 longitude : "+store_longitude) #jasnon이 되면 jason으로 출력하기
                                
                            elif com =="2":
                                #가게 태그보기
                                #tag_list = (seller_id,store_name,tag_list)
                                print("1. 태그 추가 2. 태그 보기")
                                com =input()
                                tag_list=[]
                                #store_name[store_idx][0]
                                if com =="1":
                                    #태그추가
                                    print("태그를 추가해주세요 종료를원하면 0을 눌러주세요")
                                    while 1:
                                        print("입력 :")
                                        tag = input()
                                        if tag=="0":
                                            break
                                        tag_list.append(tag)
                                    tag_list=",".join(tag_list)
                                    sql ="insert into tag_list(sid,tag_list) values("+"'"+sid[0][0]+"','"+tag_list+"')"
                                    admin_table(sql)
                                    print("태그 추가가 완료되었습니다.")
                                elif com =="2":
                                    #태그보기
                                    print("판매자님의 가게인 "+store_name[str_idx][0]+"의 태그리스트입니다.")
                                    sql = "select tag_list from tag_list where sid = "+"'"+sid[0][0]+"'"
                                    result = execute_data(sql)
                                    for i in range (0,len(result)):
                                        print(i+1," : ",result[i][0])
                            else : 
                                print("없는 명령입니다.")
                
#|-------------------------------가게 정보 관리------------------------------------------------------|

                        elif com =="2":
                            #현재메뉴관리
                            print("현재 메뉴")
                            sql = "select m.menu from menu m, store s where m.sid = s.sid and m.sid ="+"'"+sid[0][0]+"'"
                            result = execute_data(sql)
                            for i in range(0,len(result)):
                                print(i+1,": ",result[i][0])
                            print("관리할 메뉴의 번호를 선택하세요 : ")
                            com = input()
                            menu_name = result[int(com)-1][0]
                            print("1.메뉴 변경\n2.메뉴 삭제")
                            com = input()
                            if com =="1":
                                #메뉴변경 2
                                print("변경할 이름을 적어주세요 : ")
                                menu_new_name = input()
                                sql = "update menu set menu = "+"'"+menu_new_name+"' where menu.menu="+"'"+menu_name+"'"
                                admin_table(sql)
                                print("메뉴 "+menu_name+"가 "+ menu_new_name+"으로 변경이 완료되었습니다.")
                            elif com =="2":
                                #메뉴삭제
                                sql = "delete from menu where menu.menu = "+"'"+menu_name+"'"
                                result = admin_table(sql)
                                print("삭제가 완료되었습니다.")
                                print("삭제 후 메뉴입니다")
                                sql = "select m.menu from menu m, store s where m.sid = s.sid and m.sid ="+"'"+sid[0][0]+"'"
                                result = execute_data(sql)
                                for i in range(0,len(result)):
                                    print(i+1,": ",result[i][0])
                            
                            else:
                                print("없는 명령입니다.")
 #|-------------------------------가게 메뉴 관리------------------------------------------------------| 배달부 선택안함

                        elif com =="3":
                            #현재 주문관리
                            #order를 구매자에서 생성한 후 수행해야한다.
                            print("1. 현재 주문 확인\n2. 주문 취소하기")
                            com =input()
                            if com =="1":
                                #현재 주문확인
                                sql = "select * from order_list where order_list.order_store = "+"'"+sid[0][0]+"'"+" order by cast(order_list.delivering as integer) asc"
                                result = execute_data(sql)
                                order = result
                                print('(주문자ID, 주문가게이름, 주문한 메뉴, 결제 정보, 결제시간, 배달부 할당 여부, 배달부')
                                print("ps. 배달부 할당 여부는 1: 배달부 할당 안됨 2: 배달부 할당 됨(배달중) 3. 배달완료입니다.")
                                print("배달부가 할당되지않을 때는 null로 표시됩니다.")
                                for i in range(0,len(result)):
                                    print(i+1," : ",result[i])
                                print("배달부를 할당하시겠습니까?[y/n]")
                                com = input()
                                if com =="y":
                                    print("배달부를 할당할 주문을 선택하세요")
                                    order_num = input()
                                #!배달부 나타낸 후 선택하기
                                    sql = "select d.did, d.name from delivery d, store s where cast(d.stock as integer) <5 and s.sid ="+"'"+sid[0][0]+"'"+"order by abs(cast(d.lat as float)-cast(s.lat as float))+abs(cast(d.lng as float)-cast(s.lng as float)) limit 5"
                                    
                                    result = execute_data(sql)
                                    for i in range(0,len(result)):
                                        print("name : ",result[i][1],", did : ",result[i][0])
                                    print("이용할 배달자의 did를 선택하세요")
                                    com = input()
                                    did = com
                                    
                                    #주문자는 같은시간에 두개의 주문을 생성할 수 있기 때문에 주문자명과 시간이 같을때
                                    sql ="update order_list set did = "+"'"+did+"'"+" where order_id = "+"'"+order[int(order_num)-1][0]+"' and payment_time = "+"'"+order[int(order_num)-1][4]+"'"   
                                    #print(sql)
                                    admin_table(sql)
                                    print("배달부 할당이 완료되었습니다.")
                                    sql ="update order_list set delivering = "+"'2'"+" where order_id = "+"'"+order[int(order_num)-1][0]+"' and payment_time = "+"'"+order[int(order_num)-1][4]+"'"   
                                    admin_table(sql)
                                elif com =="n":
                                    print("종료합니다.")
                                else:
                                    print("잘못입력하셨습니다.")

                            elif com == "2":
                                sql = "select * from order_list where order_list.order_store = "+"'"+sid[0][0]+"'"+" order by cast(order_list.delivering as integer) asc"
                                result = execute_data(sql)
                                order = result
                                for i in range(0,len(result)):
                                    print(i+1," : ",result[i])
                                print("취소할 주문의 번호를 선택하세요")
                                order_num = input()
                                order_id = order[int(order_num)-1][0]
                                sql = "delete from order_list where order_id = "+"'"+order[int(order_num)-1][0]+"' and payment_time = "+"'"+order[int(order_num)-1][4]+"'"
                                print(sql)
                                result = execute_data(sql)
                                print("주문 취소가 완료되었습니다.")
                                #주문 취소
                            else :
                                print("잘못입력하셨습니다.")
                        
                        else:
                            print("잘못입력하셨습니다.")
#|------------------------------- 가게 주문 관리------------------------------------------------------|

                elif com =="N":
                    break
                else :
                    print("잘못입력하셨습니다.")        

#|-------------------------------내 소유 가게 관리------------------------------------------------------|
            elif com =="2" : 
                #개인 정보 변경
                while 1:
                    print("변경할 정보를 선택하세요.")
                    print("1. 이름 변경\n2. 비밀번호 변경\n0.나가기")
                    com = input("입력 : ")

                    if com == "0":
                        #종료
                        break
                        
                    elif com == "1":
                        #  판매자 개인정보 이름 변경

                        print("변경할 이름을 입력해 주세요")
                        name = input("입력 : ")
                        sql = "select s.name from seller s where s.local = "+"'"+ID[0]+"'and s.domain = "+"'"+ID[1]+"'"
                        result = execute_data(sql)
                        sql = "update seller set name = "+"'"+name+"' where seller.local = "+"'"+ID[0]+"'and seller.domain = "+"'"+ID[1]+"'"
                        admin_table(sql)
                        # sql = "select s.local"+" from "+table+" s where s.local = "+"'"+login_ID[0]+"'and s.domain = "+"'"+login_ID[1]+"'"
                        print(result[0][0]+"님의 이름이 "+name+"으로 성공적으로 변경했습니다.")

                    elif com =="2":
                        # 판매자 개인정보 비밀번호 변경

                        print("변경할 비밀번호를 입력해 주세요")
                        pw = input("입력 : ")
                        sql = "update seller set passwd = "+"'"+pw+"' where seller.local = "+"'"+ID[0]+"'and seller.domain = "+"'"+ID[1]+"'"
                        admin_table(sql)
                        print("변경 성공")
                    else:
                        print("잘못입력하셨습니다. 다시 입력해 주세요")

                else :
                    print("잘못입력하셨습니다. 다시 입력해 주세요")
                #판매자 화면까지 구현완료
            else:
                print("잘못입력하셨습니다.")
#|---------------------------------개인정보  관리------------------------------------------------------|
#|---------------------------------구매자일때------------------------------------------------------|

    elif result =='2': #구매자일때
        print("회원님은 배달의 한양의 구매자로 등록되어 계십니다.")
        print("==============================================")
        #구매자 관리화면- (개인정보관리), 주소록 목록
        while 1:
            print("원하시는 기능을 선택해 주세요")
            print("1. 내 정보 관리\n2. 주문내역확인\n3. 가게 검색 후 주문하기\n0.나가기") #1,2 실행안해봄
            com = input()
        
            if com =="0":
                break
            elif com =="1":
                # 내 정보 관리
                print("원하시는 기능을 선택해주세요")
                print("1. 개인정보 관리\n2.주소록 관리")
                com = input()
                if com =="1":
                    #개인정보 관리
                    while 1:
                        print("변경할 정보를 선택하세요.")
                        print("1. 이름 변경\n2. 비밀번호 변경\n0.나가기")
                        com = input("입력 : ")

                        if com == "0":
                            #종료
                            break
                        elif com == "1":
                        #  구매자 개인정보 이름 변경
                            print("변경할 이름을 입력해 주세요")
                            name = input("입력 : ")
                            sql = "select s.name from customer s where s.local = "+"'"+ID[0]+"'and s.domain = "+"'"+ID[1]+"'"
                            result = execute_data(sql)
                            sql = "update customer set name = "+"'"+name+"' where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"
                            admin_table(sql)
                            # sql = "select s.local"+" from "+table+" s where s.local = "+"'"+login_ID[0]+"'and s.domain = "+"'"+login_ID[1]+"'"
                            print(result[0][0]+"님의 이름이 "+name+"으로 성공적으로 변경했습니다.")

                        elif com =="2":
                            # 구매자 개인정보 비밀번호 변경
                            print("변경할 비밀번호를 입력해 주세요")
                            pw = input("입력 : ")
                            sql = "update customer set passwd = "+"'"+pw+"' where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"
                            admin_table(sql)
                            print("변경 성공")
                        else:
                            print("잘못입력하셨습니다. 다시 입력해 주세요")

#|---------------------------------개인정보  관리------------------------------------------------------|
                elif com =='2':
                    #주소록 관리
                    #주소록 보여주기
                    print("현재 회원님의 주소록입니다.")
                    sql = "select c.nickname,c.contact from customer_contact c where c.customer_local = "+"'"+ID[0]+"'"+" and c.customer_domain ="+"'"+ID[1]+"'"
                    result = execute_data(sql)
                    print("  (닉네임, 주소)")
                    for i in range(0,len(result)):
                        print(i+1,result[i])
                    print("\n")

                    print("1. 주소록 추가\n2. 주소록 변경\n3. 주소록 제거")
                    com = input()
                    
                    if com == "1":
                        #주소록 추가
                        #customer_contact(customer_id,passwd,contact)로 관리
                        print("추가할 주소와 주소에 대한 닉네임을 입력하세요")
                        print("주소 : " )
                        contact =input()
                        print("닉네임 : ")
                        nickname = input()
                        sql = "insert into customer_contact(customer_local,customer_domain,contact,nickname) values ("+"'"+ID[0]+"'"+","+"'"+ID[1]+"'"+","+"'"+contact+"'"+","+"'"+nickname+"')"   
                        admin_table(sql)
                        print("성공적으로 추가하였습니다.")
                    elif com =="2":
                        #주소록 변경
                        print("변경할 주소록의 닉네임을 입력하세요")
                        nickname = input()
                        print("1. 닉네임변경 2. 주소변경")
                        com = input()
                        if com =="1":
                            #닉네임변경
                            print("변경할 닉네임을 입력하세요")
                            new_nickname = input()
                            sql = "update customer_contact set nickname = "+"'"+new_nickname+"' where customer_contact.nickname="+"'"+nickname+"'"
                            admin_table(sql)
                            print("닉네임 변경이 완료되었습니다.")
                        elif com =="2":
                            print("변경할 주소를 입력하세요")
                            new_contact = input()
                            sql = "update customer_contact set contact = "+"'"+new_contact+"' where customer_contact.nickname="+"'"+nickname+"'"
                            admin_table(sql)
                            print("주소 변경이 완료되었습니다.")
                    elif com =="3":
                        #주소록 삭제
                        print("변경할 주소록의 닉네임을 입력하세요")
                        nickname = input()
                        sql = "delete from customer_contact where customer_contact.nickname = "+"'"+nickname+"'"
                        admin_table(sql)
                        print("주소 삭제가 완료되었습니다.")       
                else:
                    print("잘못입력하셨습니다.")
#|---------------------------------주소록  관리------------------------------------------------------| 
            elif com =="2":
                print("1. 주문내역확인\n2. 주문현황 확인 및 관리\n3. 결제수단 관리")
                com = input()
                if com =="1":
                    #주문내역확인
                    #만약 배송확인된 주문만 주문내역으로 이동하면 delivering이 2인 애만 보여주면됨
                    order_id=ID[0]+"@"+ID[1]
                    sql ="select order_store,payment_method,payment_time from order_list where order_list.order_id ="+"'"+order_id+"'"+"and order_list.delivering ='3' order by payment_time desc"
                    result = execute_data(sql)
                    print("(주문 가게, 결제 방법, 결제시간)")
                    for i in range(0,len(result)):
                        print(i+1," : " ,result[i])
                    #주문내역 추가해서 order순으로 되는지 확인하기
                elif com =="2":
                    #주문현황 확인 및 관리
                    print("주문현황")
                    order_id=ID[0]+"@"+ID[1]
                    sql ="select delivering,did,order_store,shopping_bascket,payment_method,payment_time from order_list where order_id ="+"'"+order_id+"'"+"order by payment_time desc"
                    result = execute_data(sql)
                    print("배달상태는 1: 배달부 할당 안됨 2: 배달중(배달부 할당됨) 3: 배달완료 이고 1일때 배달부 정보는 0으로 나옵니다.그리고 배달부 정보는 배달부 id로 출력됩니다.")
                    print("주문 가게에 번호 또한 따로 조회할 수있습니다.")
                    print("배달 상태, 배달부 정보, 주문 가게 번호, 주문 메뉴, 결제방법, 결제시간")

                    for i in range(0,len(result)):
                        print(i+1," : ",result[i])
                    print("배송을 완료하시겠습니까?[y/n]")
                    y_n = input()
                    if y_n =="y": 
                        print("주문을 완료할 주문번호를 선택해주세요. 배달 상태가 2인 주문만 주문을 완료할 수 있습니다.")
                        com = input()
                        pay = result[int(com)-1][5]
                        if result[int(com)-1][0]!="2":
                            print("배달완료를 할 수 없거나 이미 배달완료한 주문입니다.")
                            exit()
                            #배송완료
                        sql = "update order_list set delivering = '3' where order_list.payment_time = "+"'"+pay+"' and order_list.order_id = "+"'"+order_id+"'"
                        admin_table(sql)
                        print("배송완료가 완료되었습니다.")
                    elif y_n =="n":
                        print("배송완료를 하지 않습니다.")
                    else :
                        print("잘못입력하셨습니다.")
                    

                elif com =="3": #customer_list를 sql에 적용할수있으면 됨
                    #결제수단 관리
                    print("1. 결제수단 추가\n2. 결제수단 변경\n3. 결제수단 제거")
                    com = input()
                    
                    
                    if com =="1":
                        #결제수단 추가
                        sql ="select customer.payments from customer where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"
                        customer_payment = execute_data(sql)
                        customer_payment = customer_payment[0][0]
                        customer_payment=customer_payment[1:-1]
                        customer_payment=ast.literal_eval(customer_payment) #리스트와 딕셔너리로 만들기
                        #print(customer_payment)
                        print("1. account 추가 2. card 추가")
                        type_payment =input()
                        if type_payment =="1":
                            #account 추가
                            print("은행를 입력하세요")
                            bid_name = input()
                            sql = "select bid from bank where bank.name = "+"'"+bid_name+"'"
                            result = execute_data(sql)
                            if not result:
                                print("없는 은행입니다.")
                                break
                            else :
                                bid = result[0][0]
                                print("계좌번호를 입력하세요")
                                acc_num = input()
                                dic={"type":"account"}
                                dic_temp = {"bid":int(bid)}
                                dic_temp["acc_num"]=int(acc_num)
                                dic_temp = str(dic_temp)
                                dic_temp = dic_temp.replace("'",'"')
                                
                                dic["data"]=dic_temp
                                customer_payment.append(dic) #계좌번호 추가
                                for i in range(0,len(customer_payment)):
                                    customer_payment[i] = str(customer_payment[i])
                                customer_payment = str(customer_payment)
                                customer_payment = "'\""+str(customer_payment)+"\"'"
                                i=0
                                while i<len(customer_payment):
                                    if customer_payment[i]=="{" and customer_payment[i+1]=="\\":
                                        customer_payment=customer_payment[:i-1]+customer_payment[i:]
                                        i=i+2
                                        #print(customer_payment)
                                    elif customer_payment[i]=="}"and customer_payment[i+1]=="'":
                                        customer_payment = customer_payment[:i+1]+customer_payment[i+2:]
                                        i=i+2
                                    else : 
                                        i=i+1
                                customer_payment = customer_payment.replace("\\","'")
                               
                                
                                #이쪽부분 업데이트가 안되는데 어떻게해야하지

                                sql = "update customer set payments = "+customer_payment+" where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"
                                admin_table(sql)
                        elif type_payment=="2":
                            #card 추가
                            print("카드 번호를 입력하시오")
                            card_num = input()
                            dic = {"type":"card"}
                            dic_temp = {"card_num":int(card_num)}
                            dic_temp = str(dic_temp)
                            dic_temp = dic_temp.replace("'",'"')
                            dic["data"] = str(dic_temp)
                            customer_payment.append(dic)
                            
                            for i in range(0,len(customer_payment)):
                                customer_payment[i] = str(customer_payment[i])
                            customer_payment = str(customer_payment)
                            customer_payment = "'\""+str(customer_payment)+"\"'"
                            i=0
                            while i<len(customer_payment):
                                if customer_payment[i]=="{" and customer_payment[i+1]=="\\":
                                    customer_payment=customer_payment[:i-1]+customer_payment[i:]
                                    i=i+2
                                        #print(customer_payment)
                                elif customer_payment[i]=="}"and customer_payment[i+1]=="'":
                                    customer_payment = customer_payment[:i+1]+customer_payment[i+2:]
                                    i=i+2
                                else : 
                                    i=i+1
                            customer_payment = customer_payment.replace("\\","'")
                            sql = "update customer set payments = "+customer_payment+" where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"
                            admin_table(sql)
                        else :
                            print("잘못입력했습니다.")    
                    elif com =="2":
                        #결제수단 변경
                        sql ="select customer.payments from customer where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"   

                        customer_payment = execute_data(sql)
                        customer_payment = customer_payment[0][0]
                        customer_payment=customer_payment[1:-1]
                        customer_payment=ast.literal_eval(customer_payment) #리스트와 딕셔너리로 만들기
                        print("bid 목록보기")
                        sql = "select bid,name from bank"
                        result = execute_data(sql)
                        for i in range(0,len(result)):
                            print(result[i])
                        print("변경할 결제수단을 선택하세요")
                    
                        for i in range(0,len(customer_payment)):
                            print(i+1," : type : "+customer_payment[i]["type"]+", data : "+customer_payment[i]["data"])                    
                        com =input()
                        payment_method = customer_payment[int(com)-1]
                        del customer_payment[int(com)-1]

                        if payment_method["type"]=="account":
                            print("변경할 은행번호을 입력하세요")
                            new_bank = input()
                            print("변경할 계좌번호를 입력하세요")
                            new_account = input()
                            dic={"type":"account"}
                            dic_temp = {"bid":int(new_bank)}
                            dic_temp["acc_num"]=int(new_account)
                            dic_temp = str(dic_temp)
                            dic_temp = dic_temp.replace("'",'"')
                                
                            dic["data"]=dic_temp
                            customer_payment.append(dic) #계좌번호 추가
                                
                        
                            for i in range(0,len(customer_payment)):
                                customer_payment[i] = str(customer_payment[i])
                            customer_payment = str(customer_payment)
                            customer_payment = "'\""+str(customer_payment)+"\"'"
                            i=0
                            while i<len(customer_payment):
                                if customer_payment[i]=="{" and customer_payment[i+1]=="\\":
                                    customer_payment=customer_payment[:i-1]+customer_payment[i:]
                                    i=i+2
                                        #print(customer_payment)
                                elif customer_payment[i]=="}"and customer_payment[i+1]=="'":
                                    customer_payment = customer_payment[:i+1]+customer_payment[i+2:]
                                    i=i+2
                                else : 
                                    i=i+1
                            customer_payment = customer_payment.replace("\\","'")
                            sql = "update customer set payments = "+customer_payment+" where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"
                            admin_table(sql)
                            


                            #update해야함
                        elif payment_method["type"]=="card":
                            print("변경할 카드 번호를 입력하세요")
                            new_card_num = input()

                            dic = {"type":"card"}
                            dic_temp = {"card_num":int(new_card_num)}
                            dic_temp = str(dic_temp)
                            dic_temp = dic_temp.replace("'",'"')
                            dic["data"] = str(dic_temp)
                            customer_payment.append(dic)
                            
                            for i in range(0,len(customer_payment)):
                                customer_payment[i] = str(customer_payment[i])
                            customer_payment = str(customer_payment)
                            customer_payment = "'\""+str(customer_payment)+"\"'"
                            i=0
                            while i<len(customer_payment):
                                if customer_payment[i]=="{" and customer_payment[i+1]=="\\":
                                    customer_payment=customer_payment[:i-1]+customer_payment[i:]
                                    i=i+2
                                elif customer_payment[i]=="}"and customer_payment[i+1]=="'":
                                    customer_payment = customer_payment[:i+1]+customer_payment[i+2:]
                                    i=i+2
                                else : 
                                    i=i+1
                            customer_payment = customer_payment.replace("\\","'")
                            sql = "update customer set payments = "+customer_payment+" where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"
                            admin_table(sql)


                    elif com =="3":
                        #결제수단 취소
                        sql ="select customer.payments from customer where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"   

                        customer_payment = execute_data(sql)
                        customer_payment = customer_payment[0][0]
                        customer_payment=customer_payment[1:-1]
                        customer_payment=ast.literal_eval(customer_payment) #리스트와 딕셔너리로 만들기
                        print("bid 목록보기")
                        sql = "select bid,name from bank"
                        result = execute_data(sql)
                        for i in range(0,len(result)):
                            print(result[i])
                        print("취소할 결제수단을 선택하세요")
                    
                        for i in range(0,len(customer_payment)):
                            print(i+1," : type : "+customer_payment[i]["type"]+", data : "+customer_payment[i]["data"])                    
                        com =input()
                        del customer_payment[int(com)-1]
                        for i in range(0,len(customer_payment)):
                            customer_payment[i] = str(customer_payment[i])
                        customer_payment = str(customer_payment)
                        customer_payment = "'\""+str(customer_payment)+"\"'"
                        i=0
                        while i<len(customer_payment):
                            if customer_payment[i]=="{" and customer_payment[i+1]=="\\":
                                customer_payment=customer_payment[:i-1]+customer_payment[i:]
                                i=i+2
                                        #print(customer_payment)
                            elif customer_payment[i]=="}"and customer_payment[i+1]=="'":
                                customer_payment = customer_payment[:i+1]+customer_payment[i+2:]
                                i=i+2
                            else : 
                                i=i+1
                        customer_payment = customer_payment.replace("\\","'")
                        sql = "update customer set payments = "+customer_payment+" where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"
                        admin_table(sql)
                    else:
                        print("잘못입력했습니다.")
                else :
                    print("잘못입력했습니다.")
#|---------------------------------주문 내역 확인(아직 안 함)------------------------------------------------------| 
            elif com =="3":
                #가게 검색 후 주문하기
                #검색방법
                print("가게를 검색해 보세요!")
                print("1.내 위치기준 운영중인 가게 검색하기\n2.주소로 가게검색하기\n3.태그로 가게검색하기\n4.이름으로 가게검색하기")
                com = input()
                search_store_list =[]
                search_store=None
                select_sid =None
                if com =="1":
                    #내 위치기준 운영중인 가게 검색
                    isopen=0
                    sql = "select timeofday()"
                    result = execute_data(sql)
                    current_timeofday = result[0][0]
                    #current_timeofday = Fri Dec 07 17:49:20.560381 2018 KST
                    current_day_of_week=current_timeofday[0:3]#오늘요일
                    current_day_of_week_int=0
                    if current_day_of_week=="Mon":
                        current_day_of_week_int=0
                    elif current_day_of_week =="Tue":
                        current_day_of_week_int=1
                    elif current_day_of_week =="Wed":
                        current_day_of_week_int=2
                    elif current_day_of_week =="Thu":
                        current_day_of_week_int=3
                    elif current_day_of_week =="Fri":
                        current_day_of_week_int=4
                    elif current_day_of_week =="Sat":
                        current_day_of_week_int=5
                    elif current_day_of_week =="Sun":
                        current_day_of_week_int=6
                    current_time = current_timeofday[11:13]#오늘시간
                    current_minute = current_timeofday[14:16]#오늘분
                    current_time =current_time+current_minute

                    #비슷한 위치에 가게를 찾자
                    sql = "select store.schedules from store, customer where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'" +"order by abs(cast(customer.lat as float) - cast(store.lat as float))+ abs(cast(customer.lng as float) - cast(store.lng as float)) asc limit 5"
                    location_schedule = execute_data(sql)
                    sql = "select store.sname,store.sid from store, customer where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'" +"order by abs(cast(customer.lat as float) - cast(store.lat as float))+ abs(cast(customer.lng as float) - cast(store.lng as float)) asc limit 5"
                    store_candidate = execute_data(sql)
                    cur_schedule_list = None
                    for i in range (0,len(location_schedule)):#리스트 스케쥴 5개 나올거임
                        cur_schedule_list = location_schedule[i][0] #현재가게
                        cur_sid = store_candidate[i][1]
                        cur_store = store_candidate[i][0]
                        cur_schedule_list = ast.literal_eval(cur_schedule_list)
                        cur_schedule_list = ast.literal_eval(cur_schedule_list) #dic과 list로 바꿈
                        if cur_schedule_list[current_day_of_week_int]["holiday"]==1: #holiday다
                            open_= cur_schedule_list[current_day_of_week_int].get("open","null")
                            close_ = cur_schedule_list[current_day_of_week_int].get("closed","null")
                        else :
                            open_= cur_schedule_list[current_day_of_week_int].get("open","null")
                            close_ = cur_schedule_list[current_day_of_week_int].get("closed","null")
                        if open_!="null" and close_!="null": #open과 closed란 키가 존재할때
                            open_time = open_[0:2]
                            open_minute = open_[2:4]
                            closed_time = close_[0:2]
                            closed_minute = close_[2:4]
                            open_time = open_time+open_minute
                            closed_time = closed_time+closed_minute
                            #현재시각 - 오픈시각 <0 이고 마감 - 현재 <0 이지 않으면 되게끔
                            if not(int(current_time)-int(open_time)<0 and int(closed_time)-int(current_time)<0):
                                temp=[]
                                temp.append(cur_store)
                                temp.append(cur_sid)
                                search_store_list.append(temp)
                    print("근처에 영업중인 가게들입니다.")

                    for i in range(0,len(search_store_list)):
                        print(i+1," : " ,search_store_list[i])
                    
                    print("주문할 가게의 번호를 선택해주세요")
                    com = input()
                    search_store = search_store_list[int(com)-1][0]
                    select_sid = search_store_list[int(com)-1][1]
                    print(search_store+"를 선택하였습니다.")
                                            
#|---------------------------------내 위치 기준 가게 찾기------------------------------------------------------| 
                elif com =="2":
                    #주소로 가게 검색하기
                    print("검색할 가게의 주소를 입력하세요")    
                    input_store = input()
                    sql = "select store.sname,store.sid from store where store.address LIKE "+"'%"+input_store+"%'"
                    result = execute_data(sql)
                    if not result:
                        print("검색하신 주소의 가게를 찾지 못했습니다.")
                    else:
                        for i in range(0,len(result)):
                            print(i+1,": ",result[i][1], " ",result[i][0])
                        print("주문할 가게를 선택하세요")
                        num = input()
                        search_store = result[int(num)-1][0]
                        select_sid = result[int(num)-1][1]
                        print(search_store+"를 선택하셨습니다.")
#|---------------------------------주소 기준 가게 찾기------------------------------------------------------| 

                elif com =="3": 
                    #태그검색
                    print("태그를 입력하세요")    
                    tag = input()
                    sql = "select s.sname, s.sid from store s, tag_list t where s.sid = t.sid and  t.tag_list LIKE "+"'%"+tag+"%'"
                    result = execute_data(sql)
                    result = execute_data(sql)
                    for i in range(0,len(result)):
                        print(i+1," : ",result[i][1]," ",result[i][0])
                    print("주문할 가게를 선택하세요")
                    num = input()
                    search_store = result[int(num)-1][0]
                    select_sid = result[int(num)-1][1]
                    print(search_store+"를 선택하셨습니다.")
                    #태그로 가게검색
#|---------------------------------태그 기준 가게 찾기(아직안함)------------------------------------------------------| 
                elif com =="4":
                    #이름으로 가게검색
                    print("검색할 가게의 이름을 입력하세요")
                    search_store_name = input()
                    sql  = "select store.sname,store.sid from store where store.sname LIKE "+"'%"+search_store_name+"%'"                    
                    result = execute_data(sql)
                    if not result:
                        print("검색하신 이름의 가게를 찾지 못했습니다.")
                    else : 
                        for i in range(0,len(result)):
                            print(i+1,": ",result[i][1]," ",result[i][0])
                        print("주문할 가게를 선택하세요")
                        num = input()
                        search_store = result[int(num)-1][0]
                        select_sid = result[int(num)-1][1]
                        print(search_store+"를 선택하셨습니다.")
                
                else :
                    print("잘못입력하셨습니다.")

            
#|---------------------------------이름 기준 가게 찾기------------------------------------------------------| 
                #search_store로 가게를 골랐으니 주문을 해보자!                
                if search_store is None:#선택된 가게가 없을 때
                    break
                else : #선택된 가게가 있을때
                    #주문을 생성해야함
                    #메뉴보여주기
                    # sql = "select sid from store, seller where store.sname = "+"'"+store_name[str_idx][0]+"'"+" and seller.local = "+"'"+ID[0]+"'and seller.domain = "+"'"+ID[1]+"'"+"and seller.seller_id = store.seller_id"
                   
                    sql = "select m.menu from menu m, store s where m.sid = s.sid and m.sid =" "'"+select_sid+"'"
                    result = execute_data(sql)
                    for i in range(0,len(result)):
                        print(i+1,": ",result[i][0])
                    menu_list=[]
                    print("주문할 메뉴의 번호를 선택하세요. 선택을 멈출시 0을 입력하세요 : ")
                    while 1:
                        com = input()
                        if com =="0":
                            break
                        print("선택한 메뉴의 수량을 입력해주세요")
                        quantity = input()
                        menu_quantity = result[int(com)-1][0] +": "+quantity+"개"
                        menu_list.append(menu_quantity)
                        print("주문할 메뉴의 번호를 선택하세요. 선택을 멈출시 0을 입력하세요 : ")
                    menu_Str = ",".join(menu_list)#menu list를 string으로 만들기
                    print(menu_Str+"를 선택하였습니다.")
                    
#|---------------------------------가게 선택 후 메뉴선택완료------------------------------------------------------| 
                    sql ="select customer.payments from customer where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'"   

                    customer_payment = execute_data(sql)
                    customer_payment = customer_payment[0][0]
                    customer_payment=customer_payment[1:-1]
                    customer_payment=ast.literal_eval(customer_payment) #리스트와 딕셔너리로 만들기
                    print("bid 목록보기")
                    sql = "select bid,name from bank"
                    result = execute_data(sql)
                    for i in range(0,len(result)):
                        print(result[i])
                    print("결제수단을 선택하세요")
                    
                    for i in range(0,len(customer_payment)):
                        print(i+1," : type : "+customer_payment[i]["type"]+", data : "+customer_payment[i]["data"])                    
                    com =input()
                    payment_method = customer_payment[int(com)-1]
                    payment_list =[]
                    if payment_method["type"]=="account":
                        #account일때 스트링으로 만들기
                        payment_list.append(payment_method["type"])
                        #"data"인 애도 ast를 통해 변경해줘야함 밑에꺼 수정하기 위에도 account 수정해아함
                        bank=ast.literal_eval(payment_method["data"]) #리스트와 딕셔너리로 만들기
                        bank_num = bank["bid"]
                        sql = "select name from bank where bank.bid = "+"'"+str(bank_num)+"'"
                        bank_name = execute_data(sql)
                        bank_name=bank_name[0][0]
                        payment_list.append(str(bank_name))
                        payment_list.append(str(bank["acc_num"]))
                    elif payment_method["type"]=="card":
                        #card일때 스트링으로 만들기 
                        payment_list.append(payment_method["type"])
                        card=ast.literal_eval(payment_method["data"]) #리스트와 딕셔너리로 만들기
                        card_num = card["card_num"]
                        payment_list.append(str(card_num))
                    payment_method = ",".join(payment_list)
                    
                    if payment_method is None:
                        print("결제수단 선택을 실패하였습니다.")
                    else :
                        #결제수단 선택 성공 결제하면됨
                        print("결제수단 선택을 완료하였습니다.")
                        print("===============결제 및 주문정보==============")
                        sql = "select name from customer where customer.local = "+"'"+ID[0]+"'and customer.domain = "+"'"+ID[1]+"'" 
                        result = execute_data(sql)               
                        print("결제자 : " +result[0][0] +"\n주문가게 : "+search_store+"\n주문메뉴 및 수량 : "+menu_Str+"\n결제수단 : "+payment_method)
                        print("============================================")    
                        print("결제하시겠습니까? [Y/N]")
                        com =input()
                        if com =="Y":
                            print("결제가 진행중입니다.")
                            order_id = ID[0]+"@"+ID[1]
                            sql ="insert into order_list(order_id,order_store,shopping_bascket,payment_method,payment_time,delivering,did) values("+"'"+order_id+"'"+','+"'"+select_sid+"'"+','+"'"+menu_Str+"'"+','+"'"+payment_method+"'"+','+"now()"+",'"+"1"+"',"+"'"+"null"+"')"
                            admin_table(sql)
                            print("주문이 완료되었습니다.")
                        elif com == "N":
                            print("결제가 종료되었습니다.")
            else :
                print("잘못입력하셨습니다.")
#|---------------------------------결제 및 주문 완료------------------------------------------------------| 
#|---------------------------------배달자 로그인 시작------------------------------------------------------| 

    if result =="3":
        #delivery
        print("회원님은 배달의 한양에 배달자로 등록되어있습니다.")
        sql = "select d.did from delivery d where d.local = "+"'"+ID[0]+"'and d.domain = "+"'"+ID[1]+"'"
        result = execute_data(sql)
        did = result[0][0]
        sql = "select o.order_id,o.shopping_bascket,o.payment_time from order_list o where o.did = "+"'"+did+"'"
        result = execute_data(sql)
        print("현재 회원님이 배송중인 주문들입니다..")
        for i in range(0,len(result)):
            order_id = result[i][0]
            order_shopping=result[i][1]
            order_payment_time = result[i][2]
            order_id_split = order_id.split("@")
            sql = "select c.lat,c.lng,c.phone from customer c, order_list o where o.order_id = "+"'"+order_id+"'"+"and c.local = "+"'"+order_id_split[0]+"'and c.domain = "+"'"+order_id_split[1]+"'"+"and o.did = "+"'"+did+"'"
            temp = execute_data(sql)
            print(i+1,")")
            print("구매자 정보(위도,경도,전화번호) : ",temp[0][0]," ",temp[0][1]," ",temp[0][2])
            print("주문정보 (메뉴,주문시간) : ",order_shopping," ",order_payment_time)
        break
                            
