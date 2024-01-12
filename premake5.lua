workspace "renderer"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "viewer"

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
intdir = "%{wks.location}/bin/int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "core"
include "viewer"
