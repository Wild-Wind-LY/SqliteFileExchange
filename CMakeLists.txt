cmake_minimum_required(VERSION 3.15)

project(SqliteFileExchange VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(CPM_PATH "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
if(NOT EXISTS ${CPM_PATH})
    file(DOWNLOAD 
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.0/CPM.cmake
        ${CPM_PATH}
        SHOW_PROGRESS
    )
endif()
include(${CPM_PATH})

if(WIN32)
    set(SQLite3_INCLUDE_DIR "D:/ProjectFiles/CppProject/GitHub/sqlite3/include")
    set(SQLite3_LIBRARY "D:/ProjectFiles/CppProject/GitHub/sqlite3/lib/libsqlite3.a")
endif()



# 添加需要的库
CPMAddPackage("gh:gabime/spdlog@1.15.2")
CPMAddPackage("gh:fnc12/sqlite_orm@1.9.1")
CPMAddPackage(
    NAME range-v3
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/range-v3
    VERSION 0.12.0
    OPTIONS
        "RANGE_V3_INCLUDE_TESTS OFF"
        "RANGE_V3_INCLUDE_BENCHMARKS OFF"
        "RANGE_V3_INCLUDE_EXAMPLES OFF"
)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

aux_source_directory(src SRC_LIST)

add_executable(SqliteFileExchange ${SRC_LIST})

if(WIN32)
    find_package(SQLite3 REQUIRED PATHS "D:/ProjectFiles/CppProject/GitHub/sqlite3/lib/cmake/sqlite3")
else()
    find_package(SQLite3 REQUIRED)
endif()

# 查找并链接依赖库
# find_package(fmt REQUIRED)
# find_package(glfw REQUIRED)

# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt glfw::glfw)
target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog SQLite::SQLite3 sqlite_orm range-v3)