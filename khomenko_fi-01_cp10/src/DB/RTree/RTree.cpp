#include "RTree.h"


void RTree::Print() {
    if(root_){
        SubPrint(root_, "", true);
    }
}


void RTree::SubPrint(Node* node, const std::string& shift, bool last) {
    // node is INode or Leaf

    bool root = (node == root_);

    std::cout << shift;
    if(!shift.empty() || !root){
        if(last){
            std::cout << "└── ";
        }
        else{
            std::cout << "├── ";
        }
    }

    std::cout << node->rect_.ToString() << std::endl;

    INode* inner_node = dynamic_cast<INode*>(node);
    if(inner_node){
        auto inner_node_iter = inner_node->nodes_.begin();

        for(; inner_node_iter != inner_node->nodes_.end(); inner_node_iter++){
            if (inner_node_iter == inner_node->nodes_.end() - 1){
                // last branch here. we shouldn't print |

                if(root){
                    SubPrint(*inner_node_iter, shift, true);
                }
                else{
                    SubPrint(*inner_node_iter, shift + (last ? "    " : "│   "), true);
                }
            }
            else{
                if(root){
                    SubPrint(*inner_node_iter, shift, false);
                }
                else{
                    SubPrint(*inner_node_iter, shift + (last ? "    " : "│   "), false);
                }
            }
        }
    }
    else{
        Leaf* leaf_node = dynamic_cast<Leaf*>(node);

        auto leaf_node_iter = leaf_node->points_.begin();
        for(; leaf_node_iter != leaf_node->points_.end(); leaf_node_iter++){
            if (leaf_node_iter == leaf_node->points_.end() - 1){
                SubPrint(*leaf_node_iter, shift + (last ? "    " : "│   "), true);
            }
            else{
                SubPrint(*leaf_node_iter, shift + (last ? "    " : "│   "), false);
            }
        }
    }
}

void RTree::SubPrint(Point *point, const std::string &shift, bool last) {
    std::cout << shift;
    if(!shift.empty()){
        if(last){
            std::cout << "└── ";
        }
        else{
            std::cout << "├── ";
        }
    }

    std::cout << point->ToString() << std::endl;
}

bool RTree::Contains(Point *point) {
    if(root_){
        return SubContains(point, root_);
    }
    return false;
}

bool RTree::SubContains(Point *point, RTree::Node *node) {
    Rectangle rect = node->rect_;
    bool res = false;

    INode* inner_node = dynamic_cast<INode*>(node);
    if(inner_node) {
        auto inner_node_iter = inner_node->nodes_.begin();

        for (; inner_node_iter != inner_node->nodes_.end(); inner_node_iter++) {
            if(rect.Contains(point)){
                res = res || SubContains(point, *inner_node_iter);
            }
        }
    }
    else{
        Leaf* leaf_node = dynamic_cast<Leaf*>(node);
        auto leaf_node_iter = leaf_node->points_.begin();

        for (; leaf_node_iter != leaf_node->points_.end(); leaf_node_iter++) {
            res = res || (((*leaf_node_iter)->x == point->x) && ((*leaf_node_iter)->y == point->y));
        }
    }

    return res;
}


std::vector<Point *> RTree::Search() {
    std::vector<Point*> res;

    if(root_){
        SubSearch(root_, res);
    }
    return res;
}

void RTree::SubSearch(RTree::Node *node, std::vector<Point *>& collected_points) {
    Leaf* leaf_node = dynamic_cast<Leaf*>(node);

    if(leaf_node){
        auto leaf_node_iter = leaf_node->points_.begin();
        for (; leaf_node_iter != leaf_node->points_.end(); leaf_node_iter++) {
            collected_points.push_back(*leaf_node_iter);
        }
    }
    else{
        INode* inner_node = dynamic_cast<INode*>(node);
        auto inner_node_iter = inner_node->nodes_.begin();

        for (; inner_node_iter != inner_node->nodes_.end(); inner_node_iter++) {
            SubSearch(*inner_node_iter, collected_points);
        }
    }
}

std::vector<Point *> RTree::SearchInside(Point *point1, Point *point2) {
    return std::vector<Point *>();
}

std::vector<Point *> RTree::SearchNN(Point *point) {
    return std::vector<Point *>();
}

std::vector<Point *> RTree::SearchLeftOf(int number) {
    return std::vector<Point *>();
}


bool RTree::Insert(Point *point) {
    // returns true if point was added to set

    if(!root_){
        Leaf* leaf = new Leaf;
        leaf->points_.push_back(point);
        leaf->UpdateMBR();
        root_ = leaf;
        return true;
    }

    if(Contains(point)){
        return false;
    }

    Node* new_node = SubInsert(point, root_);
    if(new_node){
        INode* new_root = new INode();
        new_root->nodes_.push_back(root_);
        new_root->nodes_.push_back(new_node);
        root_ = new_root;
        root_->UpdateMBR();
    }
    return true;
}

RTree::Node *RTree::SubInsert(Point *point, RTree::Node *node) {
    // choosing subtree

    Leaf* leaf_node = dynamic_cast<Leaf*>(node);

    if(leaf_node){
        // leaf node

        if(leaf_node->points_.size() == M_){
            // split leaf
            leaf_node->points_.push_back(point);
            return Split(leaf_node);
        }
        else{
            leaf_node->points_.push_back(point);
            leaf_node->UpdateMBR();
            return nullptr;
        }
    }
    else{
        // inode

        INode* internal_node = dynamic_cast<INode*>(node);
        Node* next_node = ChooseSubtree(internal_node, point);

        Node* new_split_node = SubInsert(point, next_node);

        if(new_split_node){
            if(internal_node->nodes_.size() == M_){
                // split here ; return new node

                internal_node->nodes_.push_back(new_split_node);
                return Split(internal_node);
            }
            else{
                internal_node->nodes_.push_back(new_split_node);
            }
        }
        internal_node->UpdateMBR();
        return nullptr;
    }
}

RTree::Node *RTree::ChooseSubtree(RTree::INode *node, Point *point) {
    // node - leaf or inode

    int min_area_increase = -1;
    int area;
    Node* selected_node;

    for(auto inode: node->nodes_){
        area = inode->rect_.MinAreaIncrease(point);

        if(min_area_increase == -1){
            min_area_increase = area;
            selected_node = inode;
        }
        else{
            if(area < min_area_increase){
                min_area_increase = area;
                selected_node = inode;
            }
        }
    }
    return selected_node;
}

RTree::INode *RTree::Split(RTree::INode *inode) {
    INode* new_node = new INode();
    Node* current_inode;

    int size1 = inode->nodes_.size() / 2;

    for(int i = size1; i <= inode->nodes_.size(); i++){
        current_inode = inode->nodes_.back();
        new_node->nodes_.push_back(current_inode);
        inode->nodes_.pop_back();
    }

    inode->UpdateMBR();
    new_node->UpdateMBR();

    return new_node;
}

RTree::Leaf *RTree::Split(RTree::Leaf *leaf) {
    Leaf* new_leaf = new Leaf();
    Point* current_point;

    int size1 = leaf->points_.size() / 2;

    for(int i = size1; i <= leaf->points_.size(); i++){
        current_point = leaf->points_.back();
        new_leaf->points_.push_back(current_point);
        leaf->points_.pop_back();
    }

    leaf->UpdateMBR();
    new_leaf->UpdateMBR();
    return new_leaf;
}
