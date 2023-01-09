#include "Trie.hpp"
#include <sstream>
#include <stack>
#include <list>


Trie::Node::Node() {
    children = std::map<char, Node *>();
    isEnd = false;
}

void Trie::insert(std::string str) {
    auto iter = str.begin();
    Node *curr = &root, *parent;
    while (iter != str.end() && curr->children.contains(*iter)) {
        curr = curr->children[*iter];
        ++iter;
    }
    while (iter != str.end()) {
        parent = curr;
        curr = new Node();
        parent->children.insert({*iter, curr});
        ++iter;
    }
    curr->isEnd = true;
}

std::string Trie::print() {
    std::list<bool> branch_is_over;
    std::stack<std::_Rb_tree_iterator<std::pair<const char, Trie::Node *>>> iterators, backs;
    backs.push(root.children.end());
    iterators.push(root.children.begin());

    std::stringstream ss;
    ss << "[root]";
    if (root.isEnd) ss << '!';
    ss << std::endl;

    while (iterators.size() != 1 || iterators.top() != backs.top()) {
        if (iterators.top() != backs.top()) {
            for (bool b: branch_is_over)
                if (!b)
                    ss << " |  ";
                else
                    ss << "    ";
            ss << " +--\"" << iterators.top()->first << '\"';
            if (iterators.top()->second->isEnd)
                ss << '!';
            ss << std::endl;
            branch_is_over.push_back(std::next(iterators.top()) == backs.top());
            backs.push(iterators.top()->second->children.end());
            iterators.push(iterators.top()->second->children.begin());
        } else {
            branch_is_over.pop_back();
            backs.pop();
            iterators.pop();
            ++(iterators.top());
        }
    }

    return ss.str();
}

bool Trie::contains(std::string str) {
    auto iter = str.begin();
    Node *curr = &root;
    while (true) {
        if (iter == str.end()) {
            return curr->isEnd;
        }
        if (!curr->children.contains(*iter)) {
            return false;
        }
        curr = curr->children[*iter];
        ++iter;
    }
}

std::vector<std::string> Trie::search() {
    std::vector<std::string> strings;
    std::stack<std::_Rb_tree_iterator<std::pair<const char, Trie::Node *>>> iterators, backs;
    std::string prefix;
    backs.push(root.children.end());
    iterators.push(root.children.begin());
    if (root.isEnd)
        strings.emplace_back("");

    while (iterators.size() != 1 || iterators.top() != backs.top()) {
        if (iterators.top() != backs.top()) {
            prefix.push_back(iterators.top()->first);
            if (iterators.top()->second->isEnd)
                strings.push_back(prefix);
            backs.push(iterators.top()->second->children.end());
            iterators.push(iterators.top()->second->children.begin());
        } else {
            prefix.pop_back();
            backs.pop();
            iterators.pop();
            ++(iterators.top());
        }
    }

    return strings;
}
