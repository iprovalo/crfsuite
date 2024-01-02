#!/bin/bash

set -e
TEAM_ID="Ivan Provalov"

# This will configure cmake build.  After this step, open the project in XCode and you may need to make some changes for the build time:
#1. Build Settings -> Other Linker Flags - make sure has the file names as crfsuitelib for @rpath
#2. PROJECT LEVEL - Build Settings - Build Active Architecture Only - NO
#3. Build crfsuitelib target
#4. Open build-os folder containing dylib in Finder
#5. Drag and drop the dylib in XCode (Do not copy) to you target app project
#6. Make sure these are now linked to the Target in both Binary and Embed Libraries under Build Phases of the specific target
#7. Make sure these are findable - Build Settings of the specific target - Header and Library Search Paths include recursive references to the header folder src and build-ios folder of the sentencepiece


if [ "$1" == "help" ]; then
  echo "Run bash ios_build.sh build clean"
  exit
fi

if [ "$1" == "build" ] || [ "$1" == "configure" ]; then
echo "Running CMake configuration..."

# clean up old builds
if [ "$2" == "clean" ]; then rm -Rf build-ios; fi

# generate new builds
cmake -Bbuild-ios -GXcode -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=11.0 \
    -DCMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM="$TEAM_ID"
fi