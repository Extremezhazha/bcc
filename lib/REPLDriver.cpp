#include <string>
#include <filesystem>
#include <fstream>
#include <array>
#include "REPLDriver.h"
#include "eval/Print.h"


namespace {
    std::string exec(const char* cmd) {
        std::array<char, 128> buffer{};
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe{popen(cmd, "r"), pclose};
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }
}

namespace bcc {
    void REPLDriver::emit(bcc::AST::node_ptr_t value) {
        instructions.emplace_back(std::move(value));
    }

    void REPLDriver::emitPrint(bcc::AST::node_ptr_t value) {
        std::vector<std::unique_ptr<bcc::Term>> instructionGenerated{};
        std::map<std::string, int> varSSAMap{};
        for (auto const & instruction : instructions) {
            instruction->gen(instructionGenerated, varSSAMap, false);
        }


        std::vector<std::unique_ptr<bcc::Term>> printGenerated{};
        value->gen(printGenerated, varSSAMap, false);

        std::ifstream sourceTmpl{"ext_include/MainTmpl.cpp"};
        std::filesystem::remove_all("tmp");
        std::filesystem::create_directory("tmp");
        std::filesystem::copy_file("ext_include/Definitions.h", "tmp/Definitions.h");
        std::ofstream sourceGenerated{"tmp/generated_main.cpp"};

        std::string line;

        while (std::getline(sourceTmpl, line)) {
            if (std::string::size_type pos = line.find("/** MAIN_STUFF **/"); pos != std::string::npos) {
                sourceGenerated << std::string(pos, ' ') << bcc::Print{std::move(printGenerated[0])} << std::endl;
            } else if (std::string::size_type pos1 = line.find("/** STATEMENTS **/"); pos1 != std::string::npos) {
                std::string spaces(pos1, ' ');
                for (auto & cur: instructionGenerated) {
                    sourceGenerated << spaces << *cur << std::endl;
                }
            } else {
                sourceGenerated << line << std::endl;
            }
        }

        exec("g++ tmp/generated_main.cpp -O2 -o tmp/generated_main");
        std::cout << exec("./tmp/generated_main");
    }

    void REPLDriver::run() {
        std::string line;
        while (true) {
            std::getline(inputStream, line);
            parserDriver->parseString(line);
        }
    }

    REPLDriver::REPLDriver(std::istream & inputStream, std::ostream & outputStream)
            : inputStream{inputStream},
              outputStream{outputStream},
              parserDriver{std::make_unique<bccparse::ParserDriver>(*this)} {}
} // bcc