project "viewer"
   language "C"
   staticruntime "off"

   files { "src/**.h", "src/**.c" }

   includedirs
   {
      "src",

	  -- Include Core
	  "../core/src"
   }

   links
   {
      "core"
   }

   targetdir (outputdir .. "/%{prj.name}")
   objdir (intdir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       kind "ConsoleApp"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       kind "ConsoleApp"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       kind "WindowedApp"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"