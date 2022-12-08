#include "Tree.h"

Tree::Node::Node() : letter(nullptr) , endWord(false)
{
    for(int i = 0; i < 95; ++i)
    {
        childrens[i] = nullptr;
    }
}

Tree::Node::Node(const char& letter) : endWord(false)
{
    this->letter = new char(letter);
    for(int i = 0; i < 95; ++i)
    {
        childrens[i] = nullptr;
    }
}

Tree::Node::~Node()
{
    if(letter != nullptr)
        delete letter;
    for(int i = 0; i < 95; ++i)
    {
        if(childrens[i] != nullptr)
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
    for(int i = 0; i < 95; ++i)
        root->childrens[i] = nullptr;
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
        if(letter[i] < ' ' || letter[i] > '~')
            throw "ERROR INCORECT INPUT";
        int indexNextNode = letter[i] - 32;// letter[i] - '!' = index in exist

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
        int indexNextNode = word[i] - 32;
        if(cur->childrens[indexNextNode] == nullptr)
        {
            return false;
        }
        cur = cur->childrens[indexNextNode];
    }
    if(!cur->endWord)
        return false;
    return true;
}

void Tree::search( std::string match, std::string from, std::string to,int ad)
{
    std::string build = "";
    std::vector<std::string> result;
    if(match == "" && from == "" && to == "")
        searchTree(root, build,result);
    else if(match != "")
            searchMatch(match,0,root,build,result);
    else
        searchBetween(root,build,result,from,to);


    if(ad) // ad = 1 -> DESK
        for(int i = result.size() - 1; i >= 0; --i)
            std::cout<<result[i]<<", ";
    else
        for(int i = 0; i < result.size(); ++i)
            std::cout<<result[i]<<", ";
    std::cout<<'\n';
}

void Tree::searchMatch(std::string match, int k, Node* cur, std::string build, std::vector<std::string> &result)
{
    if(k == match.size())
    {
        if(cur->endWord)
        {
            result.push_back(build);
        }

        return;
    }
    if(match[k] == '*')
    {
        searchTree(cur,build,result);
        return;
    }else if(match[k] == '?')
    {
        for(int i = 0; i < 95; ++i)
        {
            if (cur->childrens[i] != nullptr)
            {
                searchMatch(match,k+1, cur->childrens[i], build+cur->childrens[i]->letter, result);
            }
        }
    }else
    {
        if(cur->childrens[match[k]-32] == nullptr)
        {
            return;
        }

        searchMatch(match,k+1, cur->childrens[match[k]-32], build+cur->childrens[match[k]-32]->letter, result);
    }


}


void Tree::searchBetween(Node* cur, std::string& stringBuilder,std::vector<std::string> &result,const std::string& from, const std::string& to)
{
    if(cur->endWord  && from <= stringBuilder  && stringBuilder <= to)
        result.push_back(stringBuilder);

    if(cur->countChildrens > 0)
    {
        for(int i = 0; i < 95; ++i)
        {
            if(cur->childrens[i] != nullptr)
            {
                stringBuilder += cur->childrens[i]->letter;

                searchBetween(cur->childrens[i], stringBuilder, result,from,to);

                if(cur == root)
                {
                    stringBuilder = "";
                }
                else if(cur->childrens[i])
                {
                    stringBuilder.pop_back();
                }
            }
        }
    }

}


void Tree::searchTree(Node* cur ,std::string& stringBuilder, std::vector<std::string> &result)
{
    std::string tmp = stringBuilder;

    if(cur->endWord)
        result.push_back(stringBuilder);
    if(cur->countChildrens > 0)
    {
        for(int i = 0; i < 95; ++i)
        {
            if(cur->childrens[i] != nullptr)
            {
                stringBuilder += cur->childrens[i]->letter;

                searchTree(cur->childrens[i], stringBuilder, result);

                if(cur == root)
                {
                    stringBuilder = "";
                }
                else if(cur->childrens[i])
                {
                    stringBuilder.pop_back();
                }
            }
        }
    }


}

void Tree::Node::print(std::string prefix, std::string childrenPrefix)
{
    int tmpCountChildren = countChildrens;
    std::cout<<prefix;
    if(letter!= nullptr)
        std::cout<<letter<<'\n';
    for(int i = 0; i < 95; ++i)
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
    std::cout<<"[root]\n";
    root->print("","");
}
