# TaskTrek - Task Scheduling System

### Team Members
- **SAMANTHA W** (23PW25)
- **SHREE SINDHIYA HARSHINI K** (23PW28)


## Overview
TaskTrek is a simple terminal-based task scheduling and prioritization system implemented in C. It uses a priority queue to manage and organize tasks by importance, and includes support for file-based saving and loading of tasks.

## Features:
- ✅ Add tasks with a priority
- 🧠 Automatically handles priority-based ordering
- 🔄 Execute (remove) the highest priority task
- 📋 Display all current tasks
- 💾 Save tasks to a file
- 📂 Load tasks from a file
- 🧹 Priority 1 tasks are treated as most urgent and handled separately

## Compilation:
To compile the program, use gcc:  
```bash
gcc tasktrek.c -o tasktrek

## Usage:
Run the program using:
  ./tasktrek

## Menu Options:
Add a task – Input task name and priority (lower number = higher priority).
Task to be done – Removes and displays the highest-priority task.
Display all tasks – Shows the full to-do list with priorities.
Save tasks to file – Saves current tasks to a file named tasks.
Load tasks from file – Loads tasks from the tasks file.
Exit – Quits the program.

## Task Priority Rules:
Priority 1 is considered most urgent and always moved to the front of the queue.
Other tasks follow a max-heap behavior (higher number = higher priority).

## File Format:
Tasks are saved in the tasks file in the following format:
  TaskName1 2
  TaskName2 1
  ...
  
Each line contains a task name and its priority, separated by a space.

## Example:
Welcome to Task Scheduling System!

Task Scheduling Menu:
1. Add a task
2. Task to be done
3. Display all tasks
4. Save tasks to file
5. Load tasks from file
6. Exit
Enter your choice:

Created as a simple C project for practicing file handling, priority queues, and menu-driven interfaces.
