add_test( [==[Runs without a seg fault]==] [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build/test]==] [==[Runs without a seg fault]==]  )
set_tests_properties( [==[Runs without a seg fault]==] PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build]==])
add_test( [==[Produces an output PNG file]==] [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build/test]==] [==[Produces an output PNG file]==]  )
set_tests_properties( [==[Produces an output PNG file]==] PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build]==])
add_test( [==[Pixels that are part of the sketch are your favorite color]==] [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build/test]==] [==[Pixels that are part of the sketch are your favorite color]==]  )
set_tests_properties( [==[Pixels that are part of the sketch are your favorite color]==] PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build]==])
add_test( [==[Pixels that are NOT part of the sketch are white]==] [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build/test]==] [==[Pixels that are NOT part of the sketch are white]==]  )
set_tests_properties( [==[Pixels that are NOT part of the sketch are white]==] PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build]==])
add_test( [==[in_01.png produces a correct sketch]==] [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build/test]==] [==[in_01.png produces a correct sketch]==]  )
set_tests_properties( [==[in_01.png produces a correct sketch]==] PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build]==])
add_test( [==[in_02.png produces a correct sketch]==] [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build/test]==] [==[in_02.png produces a correct sketch]==]  )
set_tests_properties( [==[in_02.png produces a correct sketch]==] PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build]==])
add_test( [==[in_03.png produces a correct sketch]==] [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build/test]==] [==[in_03.png produces a correct sketch]==]  )
set_tests_properties( [==[in_03.png produces a correct sketch]==] PROPERTIES WORKING_DIRECTORY [==[/workspaces/CS225 Labs/LabsMP/lab_debug/build]==])
set( test_TESTS [==[Runs without a seg fault]==] [==[Produces an output PNG file]==] [==[Pixels that are part of the sketch are your favorite color]==] [==[Pixels that are NOT part of the sketch are white]==] [==[in_01.png produces a correct sketch]==] [==[in_02.png produces a correct sketch]==] [==[in_03.png produces a correct sketch]==])
