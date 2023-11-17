Act as a world-class C++ developer. You are an expert at Object-Oriented Programming. You always adhere to SOLID Programming principles. You are my assistant and excellent teacher. We are going to develop a C++ project that we are going to test. We are going to build and test each object individually.

The program consists of a ScoreBoard class that takes in two Player objects and a GameState object as parameters. The ScoreBoard class has an update() function that prints out the points of each player and a _drawPlayerScore() function that determines the vertical offset and serves a bar of a player and draws their score using BigNumberDrawer objects. The _translate() function translates the raw score into a string format. The _showLittleNumbers() function draws little numbers on a canvas.

The ScoreBoard class has a private _bigNumberDrawer object of class BigNumberDrawer, a _pipeDrawer object (class not specified), a _big_number_font object (type not specified), and a _canvas object (type not specified).

The project structure will be:
```bash
.
├── ScoreBoard
│   ├── ScoreBoard.h
│   ├── ScoreBoard.cpp
│   ├── ScoreBoard.html
│   ├── ScoreBoard_test.cpp
│   ├── ScoreBoard.test.exe
│   └── prompt_notes.txt
├── Player.h
├── Player.cpp
├── GameState.h
├── GameState.cpp
├── BigNumberDrawer.h
├── BigNumberDrawer.cpp
├── Makefile
├── doxygen_config
└── .gitignore
```

Each file has a specific function:

ScoreBoard.h and ScoreBoard.cpp will define and implement the ScoreBoard class.
ScoreBoard.html will be a Doxygen-generated HTML file explaining the ScoreBoard class and its methods.
ScoreBoard_test.cpp will contain Google Test unit tests for the ScoreBoard class methods.
ScoreBoard.test.exe will be the executable created by compiling ScoreBoard_test.cpp.
prompt_notes.txt will hold any notes or prompts related to the ScoreBoard class or its associated files.
Player.h and Player.cpp will define and implement the Player class.
GameState.h and GameState.cpp will define and implement the GameState class.
BigNumberDrawer.h and BigNumberDrawer.cpp will define and implement the BigNumberDrawer class.
Makefile will contain build rules for compiling the project, generating documentation, and running style checks and static analysis.
doxygen_config will be the configuration file for Doxygen.
.gitignore will specify files and directories to be ignored by Git.

Finally, adhere to SOLID programming principles during development, and ensure to write unit tests for each class and method. Use Doxygen to generate well-documented HTML files for each class, and set up a Git repository to version control the project. Configure a Makefile to automate the build and testing process.

Please use your web browsing tool to find information that you are unclear about.

Please begin building the project.