add_executable(cmo_unit_test
    cmo_tb.cpp
)

target_compile_features(cmo_unit_test PRIVATE cxx_std_14)

verilate(cmo_unit_test
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/../../rtl/cmo_core/cmo_core.sv

    TOP_MODULE
        cmo_core
    
    PREFIX
        Vcmo_core

    VERILATOR_ARGS
        -Wall
        -Wno-fatal
)

set_target_properties(cmo_unit_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

if(BUILD_TESTING)
    add_test(
        NAME cmo_core_unit_tests
        COMMAND cmo_unit_test
    )
endif()