cmake_minimum_required(VERSION 2.8)

# See: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
SET(CMAKE_CXX_FLAGS "-Ofast")

add_application(MacHub
	MacHub.cpp
	size.r
	weather-icons.r
	weather-icons-bw.r
	Facebook.r
	Util.cpp
	Prefs.cpp
	Prefs.h
	Prefs.r
	Keys.cpp
	IconListDef.cpp
	ModuleManager.cpp
	Comms.cpp
	Modules/OAuthModule.cpp
	Modules/Facebook.cpp
	Modules/Google.cpp
	Modules/Weather.cpp
)

target_link_libraries(MacHub MacHTTP mbedtls mbedx509 mbedcrypto MacTCPHelper jsoncpp)