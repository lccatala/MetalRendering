workspace "Metal"
   cppdialect "C++20"
   configurations { "Debug", "Release" }
   flags { "MultiProcessorCompile" }
   toolset ("clang")

   defines {
       -- "NS_PRIVATE_IMPLEMENTATION",
       -- "CA_PRIVATE_IMPLEMENTATION",
       -- "MTL_PRIVATE_IMPLEMENTATION"
   }

   includedirs {
       "/usr/local/include",
       "vendor/metal-cpp",
       "vendor/metal-cpp-extensions",
   }

   headerdir "vendor/metal-cpp"

   libdirs {
       "/usr/local/lib",
   }


   links {
       "Cocoa.framework",
       "Foundation.framework",
       "CoreGraphics.framework",
       "QuartzCore.framework",
       "Metal.framework",
       "MetalKit.framework",
   }

project "Core"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { 
       "*.cpp",
       "%{prj.name}/src/**.h",
       "%{prj.name}/src/**.cpp",
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
