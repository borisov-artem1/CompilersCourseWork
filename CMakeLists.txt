cmake_minimum_required(VERSION 3.30)
project(Compilers)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(antlr/antlr4/runtime/Cpp)

set(LLVM_DIR "/usr/lib/llvm-18/lib/cmake/llvm")

find_package( LLVM CONFIG REQUIRED )

add_executable(${PROJECT_NAME}
        #  main.cpp
        compiler/oberonBaseListener.cpp
        compiler/oberonBaseListener.h
        compiler/oberonLexer.cpp
        compiler/oberonLexer.h
        compiler/oberonListener.cpp
        compiler/oberonListener.h
        compiler/oberonParser.cpp
        compiler/oberonParser.h
        compiler/main.cpp
        compiler/oberonBaseVisitor.h
        compiler/oberonVisitor.cpp
        compiler/oberonBaseVisitor.cpp
        compiler/oberonVisitor.h
)

target_include_directories( ${PROJECT_NAME} PRIVATE antlr/antlr4/runtime/Cpp/runtime/src )

llvm_map_components_to_libnames(llvm_libs
        core
        orcjit
        nativecodegen
        support
        target
)

target_include_directories( ${PROJECT_NAME} SYSTEM PUBLIC ${LLVM_INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME}
        PUBLIC
        ${llvm_libs}
        #antlr4_shared
        antlr4_static
)
