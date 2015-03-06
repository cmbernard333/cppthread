-- A solution contians project, and defines the available configurations
solution "CppThread"
    configurations { "Debug", "Release" }
    -- A project defines one build target
    project "CppThread"
        -- define where lua is -- MODIFY THIS
        kind "StaticLib"
        language "C++"
        -- place where sources are
        files {  "src/**.cpp" }
        -- the output location
        location "build"
        -- includes 
        includedirs { "include" }
        -- linking
        links { "pthread" }

        if os.get() == "windows" then
            defines { "windows", "win32", "WINDOWS" }
        else
            defines { "unix", "UNIX", "linux", "LINUX" }
        end

        configuration "Debug"
            defines { "DEBUG " }
            flags { "Symbols" }

        configuration "Release"
            flags { "Optimize" }
