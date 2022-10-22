#	include "User.hpp"

User::User()
{
	std::cout << "construction default USER" << std::endl;
}

User::User(int fd)
: nick_name(""), user_name(""), real_name(""), first_connexion(true), visibility(true),
IRCOperator(false), toDelete(false), allowPass(false), allowCAP(false)
{
	this->fd = fd;
	std::cout << "construction USER" << std::endl;
}
	
User::~User()
{
	std::cout << "destruction USER" << std::endl;
}


/*------ methods ------- */


void User::clearMsg()
{
	this->vector_message_protocole.clear();
}


/*------ getters and setters ------ */

bool User::getAllowCAP() const { return allowCAP; }
void User::setAllowCAP(bool choice) { allowCAP = choice; }

bool User::getAllowPass() const { return this->allowPass; }
void User::setAllowPass(bool choice) { this->allowPass = choice; }

bool User::getDelete() const { return this->toDelete; }
void User::setDelete(bool choice) { this->toDelete = choice; }


std::vector<std::string> User::getMsg() /*const */{ return this->vector_message_protocole; } 
void User::setMsg(char *buffer, size_t read_size)
{
	int pos;
	std::string temp;

	temp.insert(0, buffer, read_size);
	while ((pos = temp.find(DELIMITER)) != -1)
	{
		vector_message_protocole.push_back(temp.substr(0, pos));
		temp = temp.erase(0, pos + sizeof(DELIMITER) - 1);
	}

	for (std::vector<std::string>::iterator it = vector_message_protocole.begin() ; it != vector_message_protocole.end(); it++)
	std::cout << "⌛  🖥️  IRSSI = >" << *it << "<" << std::endl;
}


std::string User::getFullClientIdentifier(void) 
{
	//<nick>!<user>@<host>
	return this->getNickName() + "!" + this->getUserName() + "@" + this->getUserName(); 
}

void User::setUserName(std::string user_name){ this->user_name = user_name; }
std::string User::getUserName(){ return this->user_name; }

void User::setRealName(std::string real_name){ this->real_name = real_name; }
std::string User::getRealName(){ return this->real_name; }

void User::setNickName(std::string nick_name){ this->nick_name = nick_name; };
std::string User::getNickName(){ return this->nick_name; }

bool User::getFirstConnexion() const { return this->first_connexion; }
void User::setFirstConnexion(bool choice) { this->first_connexion = choice; }

void User::setFd(int fd) { this->fd = fd; }
int User::getFd() const { return this->fd; }

bool User::getVisibility() const { return this->visibility; }
void User::setVisibility(bool choice) { this->visibility = choice; }

bool User::getIRCOper() const { return this->IRCOperator; };
void User::setIRCOper(bool choice) { this->IRCOperator = choice; };

bool User::getOpServer() const { return this->opServer; }
void User::setOpServer(bool choice) { this->opServer = choice; }