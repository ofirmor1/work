# import colorgram
import turtle as t
import random
# rgb_color = []

t.colormode(255)
timmy = t.Turtle()
timmy.penup()
timmy.speed("fastest")
timmy.hideturtle()

# print(timmy.heading())
# colors = colorgram.extract('hirst.jpg', 30)
# for color in colors:
#     r = color.rgb.r
#     g = color.rgb.g
#     b = color.rgb.b
#     new_color = (r, g, b)
#     rgb_color.append(new_color)
# print(rgb_color)

colors = ((44, 103, 169), (233, 206, 117), (227, 152, 86), (185, 48, 76), (116, 92, 47), (230, 119, 146), (213, 61, 79), (109, 109, 188), (121, 174, 211), (55, 177, 110), (117, 186, 140), (204, 17, 43), (118, 172, 38), (33, 57, 113), (219, 56, 50), (182, 171, 223), (25, 143, 108), (31, 161, 178), (156, 222, 192), (84, 36, 41), (40, 45, 81), (233, 166, 179), (84, 38, 36), (236, 173, 161), (148, 208, 220), (116, 38, 36))



timmy.setheading(225)
timmy.fd(300)
timmy.setheading(0)
num_of_dots = 100

for dots_count in range(1, num_of_dots + 1):
    timmy.dot(20, random.choice(colors))
    timmy.fd(50)
    if dots_count % 10 == 0:
        timmy.setheading(90)
        timmy.fd(50)
        timmy.setheading(180)
        timmy.fd(500)
        timmy.setheading(0)






screen = t.Screen()
screen.exitonclick()










