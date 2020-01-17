import glfw
from OpenGL.GL import *
import numpy as np
from OpenGL.GLU import *

gCamAng = 0
gCamHeight = 1.

def drawCube_glVertex():
    glBegin(GL_TRIANGLES)

    glNormal3f(0,0,1) # v0, v2, v1, v0, v3, v2 normal

    glVertex3f( -1 , 1 , 1 ) # v0 position
    glVertex3f( 1 , -1 , 1 ) # v2 position
    glVertex3f( 1 , 1 , 1 ) # v1 position

    glVertex3f( -1 , 1 , 1 ) # v0 position
    glVertex3f( -1 , -1 , 1 ) # v3 position
    glVertex3f( 1 , -1 , 1 ) # v2 position

    glNormal3f(0,0,-1)
    glVertex3f( -1 , 1 , -1 ) # v4
    glVertex3f( 1 , 1 , -1 ) # v5
    glVertex3f( 1 , -1 , -1 ) # v6

    glVertex3f( -1 , 1 , -1 ) # v4
    glVertex3f( 1 , -1 , -1 ) # v6
    glVertex3f( -1 , -1 , -1 ) # v7

    glNormal3f(0,1,0)
    glVertex3f( -1 , 1 , 1 ) # v0
    glVertex3f( 1 , 1 , 1 ) # v1
    glVertex3f( 1 , 1 , -1 ) # v5

    glVertex3f( -1 , 1 , 1 ) # v0
    glVertex3f( 1 , 1 , -1 ) # v5
    glVertex3f( -1 , 1 , -1 ) # v4

    glNormal3f(0,-1,0)
    glVertex3f( -1 , -1 , 1 ) # v3
    glVertex3f( 1 , -1 , -1 ) # v6
    glVertex3f( 1 , -1 , 1 ) # v2

    glVertex3f( -1 , -1 , 1 ) # v3
    glVertex3f( -1 , -1 , -1 ) # v7
    glVertex3f( 1 , -1 , -1 ) # v6

    glNormal3f(1,0,0)
    glVertex3f( 1 , 1 , 1 ) # v1
    glVertex3f( 1 , -1 , 1 ) # v2
    glVertex3f( 1 , -1 , -1 ) # v6

    glVertex3f( 1 , 1 , 1 ) # v1
    glVertex3f( 1 , -1 , -1 ) # v6
    glVertex3f( 1 , 1 , -1 ) # v5

    glNormal3f(-1,0,0)
    glVertex3f( -1 , 1 , 1 ) # v0
    glVertex3f( -1 , -1 , -1 ) # v7
    glVertex3f( -1 , -1 , 1 ) # v3

    glVertex3f( -1 , 1 , 1 ) # v0
    glVertex3f( -1 , 1 , -1 ) # v4
    glVertex3f( -1 , -1 , -1 ) # v7

    glEnd()

def createVertexArraySeparate():
    varr = np.array([
            (0,0,1), # v0 normal
            ( -1 , 1 , 1 ), # v0 position
            (0,0,1), # v2 normal
            ( 1 , -1 , 1 ), # v2 position
            (0,0,1), # v1 normal
            ( 1 , 1 , 1 ), # v1 position

            (0,0,1), # v0 normal
            ( -1 , 1 , 1 ), # v0 position
            (0,0,1), # v3 normal
            ( -1 , -1 , 1 ), # v3 position
            (0,0,1), # v2 normal
            ( 1 , -1 , 1 ), # v2 position

            (0,0,-1),
            ( -1 , 1 , -1 ), # v4
            (0,0,-1),
            ( 1 , 1 , -1 ), # v5
            (0,0,-1),
            ( 1 , -1 , -1 ), # v6

            (0,0,-1),
            ( -1 , 1 , -1 ), # v4
            (0,0,-1),
            ( 1 , -1 , -1 ), # v6
            (0,0,-1),
            ( -1 , -1 , -1 ), # v7

            (0,1,0),
            ( -1 , 1 , 1 ), # v0
            (0,1,0),
            ( 1 , 1 , 1 ), # v1
            (0,1,0),
            ( 1 , 1 , -1 ), # v5

            (0,1,0),
            ( -1 , 1 , 1 ), # v0
            (0,1,0),
            ( 1 , 1 , -1 ), # v5
            (0,1,0),
            ( -1 , 1 , -1 ), # v4

            (0,-1,0),
            ( -1 , -1 , 1 ), # v3
            (0,-1,0),
            ( 1 , -1 , -1 ), # v6
            (0,-1,0),
            ( 1 , -1 , 1 ), # v2

            (0,-1,0),
            ( -1 , -1 , 1 ), # v3
            (0,-1,0),
            ( -1 , -1 , -1 ), # v7
            (0,-1,0),
            ( 1 , -1 , -1 ), # v6

            (1,0,0),
            ( 1 , 1 , 1 ), # v1
            (1,0,0),
            ( 1 , -1 , 1 ), # v2
            (1,0,0),
            ( 1 , -1 , -1 ), # v6

            (1,0,0),
            ( 1 , 1 , 1 ), # v1
            (1,0,0),
            ( 1 , -1 , -1 ), # v6
            (1,0,0),
            ( 1 , 1 , -1 ), # v5

            (-1,0,0),
            ( -1 , 1 , 1 ), # v0
            (-1,0,0),
            ( -1 , -1 , -1 ), # v7
            (-1,0,0),
            ( -1 , -1 , 1 ), # v3

            (-1,0,0),
            ( -1 , 1 , 1 ), # v0
            (-1,0,0),
            ( -1 , 1 , -1 ), # v4
            (-1,0,0),
            ( -1 , -1 , -1 ), # v7
            ], 'float32')
    return varr
    
def drawCube_glDrawArray():
    global gVertexArraySeparate
    varr = gVertexArraySeparate
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_NORMAL_ARRAY)
    glNormalPointer(GL_FLOAT, 6*varr.itemsize, varr)
    glVertexPointer(3, GL_FLOAT, 6*varr.itemsize,
    ctypes.c_void_p(varr.ctypes.data + 3*varr.itemsize))
    glDrawArrays(GL_TRIANGLES, 0, int(varr.size/6))

def render():
    global gCamAng, gCamHeight
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    
    glEnable(GL_DEPTH_TEST)
    
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45,1,1,10)
    
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    
    gluLookAt(5*np.sin(gCamAng),gCamHeight,5*np.cos(gCamAng), 0,0,0, 0,1,0)

    drawFrame()
    
    glEnable(GL_LIGHTING) # try to uncomment: no lighting
    glEnable(GL_LIGHT0)

    glEnable(GL_RESCALE_NORMAL) # try to uncomment: lighting will be incorrect if you scale the object
    # glEnable(GL_NORMALIZE)

    # light position
    glPushMatrix()

    # glRotatef(t*(180/np.pi),0,1,0) # try to uncomment: rotate light
    lightPos = (3.,4.,5.,1.) # try to change 4th element to 0. or 1.
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos)

    ambientLightColor = (.1,.1,.1,1.)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightColor)
    
    specularObjectColor = (1.,1.,1.,1.) 
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularObjectColor)
    
    glMaterialfv(GL_FRONT, GL_SHININESS, 10)


    glPopMatrix()
    # light intensity for each color channel
    '''lightColor = (1.,1.,1.,1.)
    ambientLightColor = (.1,.1,.1,1.)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor)
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor)
    glLightfv(GL_LIGHT0, GL_AMBIENT,ambientLightColor)

    # material reflectance for each color channel
    objectColor = (1.,0.,0.,1.)
    specularObjectColor = (1.,1.,1.,1.)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, objectColor)
    glMaterialfv(GL_FRONT, GL_SHININESS, 10)
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularObjectColor)'''

    glPushMatrix()
    # glRotatef(t*(180/np.pi),0,1,0) # try to uncomment: rotate object
    # glScalef(1.,.2,1.) # try to uncomment: scale object

    glColor3ub(0, 0, 255) # glColor*() is ignored if lighting is enabled

    # drawCube_glVertex()
    drawCube_glDrawArray()
    glPopMatrix()

    glDisable(GL_LIGHTING)

def drawTriAngle_glDrawArrays():
    global gVertexArraySeparate
    varr = gVertexArraySeparate
    glEnableClientState(GL_VERTEX_ARRAY)
    glVertexPointer(3, GL_FLOAT, 3*varr.itemsize, varr)
    glDrawArrays(GL_TRIANGLES, 0, int(varr.size/3))

def drawFrame():
    glBegin(GL_LINES)
    
    glColor3ub(255,0,0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([1.,0.,0.]))
    
    glColor3ub(0,255,0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([0.,1.,0.]))
    
    glColor3ub(0,0,255)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([0.,0.,1.]))
    
    glEnd()

def key_callback(window, key, scancode, action, mods):
    global gCamAng, gCamHeight
    if action == glfw.PRESS or action == glfw.REPEAT:
        if key == glfw.KEY_1:
            gCamAng += np.radians(-10)
        if key == glfw.KEY_3:
            gCamAng += np.radians(10)
        if key == glfw.KEY_2:
            gCamHeight += .1
        if key == glfw.KEY_W:
            gCamHeight += -.1

        if key == glfw.KEY_A:
            tlightColor = (1.,0.,0.,1.)
            #tambientLightColor = (.1,.0,.0,1.)
            glLightfv(GL_LIGHT0, GL_DIFFUSE, tlightColor)
            glLightfv(GL_LIGHT0, GL_SPECULAR,tlightColor)
            #glLightfv(GL_LIGHT0, GL_AMBIENT,tambientLightColor)
        if key == glfw.KEY_S:
            tlightColor = (0.,1.,0.,1.)
            #tambientLightColor = (.0,.1,.0,1.)
            glLightfv(GL_LIGHT0, GL_DIFFUSE, tlightColor)
            glLightfv(GL_LIGHT0, GL_SPECULAR,tlightColor)
            #glLightfv(GL_LIGHT0, GL_AMBIENT,tambientLightColor)
        if key == glfw.KEY_D:
            tlightColor = (0.,0.,1.,1.)
            #tambientLightColor = (.0,.0,.1,1.)
            glLightfv(GL_LIGHT0, GL_DIFFUSE, tlightColor)
            glLightfv(GL_LIGHT0, GL_SPECULAR,tlightColor)
            #glLightfv(GL_LIGHT0, GL_AMBIENT,tambientLightColor)
        if key == glfw.KEY_F:
            tlightColor = (1.,1.,1.,1.)
            #tambientLightColor = (.1,.1,.1,1.)
            glLightfv(GL_LIGHT0, GL_DIFFUSE, tlightColor)
            glLightfv(GL_LIGHT0, GL_SPECULAR,tlightColor)
            #glLightfv(GL_LIGHT0, GL_AMBIENT,tambientLightColor)
        if key == glfw.KEY_Z:
            tobjectColor = (1.,0.,0.,1.)
            #tspecularObjectColor = (1.,1.,1.,1.)
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tobjectColor)
            glMaterialfv(GL_FRONT, GL_SHININESS, 10)
            #glMaterialfv(GL_FRONT, GL_SPECULAR, tspecularObjectColor)
        if key == glfw.KEY_X:
            tobjectColor = (0.,1.,0.,1.)
            #tspecularObjectColor = (1.,1.,1.,1.)
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tobjectColor)
            glMaterialfv(GL_FRONT, GL_SHININESS, 10)
            #glMaterialfv(GL_FRONT, GL_SPECULAR, tspecularObjectColor)
        if key == glfw.KEY_C:
            tobjectColor = (0.,0.,1.,1.)
            #tspecularObjectColor = (1.,1.,1.,1.)
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tobjectColor)
            glMaterialfv(GL_FRONT, GL_SHININESS, 10)
            #glMaterialfv(GL_FRONT, GL_SPECULAR, tspecularObjectColor)
        if key == glfw.KEY_V:
            tobjectColor = (1.,1.,1.,1.)
            #tspecularObjectColor = (1.,1.,1.,1.)
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tobjectColor)
            glMaterialfv(GL_FRONT, GL_SHININESS, 10)
            #glMaterialfv(GL_FRONT, GL_SPECULAR, tspecularObjectColor)
gVertexArraySeparte = None
def main():
    global gVertexArraySeparate
    if not glfw.init():
        return

    window = glfw.create_window(480,480,"2017030519-7-1",None,None)
    if not window:
        glfw.terminate()
        return
    
    glfw.make_context_current(window)
    glfw.set_key_callback(window, key_callback)
    glfw.swap_interval(1)
    gVertexArraySeparate = createVertexArraySeparate()

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()