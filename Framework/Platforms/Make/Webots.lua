local extern_dir = "../../../Extern"

-- NaoTH controller running in the Cyberbotics Webots simulator
project "Webots"
  kind "ConsoleApp"
  language "C++"
  
  
  ---------------------- WEBOTS_HOME -----------------------------
  local webotsHome = os.getenv("WEBOTS_HOME")

  -- default value for linux
  if webotsHome == nil and not os.is("windows") then
	  webotsHome = "/usr/local/webots";
  end
  
  -- check if the directory can be opened by lua and warn if not
  if not os.isdir(webotsHome) then
    print("WARN: Enviroment variale WEBOTS_HOME was not set or unable to access directory (" .. webotsHome .. ")!")
	  print("no compilation for Webots possible.\n")
  else
  
    -- include core
    if(CORE_PATH == nil or CORE == nil) then
      print("WARNING: no path for the core is set")
	  CORE_PATH = "."
	  CORE = ""
    end
    
    
    print("Generating files for webots")
    includedirs {
      "../Source/", 
	  CORE_PATH,
	  "../../NaoTH-Tools/Source/",
      webotsHome .. "/include/controller/c/",
      "../Lib/win32/include/", 
      extern_dir .. "/include/",
      extern_dir .. "/include/glib-2.0/",
	  extern_dir .. "/lib/glib-2.0/include/"}
    
    libdirs {webotsHome .. "/lib/"}
    
    files{"../Source/Webots/**.cpp", "../Source/Webots/**.h"}
    
    links {CORE, "NaoTH-Commons", "Controller",
    "glib-2.0",
	  "gio-2.0",
	  "gobject-2.0",
	  "protobuf"}
    
    targetname "nao_team_0"
    targetdir "../nao_robocup/controllers/nao_team_0/"
    
    postbuildcommands {
      "premake4 webots_copy"
    }
    
    configuration {"linux"}
      linkoptions {"-Wl,-rpath \"" .. path.getabsolute("../../../Extern/lib/") .. "\""}
  end -- if WEBOTS_HOME set
  ----------------------------------------------------------------
     
-- END Webots
