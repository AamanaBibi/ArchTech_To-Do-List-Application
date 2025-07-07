# To-Do List Application - README

## Overview
A robust C++ command-line To-Do List application with persistent storage, category management, and task tracking features. This professional-grade application helps users organize their tasks efficiently with a clean interface and reliable data persistence.

## Features

### Core Functionality
- **Task Management**:
  - Add new tasks with descriptions and categories
  - Mark tasks as completed
  - Remove individual tasks
  - Clear all completed tasks

### Organizational Tools
- **Category System**:
  - View tasks filtered by category
  - Automatic category tracking
  - Category-based task organization

### Data Persistence
- Automatic saving to `todo_list.txt`
- Data preservation between sessions
- Timestamp recording for task creation

### Viewing Options
- View all tasks
- Filter by category
- View only completed tasks
- Detailed task display with status indicators

## Technical Implementation

### Data Structure
```cpp
struct Task {
    string description;
    string category;
    bool completed;
    time_t createdTime;
};
```

### File I/O Operations
- Uses `ofstream` and `ifstream` for file operations
- Implements atomic save/load functionality
- Stores all task attributes in human-readable format

### Memory Management
- RAII pattern for file handling
- Vector-based task storage
- Automatic cleanup of completed tasks

## User Interface

### Main Menu
```text
=== TO-DO LIST MENU ===
1. Add Task
2. View All Tasks
3. View Tasks by Category
4. View Completed Tasks
5. Mark Task as Completed
6. Remove Task
7. Clear Completed Tasks
8. Exit
=======================
```

### Task Display Format
```text
1. [ ] Buy groceries (Shopping) - Added: Wed Jun 15 14:30:00 2023
2. [✓] Finish report (Work) - Added: Tue Jun 14 09:15:00 2023
```

## Code Structure

### `TodoList` Class
- **Private Members**:
  - `tasks`: Vector storing all tasks
  - `filename`: Constant for data storage
- **Public Interface**:
  - Constructor/Destructor for automatic loading/saving
  - Task manipulation methods
  - Viewing methods with filtering
  - Category management

### Helper Functions
- `displayMenu()`: Shows the main interface
- Task display formatting with status indicators
- Comprehensive input validation

## Example Usage

1. **Adding a Task**:
```text
Enter task description: Prepare project presentation
Enter task category: Work
```

2. **Viewing by Category**:
```text
Available categories:
1. Work
2. Personal
Enter category number: 1
```

3. **Completing a Task**:
```text
Enter task number to mark as completed: 3
Task marked as completed.
```

## Data Persistence Details

### File Format
Each task occupies 4 lines in `todo_list.txt`:
1. Task description
2. Category
3. Completion status (0/1)
4. Creation timestamp

### Example File Content
```text
Buy milk
Shopping
0
1686847200
Finish report
Work
1
1686760500
```

## Future Enhancements

1. Task prioritization system
2. Due date functionality
3. Color-coded output
4. Search functionality
5. Export/import options

## License
MIT License - Free for personal and professional use

This professional implementation provides a solid foundation for task management with clean code organization and robust error handling. The application is suitable for both personal use and as a demonstration of C++ file I/O and data structure management.# ArchTech_To-Do-List-Application
