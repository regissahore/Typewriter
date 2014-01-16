[n, m] = map(int, input().split())
num = list(map(int, input().split()))
class TreeNode:
    l = 0
    r = 0
    w = 0
    lazy = 0
    def __init__(self):
        pass
class Tree:
    def __init__(self):
        self.tree = [TreeNode() for i in range(0, 10 ** 6 * 3)]
    def build(self, x, l, r, num):
        self.tree[x].l = l
        self.tree[x].r = r
        self.tree[x].lazy = 0
        if l == r:
            self.tree[x].w = num[l - 1]
            return
        mid = (l + r) // 2
        self.build(x * 2, l, mid, num)
        self.build(x * 2 + 1, mid + 1, r, num)
        self.tree[x].w = min([self.tree[x * 2].w, self.tree[x * 2 + 1].w])
    def relax(self, x):
        if self.tree[x].lazy:
            self.tree[x * 2].lazy += self.tree[x].lazy
            self.tree[x * 2 + 1].lazy += self.tree[x].lazy
            self.tree[x * 2].w -= self.tree[x].lazy
            self.tree[x * 2 + 1].w -= self.tree[x].lazy
            self.tree[x].lazy = 0
    def update(self, x, l, r, val):
        if self.tree[x].l == l and self.tree[x].r == r:
            self.tree[x].lazy += val
            self.tree[x].w -= val
            return
        self.relax(x)
        mid = (self.tree[x].l + self.tree[x].r) // 2
        if r <= mid:
            self.update(x * 2, l, r, val)
        elif l > mid:
            self.update(x * 2 + 1, l, r, val)
        else:
            self.update(x * 2, l, mid, val)
            self.update(x * 2 + 1, mid + 1, r, val)
        self.tree[x].w = min([self.tree[x * 2].w, self.tree[x * 2 + 1].w])
    def query(self, x, l, r):
        if self.tree[x].l == l and self.tree[x].r == r:
            return self.tree[x].w
        self.relax(x)
        mid = (self.tree[x].l + self.tree[x].r) // 2
        if r <= mid:
            return self.query(x * 2, l, r)
        if l > mid:
            return self.query(x * 2 + 1, l, r)
        return min([self.query(x * 2, l, mid), self.query(x * 2 + 1, mid + 1, r)])
tree = Tree()
tree.build(1, 1, n, num)
flag = True
for i in range(0, m):
    [d, s, t] = map(int, input().split())
    if tree.query(1, s, t) >= d:
        tree.update(1, s, t, d)
    else:
        print(-1)
        print(i + 1)
        flag = False
        break
if flag:
    print(0)
