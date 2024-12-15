# Persona
You are an AI debugger who is trying to fully describe a program, in order for another AI program to reconstruct every file, data structure, function and functionality. The user has provided you with the following files and their contents:

My files are as follows: 
# start_system.py
```python
start_system.py:
import os 
import socket
import sys

def is_port_in_use(port):
    """Check if a specific port is in use on localhost."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        return s.connect_ex(('localhost', port)) == 0

def start_agent_in_foreground(agent_name, script_path):
    """Start an agent script in the foreground."""
    print(f"Starting {agent_name} in the foreground.")
    os.execlp(sys.executable, sys.executable, script_path)

def main():
    """Main function to orchestrate the starting of agents and collaboration."""
    # Define the ports each agent listens on
    ports = {
        'CollaboratorAgent': 8001,
        'PlannerAgent': 8002,
        'CoderAgent': 8003,
        'PromptAgent': 8004
    }

    # Define paths to agent scripts
    home_directory = os.path.expanduser("~")
    scripts = {
        'CollaboratorAgent': os.path.join(home_directory, 'the_function_caller/agents/message_collaborator_agent/collaborator.py'),
        'PlannerAgent': os.path.join(home_directory, 'the_function_caller/agents/planner_agent/planner_agent_exe.py'),
        'CoderAgent': os.path.join(home_directory, 'the_function_caller/agents/coder_agent/coder_agent_exe.py'),
        'PromptAgent': os.path.join(home_directory, 'the_function_caller/agents/prompt_agent/prompt_agent_exe.py'),
        'Collaboration': os.path.join(home_directory, 'the_function_caller/agents/start_collaborating.py')
    }

    # Check if agents are currently running
    running_status = {agent: is_port_in_use(port) for agent, port in ports.items()}

    if not running_status['CollaboratorAgent']:
        print("Starting CollaboratorAgent first.")
        start_agent_in_foreground("CollaboratorAgent", scripts['CollaboratorAgent'])

    elif not running_status['PlannerAgent']:
        print("Planner agent is not running, Starting PlannerAgent...")
        start_agent_in_foreground("PlannerAgent", scripts['PlannerAgent'])

    elif not running_status['CoderAgent']:
        print("PlannerAgent is running. Starting CoderAgent.")
        start_agent_in_foreground("CoderAgent", scripts['CoderAgent'])

    elif not running_status['PromptAgent']:
        print("PlannerAgent and CoderAgent are running. Starting PromptAgent.")
        start_agent_in_foreground("PromptAgent", scripts['PromptAgent'])

    elif all(running_status.values()):
        print("All agents are running.")
        print("Switching to Collaboration Mode.")
        os.execlp(sys.executable, sys.executable, scripts['Collaboration'])

if __name__ == '__main__':
    main()
```

# Your Task
Describe the program in markdown using specific language that will help another AI program reconstruct the given program in as high fidelity as possible.