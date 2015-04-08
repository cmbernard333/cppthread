-- A solution contians project, and defines the available configurations
solution "CppThread"
    configurations { "Debug", "Release" }
    -- A project defines one build target
    project "CppThread"
        kind "SharedLib"
        language "C++"
        buildoptions { "-std=c++0x" }
        -- place where sources are -- should also include header files for vs2013
        files {  "include/cppthread.h" }
        -- the output location
        location "build"
        -- includes 
        includedirs { "include" }
        
        if os.get() == "windows" then
            files { "src/cppthreadwin.cpp" }
            defines { "windows", "win32", "WINDOWS" }
        else
            files { "src/cppthreadposix.cpp" }
            links { "pthread" }
            defines { "unix", "UNIX", "linux", "LINUX" }
        end

        configuration "Debug"
            defines { "DEBUG " }
            flags { "Symbols" }

        configuration "Release"
            flags { "Optimize" }
