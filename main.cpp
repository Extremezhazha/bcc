#include "REPLDriver.h"


int main() {
    bcc::REPLDriver driver{std::cin, std::cout};
    driver.run();
    return 0;
}
