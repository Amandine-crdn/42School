#   include "Server.hpp"

void Server::clientMessage(User &user, std::string cmd, std::string channel_name, std::string topic)
{
	std::stringstream result;
	std::string response;

   /*    */
    result << cmd << user.getNickName() << " ";
      
    /*---- BEGIN PROCEDURE WLC -----*/


    if (cmd.compare(RPL_WELCOME) == 0)
        result << ":👋 Welcome to the Internet Relay Chat Network, " << user.getNickName() << "!" << user.getUserName() /* masque d'hote : << "@" << inet_ntoa(_sin.sin_addr)*/;
    
    
    /*---- NICKNAME-----*/
	
    else if (cmd.compare(ERR_NICKNAMEINUSE) == 0) //channelname is nicknme not registred
        result << channel_name << " :Nickname is already in use";

    else if (cmd.compare(ERR_NOSUCHNICK) == 0)
        result << ":No such nick";
   
    else if (cmd.compare(ERR_USERSDONTMATCH) == 0)
        result << ":Cant change mode for other users.";

    else if (cmd.compare(ERR_ERRONEUSNICKNAME) == 0) //channelname is nicknme not registred
        result  << channel_name << " :Erroneous nickname"<< DELIMITER;
    
   

    /*----- CHANNEL ----*/

    else if (cmd.compare(ERR_NOSUCHCHANNEL) == 0)
        result << channel_name << " :No such channel";
    
    else if (cmd.compare(ERR_NOTONCHANNEL) == 0)
        result << channel_name << " :You're not on that channel";
   
    else if (cmd.compare(ERR_NOCHANMODES) == 0)
        result << channel_name << " :Channel doesn't support modes";
    
    else if (cmd.compare(ERR_USERONCHANNEL) == 0)
        result << topic << " " << channel_name << " :is already on channel"; //topic is nick

    else if (cmd.compare(ERR_USERNOTINCHANNEL) == 0)
        result << topic << " " << channel_name << " :They aren't on that channel";  //topic is nick
    
    else if (cmd.compare(ERR_CHANOPRIVSNEEDED) == 0)
        result << channel_name << " :You're not channel operator";
    
    else if (cmd.compare(RPL_NOTOPIC) == 0)
        result << channel_name << " :No topic is set";
   
    else if (cmd.compare(RPL_TOPIC) == 0)
        result << channel_name << " :" << topic;
    
    else if (cmd.compare(RPL_NAMREPLY) == 0)
        result << "= " << channel_name  << " :" << topic;
   
    else if (cmd.compare(RPL_ENDOFNAMES) == 0)
        result << channel_name << " :End of /NAMES list";

    else if (cmd.compare(RPL_LIST) == 0)
        result << channel_name  << " # visible " << " :" << topic;
   
    else if (cmd.compare(RPL_LISTEND) == 0)
        result << channel_name << " :End of LIST";

    
    /*----- MODE -----*/

    else if (cmd.compare(RPL_UMODEIS) == 0)
        result << ":public";

    else if (cmd.compare(ERR_UNKNOWNMODE) == 0)
        result << channel_name << " :is unknown mode char to me for <channel>";

    else if (cmd.compare(ERR_UMODEUNKNOWNFLAG) == 0)
        result << " :Unknown MODE flag";

   
    /*----- OTHERS -----*/

    else if (cmd.compare(ERR_ALREADYREGISTRED) == 0)
        result << ":You may not reregister";
    
    else if (cmd.compare(ERR_PASSWDMISMATCH) == 0)
        result << ": ❌ Password incorrect";
    
    else if (cmd.compare(ERR_NEEDMOREPARAMS) == 0) //channel_name is command name
        result << channel_name << " :Not enough parameters"<< DELIMITER;
   
    else if (cmd.compare(RPL_YOUREOPER) == 0)
        result << ":You are now an IRC operator"<< DELIMITER;
   
    else if (cmd.compare(ERR_UNKNOWNCOMMAND) == 0)
        result << channel_name << " :Unknown command"; //channelname = cmd unknow
  
    else if (cmd.compare(ERR_NOPRIVILEGES) == 0)
        result << ":Permission Denied- You're not an IRC operator";
    
  

    /*else if (cmd.compare(ERROR) == 0) //ERR_UNKNOWNERROR 400 ?
        result << ": Good bye"<< DELIMITER;  //euh*/


    else if (cmd.compare(ERR_NOORIGIN) == 0)
        result << ":No origin specified";
   
    else if (cmd.compare(ERR_NOSUCHSERVER) == 0)
        result << server_name << " :No such server";  
    
    else if (cmd.compare(RPL_ADMINME) == 0)
        result << server_name << " :Administrative info, Amandine Cerdan is the developer of this server"; 
    
    else if (cmd.compare(RPL_ADMINLOC1) == 0)
        result << ":Paris, France";  
   
    else if (cmd.compare(RPL_ADMINEMAIL) == 0)
        result << ":amandinecerdan91760@gmail.com"; 
    
    else if (cmd.compare(RPL_INVITING) == 0)
        result << topic << " " << channel_name; 

    result << DELIMITER;
    response += result.str();
    send(user.getFd(), response.c_str(), response.size(), 0); 
}
// /connect localhost 6667 coco