﻿# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 3.8)

project ("makeTrym")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Schließen Sie Unterprojekte ein.
add_subdirectory ("makeTrym")

set_target_properties(makeTrym PROPERTIES OUTPUT_NAME "sling")
set_target_properties(makeTrym PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR} LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR} RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
