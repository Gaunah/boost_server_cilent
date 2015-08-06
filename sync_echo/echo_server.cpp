#include <stdlib.h>
#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char* argv[]){
	using boost::asio::ip::tcp;
	if(argc != 2){
		std::cerr << "usage: ./echo_server <port>" << std::endl;
		return EXIT_FAILURE;
	}
	int port = atoi(argv[1]);

	try{
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

		while(true){ //listen loop
			tcp::socket socket(io_service);
			acceptor.accept(socket);
			std::cout << "connection established to: " << socket.remote_endpoint().address().to_string() << std::endl;
			//TODO
		}
	} catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;	
}
