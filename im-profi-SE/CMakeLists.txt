cmake_minimum_required (VERSION 3.8)

project ("im-profi-SE")

add_executable (im-profi-SE "im-profi-SE.cpp" "im-profi-SE.h")

find_package(Poco REQUIRED COMPONENTS Foundation Net Util )
add_executable(serverMainServer im-profi-SE/Server/main.cpp)
add_library(message-objSH
OBJECT
    im-profi-SE/Server/Handlers.h
    im-profi-SE/Server/Handlers.cpp
)