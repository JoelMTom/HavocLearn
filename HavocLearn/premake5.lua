baseName = path.getbasename(os.getcwd())

project(baseName)
kind "StaticLib"
language "C++"
cppdialect "c++17"
staticruntime "off"

targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
objdir "%{wks.location}/build/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

files { "src/**.h", "src/**.cpp" }

folders = os.matchdirs("dependencies/*")
for _, folderName in pairs(folders) do
	if (string.startswith("_", folderName) == false and string.startswith(".", folderName) == false) then
		if (os.isfile(folderName .. "/premake5.lua")) then
			print("HavocLearn: Linking library " .. path.getbasename(folderName) .. ": " .. path.getrelative(os.getcwd(), folderName))
			link_to(path.getrelative(os.getcwd(), folderName))
		else
			print("HavocLearn: Linking header only library " .. path.getbasename(folderName) .. ": " .. path.getrelative(os.getcwd(), folderName))
			link_header_only_lib(path.getrelative(os.getcwd(), folderName))
		end
	end
end

filter "system:windows"
defines { "_WIN32" }
libdirs { "%{wks.location}/build/**" }
links { "raylib.lib" }
