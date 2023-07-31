I am getting the following error when running:
``` command
    make all
```

``` error
g++ -std=c++14 -Wall -Wextra -c -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/MockPinInterface.o MockPinInterface.cpp
g++ -std=c++14 -Wall -Wextra -c -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinState.o ../PinState/PinState.cpp
g++ -std=c++14 -Wall -Wextra -c -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinInterface.o PinInterface.cpp
g++ -std=c++14 -Wall -Wextra -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/MockPinInterfaceTest /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/MockPinInterface.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinState.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinInterface.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest_main.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgmock.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgmock_main.a -lgtest -lgtest_main -lpthread
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinState.o: in function `PinState::PinState(std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int, std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, int> > >)':
PinState.cpp:(.text+0x34): undefined reference to `TranslateConstant::TranslateConstant()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinState.o: in function `PinState::~PinState()':
PinState.cpp:(.text+0x7c): undefined reference to `TranslateConstant::~TranslateConstant()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinState.o: in function `PinState::getPinState(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)':
PinState.cpp:(.text+0xf3): undefined reference to `TranslateConstant::get_translated_constant[abi:cxx11](int)'
/usr/bin/ld: PinState.cpp:(.text+0x1e1): undefined reference to `TranslateConstant::get_translated_constant[abi:cxx11](int)'
/usr/bin/ld: PinState.cpp:(.text+0x36d): undefined reference to `TranslateConstant::get_translated_constant[abi:cxx11](int)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinState.o: in function `PinState::setPinState(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int)':
PinState.cpp:(.text+0x573): undefined reference to `TranslateConstant::get_translated_constant[abi:cxx11](int)'
collect2: error: ld returned 1 exit status
make: *** [Makefile:29: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/MockPinInterfaceTest] Error 1
```