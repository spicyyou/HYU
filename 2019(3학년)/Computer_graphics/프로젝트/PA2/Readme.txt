1. onMouseDrag �Լ� �� isDrag==V_DRAG
vertical dragging�̹Ƿ� y���� ��ġ�� �ٲ� �� �ֵ��� �����Ѵ�.
movecow�� vector3�� ���������� �����صд�.
Horizontal dragging �ڵ带 �����߰� �ٸ� ���� ray.direction�� �̿��� �̵��Ѵ�.
�׸��� movecow�� y���� currentPos�� y���� cowPickPosition[1]�� ���� �� ������ ������ cow2wld�� �����Ѵ�.

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

2. �ѹ� Ŭ���� �Ұ� �巹�׸� ������� ����
ó�� Ŭ������ ���� üũ�� �ְ� glfw_up���� drag�� ��������������
üũ�ϴ� ������ ������ش�.
������ elif state == GLFW_UP and isDrag!=0�κ��� �����ϰ�
drag�� �Ǻ��ϴ� ������ �������.

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


2. Ŭ���� ������ cow ��ġ ����

: state�� GLFW_UP�� �� �����ϴ� �ڵ��̴�.
Ŭ���ϸ� click_cnt������ ���������ְ� ī��Ʈ�� 6�̵Ǹ� �ѷ��ڽ��͸� �����Ѵ�.
catmull spline�� �׸��� ���� ������ x, y,z���� �������� �� Catmull_Rom_Spline_curve�Լ���
��������ش�.

Catmull_Rom_Spline_curve�Լ��� ppt�� ���� ��Ľ��� ������ �ۼ��ߴ�.


 elif checkDrag and flagRoller==0:
                isDrag=H_DRAG
                #if flagRoller==0: #not ready
                #print("click_cnt",click_cnt)
                nowCowPosition.append(cow2wld)
                click_cnt=click_cnt+1 #cow��ġ �߰� , ������ �߰�

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



3. display �Լ�

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
            #z�� ����� ����
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



: �ѷ��ڽ��Ͱ� �����ϸ� get_time �Լ��� ���� animstarttime�� ������ �̸� catmull_rom_spline_curve�Լ��� ���� ������ 
Cat_x,Cat_y,Cat_z�迭�� ���� ��ġ�� ���Ѵ�. ���� ������ ���� ��ġ�� �� ��ġ�� ���� ���� ���Ѵ�.

�׸��� Ŭ��Ƚ���� �������� �������� Ŭ���� ī���� ��ġ�� �Ҹ� �׷��ش�.

�׸��� math.atan2�Լ��� ���� yaw�� pitch�� ���Ѵ�.
�ڵ��� A�� yaw B�� pitch�� �ǹ��Ѵ�. 
�׸��� temp1�� yaw�� y�� ȸ�� temp2�� pitch�� z�� ȸ����Ų �Լ��̴�. 
Temp2�� temp1�� ��İ��� cow2wld�� ������� cow�� �̵���Ų��.
