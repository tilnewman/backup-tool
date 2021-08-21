cmake_minimum_required(VERSION 3.8)
project("backup" VERSION 1.0.1 LANGUAGES CXX)


file(GLOB source_files *.?pp *.h)
add_executable(${PROJECT_NAME} ${source_files})


option(USE_DEBUG "USE_DEBUG=ON found on cmd line: Debug+AddressSanitizer" OFF)


#compiler specific stuff here
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    message("**** Using Visual Studio ****")

    if(USE_DEBUG)
        message("**** WARNING:  USE_DEBUG=ON but ignored when using Visual Studio ****")
    endif()
	
    target_compile_options(${PROJECT_NAME} PUBLIC /std:c++17 -DWIN32_LEAN_AND_MEAN /MP /W4 /w14254 /w14263 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14640 /w14826 /w14905 /w14906 /w14928)

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else()

    if(USE_DEBUG)
        target_compile_options(${PROJECT_NAME} PUBLIC -DDEBUG -O0)
    else()
        target_compile_options(${PROJECT_NAME} PUBLIC -DNDEBUG -O3)
    endif()


    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    
        message("**** Using Clang ****")

        target_compile_options(${PROJECT_NAME} PUBLIC -lstdc++ -std=c++17 -Weverything -Wno-error -Wno-unused-command-line-argument -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-global-constructors -Wno-exit-time-destructors -Wno-padded -Wno-weak-vtables -Wno-disabled-macro-expansion -Wno-deprecated -Wno-covered-switch-default -Wno-inconsistent-missing-destructor-override -Wno-ctad-maybe-unsupported -Wno-suggest-destructor-override)

        if(USE_DEBUG)
            message("**** Using Clang's Address Sanitizer ****")
            target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address -fno-omit-frame-pointer)
            target_link_libraries(${PROJECT_NAME} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
	    endif()

    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")

        message("**** Using GNU ****")

        target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17 -lstdc++ -ffast-math -DBOOST_NO_AUTO_PTR -pedantic -Wall -Wextra -Wshadow -Wfloat-equal -Wundef -Wswitch-default -Wswitch-enum -Wunreachable-code -Weffc++ -Wunused-parameter -Wfatal-errors -Wstrict-null-sentinel -Wconversion -Wsign-conversion)

    else()

        message(FATAL_ERROR " Unknwon Compiler: ${CMAKE_CXX_COMPILER_ID}")

    endif()

endif()
