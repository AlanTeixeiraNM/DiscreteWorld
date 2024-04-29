# Source code for generating the graphs in discreet 
# "Procedural generation: building worlds algorithmicaly"
# Python 3.12.3, 
# Editor: VS Code with Python, Python Debugger and Pylance extensions
# Author: Alan Teixeira

import numpy as np
import matplotlib.pyplot as plt
from functools import cache
import turtle as trt

#--------------------------Weierstrass function--------------------------------

# dpoints is the array of domain points evaluated and npartial
# is the number of partial sum considered
def weierstrass(dpoints,npartial):
    image=np.zeros(dpoints.size)
    for n in range(0,npartial):
        image=image+np.cos(3**n*np.pi*dpoints)/2**n
    return image

def draw_weierstrass():
# x axis main interval, start and end points
    start=-1
    stop=1
# number of subintervals of main interval
    intervals = 10000
# domain points
    xpoints = np.arange(start,stop,((stop-start)/intervals))
# print the function graph
    plt.plot(xpoints,weierstrass(xpoints, 600))
    plt.show()

#draw_weierstrass()

#----------------------------fibonacci word curve-------------------------------

# @cache is for memoization. This function constructs the nth Fibonacci word
@cache
def fibonacci_word(n):
    if n<0:
        return
    if n == 0:
        return "0"
    if n == 1:
        return "01"
    return fibonacci_word(n - 1) + fibonacci_word(n - 2)

# draw the curve using turtle graphics
def draw_fibonacci_curve(word, step):
    for i, c in enumerate(word, 1):
        trt.forward(step)
        if c == "0":
            if i % 2 == 0:
                trt.left(90)
            else:
                trt.right(90)

def launch_turtle_fibonacci():
    n = 21 # the nth fibonacci word.
    step = 1 # Segment length in pixels (1 since it will be hundreds of them).
    width = 1050 # Width of plot area in pixels.
    height = 750 # Height of plot area in pixels.
    w = fibonacci_word(n)

    trt.setup(width=width, height=height,starty=1)
    trt.speed(0) # no lines drawing animation
    trt.setheading(90)
    trt.left(90)
    trt.penup()
    trt.forward(300)
    trt.right(90)
    trt.backward(300)
    trt.pendown()
    trt.tracer(1000) # draw appears on screen only after each 
                     # 1000 screen updates
    trt.hideturtle() # hide the turtle while drawing
    draw_fibonacci_curve(w, step)
    trt.exitonclick()

#launch_turtle_fibonacci()

#---------------------------------binary tree-----------------------------------

# constructs the l-system for the binary tree
def binarytreesystem(steps):
    lsys='0'
    while steps>0:
        sz=len(lsys)
        i=0
        c=1
        while c<=sz:
            if lsys[i]=='1':
                lsys=lsys[:i]+'11'+lsys[i+1:]
                i+=2
                c+=1
            elif lsys[i]=='0':
                lsys=lsys[:i]+'1[0]0'+lsys[i+1:]
                i+=5
                c+=1
            elif lsys[i]=='[' or lsys[i]==']':
                i+=1
                c+=1
        steps-=1
    return lsys

# draw the binary tree. lsys is the l-sytem to be drawn
def drawtree(lsys,branchlen,leaflen):
    stack=[]
    trt.setheading(90)
    for s in lsys:
        if s=='1':
            trt.forward(branchlen)
        elif s=='0':
            trt.forward(leaflen)
        elif s=='[':
            stack.append((trt.pos(),trt.heading()))
            trt.left(45)
        elif s==']':
            trt.penup()
            ps=stack.pop()
            trt.setpos(ps[0])
            trt.setheading(ps[1])
            trt.right(45)
            trt.pendown()

# launch turtle graphics
def launch_turtle_binary():
    blen = 5 # branchs length
    llen = 2 # leafs length
    n = 7 # steps
    width = 1050 # Width of plot area in pixels.
    height = 750 # Height of plot area in pixels.
    sys=binarytreesystem(n) # binary tree l-system

    trt.setup(width=width, height=height)
    trt.speed(0)
    trt.hideturtle()
    trt.setheading(270)
    trt.penup()
    trt.forward(250)
    trt.setheading(90)
    trt.pendown()
    drawtree(sys,5,2)
    trt.exitonclick()

#launch_turtle_binary()

#---------------------------------cantor set------------------------------------

# constructs the cantor set l-system
def cantorsetsystem(steps):
    lsys='A'
    while steps>1:
        sz=len(lsys)
        i=0
        c=1
        while c<=sz:
            if lsys[i]=='A':
                lsys=lsys[:i]+'ABA'+lsys[i+1:]
                i+=3
                c+=1
            elif lsys[i]=='B':
                lsys=lsys[:i]+'BBB'+lsys[i+1:]
                i+=3
                c+=1
        steps-=1
    return lsys

# draw cantor set. origlen is the length of the original segment
def drawcantorset(steps,origlen):
    linesize=origlen
    for i in range(1,steps+1):
        lsys=cantorsetsystem(i)
        for s in lsys:
            if s=='A':
                trt.forward(linesize)
            if s=='B':
                trt.penup()
                trt.forward(linesize)
                trt.pendown()
        trt.penup()
        trt.setheading(180)
        trt.forward(origlen)
        trt.setheading(270)
        trt.forward(10)
        trt.setheading(0)
        trt.pendown()
        linesize/=3
    
def launch_turtle_cantor():
    n = 5 # steps
    linelength=600 # original segment length
    width = 1050 # Width of plot area in pixels.
    height = 750 # Height of plot area in pixels.

    trt.setup(width=width, height=height,starty=1)
    trt.speed(0)
    trt.penup()
    trt.setheading(180)
    trt.forward(linelength/2)
    trt.setheading(0)
    trt.pendown()
    trt.hideturtle()
    drawcantorset(n,linelength)
    trt.exitonclick()

#launch_turtle_cantor()