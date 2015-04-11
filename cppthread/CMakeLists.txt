cmake_minimum_required( VERSION 3.0 )
project ( CppThreadLib )
set ( CppThreadLib_VERSION_MAJOR CppThread_VERSION_MAJOR )
set ( CppThreadLib_VERSION_MINOR CppThread_VERSION_MINOR )
# set the source directory
set ( SRC_DIR ${CppThreadLib_SOURCE_DIR}/src )

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

# grab the local includes
include_directories( ${CppThreadLib_SOURCE_DIR}/include )
file( GLOB CppThreadLibHeaders ${CppThreadLib_SOURCE_DIR}/include/*/*.h* )
source_group( "Headers" FILES ${CppThreadLibHeaders})
# create the library
# need to select the right file
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
	set ( CppThreadLibImpl ${SRC_DIR}/cppthreadwin.cpp )
else()
	set ( CppThreadLibImpl ${SRC_DIR}/cppthreadposix.cpp )
endif()
add_library( CppThreadLib SHARED ${CppThreadLibImpl} ) 
