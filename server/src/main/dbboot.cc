#include "frame/process/worker_process.h"
#include "util/program_option.h"

int main(int argc, char **argv) {
  util::ProgramOption option(argc, argv);

  if (option.Exist("help")) {
    option.PrintHelp();
    return 0;
  }

  frame::WorkerProcess worker;
  worker.Run();
  return 0;
}