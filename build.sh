BUILD_DIR="build"

ls $BUILD_DIR || mkdir $BUILD_DIR
cd $BUILD_DIR

cmake  ..
cmake --build .