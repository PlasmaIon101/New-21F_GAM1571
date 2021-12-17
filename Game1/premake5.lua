workspace "MyGame"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	location "build"
	characterset "MBCS"
	startproject "MyGame"

	filter "configurations:Debug"
		symbols "on"
	
project "MyGame"
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
			"Framework/Libraries/**.cpp",
			"Framework/Libraries/**.h"
	}

	includedirs {
		"Framework/Source/",
	}