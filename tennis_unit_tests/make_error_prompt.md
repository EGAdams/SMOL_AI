I am getting the following error when running:
``` command
    make all
```

``` error
g++   -std=c++14 -Wall -Wextra -g -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1ScoreTest /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/WinSequences.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1ScoreTest.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Player.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/GameState.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/TieBreaker.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/PinState.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1Score.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/TranslateConstant.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest_main.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgmock.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgmock_main.a -lgtest -lgtest_main -lgmock -lpthread
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/WinSequences.o: in function `WinSequences::~WinSequences()':
/home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../WinSequences/WinSequences.cpp:4: undefined reference to `SetWin::~SetWin()'
...
make: *** [Makefile:24: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1ScoreTest] Error 1
```