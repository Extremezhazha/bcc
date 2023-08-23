#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <array>
#include <vector>

#include "include/eval/Print.h"
#include "include/eval/IntegerConstant.h"
#include "include/eval/Assignment.h"
#include "include/eval/RvalVariable.h"
#include "include/eval/operators/Add.h"
#include "include/eval/operators/Minus.h"
#include "include/eval/operators/Multiply.h"
#include "include/eval/arrays/Array.h"
#include "include/eval/arrays/GetFromArray.h"


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

int main() {

    std::vector<std::unique_ptr<bcc::Term>> statements;

    statements.emplace_back(std::make_unique<bcc::Assignment>("a1", std::make_unique<bcc::IntegerConstant>(10)));

    statements.emplace_back(std::make_unique<bcc::Assignment>("b1", std::make_unique<bcc::IntegerConstant>(20)));

    statements.emplace_back(std::make_unique<bcc::Assignment>("c1", std::make_unique<bcc::IntegerConstant>(6)));

    statements.emplace_back(std::make_unique<bcc::Assignment>(
            "d1",
            std::make_unique<bcc::operators::Minus> (
            std::make_unique<bcc::operators::Add>(
                    std::make_unique<bcc::operators::Multiply>(
                            std::make_unique<bcc::RvalVariable>("a1"),
                            std::make_unique<bcc::IntegerConstant>(4)),
                    std::make_unique<bcc::RvalVariable>("b1")),
            std::make_unique<bcc::RvalVariable>("c1"))));

    std::vector<std::unique_ptr<bcc::Term>> arrayContent;
    arrayContent.emplace_back(std::make_unique<bcc::IntegerConstant>(1));
    arrayContent.emplace_back(std::make_unique<bcc::IntegerConstant>(2));
    arrayContent.emplace_back(std::make_unique<bcc::IntegerConstant>(3));

    statements.emplace_back(std::make_unique<bcc::Assignment>(
            "arr1",
            std::make_unique<bcc::arrays::Array>(std::move(arrayContent))));

    statements.emplace_back(std::make_unique<bcc::Assignment>("arridx1", std::make_unique<bcc::IntegerConstant>(2)));

    statements.emplace_back(std::make_unique<bcc::Assignment>(
            "arrContent1",
            std::make_unique<bcc::arrays::GetFromArray> (
                    std::make_unique<bcc::operators::Minus>(
                            std::make_unique<bcc::RvalVariable>("arridx1"),
                            std::make_unique<bcc::IntegerConstant>(1)),
                    std::make_unique<bcc::RvalVariable>("arr1")
                    )));

    std::ifstream sourceTmpl{"ext_include/MainTmpl.cpp"};
    std::filesystem::remove_all("tmp");
    std::filesystem::create_directory("tmp");
    std::filesystem::copy_file("ext_include/Definitions.h", "tmp/Definitions.h");
    std::ofstream sourceGenerated{"tmp/generated_main.cpp"};

    std::string line;

    while (std::getline(sourceTmpl, line)) {
        if (std::string::size_type pos = line.find("/** MAIN_STUFF **/"); pos != std::string::npos) {
            sourceGenerated << std::string(pos, ' ') << bcc::Print{std::make_unique<bcc::RvalVariable>("arrContent1")} << std::endl;
        } else if (std::string::size_type pos1 = line.find("/** STATEMENTS **/"); pos1 != std::string::npos) {
            std::string spaces(pos1, ' ');
            for (auto & cur : statements) {
                sourceGenerated << spaces << *cur << std::endl;
            }
        } else {
            sourceGenerated << line << std::endl;
        }
    }

    exec("g++ tmp/generated_main.cpp -O0 -o tmp/generated_main");
    std::cout << exec("./tmp/generated_main");
    return 0;
}
