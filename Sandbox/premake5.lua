project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "off"

	targetdir("%{wks.location}/bin/" .. OutputDir .. "%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. OutputDir .. "%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/HavocLearn/src",
		"%{wks.location}/HavocLearn/dependencies/eigen/",
	}

	links
	{
		"HavocLearn"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
