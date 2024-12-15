# Program Description
The `start_system.py` file is a Python script that orchestrates the starting of different agent scripts and facilitates collaboration between these agents. It contains functions to check if a specific port is in use on localhost, as well as to start an agent script in the foreground.

## Functions
1. `is_port_in_use(port)`: This function checks if a specified port is in use on localhost by attempting to connect to it using a socket.
2. `start_agent_in_foreground(agent_name, script_path)`: This function starts an agent script in the foreground by executing the script using `os.execlp`.

## Main Functionality
- The `main()` function is the main orchestrating function of the script. It defines the ports each agent listens on and the paths to the agent scripts.
- It first checks if any of the agents (CollaboratorAgent, PlannerAgent, CoderAgent, PromptAgent) are currently running by checking if the ports they listen on are in use.
- Based on the running status of the agents, it starts the agents in a specific order:
    - If CollaboratorAgent is not running, it starts CollaboratorAgent.
    - If PlannerAgent is not running, it starts PlannerAgent.
    - If CoderAgent is not running, it starts CoderAgent.
    - If PromptAgent is not running, it starts PromptAgent.
    - If all agents are running, it switches to Collaboration Mode by executing the Collaboration script.

## Data Structures
- `ports`: A dictionary mapping agent names to the ports they listen on.
- `scripts`: A dictionary mapping agent names to the paths of their respective scripts.

## Execution
- The script is meant to be executed directly, so when run as the main program (`__name__ == '__main__'`), it calls the `main()` function to start the orchestration of agents and collaboration.

This script provides a structured way to start different agent scripts and handle the collaboration between them based on their running status.