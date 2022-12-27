# CMakeList.txt: CMake-Projekt für "makeTrym". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable(makeTrym "makeTrym.cpp" "makeTrym.h"  "depend/glad/include/glad/glad.h" "depend/glad/include/KHR/khrplatform.h" "depend/glad/src/glad.c" "depend/src/ShaderProgram.cpp" "depend/src/ShaderProgram.h" "depend/src/loading.cpp" "depend/src/loading.h" "depend/src/Entity/Entity.h" "depend/src/Entity/Entity.cpp"  "depend/src/Texture.h" "depend/src/Texture.cpp" "depend/stbi_image/stb_image.h" "depend/stbi_image/stb_image.cpp"     "depend/src/Game.cpp" "depend/src/Game.h")
# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory ("depend/glfw")
target_link_libraries(makeTrym glfw)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(makeTrym ws2_32)
  add_definitions(-DPLATFORM_WINDOWS)
elseif(CMAKE_HOST_UNIX)
	add_definitions(-DPLATFORM_UNIX)
endif()



find_package(OpenGL REQUIRED)

target_link_libraries(makeTrym OpenGL::GL)