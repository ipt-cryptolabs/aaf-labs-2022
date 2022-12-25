#include "DB.h"


void DB::Create(const std::string& set_name) {
    if(sets_.find(set_name) == sets_.end()){
        sets_[set_name] = new RTree(2, 4);
        std::cout << "Set " << set_name << " has been created" << std::endl;
    }
    else{
        throw Exception("DB already contains " + set_name + "!");
    }
}

void DB::Insert(const std::string& set_name, Point* point) {
    CheckSetPresence(set_name);
    if(sets_[set_name]->Insert(point)){
        std::cout << "Point " << point->ToString() + " has been added to " + set_name << std::endl;
    }
    else{
        std::cout << set_name + " already contains " + point->ToString() << std::endl;
    }
}

void DB::Print(const std::string& set_name) {
    CheckSetPresence(set_name);
    sets_[set_name]->Print();
}

void DB::Contains(const std::string& set_name, Point* point) {
    CheckSetPresence(set_name);

    if(sets_[set_name]->Contains(point)){
        std::cout << "TRUE" << std::endl;
    }
    else{
        std::cout << "FALSE" << std::endl;
    }
}

void DB::Search(const std::string& set_name) {
    CheckSetPresence(set_name);
    std::vector<Point *> res = sets_[set_name]->Search();

    for(auto el: res){
        std::cout << el->ToString() << std::endl;
    }
}

void DB::SearchLeftOf(const std::string& set_name, int number) {
    CheckSetPresence(set_name);
    std::vector<Point *> res = sets_[set_name]->SearchLeftOf(number);

    for(auto el: res){
        std::cout << el->ToString() << std::endl;
    }
}

void DB::SearchInside(const std::string& set_name, Point* point1, Point* point2) {
    CheckSetPresence(set_name);
    std::vector<Point *> res = sets_[set_name]->SearchInside(point1, point2);

    for(auto el: res){
        std::cout << el->ToString() << std::endl;
    }
}

void DB::SearchNN(const std::string& set_name, Point* point) {
    CheckSetPresence(set_name);
    sets_[set_name]->SearchNN(point);
}


void DB::CheckSetPresence(const std::string& set_name) {
    if(sets_.find(set_name) == sets_.end()){
        throw Exception("There is no " + set_name + " in DB !");
    }
}
