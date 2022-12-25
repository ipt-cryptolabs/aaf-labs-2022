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


std::vector<Point *> RTree::SearchNN(Point *point) {
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

RTree::Node * RTree::SubInsert(Point *point, RTree::Node *node) {
    // choosing subtree

    Leaf* leaf_node = dynamic_cast<Leaf*>(node);

    if(leaf_node){
        // leaf node

        if(leaf_node->points_.size() == M_){
            // split leaf
            leaf_node->points_.push_back(point);
            return QuadraticSplit(leaf_node);
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
                return QuadraticSplit(internal_node);
            }
            else{
                internal_node->nodes_.push_back(new_split_node);
            }
        }
        internal_node->UpdateMBR();
        return nullptr;
    }
}

RTree::Node *RTree::ChooseSubtree(RTree::INode* node, Point *point) {
    // node - leaf or inode

    int min_distance_increase = -1;
    int distance;
    Node* selected_node;

    for(auto inode: node->nodes_){
        distance = inode->rect_.DistanceBetween(point);

        if(min_distance_increase == -1){
            min_distance_increase = distance;
            selected_node = inode;
        }
        else{
            if(distance < min_distance_increase){
                min_distance_increase = distance;
                selected_node = inode;
            }
        }
    }
    return selected_node;
}

RTree::Leaf *RTree::QuadraticSplit(RTree::Leaf *leaf) {
    std::vector<Point*> points = leaf->points_;
    leaf->points_.clear();
    Leaf* split_leaf = new Leaf();

    // choose the furthest leaf and split_leaf from points and distribute other points based on leaf and split_leaf
    PickSeeds(leaf, split_leaf, points);
    QDistribute(leaf, split_leaf, points);
    return split_leaf;
}

void RTree::PickSeeds(RTree::Leaf *leaf, RTree::Leaf *split_leaf, std::vector<Point *>& points) {
    Point* point1;
    Point* point2;
    Point* res_point1;
    Point* res_point2;

    int max_distance = 0;
    int distance;

    for(int i = 0; i <= M_; i++){
        for(int j = i + 1; j <= M_; j++){
            point1 = points[i];
            point2 = points[j];

            distance = Point::SqrDistance(point1, point2);
            if(distance > max_distance){
                max_distance = distance;
                res_point1 = point1;
                res_point2 = point2;
            }
        }
    }

    leaf->points_.push_back(res_point1);
    leaf->UpdateMBR();

    split_leaf->points_.push_back(res_point2);
    split_leaf->UpdateMBR();

    points.erase(std::remove(points.begin(), points.end(), res_point1), points.end());
    points.erase(std::remove(points.begin(), points.end(), res_point2), points.end());
}

void RTree::QDistribute(RTree::Leaf *leaf, RTree::Leaf *split_leaf, std::vector<Point *>& points) {
    Point* current_point;
    int distance1;
    int distance2;
    int leaf_points_size;

    while(!points.empty() && leaf->points_.size() < M_ - m_ + 1 && split_leaf->points_.size() < M_ - m_ + 1) {
        current_point = PickNext(leaf, split_leaf, points);

        distance1 = leaf->rect_.DistanceBetween(current_point);
        distance2 = split_leaf->rect_.DistanceBetween(current_point);

        leaf_points_size = leaf->points_.size();

        // choose in which leaf point should be inserted

        if (distance1 < distance2) {
            leaf->points_.push_back(current_point);
        } else {
            if (distance1 > distance2) {
                split_leaf->points_.push_back(current_point);
            } else {
                if (leaf->rect_.Square() < split_leaf->rect_.Square()) {
                    leaf->points_.push_back(current_point);
                } else {
                    if (leaf->rect_.Square() > split_leaf->rect_.Square()) {
                        split_leaf->points_.push_back(current_point);
                    } else {
                        if (leaf->points_.size() < split_leaf->points_.size()) {
                            leaf->points_.push_back(current_point);
                        } else {
                            split_leaf->points_.push_back(current_point);
                        }
                    }
                }
            }
        }

        // should update mbr in inserted leaf
        if (leaf_points_size != leaf->points_.size()) {
            leaf->rect_ = leaf->rect_.UpdatedRectangle(current_point);
        } else {
            split_leaf->rect_ = split_leaf->rect_.UpdatedRectangle(current_point);
        }

        // delete current point from points
        for (auto iter = points.begin(); iter != points.end(); ++iter) {
            if (*iter == current_point) {
                points.erase(iter);
                break;
            }
        }
    }

    if(leaf->points_.size() == M_ - m_ + 1){
        for(auto point: points){
            split_leaf->points_.push_back(point);
        }
        split_leaf->UpdateMBR();
    }
    else{
        for(auto point: points){
            leaf->points_.push_back(point);
        }
        leaf->UpdateMBR();
    }
}

Point *RTree::PickNext(RTree::Leaf *leaf, RTree::Leaf *split_leaf, const std::vector<Point *> &points) {
    if(points.size() == 1){
        return points[0];
    }

    int max_distance_difference = 0;

    int distance1;
    int distance2;
    int distance;

    Point* res_point;

    for(auto point : points){
        distance1 = leaf->rect_.DistanceBetween(point);
        distance2 = split_leaf->rect_.DistanceBetween(point);

        distance = std::abs(distance2 - distance1);
        if(distance > max_distance_difference){
            max_distance_difference = distance;
            res_point = point;
        }
    }

    return res_point;
}

RTree::INode *RTree::QuadraticSplit(RTree::INode* inode) {
    std::vector<Node*> nodes = inode->nodes_;
    inode->nodes_.clear();
    INode* split_inode = new INode();

    // choose the furthest inode and split_inode from nodes and distribute other nodes based on inode and split_inode
    PickSeeds(inode, split_inode, nodes);
    QDistribute(inode, split_inode, nodes);

    return split_inode;
}


RTree::Node *RTree::PickNext(RTree::Node *node, RTree::Node *split_node, const std::vector<Node*> &nodes) {
    if(nodes.size() == 1){
        return nodes[0];
    }

    int max_distance_difference = 0;

    int distance1;
    int distance2;
    int distance;

    Node* res_node;

    for(auto current_node : nodes){
        distance1 = node->rect_.DistanceBetween(&current_node->rect_);
        distance2 = split_node->rect_.DistanceBetween(&current_node->rect_);

        distance = std::abs(distance2 - distance1);
        if(distance > max_distance_difference){
            max_distance_difference = distance;
            res_node = current_node;
        }
    }

    return res_node;
}

void RTree::PickSeeds(RTree::INode *node, RTree::INode *split_node, std::vector<Node *>& nodes) {
    Node* node1;
    Node* node2;
    Node* res_node1;
    Node* res_node2;

    int max_distance = 0;
    int distance;

    for(int i = 0; i <= M_; i++){
        for(int j = i + 1; j <= M_; j++){
            node1 = nodes[i];
            node2 = nodes[j];
            distance = node1->rect_.DistanceBetween(&node2->rect_);
            if(distance > max_distance){
                max_distance = distance;
                res_node1 = node1;
                res_node2 = node2;
            }
        }
    }

    // the furthest nodes have been chosen. Add them to node and split_node

    node->nodes_.push_back(res_node1);
    node->UpdateMBR();
    split_node->nodes_.push_back(res_node2);
    split_node->UpdateMBR();

    nodes.erase(std::remove(nodes.begin(), nodes.end(), res_node1), nodes.end());
    nodes.erase(std::remove(nodes.begin(), nodes.end(), res_node2), nodes.end());
}

void RTree::QDistribute(RTree::INode *node, RTree::INode *split_node, std::vector<Node *> &nodes) {
    Node* current_node;
    int distance1;
    int distance2;
    int split_node_nodes_size;

    while(!nodes.empty() && node->nodes_.size() < M_ - m_ + 1 && split_node->nodes_.size() < M_ - m_ + 1) {
        current_node = PickNext(node, split_node, nodes);

        distance1 = node->rect_.DistanceBetween(&current_node->rect_);
        distance2 = split_node->rect_.DistanceBetween(&current_node->rect_);

        split_node_nodes_size = split_node->nodes_.size();
        // choose in which node should be inserted

        if (distance1 < distance2) {
            node->nodes_.push_back(current_node);
        } else {
            if (distance1 > distance2) {
                split_node->nodes_.push_back(current_node);
            } else {
                if (node->rect_.Square() < split_node->rect_.Square()) {
                    node->nodes_.push_back(current_node);
                } else {
                    if (node->rect_.Square() > split_node->rect_.Square()) {
                        split_node->nodes_.push_back(current_node);
                    } else {
                        if (node->nodes_.size() < split_node->nodes_.size()) {
                            node->nodes_.push_back(current_node);
                        } else {
                            split_node->nodes_.push_back(current_node);
                        }
                    }
                }
            }
        }

        // should update mbr in inserted node
        if (split_node_nodes_size != split_node->nodes_.size()) {
            split_node->rect_ = split_node->rect_.UpdatedRectangle(&current_node->rect_);
        } else {
            node->rect_ = node->rect_.UpdatedRectangle(&current_node->rect_);
        }

        // delete current node from nodes
        for (auto iter = nodes.begin(); iter != nodes.end(); ++iter) {
            if (*iter == current_node) {
                nodes.erase(iter);
                break;
            }
        }
    }

    if(node->nodes_.size() == M_ - m_ + 1){
        for(auto node_: nodes){
            split_node->nodes_.push_back(node_);
        }
        split_node->UpdateMBR();
    }
    else{
        for(auto node_: nodes){
            node->nodes_.push_back(node_);
        }
        node->UpdateMBR();
    }
}

std::vector<Point *> RTree::SearchLeftOf(int x) {
    std::vector<Point *> collected_points;

    if(root_){
        SubSearchLeftOf(root_, x, collected_points);
    }

    return collected_points;
}

void RTree::SubSearchLeftOf(RTree::Node *node, int x, std::vector<Point *> &collected_points) {
    Leaf* leaf_node = dynamic_cast<Leaf*>(node);

    if(leaf_node){
        auto leaf_node_iter = leaf_node->points_.begin();
        for (; leaf_node_iter != leaf_node->points_.end(); leaf_node_iter++) {
            if((*leaf_node_iter)->x < x){
                collected_points.push_back(*leaf_node_iter);
            }
        }
    }
    else{
        INode* inner_node = dynamic_cast<INode*>(node);
        auto inner_node_iter = inner_node->nodes_.begin();

        for (; inner_node_iter != inner_node->nodes_.end(); inner_node_iter++) {
            if(inner_node->rect_.get_lb_point().x < x){
                SubSearchLeftOf(*inner_node_iter, x, collected_points);
            }
        }
    }
}

std::vector<Point *> RTree::SearchInside(Point *point1, Point *point2) {
    std::vector<Point *> collected_points;

    if(root_){
        Rectangle* rectangle = new Rectangle(*point1, *point2);
        SubSearchInside(root_, rectangle, collected_points);
        delete rectangle;
    }

    return collected_points;
}

void RTree::SubSearchInside(RTree::Node *node, Rectangle *rectangle, std::vector<Point *> &collected_points) {
    Leaf* leaf_node = dynamic_cast<Leaf*>(node);

    if(leaf_node){
        auto leaf_node_iter = leaf_node->points_.begin();
        for (; leaf_node_iter != leaf_node->points_.end(); leaf_node_iter++) {
            auto log = *leaf_node_iter;
            if(rectangle->Contains(*leaf_node_iter)){
                collected_points.push_back(*leaf_node_iter);
            }
        }
    }
    else{
        INode* inner_node = dynamic_cast<INode*>(node);
        auto inner_node_iter = inner_node->nodes_.begin();

        for (; inner_node_iter != inner_node->nodes_.end(); inner_node_iter++) {
            if((*inner_node_iter)->rect_.Intersects(rectangle)){
                SubSearchInside(*inner_node_iter, rectangle, collected_points);
            }
        }
    }
}
