function (add_kfr_library)

    cmake_parse_arguments(LIB "MULTIARCH" "NAME" "SOURCES;LIBRARIES;DEFINITIONS;OPTIONS"
                          ${ARGN})

    set(${LIB_NAME}_LIBS)
    set(${LIB_NAME}_TARGETS)
    if (KFR_ENABLE_MULTIARCH AND LIB_MULTIARCH)
        add_library(${LIB_NAME} INTERFACE)
        foreach (ARCH IN LISTS KFR_ARCHS)
            add_library(${LIB_NAME}_${ARCH} STATIC ${LIB_SOURCES})
            target_compile_definitions(${LIB_NAME}_${ARCH} PRIVATE CMT_MULTI=1)     
            foreach (ENABLED_ARCH IN LISTS KFR_ARCHS)
                string(TOUPPER ${ENABLED_ARCH} ENABLED_ARCH_UPPER)
                target_compile_definitions(${LIB_NAME}_${ARCH} PRIVATE CMT_MULTI_ENABLED_${ENABLED_ARCH_UPPER}=1)   
            endforeach()
            list(APPEND ${LIB_NAME}_LIBS ${LIB_NAME}_${ARCH})
            list(APPEND ${LIB_NAME}_TARGETS ${LIB_NAME}_${ARCH})
            target_link_libraries(${LIB_NAME} INTERFACE ${LIB_NAME}_${ARCH})
            target_set_arch(${LIB_NAME}_${ARCH} PRIVATE ${ARCH})
        endforeach ()
        list(GET KFR_ARCHS 0 BASE_ARCH)
        target_compile_definitions(${LIB_NAME}_${BASE_ARCH} PRIVATE CMT_BASE_ARCH=1)

        link_as_whole(${LIB_NAME} INTERFACE ${LIB_NAME}_${BASE_ARCH})
        
        list(APPEND ${LIB_NAME}_TARGETS ${LIB_NAME})
    else ()
        add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
        list(APPEND ${LIB_NAME}_LIBS ${LIB_NAME})
        list(APPEND ${LIB_NAME}_TARGETS ${LIB_NAME})
        target_set_arch(${LIB_NAME} PRIVATE ${KFR_ARCH})
    endif ()

    foreach (LIB IN LISTS ${LIB_NAME}_LIBS)
        target_link_libraries(${LIB} PUBLIC kfr)
        target_link_libraries(${LIB} PRIVATE ${LIB_LIBRARIES})
        target_compile_definitions(${LIB} PRIVATE ${LIB_DEFINITIONS})
        target_compile_options(${LIB} PRIVATE ${LIB_OPTIONS})        
    endforeach ()

    set(${LIB_NAME}_LIBS ${${LIB_NAME}_LIBS} PARENT_SCOPE)
    set(${LIB_NAME}_TARGETS ${${LIB_NAME}_TARGETS} PARENT_SCOPE)

endfunction ()
