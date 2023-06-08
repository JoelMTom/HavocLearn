project "HavocLearn"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	targetdir("%{wks.location}/bin/" .. OutputDir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"src",
		"dependencies/eigen/",
		"%{IncludeDirs.Eigen}",
	}
	
	filter "system:windows"
		systemversion	"latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
