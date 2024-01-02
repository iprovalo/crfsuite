#!/usr/local/bin/bash
#use bash 4 and above

lib_name="crfsuite"
base_dir=/Users/iprovalov/stash/crfsuite/build-ios

#declare -A targets=( ["aarch64-linux-android"]="arm64-v8a" ["armv7a-linux-androideabi"]="armeabi-v7a" ["i686-linux-android"]="x86" ["x86_64-linux-android"]="x86_64" )

#declare -A targets=(  ["x86_64-darwin"]="darwin_x86_64" )
declare -A targets=(  ["arm64-iphoneos"]="iphoneos_arm64" )

echo "${!targets[@]}"

for TARGET in "${!targets[@]}"
do
  echo "Installing from "$TARGET

#  if [ ! -d $TARGET ];
#  then
#    mkdir $TARGET
#  fi
#
#  cd $TARGET

#  VERSION=0.12
#  if [ ! -d $lib_name ];
#  then
#    #TODO: change to the released tag with patches? -b $VERSION
#    git clone https://github.com/chokkan/$lib_name.git
#    cd $lib_name
#    #rename libtoolize to glibtoolize on Mac:
#    mv autogen.sh autogen.txt
#    sed 's/^libtoolize/glibtoolize/g' autogen.txt > autogen.sh
#    chmod 755 autogen.sh
#  else
#    cd $lib_name
#  fi
#  export NDK=/Users/iprovalov/Library/Android/sdk/ndk/25.1.8937393
#  # Only choose one of these, depending on your build machine...
#  export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/darwin-x86_64
#  # Set this to your minSdkVersion.
#  export API=21
#  # Configure and build.
#  export AR=$TOOLCHAIN/bin/llvm-ar
#  export AS=$CC
#  export LD=$TOOLCHAIN/bin/ld
#  export RANLIB=$TOOLCHAIN/bin/llvm-ranlib
#  export STRIP=$TOOLCHAIN/bin/llvm-strip
#  #target specific commands:
#  export CC=$TOOLCHAIN/bin/$TARGET$API-clang
#  export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++

# TODO: cannot resolve the soname issue which doesn't work on Mac for now:
#  compiler=$TARGET$API-clang
#  if [[ "$TARGET" == *"darwin"* ]]; then
#    compiler="clang"
#  fi
#  export CC=$TOOLCHAIN/bin/$compiler
#  export CXX=$TOOLCHAIN/bin/$compiler++

  ./autogen.sh
  OPTS=""
  if [[ "$TARGET" == *"arch"* ]] || [[ "$TARGET" == *"arm"* ]]; then
    #disable sse for arch and arm architectures
    OPTS="--disable-sse2"
  fi
  ./configure --host $TARGET --prefix $base_dir/$lib_name-libs-distribution/"${targets[$TARGET]}" --with-liblbfgs=$base_dir/liblbfgs-libs-distribution/"${targets[$TARGET]}" $OPTS
  make
  make install
  echo "COMPLETED " $TARGET
  cd ../../

done


