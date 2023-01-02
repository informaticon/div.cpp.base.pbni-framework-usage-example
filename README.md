# div.cpp.base.pbni-framework-usage-example
Example of how to use https://github.com/informaticon/lib.cpp.base.pbni-framework

## Setup
If you havent cloned this repo with `--recursive` you need to run `git submodule update --init --recursive ` to clone the submodules.
Start by installing [vcpkg](https://vcpkg.io/en/getting-started.html).\
Then install the pacakges needed for the PBNI Framework:
```ps1
vcpkg install --triplet=x86-windows-static boost-stacktrace boost-utility boost-multiprecision
```

Clone this repo using ``--recursive``. Or clone it normally and run ``git submodule update --init --recursive`` after. Then cd into the new directory. create a build folder and run CMake:
```ps1
mkdir build; cd build

cmake .. -A Win32 `
         -DVCPKG_TARGET_TRIPLET=x86-windows-static `
         -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

Open the newly crated Visual Studio Solution and build `libUsageExample`. You should now have an `out` folder with a DLL that you can import into PowerBuilder.\
If you build `INSTALL` it will copy the DLL into the A3 Folder.
