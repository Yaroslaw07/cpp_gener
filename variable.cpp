#include "variable.h"

Variable::operator string()const{
    return this->type + " " + this->name;
}

Variable& Variable::operator=(const Variable& var) {
    this->name = var.name;
    this->type = var.type;
    return *this;   
}

ostream&  operator<<(ostream& os, const Variable& var) {
    os << var.type << " " << var.name;
    return os;
}

