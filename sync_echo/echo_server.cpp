#include <stdlib.h>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;
typedef boost::shared_ptr<tcp::socket> socket_ptr;
const int BUFFER_SIZE = 1024;


void session(socket_ptr sock){
	try{
		std::string remoteIP = sock->remote_endpoint().address().to_string();
		std::cout << "Connection established to: " << remoteIP << std::endl;

		boost::system::error_code error;
		while(true){ 
			char data[BUFFER_SIZE] = {};
			size_t length = sock->read_some(boost::asio::buffer(data), error);
			if(error == boost::asio::error::eof){
				break; //Connection closed by client
			} else if(error){
				throw boost::system::system_error(error);
			}
			std::string str(data);
			std::cout << remoteIP << ": " << str.erase(str.find_last_not_of(" \n\r\t")+1) << std::endl;
		}
		std::cout << "Connection to " << remoteIP << " closed." << std::endl;
	} catch (std::exception &e){
		std::cerr << "Exception in session: " << e.what() << std::endl;
	}	
}

int main(int argc, char* argv[]){
	if(argc != 2){
		std::cerr << "usage: ./echo_server <port>" << std::endl;
		return EXIT_FAILURE;
	}

	int port = atoi(argv[1]);
	try{
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

		std::cout << "Listening for connetions on port: " << port << std::endl;
		while(true){ //listen loop
			socket_ptr sock(new tcp::socket(io_service));
			acceptor.accept(*sock);
			boost::thread t(session, sock);
		}
	} catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;	
}
