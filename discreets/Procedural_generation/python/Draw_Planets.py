import turtle as trt
import math
import Planets #Elite_planets interface module


width = 1050 #width of the screen
height = 750 #height of the screen


def ellipse(cx,cy,a,b,angle):
    '''draws the Ellipse centered at (cx,cy) with width a, height b 
    and tilted by angle. For planet ring'''
    n = 2000
    t = 0
    x = cx + a*math.cos(t)*math.cos(math.radians(angle))-b*math.sin(t)*math.sin(math.radians(angle))
    y = cy + a*math.cos(t)*math.sin(math.radians(angle))+b*math.sin(t)*math.cos(math.radians(angle))
    trt.up()
    trt.goto(x,y)
    trt.down()
    trt.color('black')
    for i in range(n):
        x = cx + a*math.cos(t)*math.cos(math.radians(angle))-b*math.sin(t)*math.sin(math.radians(angle))
        y = cy + a*math.cos(t)*math.sin(math.radians(angle))+b*math.sin(t)*math.cos(math.radians(angle))
        trt.goto(x,y)    
        t += 2*math.pi/n

def draw_planet(planet):
    '''draws planet as well as prints planet's data
    planet is an instance of Planet class from Elite module'''
    radius=(planet.radius()/30)
    colorarr=planet.color()
    has_ring=planet.has_ring()
    info=f'''Name: {planet.name()}\nGovernment: {planet.government()}
Economy: {planet.economy()}\nTechnological level: {planet.technology()}
Population: {planet.population()} billion
Productivity: {planet.productivity()} million credits
Species: {planet.species()}\nRadius: {planet.radius()}Km
Surface color (RGB): {colorarr[0],colorarr[1],colorarr[2]}'''

    trt.setup(width=width, height=height,starty=1)
    trt.hideturtle()
    trt.penup()
    trt.setheading(0)
    trt.forward(radius)
    trt.setheading(90)
    trt.pendown()
    trt.colormode(255)
    trt.color(colorarr[0],colorarr[1],colorarr[2])
    trt.speed(10)
    trt.begin_fill()
    trt.circle(radius)
    trt.end_fill()
    trt.penup()
    trt.home()
    trt.speed(0)
    trt.colormode(1)
    trt.color('black')
    trt.pendown()
    if planet.has_ring():
        ellipse(trt.xcor(),trt.ycor(),radius+100,radius/2,0)
    trt.penup()
    trt.home()
    trt.setheading(0)
    trt.forward(radius)
    trt.setheading(90)
    trt.pendown()
    trt.colormode(255)
    trt.color(colorarr[0],colorarr[1],colorarr[2])
    trt.speed(0)
    if has_ring:
        trt.begin_fill()
        trt.circle(radius,180)
        trt.end_fill()
    trt.penup()
    trt.home()
    trt.colormode(1)
    trt.color('black')
    trt.setheading(180)
    trt.forward(450)
    trt.setheading(90)
    trt.forward(radius)

    trt.pendown()
    trt.speed(6)
    trt.write(info)
    trt.exitonclick()