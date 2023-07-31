I am getting the following error when running:
``` command
    make all
```

``` error
g++ -std=c++14 -Wall -Wextra -c -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/build/PinInterface/MockPinInterface.o MockPinInterface.cpp
g++ -std=c++14 -Wall -Wextra -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/build/PinInterface/MockPinInterfaceTest /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/build/PinInterface/MockPinInterface.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest_main.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgmock.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgmock_main.a
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest_main.a(gtest_main.cc.o): in function `main':
gtest_main.cc:(.text+0x3a): undefined reference to `testing::InitGoogleTest(int*, char**)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest_main.a(gtest_main.cc.o): in function `RUN_ALL_TESTS()':
gtest_main.cc:(.text._Z13RUN_ALL_TESTSv[_Z13RUN_ALL_TESTSv]+0x9): undefined reference to `testing::UnitTest::GetInstance()'
/usr/bin/ld: gtest_main.cc:(.text._Z13RUN_ALL_TESTSv[_Z13RUN_ALL_TESTSv]+0x11): undefined reference to `testing::UnitTest::Run()'
collect2: error: ld returned 1 exit status
make: *** [Makefile:30: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/build/PinInterface/MockPinInterfaceTest] Error 1
```