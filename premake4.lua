-- A solution contians project, and defines the available configurations
solution "CppThread"
    configurations { "Debug", "Release" }
    -- A project defines one build target
    project "CppThread"
        kind "StaticLib"
        language "C++"
        -- place where sources are -- should also include header files for vs2013
        files {  "src/**.cpp", "include/**.hpp", "include/**.h" }
        -- the output location
        location "build"
        -- includes 
        includedirs { "include" }
        
        if os.get() == "windows" then
            defines { "windows", "win32", "WINDOWS" }
        else
	    -- linking
            links { "pthread" }
            defines { "unix", "UNIX", "linux", "LINUX" }
        end

        configuration "Debug"
            defines { "DEBUG " }
            flags { "Symbols" }

        configuration "Release"
            flags { "Optimize" }
