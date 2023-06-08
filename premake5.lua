include "Dependencies.lua"

workspace "HavocLearn"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

	OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	group "HavocLearn"
		include "HavocLearn"
	group ""

	group "Sandbox"
		include "Sandbox"
	group ""
