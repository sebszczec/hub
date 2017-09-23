#!/bin/bash

gcov src/commands/*.cpp --object-directory src/commands/CMakeFiles/commands.dir/
gcov src/database/*.cpp --object-directory src/database/CMakeFiles/database.dir/
gcov src/machine/*.cpp --object-directory src/machine/CMakeFiles/machine.dir/
gcov src/network/*.cpp --object-directory src/network/CMakeFiles/network.dir/
gcov src/tools/*.cpp --object-directory src/tools/CMakeFiles/tools.dir/

gcovr . --xml-pretty > ut_cobertura.xml

rm *.gcov

