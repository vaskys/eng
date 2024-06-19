if (NOT EXISTS "/Users/samsi/Downloads/SDL-release-2.28.2/build/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"/Users/samsi/Downloads/SDL-release-2.28.2/build/install_manifest.txt\"")
endif(NOT EXISTS "/Users/samsi/Downloads/SDL-release-2.28.2/build/install_manifest.txt")

file(READ "/Users/samsi/Downloads/SDL-release-2.28.2/build/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND /opt/homebrew/Cellar/cmake/3.27.1/bin/cmake -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

