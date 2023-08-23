cmake_minimum_required(VERSION 3.24)
project(bcc)

set(CMAKE_CXX_STANDARD 17)

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
        lib/eval/arrays/Array.cpp include/eval/arrays/Array.h lib/eval/arrays/GetFromArray.cpp include/eval/arrays/GetFromArray.h)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/ext_include $<TARGET_FILE_DIR:${PROJECT_NAME}>/ext_include)