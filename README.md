
# File System Simulation in C++

## Description
Implemented a file system simulation in C++ for an Object-Oriented Programming course, supporting both file and directory structures. The system allows hierarchical file management through various commands such as creating, deleting, and navigating files and directories. The solution is extensible and modular.

## Key Features
- **File Types**: Support for both text files (`.txt`) and executable files (`.exe`). Text files contain arbitrary content, while executable files contain commands to be executed on the file system.
- **Command Execution**: The system supports command execution through `.exe` files, allowing navigation (e.g., `CD`, `LS`), file/folder creation (`NEW`), and deletion (`DEL`).
- **Hierarchy Loading**: Hierarchies are loaded from input files, and previous hierarchies are cleared when loading new ones. 
- **File and Directory Management**: Implemented an m-ary tree structure to efficiently store and manage the hierarchical relationships between files and directories within the file system. Files and directories are created, deleted, and listed in a structured manner. Directories are alphabetically sorted when listed.

## Challenges Overcome
- Efficiently handling dynamic hierarchy changes and file content loading using C++ standard library containers.
- Ensuring proper handling of edge cases (e.g., invalid paths, non-existent directories) through detailed error checking and input validation.

## Technologies Used
- **Programming Language**: C++
- **Libraries**: Standard C++ libraries including `<string>`, `<vector>`, `<list>`, `<stack>`, and `<queue>`.

## Outcomes
- Achieved a robust and extensible file system capable of handling hierarchical directory structures with command execution capabilities.
- Delivered a modular solution, following OOP principles with well-structured `.h` and `.cpp` files for easy maintainability and extensibility.

