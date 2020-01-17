#!/usr/bin/env python3
# -*- coding: utf-8 -*
# sample_python aims to allow seamless integration with lua.
# see examples below

import os
import sys
import pdb  # use pdb.set_trace() for debugging
import code # or use code.interact(local=dict(globals(), **locals()))  for debugging.
import xml.etree.ElementTree as ET
import numpy as np
from PIL import Image 
class Color:
    def __init__(self, R, G, B):
        self.color=np.array([R,G,B]).astype(np.float)

    # Gamma corrects this color.
    # @param gamma the gamma value to use (2.2 is generally used).
    def gammaCorrect(self, gamma):
        inverseGamma = 1.0 / gamma
        self.color=np.power(self.color, inverseGamma)

    def toUINT8(self):
        return (np.clip(self.color, 0,1)*255).astype(np.uint8)


def main():


    tree = ET.parse(sys.argv[1])
    root = tree.getroot() #file의 최상단 가리킴

    
    # set default values
    #viewPoint = np.array([0,0,0]).astype(np.float)
    viewDir=np.array([0,0,-1]).astype(np.float)
    viewUp=np.array([0,1,0]).astype(np.float)
    viewProjNormal=-1*viewDir  # you can safely assume this. (no examples will use shifted perspective camera)
    viewWidth=1.0
    viewHeight=1.0
    projDistance=1.0
    intensity=np.array([1,1,1]).astype(np.float)  # how bright the light is.
    #print(np.cross(viewDir, viewUp))#np.cross 는 외적을 의미
    diffuseColor_c = np.array([0,0,0,]).astype(np.float)

    imgSize=np.array(root.findtext('image').split()).astype(np.int)

    channels=3
    img = np.zeros((imgSize[1], imgSize[0], channels), dtype=np.uint8)#imgsize = [300,300]
    img[:,:]=0

    res = np.zeros((imgSize[1], imgSize[0], channels), dtype=np.uint8)#imgsize = [300,300]
    res[:,:]=0
    for c in root.findall('camera'):
        if(c.findtext('viewPoint')is not None):
            viewPoint=np.array(c.findtext('viewPoint').split()).astype(np.float)
            #print(viewPoint)
        if(c.findtext('viewDir')is not None):
            viewDir = np.array(c.findtext('viewDir').split()).astype(np.float)
            #print(viewDir)
        if(c.findtext('projNormal')is not None):
            viewProjNormal = np.array(c.findtext('projNormal').split()).astype(np.float)
            #print(viewProjNormal)
        if(c.findtext('viewUp')is not None):
            viewUp = np.array(c.findtext('viewUp').split()).astype(np.float)
            #print(viewUp)
        if(c.findtext('projDistance')is not None):
            projDistance = np.array(c.findtext('projDistance').split()).astype(np.float)
            #print(projDistance)
        if(c.findtext('viewWidth')is not None):
            viewWidth = np.array(c.findtext('viewWidth').split()).astype(np.float)
            #print(viewWidth)
        if(c.findtext('viewHeight')is not None):
            viewHeight = np.array(c.findtext('viewHeight').split()).astype(np.float) 
            #print(viewHeight)
    colordic = {}
    obj = []
    for c in root.findall('shader'):
        shadername = c.get('name')
        shadertype = c.get('type')
        diffuseColor_c=np.array(c.findtext('diffuseColor').split()).astype(np.float)
        colordic[shadername]=diffuseColor_c

    for c in root.findall('surface'):
        surfaceType = c.get('type')
        if surfaceType =="Sphere":
            center =np.array(c.findtext('center').split()).astype(np.float)#이거 어떻게하징
            radius =np.array(c.findtext('radius').split()).astype(np.float)
            
            for e in c.findall('shader'):
                ref = e.get('ref')
                diffuseColor=colordic[ref]
                obj.append([surfaceType,center,radius,diffuseColor])
        
        elif surfaceType =="Box":
            minPt =np.array(c.findtext('minPt').split()).astype(np.float)
            maxPt =np.array(c.findtext('maxPt').split()).astype(np.float)
            for e in c.findall('shader'):
                ref = e.get('ref')
                diffuseColor=colordic[ref]
                obj.append([surfaceType,minPt,maxPt,diffuseColor])


    #ray tracer
    W = viewProjNormal
    W = W/np.sqrt((W**2).sum())
    U = np.cross(viewUp,W)
    U = U/np.sqrt((U**2).sum())
    V = np.cross(W, U)
    V = V/np.sqrt((V**2).sum())            
    S = viewPoint - W*projDistance
    L = S - U*(viewWidth/2) - V*(viewHeight/2)
    for i in range(imgSize[1]):        
        for j in range(imgSize[0]):
            D = L + (U*j*(viewWidth/imgSize[0]))+(V*i*(viewHeight/imgSize[1]))
            D = D - viewPoint
            tmin = float('inf')
            closetobject = "?"
            closet = []
            t=float('inf')
            for k in obj:
                if k[0]=="Sphere":
                    center = k[1]
                    radius = k[2]
                    A = np.dot(D,D)
                    B = np.dot(D,(viewPoint-center))
                    C = np.dot((viewPoint-center),(viewPoint-center))-(radius*radius)
                    Deter = B*B - A*C
                    if(Deter>=0):
                        Deter_ = np.sqrt(Deter)
                        t1 = (((-1)*B+Deter_)/2*A)
                        t2 = ((-1)*B-Deter_)/(2*A)
                        if t1<t2:
                            t=t1
                        else:
                            t=t2
                elif k[0]=="Box":
                    minPt = k[1]
                    maxPt = k[2]
                    isok=0
                    if(D[0]!=0):
                        txmin = (minPt[0]-viewPoint[0])/D[0]
                        txmax = (maxPt[0]-viewPoint[0])/D[0]

                    if txmin>txmax :
                        temp = txmin
                        txmin = txmax
                        txmax = temp
                    if(D[1]!=0):
                        tymin = (minPt[1]-viewPoint[1])/D[1]
                        tymax = (maxPt[1]-viewPoint[1])/D[1]

                    if tymin >tymax:
                        temp = tymin
                        tymin = tymax
                        tymax = temp
                    
                    if (txmin>tymax) or (tymin>txmax):
                        continue
                    
                    if tymin>txmin:
                        txmin = tymin
                    
                    if tymax <txmax:
                        txmax = tymax
                    if(D[2]!=0):
                        #print(i,j,D,"D[2]==0")    
                        tzmin = (minPt[2]-viewPoint[2])/D[2]
                        tzmax = (maxPt[2]-viewPoint[2])/D[2]
                    

                    if tzmin>tzmax:
                        temp = tzmin
                        tzmin = tzmax
                        tzmax = temp

                    if ((txmin>tzmax) or (tzmin>txmax)):
                        continue

                    if tzmin>txmin:
                        txmin = tzmin

                    if tzmax<txmax:
                        txmax = tzmax

                    t = txmin

                if t!=float('inf'):
                    if tmin>t:
                        tmin=t
                        closet = k
                   
            if tmin==float('inf'):
                #print(i,j)
                img[i][j]=[0,0,0]
            else:
                #print(i,j)
                color = Color(closet[3][0],closet[3][1],closet[3][2])
                img[i][j]=color.toUINT8()
    #res = img
    for i in range(imgSize[1]):
        res[i] = img[imgSize[1]-1-i]   

      #specularColor = np.array(c.findtext('specularColor').split()).astype(np.int)
        #exponent = np.array(c.findtext('exponent').split()).astype(np.int)
    '''for c in root.findall('light'):
        position = np.array(c.findtext('position').split()).astype(np.float)
        intensity =np.array(c.findtext('intensity').split()).astype(np.float)'''
       
    #이건 뭐지?
    #code.interact(local=dict(globals(), **locals()))  

    # replace the code block below!
    rawimg = Image.fromarray(res, 'RGB')
    rawimg.save('out.png')
    rawimg.save(sys.argv[1]+'.png')
    
if __name__=="__main__":
    main()
