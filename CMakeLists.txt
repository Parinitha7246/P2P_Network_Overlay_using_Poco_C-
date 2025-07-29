# # cmake_minimum_required(VERSION 3.10)
# # project(P2POverlay)

# # set(CMAKE_CXX_STANDARD 17)

# # set(CMAKE_TOOLCHAIN_FILE "D:/MatreComm/project/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
# # include_directories(include)

# # find_package(Poco REQUIRED COMPONENTS Foundation Net Util JSON XML)

# # add_executable(p2p
# #     src/main.cpp
# #     src/Node.cpp
# # )

# # target_link_libraries(p2p PRIVATE Poco::Foundation Poco::Net Poco::Util Poco::JSON Poco::XML)
# #----------------------------------------------DAY 1--------------------------------------------------
# cmake_minimum_required(VERSION 3.10)
# project(P2POverlay)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_TOOLCHAIN_FILE "D:/MatreComm/project/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# include_directories(include)

# find_package(Poco REQUIRED COMPONENTS Foundation Net Util JSON XML)

# add_executable(p2p_server
#     src/main_server.cpp
#     src/Node.cpp
# )

# add_executable(p2p_client
#     src/main_client.cpp
#     src/Node.cpp
# )

# target_link_libraries(p2p_server PRIVATE Poco::Foundation Poco::Net Poco::Util Poco::JSON Poco::XML)
# target_link_libraries(p2p_client PRIVATE Poco::Foundation Poco::Net Poco::Util Poco::JSON Poco::XML)

#-----------------------------------------------------DAY 2------------------------------------------------
cmake_minimum_required(VERSION 3.10)
project(P2POverlay)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE "D:/MatreComm/project/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

include_directories(include)

find_package(Poco REQUIRED COMPONENTS Foundation Net Util JSON XML)

add_executable(p2p_server
    src/main_server.cpp
    src/Node.cpp
)

add_executable(p2p_client
    src/main_client.cpp
    src/Node.cpp
)

target_link_libraries(p2p_server PRIVATE Poco::Foundation Poco::Net Poco::Util Poco::JSON Poco::XML)
target_link_libraries(p2p_client PRIVATE Poco::Foundation Poco::Net Poco::Util Poco::JSON Poco::XML)

