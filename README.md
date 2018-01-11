# MacHub
MacHub brings modern Web Notifications to your classic Mac.

## Building & Installing

MacHub requires Retro68 for compilation, and the following libraries:

* [MacTCPHelper](https://github.com/antscode/MacTCPHelper)
* [mbedtls-Mac-68k](https://github.com/antscode/mbedtls-Mac-68k)
* [MacHTTP](https://github.com/antscode/MacHTTP)
* [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

First build and install the above libraries, then execute these commands from the top level of the MacHub directory:

    cd ..
    mkdir MacHub-build
    cd MacHub-build
    cmake ../MacHub -DCMAKE_TOOLCHAIN_FILE=<<YOUR_PATH_TO_Retro68-build>>/toolchain/m68k-apple-macos/cmake/retro68.toolchain.cmake
    make install

This will build the application in the MacHub-build directory.