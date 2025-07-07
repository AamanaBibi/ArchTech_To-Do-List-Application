#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <limits>
#include <map>
#include <ctime>

using namespace std;

struct Task {
    string description;
    string category;
    bool completed;
    time_t createdTime;
};

class TodoList {
private:
    vector<Task> tasks;
    const string filename = "todo_list.txt";

    void displayTask(const Task& task, int index) const {
        cout << index + 1 << ". ";
        if (task.completed) {
            cout << "[?] ";
        } else {
            cout << "[ ] ";
        }
        cout << task.description << " (" << task.category << ")";
        
        // Display creation time if available
        if (task.createdTime != 0) {
            char buffer[26];
            ctime_s(buffer, sizeof(buffer), &task.createdTime);
            cout << " - Added: " << buffer;
        } else {
            cout << endl;
        }
    }

    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.description << "\n";
                file << task.category << "\n";
                file << task.completed << "\n";
                file << task.createdTime << "\n";
            }
            file.close();
        }
    }

    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            tasks.clear();
            string line;
            Task task;
            while (getline(file, line)) {
                task.description = line;
                if (getline(file, line)) {
                    task.category = line;
                }
                if (getline(file, line)) {
                    task.completed = (line == "1");
                }
                if (getline(file, line)) {
                    task.createdTime = stol(line);
                }
                tasks.push_back(task);
            }
            file.close();
        }
    }

public:
    TodoList() {
        loadFromFile();
    }

    ~TodoList() {
        saveToFile();
    }

    void addTask(const string& description, const string& category) {
        Task task;
        task.description = description;
        task.category = category;
        task.completed = false;
        task.createdTime = time(nullptr);
        tasks.push_back(task);
        saveToFile();
    }

    void viewTasks(const string& filterCategory = "") const {
        if (tasks.empty()) {
            cout << "No tasks in the list.\n";
            return;
        }

        cout << "\n--- TO-DO LIST ---\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (filterCategory.empty() || tasks[i].category == filterCategory) {
                displayTask(tasks[i], i);
            }
        }
        cout << "-----------------\n";
    }

    void viewCompletedTasks() const {
        cout << "\n--- COMPLETED TASKS ---\n";
        bool found = false;
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].completed) {
                displayTask(tasks[i], i);
                found = true;
            }
        }
        if (!found) {
            cout << "No completed tasks.\n";
        }
        cout << "----------------------\n";
    }

    void markTaskCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].completed = true;
            saveToFile();
            cout << "Task marked as completed.\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }

    void removeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            saveToFile();
            cout << "Task removed.\n";
        } else {
            cout << "Invalid task number.\n";
        }
    }

    vector<string> getCategories() const {
        vector<string> categories;
        map<string, bool> seen;
        for (const auto& task : tasks) {
            if (!seen[task.category]) {
                categories.push_back(task.category);
                seen[task.category] = true;
            }
        }
        return categories;
    }

    void clearCompletedTasks() {
        tasks.erase(remove_if(tasks.begin(), tasks.end(),
            [](const Task& task) { return task.completed; }),
            tasks.end());
        saveToFile();
        cout << "Completed tasks cleared.\n";
    }
};

void displayMenu() {
    cout << "\n=== TO-DO LIST MENU ===\n";
    cout << "1. Add Task\n";
    cout << "2. View All Tasks\n";
    cout << "3. View Tasks by Category\n";
    cout << "4. View Completed Tasks\n";
    cout << "5. Mark Task as Completed\n";
    cout << "6. Remove Task\n";
    cout << "7. Clear Completed Tasks\n";
    cout << "8. Exit\n";
    cout << "=======================\n";
    cout << "Enter your choice: ";
}

int main() {
    TodoList todoList;

    cout << "=== TO-DO LIST APPLICATION ===\n";

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                string description, category;
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter task category: ";
                getline(cin, category);
                todoList.addTask(description, category);
                break;
            }
            case 2:
                todoList.viewTasks();
                break;
            case 3: {
                auto categories = todoList.getCategories();
                if (categories.empty()) {
                    cout << "No categories available.\n";
                    break;
                }
                cout << "Available categories:\n";
                for (size_t i = 0; i < categories.size(); ++i) {
                    cout << i + 1 << ". " << categories[i] << endl;
                }
                cout << "Enter category number: ";
                int catChoice;
                cin >> catChoice;
                cin.ignore();
                if (catChoice > 0 && catChoice <= categories.size()) {
                    todoList.viewTasks(categories[catChoice - 1]);
                } else {
                    cout << "Invalid category number.\n";
                }
                break;
            }
            case 4:
                todoList.viewCompletedTasks();
                break;
            case 5: {
                todoList.viewTasks();
                cout << "Enter task number to mark as completed: ";
                int index;
                cin >> index;
                cin.ignore();
                todoList.markTaskCompleted(index - 1);
                break;
            }
            case 6: {
                todoList.viewTasks();
                cout << "Enter task number to remove: ";
                int index;
                cin >> index;
                cin.ignore();
                todoList.removeTask(index - 1);
                break;
            }
            case 7:
                todoList.clearCompletedTasks();
                break;
            case 8:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}