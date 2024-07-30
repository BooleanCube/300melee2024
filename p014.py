from functools import cache
import sys as sus

sus.setrecursionlimit(int(5e4))

@cache
def dp(n):
	if n == 0: return (0, 0, 0, 0, 0, 0, 0, 0)
	if n == 1: return (2, 2, 1, 0, 0, 0, 0, 0)
	if n == 2: return (11, 16, 8, 4, 2, 1, 1, 1)
	p, pp = dp(n - 1), dp(n - 2)
	tot = (2 * p[0]) + (7 * pp[0]) + (4 * p[4])
	obo = (2 * p[0]) + (2 * p[1]) + (7 * pp[1]) + (8 * pp[0]) + (2 * p[4]) + (4 * p[5])
	tbo = p[0] + (2 * p[2]) + (7 * pp[2]) + (4 * pp[0]) + (2 * p[4]) + (4 * p[6])
	tro = (2 * p[3]) + (7 * pp[3]) + (4 * pp[0]) + (2 * p[4]) + (4 * p[7])
	pg1 = 2 * pp[0] + p[4]
	pg2 = 2 * pp[1] + pp[0] + p[5]
	pg3 = 2 * pp[2] + pp[0] + p[6] + p[4]
	pg4 = 2 * pp[3] + pp[0] + p[7]
	return (tot, obo, tbo, tro, pg1, pg2, pg3, pg4)

for _ in range(int(input())):
	k, n = map(int, input().split())
	print(k, *dp(n)[:4])