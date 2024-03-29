#include "Span.hpp"

Span::Span(unsigned int N)
: _max(N), _count(0) {
   
}

Span::~Span(){
    
}
Span::Span(Span const &cpy) : _max(cpy._max), _count(cpy._count) {
    for (int i = 0; i < this->getCount(); i++)
    this->_tab.push_back(cpy._tab[i]);
}

Span &Span::operator=(Span const &op){
    if (this != &op)
    {
        this->_count = op.getCount();
        
        for (int i = 0; i < this->getCount(); i++)
        this->_tab.push_back(op._tab[i]);

        this->_max = op._max;
    }
    return (*this);
}

//functions
void Span::addNumber( unsigned int nbAdd ){
    if (this->_count >= this->_max)
        throw Span::NoMoreException();
    else
    {
        this->_tab.push_back(nbAdd);
        this->_count++;
    }
}   

int Span::longestSpan() {
    if (this->getCount() <= 1)
        throw Span::NoPossible();
    int min = *min_element(_tab.begin(), _tab.end());
    int max = *max_element(_tab.begin(), _tab.end());
    return (max - min);
}

 int Span::shortestSpan (){
    if (this->getCount() <= 1)
        throw Span::NoPossible();
    std::vector<int> stock[_max];
    int res = 0;
    for (std::vector<int>::iterator it = _tab.begin(); it != (_tab.end() - 1); it++)
    {
        //valeur absolu
        res = *it - *(it + 1);
        if (res < 0)
            res = res * -1;
        stock->push_back(res);
    }
    int min = *min_element(stock->begin(), stock->end());
    return (min);
 }

void Span::addLotof(std::vector<int> &p){
    for(std::vector<int>::iterator begin = p.begin(); begin != p.end(); begin++)
    this->addNumber(*begin);
}

//getters
int  Span::getCount( void ) const {
    return (this->_count);
}
int  Span::getValueTab( int i ) const {
    if (i >= this->getCount())
        throw Span::InconnuValue();
    return (this->_tab[i]);
}

//exeptions
const char* Span::NoMoreException::what() const throw(){
	return ("Span : NoMoreException: is full");
}
const char* Span::InconnuValue::what() const throw(){
	return ("Span : InconnuValue: sorry is not permissed");
}
const char* Span::NoPossible::what() const throw(){
	return ("Span : NoPossible: sorry is not possible, not enought value");
}


//ostream surcharge operator
std::ostream &operator<<(std::ostream &os, Span const &sp){
    for (int i = 0; i < sp.getCount(); i++)
    os << "tab[" << i << "] = " << sp.getValueTab(i) << std::endl;
    return (os);
}

