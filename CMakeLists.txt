cmake_minimum_required(VERSION 3.15)
project(AppwriteSDK CXX)

set(CMAKE_CXX_STANDARD 17)

# Dependencies
find_package(CURL REQUIRED)
find_package(Boost REQUIRED COMPONENTS asio beast)

set(SRCS
    src/Appwrite.cpp
    src/services/Account.cpp
    src/services/Query.cpp
    src/services/Databases.cpp
    src/services/Messaging.cpp
    src/services/Storage.cpp
    src/services/Health.cpp
    src/Utils.cpp
    src/Validator.cpp
)

add_library(AppwriteSDK STATIC ${SRCS})

include_directories(include)

target_link_libraries(AppwriteSDK
    CURL::libcurl
    Boost::asio
    Boost::beast
)

set_target_properties(AppwriteSDK PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

set(HEADERS
    include/Appwrite.hpp
    include/classes/Account.hpp
    include/classes/Query.hpp
    include/classes/Databases.hpp
    include/classes/Messaging.hpp
    include/classes/Storage.hpp
    include/classes/Health.hpp
    include/config/Config.hpp
    include/enums/HttpStatus.hpp
    include/exceptions/AppwriteException.hpp
    include/Utils.hpp
    include/Validator.hpp
)

install(DIRECTORY include/ DESTINATION /usr/local/include/AppwriteSDK)
install(FILES ${HEADERS} DESTINATION /usr/local/include/AppwriteSDK)
install(TARGETS AppwriteSDK ARCHIVE DESTINATION /usr/local/lib)

# Example executable
add_executable(updateMessages examples/messaging/messages/updateMessages.cpp)
target_link_libraries(updateMessages PRIVATE AppwriteSDK CURL::libcurl Boost::asio Boost::beast)

# Custom target to build+run
add_custom_target(runUpdateMessages
    COMMAND updateMessages
    DEPENDS updateMessages
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Build + Run updateMessages"
)
