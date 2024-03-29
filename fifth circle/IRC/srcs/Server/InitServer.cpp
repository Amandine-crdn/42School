#	include "Server.hpp"


/* ------ Methods ------*/

void Server::init_server(const char *port, const char *password)
{
	int enable = 1;
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(atoi(port));
	_sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (_sin.sin_port == 0) //proteger
		error("invalid port");
	_sizeofsin = sizeof(_sin);
    if (!atoi(port)) {
        this->error("error port"); }
    this->setPassword(password);
    this->setServerFd(socket(AF_INET, SOCK_STREAM, 0));
    if (this->getServerFd() == -1) {
        this->error("error socket()"); }
	if (setsockopt(this->getServerFd(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)) == -1) {
		this->error("setsockopt()"); }
	if (fcntl(this->getServerFd(), F_SETFL, O_NONBLOCK) == -1) {
		this->error("fcntl()"); }
    if (bind(getServerFd(), (sockaddr *)&_sin, _sizeofsin) == -1)
		this->error("bind()");
    if (listen(this->getServerFd(), 5) == -1) { // 5 : file d'attente
        this->error("error listen()"); }
	
	std::cout << "🌞   🌞   🌞   🌞   🌞   🌞   🌞   🌞   🌞   🌞   🌞   🌞   🌞   🌞" << std::endl;
    std::cout << std::endl;
	std::cout << "🌺 🌺 🌺 " << this->server_name << " starting on port " << atoi(port) << " with password " << this->getPassword() << " 🌺 🌺 🌺" << std::endl;
	std::cout << std::endl;
}

void Server::connect()
{
	pollfd tempPollFd;

	_pollfds.clear();

	tempPollFd.fd = getServerFd();
	tempPollFd.revents = 0;

	tempPollFd.events = POLLIN;
	_pollfds.push_back(tempPollFd);

	for (std::vector<User>::iterator it = utilisateurs_list.begin(); it != utilisateurs_list.end(); it++)
	{
		tempPollFd.fd = it->getFd();
		_pollfds.push_back(tempPollFd);
	}
	
	if (poll(&(_pollfds[0]), _pollfds.size(), 300000) == -1) //timeout define NULL
	{
		error("poll()");
	}
	
	int tempFd;

	if (_pollfds[0].revents == POLLIN)
	{
		tempFd = accept(getServerFd(), (sockaddr *)&_sin, &_sizeofsin);
		if (tempFd == -1)
			this->error("accept()");
		utilisateurs_list.push_back(User(tempFd));
		std::cout << "\n🏡  New user accepted with fd: " << tempFd << " 🏡\n" << std::endl;
	}
}

void Server::intercept()
{
   	char buffer[BUFFER_SIZE];
	int sizeRead;
	
	for (std::vector<pollfd>::iterator itb = ++_pollfds.begin(), ite = _pollfds.end(); itb != ite; itb++)
	{
		if (itb->revents == POLLIN)
		{
			for (int i = 0; i < BUFFER_SIZE; i++)
			buffer[i] = '\0';

			sizeRead = recv(itb->fd, buffer, BUFFER_SIZE, 0);

			if (sizeRead == -1)
				this->error("error: recv()");
			else if (sizeRead == 0)
			{
				getpeername(itb->fd, (struct sockaddr *)&_sin, (socklen_t *)&_sizeofsin);
				std::cout << "Host disconnected , ip " << inet_ntoa(_sin.sin_addr) << " , port " << ntohs(_sin.sin_port) << std::endl;
				close(itb->fd);
				this->clearUser(*(this->getUserByFd(itb->fd)));
				std::cout << "host closed and user erased" << std::endl;
			}
			else
                this->getUserByFd(itb->fd)->setMsg(buffer, sizeRead);
		}
	}
}   
