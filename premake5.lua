workspace "CodilityPractice"
	architecture "x64"
	startproject "CodilityPractice"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
		
project "CodilityPractice"
	location "CodilityPractice"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
	
		
		