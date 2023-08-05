I am getting the following error when running:
``` command
    make all
```

``` error
g++   -std=c++14 -Wall -Wextra -g -o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1ScoreTest /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Player.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/GameState.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1TieBreaker.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1ScoreTest.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/PinState.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1Score.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/TranslateConstant.o /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgtest_main.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgmock.a /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/googletest/build/lib/libgmock_main.a -lgtest -lgtest_main -lgmock -lpthread
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1TieBreaker.o: in function `Mode1TieBreaker::Mode1TieBreaker(IPlayer*, IPlayer*, PinInterface*, GameState*, History*)':
/home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `PointLeds::PointLeds(IPlayer*, IPlayer*, PinInterface*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `GameLeds::GameLeds(IPlayer*, IPlayer*, PinInterface*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `ServeLeds::ServeLeds(PinInterface*, GameState*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `SetLeds::SetLeds(IPlayer*, IPlayer*, PinInterface*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `Mode1WinSequences::Mode1WinSequences(IPlayer*, IPlayer*, PinInterface*, GameState*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `Undo::Undo(IPlayer*, IPlayer*, PinInterface*, GameState*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `Mode1WinSequences::~Mode1WinSequences()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `SetLeds::~SetLeds()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `ServeLeds::~ServeLeds()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `GameLeds::~GameLeds()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:18: undefined reference to `PointLeds::~PointLeds()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1TieBreaker.o: in function `Mode1TieBreaker::~Mode1TieBreaker()':
/home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:20: undefined reference to `Undo::~Undo()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:20: undefined reference to `Mode1WinSequences::~Mode1WinSequences()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:20: undefined reference to `SetLeds::~SetLeds()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:20: undefined reference to `ServeLeds::~ServeLeds()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:20: undefined reference to `GameLeds::~GameLeds()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:20: undefined reference to `PointLeds::~PointLeds()'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1TieBreaker.o: in function `Mode1TieBreaker::mode1TBButtonFunction()':
/home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:38: undefined reference to `GameTimer::gameDelay(int)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:39: undefined reference to `Undo::setMode1Undo(History*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:45: undefined reference to `GameTimer::gameDelay(int)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:46: undefined reference to `Undo::mode1Undo(History*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:50: undefined reference to `GameTimer::gameDelay(int)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:51: undefined reference to `Undo::setMode1Undo(History*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:57: undefined reference to `GameTimer::gameDelay(int)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/../Mode1TieBreaker/Mode1TieBreaker.cpp:58: undefined reference to `Undo::mode1Undo(History*)'
/usr/bin/ld: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1TieBreaker.o: in function `Mode1TieBreaker::tieBreaker()':
...
make: *** [Makefile:24: /home/adamsl/linuxBash/SMOL_AI/tennis_unit_tests/Mode1Score/Mode1ScoreTest] Error 1
```