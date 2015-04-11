cmake_minimum_required(VERSION 3.0)
project(CppThread)
set ( CppThread_VERSION_MAJOR 1 )
set ( CppThread_VERSION_MINOR 0 )
set ( CMAKE_VERBOSE_MAKEFILE on )

# set defines
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
	add_definitions(-Dwindows -Dwin32 -DWINDOWS)
else()
	add_definitions(-Dunix -DUNIX -Dlinux -DLINUX)
endif()

add_subdirectory(cppthread)
# add_subdirectory(test)
