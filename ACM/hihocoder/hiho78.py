class Node(object):
    def __init__(self, c=None):
        self.c = c
        self.childs = [None for i in range(26)]
        self.count = 0
    
    def add(self):
        self.count = self.count + 1

class Trie(object):
    def __init__(self):
        self.root = Node()
        
    def add(self, word):
        node = self.root
        for c in word:
            pos = ord(c) - ord('a')
            if not node.childs[pos]:
                node.childs[pos] = Node(c)
            node = node.childs[pos]
            node.add();
            
    def count(self, node):
        print node.c, 'count is', node.count
        if node.count <= 5:
            print ' are found!'
            return 1
        result = 0
        for child in node.childs:
            if child:
                result = result + self.count(child)
        return result
    
    def countNum(self):
        result = 0
        for node in self.root.childs:
            if node:
                result = result + self.count(node)
        return result
        
    def setWords(self, words):
        for word in words:
            self.add(word)

if __name__ == '__main__':
    length = int(raw_input())
    if length > 0:
        words = [None for i in range(length)]
        for i in range(length):
            words[i] = raw_input()
        trie = Trie()
        trie.setWords(words)
        print trie.countNum()
    