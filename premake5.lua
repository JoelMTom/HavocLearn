
function link_to(lib)
	links(path.getbasename(lib))
	includedirs (lib .. "/src")
end

function link_header_only_lib (lib)
	includedirs (lib)
end

workspaceName = path.getbasename(os.getcwd())


workspace (workspaceName)

	configurations { "Debug", "Release" }
	architecture  "x86_64"

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "Off"
		optimize "On"

	filter {}

	startProjectName = "Sandbox"

	if(os.isdir(startProjectName)) then
		startproject (startProjectName)
		print("Project: " .. startProjectName)
		include (startProjectName)
	end
	
group "Core"
	folders = os.matchdirs("*")
	for _, folderName in pairs(folders) do
		if (string.startswith("_", folderName ) == false and string.startswith (".", folderName) == false) then
			if (os.isfile(folderName .. "/premake5.lua") and path.getbasename(folderName) ~= startProjectName) then
				print ("Project: " .. folderName)
				include (folderName)
			end
		end
	end
group ""

group "Dependencies"
	folders = os.matchdirs("**/dependencies/*")
	for _, folderName in pairs(folders) do
		if (string.startswith("_", folderName ) == false and string.startswith (".", folderName) == false) then
			if (os.isfile(folderName .. "/premake5.lua")) then
				print ("Additional library: " .. path.getbasename(folderName))
				include (folderName)
			end
		end
	end
group ""




		
