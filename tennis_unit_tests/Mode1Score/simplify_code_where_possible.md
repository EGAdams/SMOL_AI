# Your role
- Expert software engineer

# Your task
- Simplify code where possible.
  - For example:
    - original
    ```cpp
    if ( i == 0 ) {        ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 1 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 2 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 3 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 4 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 5 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe());
        } else if ( i == 6 ) { ASSERT_EQ( PLAYER_2_SERVE , gameState->getServe());
        } else if ( i == 7 ) { ASSERT_EQ( PLAYER_1_SERVE , gameState->getServe()); }
    ```
    - simplified
    ```cpp
    if ( i >= 0 && i <= 7 ) {
        if ( i % 2 == 0 ) {
            ASSERT_EQ( PLAYER_2_SERVE, gameState->getServe());
        } else {
            ASSERT_EQ( PLAYER_1_SERVE, gameState->getServe());
        }
    }
    ```