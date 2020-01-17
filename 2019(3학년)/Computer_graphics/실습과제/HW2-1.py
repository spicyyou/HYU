import glfw
from OpenGL.GL import *
import numpy as np

v = np.linspace(0,np.pi*2,13)
cos = np.cos(v)
sin = np.sin(v)
t = 4

def key_callback(window, key, scancode, action, mods):
    global t
    if key ==glfw.KEY_1:
        if action == glfw.PRESS:
            t=1
    if key ==glfw.KEY_2:
        if action == glfw.PRESS:
            t=2
    if key ==glfw.KEY_3:
        if action == glfw.PRESS:
            t=3
    if key ==glfw.KEY_4:
        if action == glfw.PRESS:
            t=4
    if key ==glfw.KEY_5:
        if action == glfw.PRESS:
            t=5
    if key ==glfw.KEY_6:
        if action == glfw.PRESS:
            t=6
    if key ==glfw.KEY_7:
        if action == glfw.PRESS:
            t=7
    if key ==glfw.KEY_8:
        if action == glfw.PRESS:
            t=8
    if key ==glfw.KEY_9:
        if action == glfw.PRESS:
            t=9
    if key ==glfw.KEY_0:
        if action == glfw.PRESS:
            t=0
    elif key==glfw.KEY_SPACE and action==glfw.PRESS:
        print ('press space: (%d, %d)'%glfw.get_cursor_pos(window))

def render(T):
    if T == 1:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_POINTS)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()
    elif T == 2:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_LINES)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()
    elif T == 3:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_LINE_STRIP)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()
    elif T == 4:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_LINE_LOOP)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()
    elif T == 5:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_TRIANGLES)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()
    elif T == 6:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_TRIANGLE_STRIP)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()
    elif T == 7:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_TRIANGLE_FAN)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()
    elif T == 8:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_QUADS)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()
    elif T == 9:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_QUAD_STRIP)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()
    elif T == 0:
        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glBegin(GL_POLYGON)
        for i in range(0,12):
            glVertex2f(cos[i],sin[i])
        glEnd()

def main():
    global t
    if not glfw.init():
        return
    window = glfw.create_window(480,480, "2D Trans", None,None)
    if not window:
        glfw.terminate()
        return

    glfw.set_key_callback(window, key_callback)
    glfw.make_context_current(window)
    while not glfw.window_should_close(window):
        glfw.poll_events()
        render(t)
        glfw.swap_buffers(window)

    glfw.terminate()
if __name__ == "__main__":
    main()