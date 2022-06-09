from turtle import Screen
from paddle import Paddle
from ball import Ball
from scoreboard import ScoreBoard
import time

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

window = Screen()
window.bgcolor("black")
window.setup(width=800, height=600)
window.title("Pong Game")
window.tracer(0)

r_paddle = Paddle(350, 0)
l_paddle = Paddle(-350, 0)
ball = Ball()
scoreboard = ScoreBoard()

window.listen()
window.onkey(r_paddle.go_up, "Up")
window.onkey(r_paddle.go_down, "Down")
window.onkey(l_paddle.go_up, "w")
window.onkey(l_paddle.go_down, "s")

game_on = True
while game_on:
    time.sleep(ball.move_speed)
    window.update()
    ball.move()

    # Detect collision with wall
    if ball.ycor() > 280 or ball.ycor() < -280:
        ball.bounce_y()

    # Detect collision with right paddle
    if ball.distance(r_paddle) < 50 and ball.xcor() > 320:
        ball.bounce_x()

    # Detect collision with left paddle
    if ball.distance(l_paddle) < 50 and ball.xcor() < -320:
        ball.bounce_x()

    # Detect right paddle misses
    if ball.xcor() > 380:
        ball.reset_position()
        scoreboard.l_point()

    # Detect left paddle misses
    if ball.xcor() < -380:
        ball.reset_position()
        scoreboard.r_point()





window.exitonclick()

