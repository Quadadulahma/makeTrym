#pragma once

#ifdef PLATFORM_WINDOWS
	#include <winsock2.h>
#elif PLATFROM_UNIX
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>.
#endif

#include <memory>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>

#include "depend/glad/include/glad/glad.h"
#include "GLFW/glfw3.h"

#include "depend/src/ShaderProgram.h"

