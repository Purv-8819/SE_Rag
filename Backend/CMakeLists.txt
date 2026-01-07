cmake_minimum_required(VERSION 3.24)
project(GraphRagCpp)

set(CMAKE_CXX_STANDARD 20)

# 1. Find Standard CMake Packages
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(utf8proc CONFIG REQUIRED)

# 2. Find Poppler (Using PkgConfig as per vcpkg logs)
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER_CPP REQUIRED IMPORTED_TARGET poppler-cpp)


# 3. Include Directories
include_directories(include)

# 4. Define the SHARED CORE Library
add_library(core_lib
        src/core/Neo4jClient.cpp
        src/core/OllamaClient.cpp
        src/core/PdfParser.cpp
)

# Link libraries (Note: PkgConfig::POPPLER_CPP is the fix here)
target_link_libraries(core_lib PUBLIC
        cpr::cpr
        nlohmann_json::nlohmann_json
        PkgConfig::POPPLER_CPP
        fmt::fmt
        spdlog::spdlog
        utf8proc::utf8proc
)

# 5. Executable A: The Ingestion CLI
add_executable(ingest_tool src/ingestion/main.cpp)
target_link_libraries(ingest_tool PRIVATE core_lib)

# 6. Executable B: The Web Server
add_executable(web_server src/server/main.cpp)
target_link_libraries(web_server PRIVATE core_lib Drogon::Drogon)