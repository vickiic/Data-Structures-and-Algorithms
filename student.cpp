#include "student.h"
#include <string>
#include <cstring>
#include <sstream>

using namespace std;


Student::Student(const char * const name, int perm):name(0) {
    this->setName(name);
    this->setPerm(perm);
}

int Student::getPerm() const {
    return this->perm;
}

const char * const Student::getName() const {
    return this->name;;
}

void Student::setPerm(const int x) {
    this->perm = x;
}

void Student::setName(const char * const name) {
    delete [] this->name;
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
}


Student::Student(const Student &orig):name(0){
    
    this->setName(orig.getName());
    this->setPerm(orig.getPerm());
}

Student::~Student() {
    delete [] this->name;
    this->perm= 0;
}

Student & Student::operator=(const Student &right) {
    // The next two lines are standard, and you should keep them.
    if (&right == this)
        return (*this);
    
    // TODO... Here is where there is code missing that you need to
    // fill in...
    // KEEP THE CODE BELOW THIS LINE
    //Student::operator=(right);
    
    // handle attributes specific to this subclass
    
    setName(right.name);
    setPerm(right.perm);
    
    // Overloaded = should end with this line, despite what the textbook says.
    return (*this);
    
}

std::string Student::toString() const
{
    std::ostringstream oss;
    oss << "[" << this->getName() << "," << this->getPerm() << "]";
    return oss.str();
}



