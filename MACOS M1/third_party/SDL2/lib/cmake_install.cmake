# Install script for directory: /users/samsi/Downloads/SDL-release-2.28.2

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/libSDL2-2.0.0.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2-2.0.0.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2-2.0.0.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2-2.0.0.dylib")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/libSDL2-2.0.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/libSDL2main.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2main.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2main.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2main.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/libSDL2.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/libSDL2_test.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2_test.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2_test.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2_test.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake"
         "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2Targets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets.cmake"
         "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2mainTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2mainTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2mainTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2mainTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets.cmake"
         "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2staticTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2staticTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2staticTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2staticTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2testTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2testTargets.cmake"
         "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2testTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2testTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2testTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2testTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/Export/f084604df1a27ef5b4fef7c7544737d1/SDL2testTargets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES
    "/Users/samsi/Downloads/SDL-release-2.28.2/build/SDL2Config.cmake"
    "/Users/samsi/Downloads/SDL-release-2.28.2/build/SDL2ConfigVersion.cmake"
    "/users/samsi/Downloads/SDL-release-2.28.2/cmake/sdlfind.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_assert.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_atomic.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_audio.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_bits.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_blendmode.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_clipboard.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_copying.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_cpuinfo.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_egl.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_endian.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_error.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_events.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_filesystem.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_gamecontroller.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_gesture.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_guid.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_haptic.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_hidapi.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_hints.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_joystick.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_keyboard.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_keycode.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_loadso.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_locale.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_log.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_main.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_messagebox.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_metal.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_misc.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_mouse.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_mutex.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_name.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_opengl.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_opengl_glext.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_opengles.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_opengles2.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_opengles2_gl2.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_opengles2_gl2ext.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_opengles2_gl2platform.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_opengles2_khrplatform.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_pixels.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_platform.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_power.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_quit.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_rect.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_render.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_rwops.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_scancode.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_sensor.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_shape.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_stdinc.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_surface.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_system.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_syswm.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_assert.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_common.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_compare.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_crc32.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_font.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_fuzzer.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_harness.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_images.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_log.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_md5.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_memory.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_test_random.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_thread.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_timer.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_touch.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_types.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_version.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_video.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/SDL_vulkan.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/begin_code.h"
    "/users/samsi/Downloads/SDL-release-2.28.2/include/close_code.h"
    "/Users/samsi/Downloads/SDL-release-2.28.2/build/include/SDL2/SDL_revision.h"
    "/Users/samsi/Downloads/SDL-release-2.28.2/build/include-config-/SDL2/SDL_config.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/SDL2" TYPE FILE FILES "/users/samsi/Downloads/SDL-release-2.28.2/LICENSE.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/sdl2.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
            execute_process(COMMAND /opt/homebrew/Cellar/cmake/3.27.1/bin/cmake -E create_symlink
              "libSDL2-2.0.dylib" "libSDL2.dylib"
              WORKING_DIRECTORY "/Users/samsi/Downloads/SDL-release-2.28.2/build")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/libSDL2.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/Users/samsi/Downloads/SDL-release-2.28.2/build/sdl2-config")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/aclocal" TYPE FILE FILES "/users/samsi/Downloads/SDL-release-2.28.2/sdl2.m4")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/samsi/Downloads/SDL-release-2.28.2/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
