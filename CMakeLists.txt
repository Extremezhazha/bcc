cmake_minimum_required(VERSION 3.24)
project(bcc)

set(CMAKE_CXX_STANDARD 17)


find_package(BISON)
find_package(FLEX)

bison_target(Parser parse/bcc.y ${CMAKE_CURRENT_BINARY_DIR}/BccParser.cpp)
flex_target(Lexer parse/bcc.l ${CMAKE_CURRENT_BINARY_DIR}/BccLexer.cpp)

add_flex_bison_dependency(Lexer Parser)

add_library(bccparse
        STATIC
        ${FLEX_Lexer_OUTPUTS}
        ${BISON_Parser_OUTPUTS} lib/ast/ASTNode.cpp include/ast/ASTNode.h lib/ParserDriver.cpp include/ParserDriver.h parse/BccLexer.h lib/ast/nodes/ID.cpp include/ast/nodes/ID.h lib/REPLDriver.cpp include/REPLDriver.h include/ASTNodeAcceptor.h include/ast/nodes/BinaryArithmeticOperator.h)

target_include_directories(bccparse PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(bccparse PUBLIC include parse)

add_executable(bcc main.cpp
        include/eval/Term.h
        include/eval/IntegerConstant.h
        lib/eval/IntegerConstant.cpp
        lib/eval/Term.cpp
        include/eval/Print.h
        lib/eval/Print.cpp
        include/eval/Assignment.h
        lib/eval/Assignment.cpp
        include/eval/RvalVariable.h
        lib/eval/RvalVariable.cpp
        lib/eval/operators/Add.cpp
        include/eval/operators/Add.h
        lib/eval/operators/Minus.cpp
        include/eval/operators/Minus.h
        include/eval/operators/Multiply.h
        lib/eval/operators/Multiply.cpp
        lib/eval/arrays/Array.cpp include/eval/arrays/Array.h lib/eval/arrays/GetFromArray.cpp include/eval/arrays/GetFromArray.h lib/ast/ASTNode.cpp include/ast/ASTNode.h lib/ParserDriver.cpp include/ParserDriver.h lib/ast/nodes/Literal.cpp include/ast/nodes/Literal.h parse/BccLexer.h lib/ast/nodes/ID.cpp include/ast/nodes/ID.h lib/REPLDriver.cpp include/REPLDriver.h include/ASTNodeAcceptor.h include/ast/nodes/BinaryArithmeticOperator.h include/eval/operators/Divide.h lib/eval/operators/Divide.cpp)

target_link_libraries(bcc bccparse)
target_include_directories(bcc PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/ext_include $<TARGET_FILE_DIR:${PROJECT_NAME}>/ext_include)