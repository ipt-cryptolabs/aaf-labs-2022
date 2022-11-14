#include "DBImpl.h"


void DBImpl::Create(std::string set_name) {
    std::cout << "Create " << set_name << std::endl;
}

void DBImpl::Insert(std::string set_name, std::pair<int, int> point) {
    std::cout << "Insert " << set_name <<" (" << point.first << ", " << point.second << ")"<< std::endl;
}

void DBImpl::Print(std::string set_name) {
    std::cout << "Print " << set_name << std::endl;
}

void DBImpl::Contains(std::string set_name, std::pair<int, int> point) {
    std::cout << "Contains " << set_name <<" (" << point.first << ", " << point.second << ")"<< std::endl;
}

void DBImpl::Search(std::string set_name) {
    std::cout << "Search " << set_name << std::endl;
}

void DBImpl::SearchInside(std::string set_name, std::pair<int, int> point1, std::pair<int, int> point2) {
    std::cout << "SearchInside " << set_name <<" (" << point1.first << ", " << point1.second << ")" <<
        " (" << point2.first << ", " << point2.second << ")" << std::endl;
}

void DBImpl::SearchNN(std::string set_name, std::pair<int, int> point) {
    std::cout << "SearchNN " << set_name <<" (" << point.first << ", " << point.second << ")"<< std::endl;
}

void DBImpl::SearchLeftOf(std::string set_name, int number) {
    std::cout << "SearchLeftOf " << set_name << " " <<  number << std::endl;
}
