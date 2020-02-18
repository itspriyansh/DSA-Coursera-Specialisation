#uses python3

import sys
import threading

# This code is used to avoid stack overflow issues
sys.setrecursionlimit(10**6) # max depth of recursion
threading.stack_size(2**26)  # new thread will get stack of such size


class Vertex:
    def __init__(self, weight):
        self.weight = weight
        self.children = []


def ReadTree():
    size = int(input())
    tree = [Vertex(w) for w in map(int, input().split())]
    for i in range(1, size):
        a, b = list(map(int, input().split()))
        tree[a - 1].children.append(b - 1)
        tree[b - 1].children.append(a - 1)
    return tree


def dfs(tree, vertex, parent):
    # for child in tree[vertex].children:
    #     if child != parent:
    #         dfs(tree, child, vertex)

    # This is a template function for processing a tree using depth-first search.
    # Write your code here.
    # You may need to add more parameters to this function for child processing.
    if not tree[vertex].children:
        return tree[vertex].weight
    result = tree[vertex].weight
    alternate = 0
    for child in tree[vertex].children:
        if child == parent:
            continue
        alternate += dfs(tree, child, vertex)
        for grandchild in tree[child].children:
            if grandchild == vertex:
                continue
            result += dfs(tree, grandchild, child)
    return max(result, alternate)


def MaxWeightIndependentTreeSubset(tree):
    size = len(tree)
    if size == 0:
        return 0
    return dfs(tree, 0, -1)
    # You must decide what to return.


def main():
    tree = ReadTree();
    weight = MaxWeightIndependentTreeSubset(tree);
    print(weight)


# This is to avoid stack overflow issues
threading.Thread(target=main).start()
