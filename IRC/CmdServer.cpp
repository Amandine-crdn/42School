#	include "CmdServer.hpp"

/* ------ Methods ------*/


std::string Server::passCmd(User &user, std::vector<std::string> data, bool first)
{
    std::string password = "";
	if (first == true) {
		if (data[1].compare(this->getPassword()) == 0) {
			password = data[1];
			std::cout << "\t\t✅ Great password" << std::endl; }
		else {
			this->clientMessage(user, ERR_PASSWDMISMATCH);
			this->disconnected(user);}}

	else if (first == false) {
		clientMessage(user, ERR_ALREADYREGISTRED); }

    return password; 
}

std::string Server::nickCmd(User &user, std::vector<std::string> data, bool first)
{
	std::string nickname = "";
	std::vector<std::string>::iterator d;

	for (d = ++data.begin(); d != data.end(); d++){
		nickname.append(*d);
		if (d != data.end() - 1)
			nickname.push_back(' ');}
	if (nickname.size() > 9) {
		this->clientMessage(user, ERR_ERRONEUSNICKNAME);
		if (first == true)
			return ""; }
	else {
		std::map<int, User>::iterator itv;
		for (itv = users_list.begin(); itv != users_list.end(); itv++) {
			if (nickname == itv->second.getNickName()) {
				this->clientMessage(user, ERR_NICKNAMEINUSE);
				return ""; }}}
	if (first == false)
		user.setNickName(nickname);
    return nickname;
}

std::string Server::userCmd(User &user, std::vector<std::string> data, bool first)
{ 
	std::string username = "";
	if (first == true) {
    std::vector<std::string>::iterator d;
	for (d = ++data.begin(); d != data.end(); d++){
		username.append(*d);
		if (d != data.end() - 1)
			username.push_back(' '); }}

	else if (first == false)
		this->clientMessage(user, ERR_ALREADYREGISTRED);

    return username;
}

void Server::modeCmd(User &user, std::vector<std::string> data)
{
	bool correspondance = false;
	std::map<int, User>::iterator itv;
    for (itv = users_list.begin(); itv != users_list.end(); itv++) {
    	if (data[1] == itv->second.getNickName()) {
			correspondance = true; }}

	if (data[0].compare("MODE") == 0 && correspondance == false)
		clientMessage(user, ERR_NOSUCHNICK);
	else if (data[0].compare("MODE") == 0 && data[1].compare(user.getNickName()) != 0)
		clientMessage(user, ERR_USERSDONTMATCH);
	else if (data[0].compare("MODE") == 0 && data[1].compare(user.getNickName()) == 0 && \
		data[2].compare("+i") == 0) {
		clientMessage(user, RPL_UMODEIS);
		user.setVisibility(false); }
}

void Server::quitCmd(User &user, std::vector<std::string> data)
{
	std::cout << "🌙 " << std::endl;
	(void)data;
	clientMessage(user, ERROR);
	// close fd and disconnected hote
}

void Server::pingCmd(User &user, std::vector<std::string> data)
{
	std::stringstream result; 
	std::string response;

	if (data.size() == 1)
		clientMessage(user, ERR_NEEDMOREPARAMS);
	else { // comment etre sur que cela repond bien au ping ?
		result << server_name << " PONG :" << data[1] << DELIMITER; 
		response += result.str();
		send(user.getFd(), response.c_str(), response.size(), 0); }
}

void Server::joinCmd(User &user, std::vector<std::string> data)
{
	std::vector<std::string>::iterator itd;
	std::vector<Channel>::iterator itc;
	std::map<bool, std::string>::iterator itu;

	std::vector<std::string> new_data = this->split(data[1], ',');
	
	for (itd = new_data.begin(); itd != new_data.end(); itd++)
	{
		bool correspondance = false;
		bool use = false;
		for (itc = this->channels_list.begin(); itc != this->channels_list.end(); itc++) {		
			if (itc->getChannelName() == *itd) {
				correspondance = true;
				for (itu = user.channels_list_by_user.begin(); itu != user.channels_list_by_user.end(); itu++) {
					if (itu->second == *itd) {
						use = true; }}
				if (use == false) {
					user.setChannelListByUser(false, *itd);
					std::cout << "\t 🍀 " << user.getNickName() << "! Welcome to "  << *itd << " 🍀 " << std::endl;
					clientMessage(user, *itd); }}}
		if (correspondance == false) {
			this->setChannelList(*itd);
			std::cout << "\n 🍑 The channel " << *itd << " was created" << std::endl;
			user.setChannelListByUser(true, *itd);
			std::cout << "\t 🍀 " << user.getNickName() << "! Welcome to "  << *itd << " 🍀 " << std::endl;
			std::cout << "\t 🎈 🎈  🎈 Congratulations you're channel's operator 🎈 🎈 🎈" << std::endl;
			clientMessage(user, RPL_NOTOPIC, *itd); }}
}

void Server::privMsgCmd(User &user, std::string msg) {

	//std::stringstream message;
	(void)user; 
	std::vector<std::string> data;
	data = this->split(msg, ':');
	std::string target = this->split(data[0], ':')[1];
	std::string message = data[1];
	
	std::cout << "target = " << target << std::endl;
	
	std::cout << "message = " << message << std::endl;
}

void Server::operCmd(User &user, std::vector<std::string> data) {

	std::string opername = "opername";
	std::string operpass = "operpass";

	std::string name = data[1];
	std::string pass = data[2];


	if (data.size() < 2){
		this->clientMessage(user, ERR_NEEDMOREPARAMS);
		return; }

	if (name != opername || pass != operpass) {
		this->clientMessage(user, ERR_PASSWDMISMATCH);
		return; }

	user.setIRCOper(true);
	this->clientMessage(user, RPL_YOUREOPER);
} 




// /connect localhost 6667 coco