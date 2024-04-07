#!/bin/sh

set -e

git submodule update --init

# glfw
rm -rf tmp/builddir tmp/external
cmake -B tmp/builddir -DCMAKE_INSTALL_PREFIX:PATH=./external submodules/glfw
cmake --build tmp/builddir --target install --config Release --parallel
mv tmp/builddir/external ./tmp
rm -rf tmp/builddir

# core
make -C submodules/core
cp -r submodules/core/include/* tmp/external/include
cp submodules/core/libmb_core.a tmp/external/lib
make -C submodules/core clean

# real_float
make -C submodules/real_float
cp -r submodules/real_float/include/* tmp/external/include
cp submodules/real_float/libmb_real_float.a tmp/external/lib
make -C submodules/real_float clean

# colorizer_basic
make -C submodules/colorizer_basic
cp -r submodules/colorizer_basic/include/* tmp/external/include
cp submodules/colorizer_basic/libmb_colorizer_basic.a tmp/external/lib
make -C submodules/colorizer_basic clean

# gui_fps
make -C submodules/gui_fps
cp -r submodules/gui_fps/include/* tmp/external/include
cp submodules/gui_fps/libmb_gui_fps.a tmp/external/lib
make -C submodules/gui_fps clean

rm -rf external
mv tmp/external .
