#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#include "common/connection/tcp_connection.h"
#include "common/message/message.pb.h"

using namespace std;
#define MSG_LEN 128

int main(int argc, char *argv[]) {
  int readlen, msglen;
  /* TODO : need to get ip and port from tip file */
  std::string address = "127.0.0.1";
  uint16_t port = atoi(argv[1]);

  boost::asio::io_context io_context;
  common::TcpConnection conn(io_context);
  conn.Connect(address, port);

  cout << "Connected to MyDB2." << endl;
  cout << endl;

  /* Connection Reply */
  common::Message message;
  message.set_type(common::MessageType::CONNECT_REQUEST);
  message.mutable_connect_request()->set_username("mydb2");
  message.mutable_connect_request()->set_password("test");

  std::string connect_msg;
  if (!message.SerializeToString(&connect_msg)) {
    std::cerr << "Failed to serialize the message." << std::endl;
  }
  conn.Write(connect_msg.c_str(), connect_msg.size());

  while (true) {
    string input;
    string temp;
    cout << "SQL> ";
    getline(cin, temp);

    if (temp == "q" || temp == "Q")
      break;
    input = temp;
    if (temp.size() > 0 && temp[temp.size() - 1] != ';') {
      getline(cin, temp, ';');
      cin.ignore(MSG_LEN, '\n');
      input += " ";
      input += temp;
    }
    // cout << input << endl;
    if (input.size() == 1)
      continue;
    conn.Write(input.c_str(), input.size());
  }
  return 0;
}
