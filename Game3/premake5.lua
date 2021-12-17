workspace "Game"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	location "build"
	characterset "MBCS"
	startproject "Game"

	filter "configurations:Debug"
		symbols	"on"

project "Game"
	kind "WindowedApp"
	debugdir "Game"

	files {
		"Game/Source/**.cpp",
		"Game/Source/**.h",
		"Game/Data/Shaders/**.vert",
		"Game/Data/Shaders/**.frag",
		"premake5.lua",
		"GenerateProjectFiles.bat",
	}

	includedirs {
		"Game/Source/",
		"Framework/Source/",
	}

	links {
		"Framework",
		"opengl32",
	}

project "Framework"
    kind "StaticLib"
    
    files {
		"Framework/Source/**.cpp",
		"Framework/Source/**.h",
		"Framework/Libraries/imgui/*.cpp",
		"Framework/Libraries/imgui/*.h",
		"Framework/Libraries/stb/*.h",
		"Framework/Libraries/rapidjson/**.h",
    }

	includedirs {
		"Framework/Source/",
	}
