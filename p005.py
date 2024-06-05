from fractions import Fraction
from math import dist, floor

a, b, n = map(int, input().split())
m = d = a/b
x, y, xn, yn = 1, 1, 0, 0
sp = (-1, 0)
while xn+yn < n:
    p1, p2 = (x, m*x+d), ((y-d)/m, y)
    if dist(sp, p1) < dist(sp, p2): x += 2; xn += 1
    else: y += 2; yn += 1

p1, p2 = (x, m*x+d), ((y-d)/m, y)
if dist(sp, p1) < dist(sp, p2):
    yc = Fraction(round(a*x+d*b), b)
    mo2 = floor(yc)
    if mo2 & 1: mo2 += 1
    yc -= mo2
    if yn & 1: yc *= -1
    if xn & 1:
        xa, xb = -1, 1
        ya, yb = yc.as_integer_ratio()
        print(xa, xb, ya, yb)
    else:
        xa, xb = 1, 1
        ya, yb = yc.as_integer_ratio()
        print(xa, xb, ya, yb)
else:
    xc = Fraction(round((y-d)*b), a)
    mo2 = floor(xc)
    if mo2 & 1: mo2 += 1
    xc -= mo2
    if xn & 1: xc *= -1
    if yn & 1:
        ya, yb = -1, 1
        xa, xb = xc.as_integer_ratio()
        print(xa, xb, ya, yb)
    else:
        ya, yb = 1, 1
        xa, xb = xc.as_integer_ratio()
        print(xa, xb, ya, yb)
