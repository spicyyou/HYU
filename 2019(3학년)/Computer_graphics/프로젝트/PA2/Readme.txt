1. onMouseDrag 함수 중 isDrag==V_DRAG
vertical dragging이므로 y축의 위치만 바꿀 수 있도록 설정한다.
movecow는 vector3의 전역변수로 선언해둔다.
Horizontal dragging 코드를 참고했고 다른 점은 ray.direction을 이용해 이동한다.
그리고 movecow의 y값을 currentPos의 y값과 cowPickPosition[1]에 값을 뺀 값으로 저장해 cow2wld에 저장한다.

if(cursorOnCowBoundingBox):
                ray=screenCoordToRay(window, x, y)
                pp=pickInfo 
                p=Plane(ray.direction, pp.cowPickPosition)
                c=ray.intersectsPlane(p) 
                currentPos=ray.getPoint(c[1])
                movecow[1] = currentPos[1]-pp.cowPickPosition[1]
                #nowPos = np.array((0,currentPos[1]-pp.cowPickPosition[1],0))
                T=np.eye(4)
                #setTranslation(T, nowPos)
                
                if(flagvdrag == 1):  
                    correction = movecow[1]
                    flagvdrag = 0
				
                movecow[1] =movecow[1]- correction

                setTranslation(T,movecow)   
                cow2wld=T@pp.cowPickConfiguration
                # create a dr/agging plane perpendicular to the ray direction, 
                # and test intersection with the screen ray.
                print('vdrag')

2. 한번 클릭후 소가 드레그를 따라오게 만듬
처음 클릭했을 때를 체크해 주고 glfw_up에서 drag를 시작할지안할지
체크하는 변수를 만들어준다.
기존의 elif state == GLFW_UP and isDrag!=0부분을 변경하고
drag를 판별하는 변수를 만들었다.

if state == GLFW_DOWN:
            if firstclick==0: 
                firstclick = 1 
                '''elif isDrag==H_DRAG:
                isDrag=0'''
            elif checkDrag and flagRoller==0:
                print("vdrag")
                isDrag=V_DRAG 
                flagvdrag=1
elif state == GLFW_UP : 
            isDrag=H_DRAG 
            print( "Left mouse up\n") 
            if firstclick and checkDrag==0 :
                isDrag=H_DRAG
                checkDrag=1 
                flagvdrag=0


2. 클릭할 때마다 cow 위치 저장

: state가 GLFW_UP일 때 실행하는 코드이다.
클릭하면 click_cnt변수를 증가시켜주고 카운트가 6이되면 롤러코스터를 시작한다.
catmull spline을 그리기 위해 현재의 x, y,z값을 저장해준 후 Catmull_Rom_Spline_curve함수를
실행시켜준다.

Catmull_Rom_Spline_curve함수는 ppt에 나온 행렬식을 참고해 작성했다.


 elif checkDrag and flagRoller==0:
                isDrag=H_DRAG
                #if flagRoller==0: #not ready
                #print("click_cnt",click_cnt)
                nowCowPosition.append(cow2wld)
                click_cnt=click_cnt+1 #cow위치 추가 , 마리수 추가

                if click_cnt==6: #calculate catmull-rom spline
                    cursorOnCowBoundingBox=0
                    flagRoller=1 #ready
                    nowCowPosition=np.array(nowCowPosition)
                    x = np.zeros(6)
                    y = np.zeros(6)
                    z = np.zeros(6)
                    for i in range(0,6):
                        getT = getTranslation(nowCowPosition[i])
                        x[i]=getT[0]
                        y[i]=getT[1]
                        z[i]=getT[2]
                    Catmull_Rom_Spline_curve(x,y,z)
                    glfw.set_time(0.0)
                    firstclick=0


def Catmull_Rom_Spline_curve(x,y,z):
    for i in range(1,4):
        Cat_x[i][0] = -0.5*x[i-1] + 1.5*x[i] - 1.5*x[i+1] + 0.5*x[i+2]
        Cat_x[i][1] = x[i-1] - 2.5*x[i] + 2*x[i+1] - 0.5*x[i+2] 
        Cat_x[i][2] = -0.5*x[i-1] + 0.5*x[i+1] 
        Cat_x[i][3] = x[i] 

        Cat_y[i][0] = -0.5*y[i-1] + 1.5*y[i] - 1.5*y[i+1] + 0.5*y[i+2] 
        Cat_y[i][1] = y[i-1] - 2.5*y[i] + 2*y[i+1] - 0.5*y[i+2] 
        Cat_y[i][2] = -0.5*y[i-1] + 0.5*y[i+1] 
        Cat_y[i][3] = y[i] 

        Cat_z[i][0] = -0.5*z[i-1] + 1.5*z[i] - 1.5*z[i+1] + 0.5*z[i+2] 
        Cat_z[i][1] = z[i-1] - 2.5*z[i] + 2*z[i+1] - 0.5*z[i+2] 
        Cat_z[i][2] = -0.5*z[i-1] + 0.5*z[i+1] 
        Cat_z[i][3] = z[i] 
	
	#cyclic spline
    Cat_x[4][0] = -0.5*x[3] + 1.5*x[4] - 1.5*x[5] + 0.5*x[0] 
    Cat_x[4][1] = x[3] - 2.5*x[4] + 2*x[5] - 0.5*x[0] 
    Cat_x[4][2] = -0.5*x[3] + 0.5*x[5] 
    Cat_x[4][3] = x[4] 

    Cat_y[4][0] = -0.5*y[3] + 1.5*y[4] - 1.5*y[5] + 0.5*y[0] 
    Cat_y[4][1] = y[3] - 2.5*y[4] + 2*y[5] - 0.5*y[0] 
    Cat_y[4][2] = -0.5*y[3] + 0.5*y[5] 
    Cat_y[4][3] = y[4] 

    Cat_z[4][0] = -0.5*z[3] + 1.5*z[4] - 1.5*z[5] + 0.5*z[0] 
    Cat_z[4][1] = z[3] - 2.5*z[4] + 2*z[5] - 0.5*z[0] 
    Cat_z[4][2] = -0.5*z[3] + 0.5*z[5] 
    Cat_z[4][3] = z[4] 

    Cat_x[5][0] = -0.5*x[4] + 1.5*x[5] - 1.5*x[0] + 0.5*x[1] 
    Cat_x[5][1] = x[4] - 2.5*x[5] + 2*x[0] - 0.5*x[1] 
    Cat_x[5][2] = -0.5*x[4] + 0.5*x[0] 
    Cat_x[5][3] = x[5] 

    Cat_y[5][0] = -0.5*y[4] + 1.5*y[5] - 1.5*y[0] + 0.5*y[1] 
    Cat_y[5][1] = y[4] - 2.5*y[5] + 2*y[0] - 0.5*y[1] 
    Cat_y[5][2] = -0.5*y[4] + 0.5*y[0] 
    Cat_y[5][3] = y[5] 

    Cat_z[5][0] = -0.5*z[4] + 1.5*z[5] - 1.5*z[0] + 0.5*z[1] 
    Cat_z[5][1] = z[4] - 2.5*z[5] + 2*z[0] - 0.5*z[1] 
    Cat_z[5][2] = -0.5*z[4] + 0.5*z[0] 
    Cat_z[5][3] = z[5] 

    Cat_x[0][0] = -0.5*x[5] + 1.5*x[0] - 1.5*x[1] + 0.5*x[2] 
    Cat_x[0][1] = x[5] - 2.5*x[0] + 2*x[1] - 0.5*x[2] 
    Cat_x[0][2] = -0.5*x[5] + 0.5*x[1] 
    Cat_x[0][3] = x[0] 

    Cat_y[0][0] = -0.5*y[5] + 1.5*y[0] - 1.5*y[1] + 0.5*y[2] 
    Cat_y[0][1] = y[5] - 2.5*y[0] + 2*y[1] - 0.5*y[2] 
    Cat_y[0][2] = -0.5*y[5] + 0.5*y[1] 
    Cat_y[0][3] = y[0] 

    Cat_z[0][0] = -0.5*z[5] + 1.5*z[0] - 1.5*z[1] + 0.5*z[2] 
    Cat_z[0][1] = z[5] - 2.5*z[0] + 2*z[1] - 0.5*z[2] 
    Cat_z[0][2] = -0.5*z[5] + 0.5*z[1] 
    Cat_z[0][3] = z[0] 



3. display 함수

if flagRoller:
        animStartTime = glfw.get_time()
        if animStartTime <18.0:
            int_animStartTime = int(animStartTime)
            #print("int_animStartTime",int_animStartTime)
            animTime=glfw.get_time()-int(animStartTime)
            #print("animTime : ",animTime)
            #print("animStartTime : ",animStartTime)
            position = np.zeros(3)
            position[0] = Cat_x[int_animStartTime%6][3] + (Cat_x[int_animStartTime%6][2] + animTime * (Cat_x[int_animStartTime%6][1] + animTime * Cat_x[int_animStartTime%6][0])) * animTime
            position[1] = Cat_y[int_animStartTime%6][3] + (Cat_y[int_animStartTime%6][2] + animTime * (Cat_y[int_animStartTime%6][1] + animTime * Cat_y[int_animStartTime%6][0])) * animTime
            position[2] = Cat_z[int_animStartTime%6][3] + (Cat_z[int_animStartTime%6][2] + animTime * (Cat_z[int_animStartTime%6][1] + animTime * Cat_z[int_animStartTime%6][0])) * animTime
            position=np.array(position)
            Dir = position-prev
            
            A = -math.atan2(Dir[2],Dir[0])*180/np.pi #yaw
            B = -math.atan2(-Dir[1],np.sqrt(Dir[0]*Dir[0]+Dir[2]*Dir[2]))*180/np.pi #pitch
            
            
            #y-rotate
            #temp1 = np.array([[np.cos(A),0,np.sin(A)],[0,1,0],[-np.sin(A),0,np.cos(A)]])
            #yaw
            temp1 = np.array([[np.cos(np.pi*A/180),0,np.sin(np.pi*A/180),0],[0,1,0,0],[-np.sin(np.pi*A/180),0,np.cos(np.pi*A/180),0],[0,0,0,1]])
            
            '''cow2wld=temp1     
            #z-rotate
            if B!=0 :
                temp2 = np.array([[np.cos(np.pi*B/180),-np.sin(np.pi*B/180),0,0],[np.sin(np.pi*B/180),np.cos(np.pi*B/180),0,0],[0,0,1,0],[0,0,0,1]])            #x-rotate
                cow2wld=temp2@temp1'''
            #z를 제대로 하자
            #pitch
            temp2 = np.array([[np.cos(np.pi*B/180),-np.sin(np.pi*B/180),0,0],[np.sin(np.pi*B/180),np.cos(np.pi*B/180),0,0],[0,0,1,0],[0,0,0,1]])  
            cow2wld=temp2@temp1
            setTranslation(cow2wld,position)

            #head direction
            prev = position

        else:#reset
            isDrag=0
            firstclick=0
            checkDrag=0
            Cat_x = np.zeros((6,4))
            Cat_y = np.zeros((6,4))
            Cat_z = np.zeros((6,4))
            click_cnt=0
            flagRoller=0
            nowCowPosition=[]

    else: #finish
    														
        for i in range(click_cnt):
            drawCow(nowCowPosition[i],0)



: 롤러코스터가 시작하면 get_time 함수를 통해 animstarttime을 구한후 미리 catmull_rom_spline_curve함수를 통해 저장한 
Cat_x,Cat_y,Cat_z배열을 통해 위치를 구한다. 소의 방향은 현지 위치와 전 위치의 차를 통해 구한다.

그리고 클릭횟수를 충족하지 못했으면 클릭한 카우의 위치에 소를 그려준다.

그리고 math.atan2함수를 통해 yaw와 pitch를 구한다.
코드중 A는 yaw B는 pitch를 의미한다. 
그리고 temp1은 yaw를 y축 회전 temp2는 pitch를 z축 회전시킨 함수이다. 
Temp2와 temp1의 행렬곱을 cow2wld에 저장시켜 cow를 이동시킨다.
