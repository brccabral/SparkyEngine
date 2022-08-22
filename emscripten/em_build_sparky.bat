call D:\CPP_Win\ExternalSources\emsdk\emsdk.bat activate 3.1.19
call emcc --bind -sMAIN_MODULE -std=c++11 -I"../Dependencies/FreeImage/Source" -I"Web" "Web/freeimage-tiff.bc" "Web/freeimage-libopenjpeg.bc" "Web/freeimage-libpng.bc" "Web/freeimage-libjpeg.bc" "Web/freeimage-openexr.bc" "Web/freeimage-zlib.bc" "Web/freeimage-c.bc" "Web/freeimage-webp.bc" "Web/freeimage-main.bc" "../Sparky/src/graphics/buffers/buffer.cpp" "../Sparky/src/graphics/buffers/indexbuffer.cpp" "../Sparky/src/graphics/buffers/vertexarray.cpp" "../Sparky/src/graphics/layers/group.cpp" "../Sparky/src/graphics/layers/layer.cpp" "../Sparky/src/graphics/label.cpp" "../Sparky/src/graphics/sprite.cpp" "../Sparky/src/graphics/batchrenderer2d.cpp" "../Sparky/src/graphics/font.cpp" "../Sparky/src/graphics/font_manager.cpp" "../Sparky/src/graphics/renderable2d.cpp" "../Sparky/src/graphics/shader.cpp" "../Sparky/src/graphics/texture.cpp" "../Sparky/src/graphics/window.cpp" "../Sparky/src/maths/mat4.cpp" "../Sparky/src/maths/vec2.cpp" "../Sparky/src/maths/vec3.cpp" "../Sparky/src/maths/vec4.cpp" "../Sparky/src/utils/timer.cpp" "../Sparky/examples/game.cpp" "../Sparky/src/audio/sound.cpp" "../Sparky/src/audio/sound_manager.cpp" "Web/freetype.bc" -s USE_GLFW=3 -s FULL_ES3=1 -DSPARKY_EMSCRIPTEN=1 --memory-init-file 0 --embed-file Web\res -O3 -o Web\sparky.html