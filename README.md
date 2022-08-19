# div.cpp.base.pbni-framework-usage-example
Example of how to use https://github.com/informaticon/lib.cpp.base.pbni-framework

## Setup
Clone the repo using ``--recursive``. Or clone it normally and run ``git submodule update --init --recursive`` after. Then create a build or bin folder, cd into it and run ``cmake .. -G "Visual Studio 17 2022" -A Win32``. Open the newly crated Visual Studio Solution and build libUsageExample. You should now have an `out` folder with a DLL that you can import into PowerBuilder.\
If you build `INSTALL` it will copy the DLL into the A3 Folder.
