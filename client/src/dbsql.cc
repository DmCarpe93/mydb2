#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

#define MSG_LEN 128

void error_handling(string message);

int main (int argc, char* argv[]) {
	int sock;
	sockaddr_in serv_addr;
	char message[MSG_LEN];
	int readlen, msglen;
	/* TODO : need to get ip and port from tip file */
	string serv_ip = "127.0.0.1";
	uint16_t port = atoi(argv[1]);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0x00, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(serv_ip.c_str());
	serv_addr.sin_port = htons(port);

	if (connect(sock, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error");

	cout << "Connected to MyDB2." << endl;
	cout << endl;
	while (true) {
		string input;
		string temp;
		cout << "SQL> ";
		getline(cin, temp);

		if (temp == "q" || temp == "Q")
			break;
		input = temp;
		if (temp.size() > 0 && temp[temp.size()-1] != ';') {
			getline(cin, temp, ';');
			cin.ignore(MSG_LEN, '\n');
			input += " ";
			input += temp;
		}
		//cout << input << endl;
		if (input.size() == 1)
			continue;

		write(sock, input.c_str(), input.size());
	}
	close(sock);
	return 0;
}

void error_handling(string message) {
	cerr << message << endl;
	exit(1);
}
