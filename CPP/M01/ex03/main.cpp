#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

//gerer le cas ou Human B n'a pas d'arme

int main()
{
    {
        Weapon club = Weapon("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }
    
    {
        Weapon club = Weapon("dragon tooth");
        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();
        club.setType("some other type of club");
        jim.attack();
    }
    
    return (0);
}