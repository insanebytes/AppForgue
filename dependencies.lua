IncludeDir = {}
IncludeDir["imgui"] = "%{wks.location}/AppForgue/vendor/imgui"
IncludeDir["glfw"] = "%{wks.location}/AppForgue/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/AppForgue/vendor/glad/include"
IncludeDir["glm"] = "%{wks.location}/AppForgue/vendor/glm"

-- Windows
Library = {}
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"