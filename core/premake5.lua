project "core"
   kind "StaticLib"
   language "C"
   staticruntime "off"

   pchheader "pch.h"
   pchsource "src/pch.c"

   files { "src/**.h", "src/**.c" }

   includedirs
   {
      "src"
   }

   targetdir (outputdir .. "/%{prj.name}")
   objdir (intdir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"