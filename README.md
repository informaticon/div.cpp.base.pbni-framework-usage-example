# div.cpp.base.pbni-framework-usage-example
Example of how to use https://github.com/informaticon/lib.cpp.base.pbni-framework

## Prerequisites
Firstly you need to install [Visual Studio](https://visualstudio.microsoft.com/downloads/), [Git](https://git-scm.com/downloads), [cmake](https://cmake.org/install/) and [vcpkg](https://vcpkg.io/en/getting-started.html).\
Then install the pacakges needed for the PBNI Framework:
```ps1
vcpkg install --triplet=x86-windows-static boost-stacktrace boost-utility boost-multiprecision
```

## Setup
Clone this repo using ``--recursive``. Or clone it normally and run ``git submodule update --init --recursive`` after. Then cd into the new directory. create a build folder and run CMake:
```ps1
mkdir build; cd build

cmake .. -A Win32 `
         -DVCPKG_TARGET_TRIPLET=x86-windows-static `
         -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

Open the newly crated Visual Studio Solution and build `libUsageExample`. You should now have an `out` folder with a DLL that you can import into PowerBuilder.\
If you build `INSTALL` it will copy the DLL into the A3 Folder.
