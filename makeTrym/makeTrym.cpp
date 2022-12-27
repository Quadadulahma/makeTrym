#include "makeTrym.h"


#include <winsock2.h>
#include <thread>

#define PORT 80
#define BACKLOG 5

void client_handler(SOCKET client)
{
	char buffer[1024];
	while (true)
	{
		// Receive data from the client
		int bytes_received = recv(client, buffer, 1024, 0);
		if (bytes_received > 0)
		{
			// Data was received from the client
			// Process the data in the buffer
			// ...
			std::cout << "-------------------" << std::endl;
			std::cout << "message from client" << client << std::endl;
			std::cout << "-------------------" << std::endl;
			std::cout << "will answer on thread " << std::this_thread::get_id();

		}
		else if (bytes_received == 0)
		{
			// The client has closed the connection
			break;
		}
		else
		{
			// An error occurred
			break;
		}

		// Send data to the client
		char* data = "Hello from the server!";
		int bytes_sent = send(client, data, strlen(data), 0);
		if (bytes_sent == SOCKET_ERROR)
		{
			// An error occurred
			break;
		}
	}
	std::cout << "closing thread " << client << " thread ID: " << std::this_thread::get_id() << std::endl;

	// Close the client socket
	closesocket(client);
}

void server_loop(SOCKET sock)
{
	// Main server loop
	while (true)
	{
		// Accept incoming connections
		SOCKET client = accept(sock, NULL, NULL);
		if (client == INVALID_SOCKET)
		{
			std::cout << "an error accuRENDA DSHAOSIDJSAOIDJJDOIJSAID" << std::endl;
			// An error occurred
			break;
		}
		std::cout << "creating new thread" << std::endl;

		// Create a new thread to handle the client
		std::thread client_thread(client_handler, client);
		client_thread.detach(); // Detach the thread to allow it to run independently
	}
}



int main()
{

	/*
	// Bind the socket to a local address and port
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		// An error occurred
		return 1;
	}

	// Start listening for incoming connections
	if (listen(sock, BACKLOG) == SOCKET_ERROR)
	{
		// An error occurred
		return 1;
	}

	// Create the server thread
	std::thread server_thread(server_loop, sock);
	*/


	init_game();
	run();
	destroy_game();
	

	// Wait for the server thread to finish
//	server_thread.join();

	// Clean up
//	closesocket(sock);
	WSACleanup();
	

	return 0;
}

