#!/bin/bash

APP_NAME="filex"
BUILD_DIR="build"

echo "🔨 Building FileX..."

mkdir -p $BUILD_DIR

g++ -std=c++17 src/*.cpp -o $BUILD_DIR/$APP_NAME -lncurses

if [ $? -eq 0 ]; then
    echo "✅ Build success!"
    echo "📦 Output: $BUILD_DIR/$APP_NAME"
else
    echo "❌ Build failed!"
fi
