import sys

n, m = map(int, input().split())
grid = []
result = []
for i in range(m):
	x = list(map(int, input().split()))
	grid.append(x)

for i in range(n - m):
	grid.append([0 for i in range(n)])

possible = {}
for i in range(n): 
	for j in range(n):
		possible[(i, j)] = set([i for i in range(1, n + 1)])


for i in range(m):
	for j in range(n):
		num = grid[i][j]
		for k in range(0, n):
			if k == j:
				continue
			if num == grid[i][k]:
				print("NO")
				sys.exit(0)
			else: 
				if num in possible[(i, k)]:
					possible[(i, k)].remove(num)

		for k in range(0, n):
			if k == i: 
				continue;
			if num == grid[k][j]:
				print("NO")
				sys.exit(0)
			else: 
				if num in possible[(k, j)]:
					possible[(k, j)].remove(num)


lst = []
for i in range(n):
	for j in range(n):
		if len(possible[(i, j)]) == 0 and grid[i][j] == 0:
			print("NO")
			sys.exit(0)
		if len(possible[(i, j)]) == 1 and grid[i][j] == 0:
			lst.append((i, j))


while(1):
	i, j, min_count = -1, -1, float('inf');
	for ii in range(n):
		for jj in range(n):
			if grid[ii][jj] != 0:
				continue 
			if min_count > len(possible[(ii, jj)]):
				min_count = len(possible[(ii, jj)])
				i, j = ii, jj
	if i == -1 and j == -1:
		break
	
	'''print(grid)
	for i in range(n):
		for j in range(n):
			print("({0}, {1})".format(i, j), end = " ")
			print(possible[(i, j)], end = " ")
		print()
	'''
	while (len(lst)):
		#print(lst)
		r, c = lst.pop(0);
		#print("({0}, {1}) = {2}".format(r, c, min(possible[(r, c)])))
		if len(possible[(r, c)]) == 0:
			print("NO")
			sys.exit(0)
		grid[r][c] = min(possible[(r, c)])
		#print(grid)
		num = grid[r][c]
		
		for k in range(0, n):
			if k == r or grid[k][c] != 0:
				continue 
			else: 
				if num in possible[(k, c)]:
					possible[(k , c)].remove(num)
					if (len(possible[(k, c)]) == 1):
						lst.append((k, c))
		for k in range(0, n):
			if k == c or grid[r][k] != 0:
				continue
			else:
				if num in possible[(r, k)]:
					possible[(r, k)].remove(num)
					if (len(possible[(r, k)]) == 1):
						lst.append((r, k))
	lst.append((i, j))

for i in range(n):
	for j in range(n):
		print(grid[i][j], end = " ")
	print()
