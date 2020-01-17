import glfw
import sys
import pdb
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.arrays import ArrayDatatype
import time
import numpy as np
import ctypes
from PIL.Image import open
import OBJ
import math
from Ray import *


# global variables
firstclick=0
checkDrag=0
flagh=0
wld2cam=[]
cam2wld=[]
cow2wld=None
cursorOnCowBoundingBox=False
pickInfo=None
nowCowPosition=[]
floorTexID=0
flagRoller=0
click_cnt=0
cameras= [
	[28,18,28, 0,2,0, 0,1,0],   
	[28,18,-28, 0,2,0, 0,1,0], 
	[-28,18,28, 0,2,0, 0,1,0], 
	[-12,12,0, 0,2,0, 0,1,0],  
	[0,100,0,  0,0,0, 1,0,0]
]
camModel=None
cowModel=None
H_DRAG=1
V_DRAG=2
# dragging state
isDrag=0
movecow=np.array((0,0,0))
correction=0
#Catmull-rom-array
Cat_x = np.zeros((6,4))
Cat_y = np.zeros((6,4))
Cat_z = np.zeros((6,4))

prev = np.zeros(3)
flagvdrag =0

class PickInfo:
    def __init__(self, cursorRayT, cowPickPosition, cowPickConfiguration, cowPickPositionLocal):
        self.cursorRayT=cursorRayT
        self.cowPickPosition=cowPickPosition.copy()
        self.cowPickConfiguration=cowPickConfiguration.copy()
        self.cowPickPositionLocal=cowPickPositionLocal.copy()

def vector3(x,y,z):
    return np.array((x,y,z))
def position3(v):
    # divide by w
    w=v[3]
    return vector3(v[0]/w, v[1]/w, v[2]/w)

def vector4(x,y,z):
    return np.array((x,y,z,1))

def rotate(m,v):
    return m[0:3, 0:3]@v
def transform(m, v):
    return position3(m@np.append(v,1))

def getTranslation(m):
    return m[0:3,3]
def setTranslation(m,v):
    m[0:3,3]=v

def makePlane( a,  b,  n):
    v=a.copy()
    for i in range(3):
        if n[i]==1.0:
            v[i]=b[i] 
        elif n[i]==-1.0:
            v[i]=a[i] 
        else:
            assert(n[i]==0.0) 
            
    return Plane(rotate(cow2wld,n),transform(cow2wld,v)) 

def onKeyPress( window, key, scancode, action, mods):
    global cameraIndex
    if action==glfw.RELEASE:
        return   # do nothing
    # If 'c' or space bar are pressed, alter the camera.
    # If a number is pressed, alter the camera corresponding the number.
    if key==glfw.KEY_C or key==glfw.KEY_SPACE:
        print( "Toggle camera %s\n"% cameraIndex ) 
        cameraIndex += 1 
    elif key ==glfw.KEY_1:
        cameraIndex = 0
    elif key ==glfw.KEY_2:
        cameraIndex =1
    elif key ==glfw.KEY_3:
        cameraIndex =2
    elif key ==glfw.KEY_4:
        cameraIndex = 3
    elif key ==glfw.KEY_5:
        cameraIndex = 4
    if cameraIndex >= len(wld2cam):
        cameraIndex = 0 

def drawOtherCamera():
    global cameraIndex,wld2cam, camModel
    for i in range(len(wld2cam)):
        if (i != cameraIndex):
            glPushMatrix() 												# Push the current matrix on GL to stack. The matrix is wld2cam[cameraIndex].matrix().
            glMultMatrixd(cam2wld[i].T)
            drawFrame(5) 											# Draw x, y, and z axis.
            frontColor = [0.2, 0.2, 0.2, 1.0] 
            glEnable(GL_LIGHTING) 									
            glMaterialfv(GL_FRONT, GL_AMBIENT, frontColor) 			# Set ambient property frontColor.
            glMaterialfv(GL_FRONT, GL_DIFFUSE, frontColor) 			# Set diffuse property frontColor.
            glScaled(0.5,0.5,0.5) 										# Reduce camera size by 1/2.
            glTranslated(1.1,1.1,0.0) 									# Translate it (1.1, 1.1, 0.0).
            camModel.render()
            glPopMatrix() 												# Call the matrix on stack. wld2cam[cameraIndex].matrix() in here.

def drawFrame(leng):
    glDisable(GL_LIGHTING) 	# Lighting is not needed for drawing axis.
    glBegin(GL_LINES) 		# Start drawing lines.
    glColor3d(1,0,0) 		# color of x-axis is red.
    glVertex3d(0,0,0) 			
    glVertex3d(leng,0,0) 	# Draw line(x-axis) from (0,0,0) to (len, 0, 0). 
    glColor3d(0,1,0) 		# color of y-axis is green.
    glVertex3d(0,0,0) 			
    glVertex3d(0,leng,0) 	# Draw line(y-axis) from (0,0,0) to (0, len, 0).
    glColor3d(0,0,1) 		# color of z-axis is  blue.
    glVertex3d(0,0,0) 
    glVertex3d(0,0,leng) 	# Draw line(z-axis) from (0,0,0) - (0, 0, len).
    glEnd() 			# End drawing lines.

#*********************************************************************************
# Draw 'cow' object.
#*********************************************************************************/
def drawCow(_cow2wld, drawBB):

    glPushMatrix() 		# Push the current matrix of GL into stack. This is because the matrix of GL will be change while drawing cow.

    # The information about location of cow to be drawn is stored in cow2wld matrix.
    # (Project2 hint) If you change the value of the cow2wld matrix or the current matrix, cow would rotate or move.
    glMultMatrixd(_cow2wld.T)

    drawFrame(5) 										# Draw x, y, and z axis.
    frontColor = [0.8, 0.2, 0.9, 1.0] 
    glEnable(GL_LIGHTING) 
    glMaterialfv(GL_FRONT, GL_AMBIENT, frontColor) 		# Set ambient property frontColor.
    glMaterialfv(GL_FRONT, GL_DIFFUSE, frontColor) 		# Set diffuse property frontColor.
    cowModel.render()	# Draw cow. 
    glDisable(GL_LIGHTING) 
    if drawBB:
        glBegin(GL_LINES) 
        glColor3d(1,1,1) 
        cow=cowModel
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmax[2]) 

        glColor3d(1,1,1) 
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmax[2]) 

        glColor3d(1,1,1) 
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmax[2]) 


        glColor3d(1,1,1) 
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmax[2]) 

        glColor3d(1,1,1) 
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmin[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmin[0], cow.bbmax[1], cow.bbmax[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmin[2]) 
        glVertex3d( cow.bbmax[0], cow.bbmax[1], cow.bbmax[2]) 
        glEnd() 
    glPopMatrix() 			# Pop the matrix in stack to GL. Change it the matrix before drawing cow.
def drawFloor():

    glDisable(GL_LIGHTING) 

    # Set color of the floor.
    # Assign checker-patterned texture.
    glEnable(GL_TEXTURE_2D) 
    glBindTexture(GL_TEXTURE_2D, floorTexID ) 

    # Draw the floor. Match the texture's coordinates and the floor's coordinates resp. 
    nrep=4
    glBegin(GL_POLYGON) 
    glTexCoord2d(0,0) 
    glVertex3d(-12,-0.1,-12) 		# Texture's (0,0) is bound to (-12,-0.1,-12).
    glTexCoord2d(nrep,0) 
    glVertex3d( 12,-0.1,-12) 		# Texture's (1,0) is bound to (12,-0.1,-12).
    glTexCoord2d(nrep,nrep) 
    glVertex3d( 12,-0.1, 12) 		# Texture's (1,1) is bound to (12,-0.1,12).
    glTexCoord2d(0,nrep) 
    glVertex3d(-12,-0.1, 12) 		# Texture's (0,1) is bound to (-12,-0.1,12).
    glEnd() 

    glDisable(GL_TEXTURE_2D) 	
    drawFrame(5) 				# Draw x, y, and z axis.

def display():
    global cameraIndex, cow2wld
    glClearColor(0.8, 0.9, 0.9, 1.0)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) 				# Clear the screen
    # set viewing transformation.
    glLoadMatrixd(wld2cam[cameraIndex].T)

    drawOtherCamera() 													# Locate the camera's position, and draw all of them.
    drawFloor() 													# Draw floor.
    global flagRoller,isDrag, Cat_x, Cat_y,Cat_z,click_cnt,nowCowPosition,prev,firstclick,checkDrag
    # TODO: 
    # update cow2wld here to animate the cow.
    #animTime=glfw.get_time()-animStartTime 
    #you need to modify both the translation and rotation parts of the cow2wld matrix.
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
        
# Draw cow.

    drawCow(cow2wld, cursorOnCowBoundingBox) 
    glFlush() 

def reshape(window, w, h):
    width = w 
    height = h 
    glViewport(0, 0, width, height) 
    glMatrixMode(GL_PROJECTION)             # Select The Projection Matrix
    glLoadIdentity()                        # Reset The Projection Matrix
    # Define perspective projection frustum
    aspect = width/(float)(height) 
    gluPerspective(45, aspect, 1, 1024) 
    matProjection=glGetDoublev(GL_PROJECTION_MATRIX).T
    glMatrixMode(GL_MODELVIEW)              # Select The Modelview Matrix
    glLoadIdentity()                        # Reset The Projection Matrix

def initialize(window):
    global cursorOnCowBoundingBox, floorTexID, cameraIndex, camModel, cow2wld, cowModel
    cursorOnCowBoundingBox=False 
    # Set up OpenGL state
    glShadeModel(GL_SMOOTH)          # Set Smooth Shading
    glEnable(GL_DEPTH_TEST)          # Enables Depth Testing
    glDepthFunc(GL_LEQUAL)           # The Type Of Depth Test To Do
    # Use perspective correct interpolation if available
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST) 
    # Initialize the matrix stacks
    width, height = glfw.get_window_size(window)
    reshape(window, width, height) 
    # Define lighting for the scene
    lightDirection   = [1.0, 1.0, 1.0, 0] 
    ambientIntensity = [0.1, 0.1, 0.1, 1.0] 
    lightIntensity   = [0.9, 0.9, 0.9, 1.0] 
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientIntensity) 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity) 
    glLightfv(GL_LIGHT0, GL_POSITION, lightDirection) 
    glEnable(GL_LIGHT0) 

    # initialize floor
    im = open('bricks.bmp')
    try:
        ix, iy, image = im.size[0], im.size[1], im.tobytes("raw", "RGB", 0, -1)
    except SystemError:
        ix, iy, image = im.size[0], im.size[1], im.tobytes("raw", "RGBX", 0, -1)

    # Make texture which is accessible through floorTexID. 
    floorTexID=glGenTextures( 1)
    glBindTexture(GL_TEXTURE_2D, floorTexID) 		
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST) 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST) 
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE) 
    glTexImage2D(GL_TEXTURE_2D, 0, 3, ix, ix, 0, GL_RGB, GL_UNSIGNED_BYTE, image) 
    # initialize cow
    cowModel=OBJ.OBJrenderer("cow.obj")

    # initialize cow2wld matrix
    glPushMatrix() 		        # Push the current matrix of GL into stack.
    glLoadIdentity() 		        # Set the GL matrix Identity matrix.
    glTranslated(0,-cowModel.bbmin[1],-8) 	# Set the location of cow.
    glRotated(-90, 0, 1, 0) 		# Set the direction of cow. These information are stored in the matrix of GL.
    cow2wld=glGetDoublev(GL_MODELVIEW_MATRIX).T # convert column-major to row-major 
    glPopMatrix() 			# Pop the matrix on stack to GL.


    # intialize camera model.
    camModel=OBJ.OBJrenderer("camera.obj")


    # initialize camera frame transforms.

    cameraCount=len(cameras)
    for i in range(cameraCount):
        # 'c' points the coordinate of i-th camera.
        c = cameras[i] 										
        glPushMatrix() 													# Push the current matrix of GL into stack.
        glLoadIdentity() 												# Set the GL matrix Identity matrix.
        gluLookAt(c[0],c[1],c[2], c[3],c[4],c[5], c[6],c[7],c[8]) 		# Setting the coordinate of camera.
        wld2cam.append(glGetDoublev(GL_MODELVIEW_MATRIX).T)
        glPopMatrix() 													# Transfer the matrix that was pushed the stack to GL.
        cam2wld.append(np.linalg.inv(wld2cam[i]))
    cameraIndex = 0 

def onMouseButton(window,button, state, mods):
    global isDrag, V_DRAG, H_DRAG,flagRoller, checkDrag,firstclick,flagvdrag
    global click_cnt, nowCowPosition,flagvdrag
    GLFW_DOWN=1 
    GLFW_UP=0 
    x, y=glfw.get_cursor_pos(window)
    if button == glfw.MOUSE_BUTTON_LEFT:
        if state == GLFW_DOWN:
            if firstclick==0: 
                firstclick = 1 
                '''elif isDrag==H_DRAG:
                isDrag=0'''
            elif checkDrag and flagRoller==0:
                print("vdrag")
                isDrag=V_DRAG 
                flagvdrag=1

            print( "Left mouse down-click at %d %d\n" % (x,y))
            # start vertical dragging
        
        elif state == GLFW_UP :#and isDrag!=0:
            isDrag=H_DRAG 
            print( "Left mouse up\n") 
            if firstclick and checkDrag==0 :
                isDrag=H_DRAG
                checkDrag=1
                flagvdrag=0

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
            # start horizontal dragging using mouse-move events.
            

    elif button == glfw.MOUSE_BUTTON_RIGHT:
        if state == GLFW_DOWN:
            print( "Right mouse click at (%d, %d)\n"%(x,y) ) 

#catmull rom spline curve
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





def onMouseDrag(window, x, y):
    global isDrag,cursorOnCowBoundingBox, pickInfo, cow2wld,flagvdrag,correction
    if isDrag: 
        print( "in drag mode %d\n"% isDrag) 
        if  isDrag==V_DRAG:
            # vertical dragging
            # TODO:
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

        else:
            # horizontal dragging
            # Hint: read carefully the following block to implement vertical dragging.
            if cursorOnCowBoundingBox:
                ray=screenCoordToRay(window, x, y) 
                pp=pickInfo 
                p=Plane(np.array((0,1,0)), pp.cowPickPosition) 
                c=ray.intersectsPlane(p) 

                currentPos=ray.getPoint(c[1])
                print(pp.cowPickPosition, currentPos)
                print(pp.cowPickConfiguration, cow2wld)
                movecow[0] = currentPos[0]-pp.cowPickPosition[0]
                movecow[2] = currentPos[2]-pp.cowPickPosition[2]

                T=np.eye(4)
                #setTranslation(T, currentPos-pp.cowPickPosition)
                setTranslation(T, movecow)
                cow2wld=T@pp.cowPickConfiguration 
    else:
        ray=screenCoordToRay(window, x, y)

        planes=[] 
        cow=cowModel
        bbmin=cow.bbmin
        bbmax=cow.bbmax

        planes.append(makePlane(bbmin, bbmax, vector3(0,1,0))) 
        planes.append(makePlane(bbmin, bbmax, vector3(0,-1,0))) 
        planes.append(makePlane(bbmin, bbmax, vector3(1,0,0))) 
        planes.append(makePlane(bbmin, bbmax, vector3(-1,0,0))) 
        planes.append(makePlane(bbmin, bbmax, vector3(0,0,1))) 
        planes.append(makePlane(bbmin, bbmax, vector3(0,0,-1))) 


        o=ray.intersectsPlanes(planes) 
        cursorOnCowBoundingBox=o[0]
        cowPickPosition=ray.getPoint(o[1])
        cowPickLocalPos=transform(np.linalg.inv(cow2wld),cowPickPosition)
        pickInfo=PickInfo( o[1], cowPickPosition, cow2wld, cowPickLocalPos)
        pp=pickInfo
        movecow[1] = pp.cowPickPositionLocal[1]

def screenCoordToRay(window, x, y):
    width, height = glfw.get_window_size(window)

    matProjection=glGetDoublev(GL_PROJECTION_MATRIX).T
    matProjection=matProjection@wld2cam[cameraIndex]  # use @ for matrix mult.
    invMatProjection=np.linalg.inv(matProjection) 
    # -1<=v.x<1 when 0<=x<width
    # -1<=v.y<1 when 0<=y<height
    vecAfterProjection =vector4(
            (float(x - 0))/(float(width))*2.0-1.0,
            -1*(((float(y - 0))/float(height))*2.0-1.0),
            -10)

    #std::cout<<"cowPosition in clip coordinate (NDC)"<<matProjection*cow2wld.getTranslation()<<std::endl 
	
    vecBeforeProjection=position3(invMatProjection@vecAfterProjection) 

    rayOrigin=getTranslation(cam2wld[cameraIndex])
    return Ray(rayOrigin, normalize(vecBeforeProjection-rayOrigin))

def main():
    if not glfw.init():
        print ('GLFW initialization failed')
        sys.exit(-1)
    width = 800 
    height = 600 
    window = glfw.create_window(width, height, 'modern opengl example', None, None)
    if not window:
        glfw.terminate()
        sys.exit(-1)

    glfw.make_context_current(window)
    glfw.set_key_callback(window, onKeyPress)
    glfw.set_mouse_button_callback(window, onMouseButton)
    glfw.set_cursor_pos_callback(window, onMouseDrag)
    glfw.swap_interval(1)

    initialize(window) 						
    while not glfw.window_should_close(window):
        glfw.poll_events()
        display()

        glfw.swap_buffers(window)

    glfw.terminate()
if __name__ == "__main__":
    main()