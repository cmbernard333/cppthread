cmake_minimum_required(VERSION 3.0)
project(CppThreadTest)
set(SRC_DIR ${CppThreadTest_SOURCE_DIR}/src)

# set compiler flags
if (APPLE OR CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64 -fno-exceptions -fno-rtti -fPIC -fno-omit-frame-pointer -momit-leaf-frame-pointer" )
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# grab CppThreadLib include directory
include_directories(${CppThreadLib_SOURCE_DIR}/include)
# grab the local directory
include_directories(${CppThreadTest_SOURCE_DIR}/include)
# glob the headers
file(GLOB CppThreadTest_Headers ${CppThreadTest_SOURCE_DIR}/include/*/*.h*)
source_group( "Headers" FILES ${CppThreadTest_Headers})
# generate the executable
add_executable(CppThreadTest ${SRC_DIR}/cppthreadtest.cpp ${CppThreadTest_Headers})
# link the CppThreadLibrary library
target_link_libraries(CppThreadTest CppThreadLib)
