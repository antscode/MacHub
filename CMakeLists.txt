cmake_minimum_required(VERSION 2.8)

# See: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
SET(CMAKE_CXX_FLAGS "-Ofast")

add_application(MacHub
	MacHub.cpp
	size.r
	weather-icons.r
	weather-icons-bw.r
	Weather.cpp
	Module.h
	Facebook.cpp
	Facebook.r
	Util.h
	Util.cpp
	Prefs.cpp
	Prefs.h
	Prefs.r
	IconListDef.cpp
	ModuleManager.cpp
)

target_link_libraries(MacHub MacHTTP mbedtls mbedx509 mbedcrypto MacTCPHelper jsoncpp)