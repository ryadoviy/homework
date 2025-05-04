#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Task {
    string title;
    int priority;
    bool done = false;
};

class TaskManager {
    vector<Task> tasks;

public:
    void addTask() {
        Task t;
        cout << "Enter task title: ";
        getline(cin >> ws, t.title);
        cout << "Enter priority (1 = high, 5 = low): ";
        cin >> t.priority;
        tasks.push_back(t);
        cout << "Task added!\n";
    }

    void showTasks() {
        if (tasks.empty()) {
            cout << "No tasks found.\n";
            return;
        }

        for (int i = 0; i < tasks.size(); ++i)
            for (int j = i + 1; j < tasks.size(); ++j)
                if (tasks[j].priority < tasks[i].priority)
                    swap(tasks[i], tasks[j]);

        cout << "Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].title
                << " (priority: " << tasks[i].priority << ") - "
                << (tasks[i].done ? "Done" : "Not Done") << "\n";
        }
    }

    void completeTask() {
        if (tasks.empty()) {
            cout << "No tasks to complete.\n";
            return;
        }

        showTasks();
        int n;
        cout << "Enter task number to mark as done: ";
        cin >> n;

        if (n < 1 || n > tasks.size()) {
            cout << "Invalid task number.\n";
            return;
        }

        if (tasks[n - 1].done) {
            cout << "Task already marked as done.\n";
        }
        else {
            tasks[n - 1].done = true;
            cout << "Marked as done: " << tasks[n - 1].title << "\n";
        }
    }

    void menu() {
        int choice;
        do {
            cout << "1. Add Task\n2. Show Tasks\n3. Complete Task\n4. Exit\nChoose: ";
            cin >> choice;
            switch (choice) {
            case 1: addTask(); break;
            case 2: showTasks(); break;
            case 3: completeTask(); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    TaskManager tm;
    tm.menu();
    return 0;
}

