#include "RTree.h"


void RTree::Insert(Point *point) {

}


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

    std::cout << node->rect_->ToString() << std::endl;

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
    Rectangle* rect = node->rect_;
    bool res = false;

    INode* inner_node = dynamic_cast<INode*>(node);
    if(inner_node) {
        auto inner_node_iter = inner_node->nodes_.begin();

        for (; inner_node_iter != inner_node->nodes_.end(); inner_node_iter++) {
            if(rect->Contains(point)){
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
