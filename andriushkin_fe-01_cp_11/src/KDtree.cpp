#include "KDtree.hpp"

std::ostream& operator<<(std::ostream& os, std::vector<std::string> vec)
{
    for( std::string s: vec)
        os << s;
    return os;
}

std::ostream& operator<<(std::ostream& os, KDtree::Node node)
{
    os << '(' << node.coords[0] << ',' << node.coords[1] << ')'; 
    return os;
}

KDtree::Node::Node(int64_t x, int64_t y, bool rot)
    : coords({x, y}), rotation(rot)
{}

void KDtree::Node::Print(std::vector<std::string>& prexif)
{
    if( right != nullptr & left != nullptr)
    {
        std::cout << prexif << "├── " << *right << std::endl;
        prexif.push_back("│   ");
        right->Print(prexif);
        prexif.pop_back();
        std::cout << prexif << "└── " << *left << std::endl;
        prexif.push_back("    ");
        left->Print(prexif);
        prexif.pop_back();
    }
    else if( right != nullptr | left != nullptr)
    {
        Node* ptr = right != nullptr ? left : right;
        std::cout << prexif << "└── " << *ptr << std::endl;
        prexif.push_back("    ");
        ptr->Print(prexif);
        prexif.pop_back();
    }
}

bool KDtree::Insert(const int64_t &x_, const int64_t &y_)
{
    std::array<int64_t, 2> ins_coords({x_, y_});
    Node *prev_ptr = nullptr, *node_ptr = first_node;
    bool lr;
    while(node_ptr != nullptr)
    {
        if(ins_coords == node_ptr->coords)
            return false;
        prev_ptr = node_ptr;
        if( node_ptr->coords[node_ptr->rotation] > ins_coords[node_ptr->rotation])            
        {
            lr = false;
            node_ptr = node_ptr->left;
        }
        else
        {
            lr = true;
            node_ptr = node_ptr->right;
        }
    }

    if(prev_ptr != nullptr)
    {
        if(lr)
            prev_ptr->right = new Node(x_, y_, !prev_ptr->rotation);
        else
            prev_ptr->left = new Node(x_, y_, !prev_ptr->rotation);
    }
    else
        first_node = new Node(x_, y_, false);
    return true;
}

void KDtree::PrintTree()
{
    std::vector<std::string> prefix;
    
    if(first_node == nullptr)
        std::cout << "Set is empty" << std::endl;
    else
    {
        std::cout << *first_node << std::endl;
        first_node->Print(prefix);
    }
}

bool KDtree::Contains(const int64_t &x_, const int64_t &y_)
{
    std::array<int64_t, 2> ins_coords({x_, y_});
    Node *node_ptr = first_node;

    while(node_ptr != nullptr)
    {
        if(ins_coords == node_ptr->coords)
            return true;
        if( node_ptr->coords[node_ptr->rotation] > ins_coords[node_ptr->rotation])            
            node_ptr = node_ptr->left;
        else
            node_ptr = node_ptr->right;
    }
    return false;
}

std::vector<KDtree::Node*> KDtree::GetAll()
{
    std::vector<Node*> ret;
    std::stack<Node*> stack;
    Node* curr;
    if(first_node != nullptr)
        stack.push(first_node);
    while( !stack.empty())
    {
        curr = stack.top();
        stack.pop();
        if(curr == nullptr)
            continue;
        ret.push_back(curr);
        stack.push(curr->right);
        stack.push(curr->left);
    }
    return ret;
}
