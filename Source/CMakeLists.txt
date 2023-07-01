add_library(
    LibJsonRpc_Source

    LibJsonRpc.hpp
    LibJsonRpc/Request/Request.hpp
    LibJsonRpc/Server/Server.hpp

    LibJsonRpc/Server/Server.cpp
)
target_include_directories(
        LibJsonRpc_Source

        PUBLIC
        ../Source
)
include(FetchContent)

FetchContent_Declare(
    daw-json-link
    URL https://github.com/beached/daw_json_link/archive/refs/tags/v3.17.2.zip
)
FetchContent_Declare(
    libcurl
    URL https://github.com/curl/curl/archive/refs/tags/curl-8_1_2.zip
)
FetchContent_MakeAvailable(
    daw-json-link
    libcurl
)
target_link_libraries(
    LibJsonRpc_Source

    PUBLIC
    libcurl
    daw::daw-json-link
)
if(PROJECT_IS_TOP_LEVEL)
    add_executable(
        LibJsonRpc_Tests

        LibJsonRpc/Request/Request.test.cpp
        LibJsonRpc/Server/Server.test.cpp
    )
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    target_link_libraries(
        LibJsonRpc_Tests

        PRIVATE
        LibJsonRpc_Source
        gmock_main
    )
    enable_testing()
endif()