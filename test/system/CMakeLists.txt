find_program(LLVM_CONFIG_EXECUTABLE llvm-config-17)

if (NOT LLVM_CONFIG_EXECUTABLE)
  message(WARNING "llvm-config-17 is required to automatically run system tests.
  To run system tests manually, refer to test/system/run.sh")
  return()
endif ()

execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --bindir
    OUTPUT_VARIABLE LLVM_CLANG_BINDIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "LLVM Clang: ${LLVM_CLANG_BINDIR}")

set(TIPCLANG_PATH "${LLVM_CLANG_BINDIR}/clang")

message(STATUS "TIPClang: ${TIPCLANG_PATH}")

find_program(BASH_EXECUTABLE NAMES bash)

if (NOT BASH_EXECUTABLE)
  message(FATAL_ERROR "Bash not found on the system.")
  return()
endif ()

execute_process(
    COMMAND ${BASH_EXECUTABLE} -c "TIPCLANG=${TIPCLANG_PATH} sh build.sh"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/rtlib
    RESULT_VARIABLE result
)

if (NOT result EQUAL 0)
  message(FATAL_ERROR "RTLib built failed with message '${result}'.
    To run system tests manually, refer to test/system/run.sh")
  return()
else ()
  message(STATUS "RTLib built successfully")
endif ()

set(test_script_name run.sh)
set(test_script_path ${CMAKE_CURRENT_SOURCE_DIR}/${test_script_name})

file(CHMOD ${test_script_path} PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)

add_test(
    NAME system_tests
    COMMAND ${test_script_path}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set_tests_properties(
    system_tests PROPERTIES
    ENVIRONMENT "TIPCLANG=${TIPCLANG_PATH};TRAVIS_BUILD_DIR=${PROJECT_SOURCE_DIR}"
)