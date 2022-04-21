class Node:
    def __init__(self, data, _left=None, _right=None):
        self.__right = _right
        self.__left = _left
        self.__data = data
        self.__height = 1

    @property
    def data(self):
        return self.__data

    @data.setter
    def data(self, _data):
        self.__data = _data

    @property
    def left(self):
        return self.__left

    @left.setter
    def left(self, _left):
        self.__left = _left

    @property
    def right(self):
        return self.__right

    @right.setter
    def right(self, _right):
        self.__right = _right

    @property
    def height(self):
        return self.__height

    @height.setter
    def height(self, _height):
        self.__height = _height

    def __str__(self):
        return f"{self.__data}"


class Tree:
    def __init__(self, root: Node = None):
        self.__root = root

    @property
    def root(self):
        return self.__root

    @root.setter
    def root(self, root):
        self.__root = root

    def insert(self, current: Node, data) -> Node:
        if current is None:
            return Node(data=data)
        elif current.data > data:
            current.left = self.insert(current.left, data)
        elif current.data < data:
            current.right = self.insert(current.right, data)
        return current

    def in_order(self, current: Node):
        if current is not None:
            self.in_order(current.left)
            print(current.data, end='\t')
            self.in_order(current.right)

    def pre_order(self, current: Node):
        if current is not None:
            print(current.data, end='\t')
            self.pre_order(current.left)
            self.pre_order(current.right)

    def post_order(self, current: Node):
        if current is not None:
            self.post_order(current.left)
            self.post_order(current.right)
            print(current.data, end='\t')

    def maximum(self, current) -> Node:
        while current.right is not None:
            current = current.right
        return current

    def is_exist(self, key: int) -> bool:
        if self.root is None:
            return False
        current = self.root
        while current is not None and current.data != key:
            if current.data > key:
                current = current.left
            else:
                current = current.right

        return False if current is None else True

    def minimum(self, current) -> Node:
        while current.left is not None:
            current = current.left
        return current

    def delete(self, current: Node, key: int):
        if current is None:
            return None
        else:
            if current.data == key:
                if current.left is None and current.right is None:
                    del current
                    return None
                elif current.left is None:
                    temp = current.right
                    del current
                    return temp
                elif current.right is None:
                    temp = current.left
                    del current
                    return temp
                else:
                    replaced = self.maximum(current.left)
                    current.data = replaced.data
                    current.left = self.delete(current.left, replaced.data)

            elif current.data > key:
                current.left = self.delete(current.left, key)
            else:
                current.right = self.delete(current.right, key)
        return current


class AVL(Tree):
    def __str__(self):
        super().__init__()

    def insert(self, current: Node,  data):
        node = super().insert(current, data)
        node.height = self.__max(self.__cal_height(node.left), self.__cal_height(node.right)) + 1

        return self.perform_balance(node, data)

    def __cal_height(self, node: Node) -> int:
        if node is None:
            return 0
        return node.height

    def __max(self, a: int, b: int) -> int:
        return a if a > b else b

    def __get_balance(self, node: Node) -> int:

        if node is None:
            return 0
        return self.__cal_height(node.left) - self.__cal_height(node.right)

    def __right_rotate(self, node: Node) -> Node:
        left = node.left
        left_right = left.rigt
        left.right = node
        node.left = left_right
        node.height = self.__max(self.__cal_height(node.right), self.__cal_height(node.left)) + 1
        left.height = self.__max(self.__cal_height(left.right), self.__cal_height(left.left)) + 1
        return left

    def __left_rotate(self, node: Node) -> Node:
        right = node.right
        right_left = right.left
        right.left = node
        node.right = right_left
        node.height = self.__max(self.__cal_height(node.right), self.__cal_height(node.left)) + 1
        right.height = self.__max(self.__cal_height(right.right), self.__cal_height(right.left)) + 1
        return right

    def perform_balance(self,node: Node,  key: int ) -> Node:
        balance = self.__get_balance(node)

        if balance > 1 and node.data > key:  # left left case
            return self.__right_rotate(node)

        if balance < -1 and node.data < key:  # right right case
            return self.__left_rotate(node)

        if balance > 1 and node.data < key:  # left right case
            node.left = self.__left_rotate(node.left)
            return self.__right_rotate(node)
        if balance < -1 and node.data > key:  # rotate right left
            node.right = self.__right_rotate(node.right)
            return self.__left_rotate(node)

        return node

    def delete(self, current: Node, key: int) -> Node:
        node = super().delete(current=current, key=key)
        return self.perform_balance(node=node, key=key)


if __name__ == '__main__':
    avl = AVL()
    for i in range(1, 15):
        avl.root = avl.insert(avl.root, i)

    print()
    avl.in_order(avl.root)
    print()
    avl.pre_order(avl.root)
    print()
    avl.post_order(avl.root)
    print('\n',"*"*20, "deleting 8", "*"*20)
    avl.root = avl.delete(avl.root, 8)
    avl.in_order(avl.root)
    print()
    avl.pre_order(avl.root)
    print()
    avl.post_order(avl.root)
