#include <boost/program_options.hpp>
#include <iostream>
#include <string>

namespace util {

class ProgramOption {
public:
  ProgramOption(int argc, char **argv)
      : argc_(argc), argv_(argv),
        desc("Usage:" + std::string(argv_[0]) + " [OPTION] ... \n\n OPTION") {
    desc.add_options()("help,h", "show all options")(
        "port,p", boost::program_options::value<uint16_t>(), "listener port");
    boost::program_options::store(
        boost::program_options::parse_command_line(argc_, argv_, desc), vm);
  }
  bool Exist(std::string option) { return vm.count(option); }
  void PrintHelp() { std::cout << desc << std::endl; }

  template <typename T, typename std::enable_if_t<std::is_integral<T>::value, T>
                            * = nullptr>
  T Get(std::string option) {
    return vm[option].as<T>();
  }

  std::string Get(std::string option) { return vm[option].as<std::string>(); }

private:
  int argc_;
  char **argv_;
  boost::program_options::options_description desc;
  boost::program_options::variables_map vm;
};

} // namespace util