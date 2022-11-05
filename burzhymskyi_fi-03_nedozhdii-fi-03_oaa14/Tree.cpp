#include "Tree.h"

Tree::Node::Node() : letter(nullptr) , endWord(false)
{

}

Tree::Node::Node(const char& letter) : endWord(false)
{
    this->letter = new char(letter);
    for(int i = 0; i < 94;++i)
    {
        childrens[i] = new Node;
    }
}

Tree::Node::~Node()
{
    delete letter;//todo delete only that exist, just see that element dont equal null
    for(int i = 0; i < 94; ++i)
    {
        delete childrens[i];
    }
}

Tree::~Tree()
{
    delete root;
}

Tree::Tree()
{
    root = new Node;
}

Tree::Tree(const std::string word)
{
    root = new Node;

    insert(word);
}

void Tree::insert(std::string letter)
{
    Node *cur = root;

    for(int i = 0; i < letter.size(); ++i)
    {
        if(letter[i] == ' ' || letter[i] > '~')
            throw "ERROR INCORECT INPUT";
        int indexNextNode = letter[i] - 33;// letter[i] - '!' = index in exist

        if(cur->childrens[indexNextNode] == nullptr)
        {
            cur->childrens[indexNextNode] = new Node;
            ++cur->countChildrens;
            cur->childrens[indexNextNode]->letter = new char(letter[i]);
        }
        if(i == letter.size() - 1)
        {
            cur->childrens[indexNextNode]->endWord = true;
            return;
        }
        cur = cur->childrens[indexNextNode];  //go to next node

    }

}

bool Tree::contains(std::string word)
{
    Node* cur = root;
    for(int i = 0; i < word.size(); ++i)
    {
        int indexNextNode = word[i] - 33;// letter[i] - '!' = index in exist
        if(cur->childrens[indexNextNode] == nullptr)
        {
            return false;
        }
        cur = cur->childrens[indexNextNode];
    }
    return true;
}

void Tree::search()
{
    std::string build = "";
    searchTree(root, build);
}

void Tree::searchTree(Node* cur ,std::string& stringBuilder)
{

    std::string tmp = stringBuilder;

    if(cur->endWord)
        std::cout<<stringBuilder<<' ';
    if(cur->countChildrens > 0)
    {
        for(int i = 0; i < 94; ++i)
        {
            if(cur->childrens[i] != nullptr)
            {
                stringBuilder += cur->childrens[i]->letter;

                searchTree(cur->childrens[i],stringBuilder);

                if(cur == root)
                {
                    stringBuilder = "";
                }else if(cur->childrens[i])
                {
                    stringBuilder.pop_back();
                }
            }
        }
    }
    if(cur == root)
    {
        std::cout<<'\n';
    }

}

void Tree::Node::print(std::string prefix, std::string childrenPrefix)
{
    int tmpCountChildren = countChildrens;
    std::cout<<prefix;
    if(letter!= nullptr)
        std::cout<<letter<<'\n';
    for(int i = 0; i < 94; ++i)
    {
        if(childrens[i]!=nullptr && tmpCountChildren > 1 )
        {
            tmpCountChildren--;
            this->childrens[i]->print(childrenPrefix + "├── ", childrenPrefix + "│   ");
        }
        else if(this->childrens[i] != nullptr)
        {
            this->childrens[i]->print(childrenPrefix + "└── ", childrenPrefix + "    ");
        }
    }
}

void Tree::printTree()
{
    //root->letter = new char(' ');
    std::cout<<"[root]\n";
    root->print("","");
}
