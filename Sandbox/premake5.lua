baseName = path.getbasename(os.getcwd())

project (baseName)
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "off"

	targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}" 
	objdir "%{wks.location}/build/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}" 

	files { "src/**.h", "src/**.cpp"}

	print("Sandbox: Linking Header only library: ../HavocLearn/dependencies/eigen")
	link_header_only_lib ("../HavocLearn/dependencies/eigen")
	link_to("../HavocLearn")

