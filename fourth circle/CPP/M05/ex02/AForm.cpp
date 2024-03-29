#include "AForm.hpp"

AForm::AForm() : _name("no_name"), _gradetosign(0), _gradetoexec(0) , _signed(false) {}

AForm::~AForm(){}

AForm::AForm(const std::string name, const int gts, const int gte) : _name(name), _gradetosign(gts), _gradetoexec(gte), _signed(false) {
    if (this->_gradetosign < 1 || this->_gradetoexec < 1)
		throw AForm::GradeTooHighException();
    else if (this->_gradetosign > 150 || this->_gradetoexec > 150)
		throw AForm::GradeTooLowException();
}

//copy
AForm::AForm(AForm const &cp) : _name(cp._name), _gradetosign(cp._gradetosign), _gradetoexec(cp._gradetoexec), _signed(cp._signed) {}
AForm& AForm::operator=(AForm const &op) {
    this->_signed = op.getSigned();
    return (*this);
}

//getters
const std::string AForm::getName() const {
    return (this->_name);
} 
int AForm::getGradetosign() const {
    return (this->_gradetosign);
}
int AForm::getGradetoexec() const {
     return (this->_gradetoexec);
}
bool AForm::getSigned() const {
    return(this->_signed);
}
    
//exeptions
const char* AForm::GradeTooHighException::what() const throw(){
	return ("AForm : GradeTooHighException: Grade too high!");
}

const char* AForm::GradeTooLowException::what() const throw(){
	return ("AForm : GradeTooLowException: Grade too low!");
}

const char* AForm::NotSignedException::what() const throw(){
	return ("AForm : NotSignedException: The form is not signed!");
}

const char* AForm::ErrorOpen::what() const throw(){
	return ("AForm : ErrorOpen: The form meet difficults, the jober can't create a file!");
}

//surcharge d'operateur d'insertion
std::ostream &operator<<(std::ostream &os, const AForm &b){
     os << "Name : " << b.getName() << std::endl << 
     "AForm signed ? : " << b.getSigned() << std::endl <<
     "Grade to sign is : " << b.getGradetosign() << std::endl <<
    "Grade to exec : " << b.getGradetoexec() << std::endl;
    return (os);
}

//functions
void AForm::beSigned(const Bureaucrat &b){
    if (b.getGrade() > this->_gradetoexec || b.getGrade() > this->_gradetosign)
        throw AForm::GradeTooLowException();
    else if (b.getGrade() < 1)
        throw AForm::GradeTooHighException();
    else
        this->_signed = true;
}
