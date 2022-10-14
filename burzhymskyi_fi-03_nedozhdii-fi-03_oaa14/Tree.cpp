#include "Tree.h"

Tree::Node::Node() : letter(nullptr) , endBranch(true), endWord(false)
{
    for(int i = 0; i < 94;++i)
    {
        exist[i] = false;
    }
}

Tree::Node::Node(const char& letter, const bool& endBranch) : endBranch(endBranch), endWord(false)
{
    this->letter = new char(letter);
    for(int i = 0; i < 94;++i)
    {
        exist[i] = false;
        childrens[i] = new Node;
    }
}

Tree::Node::~Node()
{
    delete letter;
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
    root->endBranch = true;
}

Tree::Tree(const std::string word)
{
    root = new Node;
    root->endBranch = true;

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

        if(!cur->exist[indexNextNode])
        {
            cur->exist[indexNextNode] = true;
            cur->childrens[indexNextNode] = new Node;
            ++cur->countChildrens;
            cur->childrens[indexNextNode]->letter = new char(letter[i]);
            if(cur->endBranch)
            {
                cur->endBranch = false;
                cur->childrens[indexNextNode]->endBranch = true;
            }
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
        if(!cur->exist[indexNextNode])
        {
            return false;
        }
        cur = cur->childrens[indexNextNode];
    }
    return true;
}

std::string Tree::search(Node* cur = nullptr, int k = 0,std::string* stringBuilder = nullptr,std::string tmp = "")
{
    if(k == 0)
    {
        stringBuilder = new std::string("");
        cur = root;
    }

    for(int i = 0; i < 94; ++i)
    {
        if(k == 0)
            tmp = "";

        if(cur->exist[i])
        {

            if(cur->childrens[i]->endWord)
            {
                if(tmp.size() > k)
                    tmp.pop_back(); // work by O(1)
                *stringBuilder += tmp + cur->childrens[i]->letter+' ';
            }
            tmp+=cur->childrens[i]->letter;

            if(!cur->childrens[i]->endBranch)
                search(cur->childrens[i],k+1,stringBuilder,tmp);

            //std::cout<<*stringBuilder<<'\n';
        }

    }

    return *stringBuilder;
}

void Tree::Node::print(std::string prefix, std::string childrenPrefix)
{
    int tmpCountChildren = countChildrens;
    std::cout<<prefix;
    if(letter!= nullptr)
        std::cout<<letter<<'\n';
    for(int i = 0; i < 94; ++i)
    {
        if(exist[i] && tmpCountChildren > 1 )
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
    root->letter = new char(' ');
    std::cout<<"[root]";
    root->print("","");
}
