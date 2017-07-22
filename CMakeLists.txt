cmake_minimum_required(VERSION 3.8.0)
project(unity_examples)

set(this        ${CMAKE_CURRENT_SOURCE_DIR})
set(cmock_root  ${this}/vendor/CMock)
set(unity_root  ${cmock_root}/vendor/unity)
set(src_dir     ${this}/src)
set(test_dir    ${this}/test)
set(runners_dir ${this}/build/test_runners)
set(mocks_dir   ${this}/build/mocks)
set(unity_src   ${unity_root}/src/unity.c)
set(cmock_src   ${cmock_root}/src/cmock.c)
file(GLOB src_files	"${src_dir}/*.c")
file(GLOB h_files	"${src_dir}/*.h")
file(GLOB test_files	"${test_dir}/test_*.c")
file(GLOB common_test_files "${test_dir}/common_*.c")
file(MAKE_DIRECTORY      ${mocks_dir})
file(MAKE_DIRECTORY      ${runners_dir})
file(GLOB mock_files	"${mocks_dir}/*.[ch]")
include_directories(${src_dir} ${unity_root}/src ${cmock_root}/src ${mocks_dir})

function(set_file_names file src runner binary)
  execute_process(
    COMMAND ${this}/file_names ${file}
    OUTPUT_VARIABLE files
    )
  list(GET files 0 _src)
  list(GET files 1 _runner)
  list(GET files 2 _binary)
  set(${src} ${_src} PARENT_SCOPE)
  set(${runner} ${_runner} PARENT_SCOPE)
  set(${binary} ${_binary} PARENT_SCOPE)
endfunction(set_file_names)

function(set_mock_names header mock_c mock_h)
  execute_process(
    COMMAND ${this}/mock_names ${header}
    OUTPUT_VARIABLE files
    ) 
  list(GET files 0 _mock_c)
  list(GET files 1 _mock_h)
  set(${mock_c} ${_mock_c} PARENT_SCOPE)
  set(${mock_h} ${_mock_h} PARENT_SCOPE)
endfunction(set_mock_names)

foreach(header ${h_files})
  set_mock_names(${header} mock_c mock_h)
   
  add_custom_command(
    OUTPUT  ${mocks_dir}/${mock_c} ${mocks_dir}/${mock_h}
    DEPENDS ${header}
    COMMAND ruby
            ${cmock_root}/lib/cmock.rb
	    --mock_prefix="mock_" --mock_path=${mocks_dir}
	    ${header}
    COMMENT "Generate mocks for all modules and for all interfaces files"  
    )
endforeach()

# Generate test runners for each file and generate test executables.
foreach(test ${test_files})
  set_file_names(${test} src runner binary)
  
  add_custom_command(
    OUTPUT  ${runners_dir}/${runner}
    DEPENDS ${test} ${src_dir}/${src}
    COMMAND ruby
            ${unity_root}/auto/generate_test_runner.rb
	    ${test}
	    ${runners_dir}/${runner}
    COMMENT "generate unity test runner"
    )

  # Get test file mock dependencies
  execute_process(
    COMMAND ${this}/test_mocks_depend ${test}
    OUTPUT_VARIABLE mocks
    )
  
  add_executable(
    ${binary}         # add a new test binary
    ${runners_dir}/${runner} # contains the main function
    ${src_dir}/${src} # include the file that's being tested (if more
                      # files per module, it should include all of
		      # them - not implemented now)
    ${src_files}      # should remove the mocked sources!!!
    ${common_test_files} 
    ${mocks}	      # include mocks for all the modules the file
		      # under test depends on
    ${test}	      # the test file
    ${unity_src}
    ${cmock_src}
    )
  target_include_directories(
    ${binary} PUBLIC
    ${test_dir}	      # common test file headers for each test binary
    )

  # set_target_properties(${binary} PROPERTIES
  #   INCLUDE_DIRECTORIES ${test_dir} # for common files to all tests
  #   )
endforeach()

# add_executable(calculator ${src_files})

# set_target_properties(whateverrr PROPERTIES
#   COMPILE_FLAGS "-Wall")
