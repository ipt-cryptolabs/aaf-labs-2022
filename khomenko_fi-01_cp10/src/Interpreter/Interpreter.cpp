#include "Interpreter.h"

void Interpreter::Interpret() {
    ASTNode* root = parser_->Parse();
    CommandNode* command_node = dynamic_cast<CommandNode*>(root);
    VisitCommand(command_node);
}

void Interpreter::VisitCommand(CommandNode *node) {
    TokenType command_type = node->get_op()->get_type();

    switch (command_type) {
        case kCreate: {
            SetNameNode* set_name_node = dynamic_cast<SetNameNode*>(node->get_left());
            db_->Create(VisitSetName(set_name_node));
            break;
        }


        case kInsert: {
            SetNameNode* set_name_node = dynamic_cast<SetNameNode*>(node->get_left());
            PointNode* point_node = dynamic_cast<PointNode*>(node->get_right());
            db_->Insert(VisitSetName(set_name_node), VisitPoint(point_node));
            break;
        }

        case kPrintTree: {
            SetNameNode* set_name_node = dynamic_cast<SetNameNode*>(node->get_left());
            db_->Print(VisitSetName(set_name_node));
            break;
        }

        case kContains: {
            SetNameNode* set_name_node = dynamic_cast<SetNameNode*>(node->get_left());
            PointNode* point_node = dynamic_cast<PointNode*>(node->get_right());
            db_->Contains(VisitSetName(set_name_node), VisitPoint(point_node));
            break;
        }

        case kSearch: {
            SetNameNode* set_name_node = dynamic_cast<SetNameNode*>(node->get_left());
            CommandNode* subcommand_node = dynamic_cast<CommandNode*>(node->get_right());

            if(!subcommand_node){
                db_->Search(VisitSetName(set_name_node));
                return;
            }

            // NN, LEFT_OF, INSIDE
            CommandNode* qualifier_node = dynamic_cast<CommandNode*>(subcommand_node->get_left());

            if(qualifier_node->get_op()->get_type() == kNN){
                PointNode* point_node = dynamic_cast<PointNode*>(qualifier_node->get_left());
                db_->SearchNN(VisitSetName(set_name_node), VisitPoint(point_node));
            }
            else{
                if(qualifier_node->get_op()->get_type() == kLeftOf){
                    IntegerNode* integer_node = dynamic_cast<IntegerNode*>(qualifier_node->get_left());
                    db_->SearchLeftOf(VisitSetName(set_name_node), VisitInteger(integer_node));
                }
                else{
                    PointNode* point_node1 = dynamic_cast<PointNode*>(qualifier_node->get_left());
                    PointNode* point_node2 = dynamic_cast<PointNode*>(qualifier_node->get_right());
                    db_->SearchInside(VisitSetName(set_name_node), VisitPoint(point_node1), VisitPoint(point_node2));
                }
            }
            break;
        }

        default:
            // never gets here
            break;
    }
}

int Interpreter::VisitInteger(IntegerNode* node) {
    return node->get_value();
}

std::string Interpreter::VisitSetName(SetNameNode *node) {
    return node->get_value();
}

Point* Interpreter::VisitPoint(PointNode *node) {
    return node->get_value();
}


