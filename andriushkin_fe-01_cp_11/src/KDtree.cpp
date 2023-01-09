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
        Node* ptr = right != nullptr ? right : left;
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

std::vector<KDtree::Node*> KDtree::RangeSearch(int64_t x1, int64_t y1, int64_t x2, int64_t y2)
{    
    std::array<int64_t, 2> left({x1, y1}), right({x2,y2});
    std::array<int64_t, 2> left_box({INT64_MIN, INT64_MIN}), right_box({INT64_MAX, INT64_MAX}), temp;
    std::stack<bounding_box> stk;
    std::vector<Node*> ret{};
    Node* curr;

    stk.push({first_node, left_box, right_box});

    while (stk.size())
    {
        curr = stk.top().node;
        left_box = stk.top().left_box;
        right_box = stk.top().right_box;
        bool inter = Intersection(left, right, left_box, right_box);
        stk.pop();
        if( curr == nullptr)
            continue;
        if( !Intersection(left, right, left_box, right_box))
            continue;
        if( InRectange(left, right, curr->coords))
            ret.push_back(curr);
        temp = right_box;
        temp[curr->rotation] = curr->coords[curr->rotation];
        stk.push({curr->left, left_box, temp});
        temp = left_box;
        temp[curr->rotation] = curr->coords[curr->rotation];
        stk.push({curr->right, temp, right_box});
    }
    return ret;
     
}

bool Intersection(std::array<int64_t,2> l1, std::array<int64_t,2> l2,
    std::array<int64_t,2> r1, std::array<int64_t,2> r2)
{
    bool lx = l1[0] >= r1[0];
    bool ly = l1[1] >= r1[1];
    bool rx = l2[0] <= r2[0];
    bool ry = l2[1] <= r2[1];
    bool l = lx && ly;
    bool r = rx && ly;
    bool ans = r || l;
    return (l1[0] >= r1[0] || l1[1] >= r1[1]) || (l2[0] <= r2[0] || l2[1] <= r2[1]);
}

bool InRectange(std::array<int64_t,2> left, std::array<int64_t,2> right, std::array<int64_t,2> point)
{
    return (point[0] >= left[0] & point[1] >= left[1] & point[0] <= right[0] & point[1] <= right[1]);
}

std::vector<KDtree::Node*> KDtree::NNSearch(int64_t x, int64_t y)
{
    Node *curr;
    double curr_best_dist = __DBL_MAX__, tmp_dist;
    std::vector<Node*> ret{};
    std::array<int64_t, 2> search_coords({x, y});
    std::array<int64_t, 2> left_box({INT64_MIN, INT64_MIN}), right_box({INT64_MAX, INT64_MAX}), temp;
    std::stack<bounding_box> search_stk;
    bounding_box tmp1, tmp2;
    
    search_stk.push({first_node, left_box, right_box});

    while ( search_stk.size())
    {
        curr = search_stk.top().node;
        left_box = search_stk.top().left_box;
        right_box = search_stk.top().right_box;
        search_stk.pop();

        if( curr == nullptr)
            continue;
        tmp_dist = Distance(curr->coords, search_coords);
        if ( tmp_dist < curr_best_dist)
        {
            curr_best_dist = tmp_dist;
            ret = {curr};
        }
        else if (tmp_dist == curr_best_dist)
            ret.push_back(curr);
        
        tmp_dist = DistanceToBox({curr, left_box, right_box}, search_coords);
        if (tmp_dist <= curr_best_dist)
        {
            temp = right_box;
            temp[curr->rotation] = curr->coords[curr->rotation];
            search_stk.push({curr->left, left_box, temp});
            temp = left_box;
            temp[curr->rotation] = curr->coords[curr->rotation];
            search_stk.push({curr->right, temp, right_box});
            if (search_coords[curr->rotation] >= curr->coords[curr->rotation])
            {
                tmp1 = search_stk.top();
                search_stk.pop();
                tmp2 = search_stk.top();
                search_stk.pop();
                search_stk.push(tmp1);
                search_stk.push(tmp2);
            }
        }
         
    }
    return ret;
}

std::vector<KDtree::Node*> KDtree::AboveSearch(int64_t y)
{
    Node *curr;
    std::vector<Node*> ret{};
    std::stack<Node*> search_stk;

    search_stk.push(first_node);

    while(search_stk.size())
    {
        curr = search_stk.top();
        search_stk.pop();
        
        if( curr == nullptr)
            continue;
        
        if( curr->coords[1] > y)
            ret.push_back(curr);
        
        if( curr->rotation)
        {
            search_stk.push(curr->right);
            if(curr->coords[1] >= y)
                search_stk.push(curr->left);
        }
            
        else
        {
            search_stk.push(curr->left);
            search_stk.push(curr->right);
        }
        
    }

    return ret;
}

double Distance(std::array<int64_t,2> l, std::array<int64_t,2> r)
{
    return sqrt((r[0]-l[0])*(r[0]-l[0]) + (r[1]-l[1])*(r[1]-l[1]));
}

double DistanceToBox(bounding_box box, std::array<int64_t,2> point)
{

    std::array<int64_t,2> cool_point;
    if ( point[0] < box.left_box[0])
        cool_point[0] = box.left_box[0];
    else if (point[0] > box.right_box[0])
        cool_point[0] = box.right_box[0];
    else
        cool_point[0] = point[0];

    if ( point[1] < box.left_box[1])
        cool_point[1] = box.left_box[1];
    else if (point[1] > box.right_box[1])
        cool_point[1] = box.right_box[1];
    else
        cool_point[1] = point[1];

    return Distance(cool_point, point);
}
