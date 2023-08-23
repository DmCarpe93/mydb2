#include "frame/process/listener_process.h"
#include "util/program_option.h"

int main(int argc, char **argv) {
  util::ProgramOption option(argc, argv);

  if (option.Exist("help")) {
    option.PrintHelp();
    return 0;
  }

  if (!option.Exist("port")) {
    std::cerr << "Invalid Program Option: Listener port must be provided"
              << std::endl;
    return -1;
  }

  uint16_t listener_port = option.Get<uint16_t>("port");
  frame::ListenerProcess listener(listener_port);
  listener.Run();
  return 0;
}