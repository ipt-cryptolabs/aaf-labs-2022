class Node:

    def __init__(self, word, doc, index):
        self.left = None
        self.right = None
        self.word = word.lower()
        self.indexes = {doc: [index]}

    def search1(self, word):
        if self.word == word: # ключове слово
            return self.indexes
        elif self.word > word:
            return self.left.search1(word) if self.left else None
        elif self.word < word:
            return self.right.search1(word) if self.right else None   

    def search2(self, word):
        if self.word[:len(word)] == word: # префікс
            result = [self]
            if self.left: result += self.left.search2(word)
            if self.right: result += self.right.search2(word)
            return result
        elif self.word > word:
            return self.left.search2(word) if self.left else []
        elif self.word < word:
            return self.right.search2(word) if self.right else []
        else: None

    def insert(self, word, doc, index):
        if self.word == word:
            if doc in self.indexes.keys():
                self.indexes[doc].append(index)
            else:
                self.indexes[doc] = [index]

        elif word < self.word:
            if self.left is None:
                self.left = Node(word, doc, index)
            else:
                self.left.insert(word, doc, index)
        elif word > self.word:
            if self.right is None:
                self.right = Node(word, doc, index)
            else:
                self.right.insert(word, doc, index)


    def __str__(self):
        return f"{self.word}: {self.indexes}" 


    def treeout(self):
        if self.left:
            self.left.treeout()
        print(f"{self.word}:")
        for doc in self.indexes.keys():
            print(f"  {doc} -> {self.indexes[doc]}")
        if self.right:
            self.right.treeout()
