I am getting the following error when running:
``` command
    make all
```

``` error
g++ -std=c++14 -Wall -Wextra -c -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/MockPinInterface.o MockPinInterface.cpp
g++ -std=c++14 -Wall -Wextra -c -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinState.o ../PinState/PinState.cpp
g++ -std=c++14 -Wall -Wextra -c -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/PinInterface.o PinInterface.cpp
make: *** No rule to make target 'TranslateConstant.cpp', needed by '/home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/PinInterface/TranslateConstant.o'.  Stop.
```