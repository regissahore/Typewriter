father = [-1 for i in range(500000 * 2 + 10)]
depth = [0 for i in range(500000 * 2 + 10)]
father[1], father[2], father[3], father[4] = -1, 1, 1, 1
depth[1], depth[2], depth[3], depth[4] = 0, 1, 1, 1
e1, e2 = 2, 3
def lca(u, v):
    global depth
    global father
    while u != v:
        if depth[u] > depth[v]:
            u = father[u]
        elif depth[u] < depth[v]:
            v = father[v]
        else:
            u = father[u]
            v = father[v]
    return u
def dist(u, v):
    global depth
    global father
    a = lca(u, v)
    return depth[u] + depth[v] - depth[a] * 2
q = int(input())
n = 5
d = 2
for i in range(q):
    v = int(input())
    father[n] = v
    depth[n] = depth[v] + 1
    d1 = dist(n, e1)
    d2 = dist(n, e2)
    if d1 > d2:
        if d1 > d:
            e2 = n
            d = d1
    else:
        if d2 > d:
            e1 = n
            d = d2
    n += 1
    father[n] = v
    depth[n] = depth[v] + 1
    n += 1
    print(d)
