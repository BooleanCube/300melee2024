import math

EPS = 1e-9

class point:
    def __init__(self, x, y):
        self.x, self.y = x, y

    def dist(self, other):
        return math.hypot(self.x - other.x, self.y - other.y)

class segment:
    def __init__(self, a, b):
        self.start, self.end, self.mag = a, b, a.dist(b)
        self.dir = point((b.x - a.x) / self.mag, (b.y - a.y) / self.mag)

    def eval(self, t):
        return point(self.start.x + t * self.dir.x, self.start.y + t * self.dir.y)

    def closest(self, other):
        res = self.start.dist(other.start)
        res = min(res, self.end.dist(other.end))
        dx = self.dir.x - other.dir.x
        dy = self.dir.y - other.dir.y

        if abs(dx) < EPS and abs(dy) < EPS: return res

        t = (other.dir.x - self.dir.x) * (self.start.x - other.start.x) + (other.dir.y - self.dir.y) * (self.start.y - other.start.y)
        t /= (dx**2 + dy**2)
        if 0 < t < self.mag:
            cm = self.eval(t)
            co = other.eval(t)
            res = min(res, cm.dist(co))

        return res

n = int(input().strip())
d1 = [point(*map(int, input().strip().split())) for _ in range(n)]
s1 = [segment(d1[i], d1[i+1]) for i in range(n-1)]
m = int(input().strip())
d2 = [point(*map(int, input().strip().split())) for _ in range(m)]
s2 = [segment(d2[i], d2[i+1]) for i in range(m-1)]

i, j = 0, 0
ans = d1[0].dist(d2[0])
while i<n-1 and j<m-1:
	cur = 0
	if s1[i].mag < s2[j].mag - EPS:
		eb = s2[j].eval(s1[i].mag)
		b = segment(s2[j].start, eb)
		cur = s1[i].closest(b)
		s2[j] = segment(eb, d2[j+1])
		i += 1
	elif s2[j].mag < s1[i].mag - EPS:
		ea = s1[i].eval(s2[j].mag)
		a = segment(s1[i].start, ea)
		cur = s2[j].closest(a)
		s1[i] = segment(ea, d1[i+1])
		j += 1
	else:
		cur = s1[i].closest(s2[j])
		i += 1; j += 1
	ans = min(ans, cur)

print(ans)