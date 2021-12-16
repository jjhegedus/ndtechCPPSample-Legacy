#!/bin/bash
source build.sh "$@"

# normally `mabu --invoke` is sufficient but it does not know about 3rd-party libs

BUILD_SPEC=`mabu -q --print-spec`

if [ `uname` = "Darwin" ]; then
DYLD_LIBRARY_PATH=$GLFW_LIBS:$DYLD_LIBRARY_PATH .out/$BUILD_SPEC/ndtechSample
elif [ `uname` = "Linux" ]; then
LD_LIBRARY_PATH=$GLFW_LIBS:$LD_LIBRARY_PATH .out/$BUILD_SPEC/ndtechSample
else
PATH=$GLFW_LIBS:$PATH .out/$BUILD_SPEC/ndtechSample
fi



