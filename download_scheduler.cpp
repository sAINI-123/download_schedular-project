
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct DownloadRequest {
    int id;
    string fileName;
    string url;
    int priority;
    bool completed;
    int order;
};

class DownloadScheduler {
private:
    vector<DownloadRequest> requests;
    int nextId = 1001;
    int orderNumber = 0;

public:
    void addRequest() {
        DownloadRequest r;

        r.id = nextId++;
        r.completed = false;
        r.order = orderNumber++;

        cout << "\nEnter file name: ";
        getline(cin >> ws, r.fileName);

        cout << "Enter download URL: ";
        getline(cin, r.url);

        cout << "Enter priority (1 = Highest, 5 = Lowest): ";

        if (!(cin >> r.priority)) {
            cout << "Invalid priority input!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }

        if (r.priority < 1 || r.priority > 5) {
            cout << "Invalid priority. Setting priority to 3.\n";
            r.priority = 3;
        }

        requests.push_back(r);

        cout << "\nRequest added successfully!\n";
        cout << "Request ID: " << r.id << endl;
    }

    void displayRequests() {
        if (requests.empty()) {
            cout << "\nNo download requests found.\n";
            return;
        }

        cout << "\n========== ALL REQUESTS ==========\n";

        for (const auto &r : requests) {
            cout << "\nRequest ID: " << r.id << endl;
            cout << "File Name: " << r.fileName << endl;
            cout << "URL: " << r.url << endl;
            cout << "Priority: " << r.priority << endl;
            cout << "Status: "
                 << (r.completed ? "Processed" : "Pending")
                 << endl;
        }
    }

    void processRequest() {
        int selected = -1;

        for (int i = 0; i < static_cast<int>(requests.size()); i++) {
            if (!requests[i].completed) {
                if (selected == -1 ||
                    requests[i].priority < requests[selected].priority ||
                    (requests[i].priority == requests[selected].priority &&
                     requests[i].order < requests[selected].order)) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            cout << "\nNo pending requests to process.\n";
            return;
        }

        DownloadRequest &r = requests[selected];

        cout << "\n========== PROCESSING REQUEST ==========\n";
        cout << "Request ID: " << r.id << endl;
        cout << "File Name: " << r.fileName << endl;
        cout << "URL: " << r.url << endl;

        r.completed = true;

        cout << "Status: Processed successfully (simulation)\n";
    }

    void searchRequest() {
        int id;

        cout << "\nEnter Request ID: ";

        if (!(cin >> id)) {
            cout << "Invalid ID input!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }

        for (const auto &r : requests) {
            if (r.id == id) {
                cout << "\nRequest Found!\n";
                cout << "Request ID: " << r.id << endl;
                cout << "File Name: " << r.fileName << endl;
                cout << "URL: " << r.url << endl;
                cout << "Priority: " << r.priority << endl;
                cout << "Status: "
                     << (r.completed ? "Processed" : "Pending")
                     << endl;
                return;
            }
        }

        cout << "\nRequest ID not found.\n";
    }

    void run() {
        int choice;

        do {
            cout << "\n====================================\n";
            cout << " DOWNLOAD REQUEST SCHEDULER SYSTEM\n";
            cout << "====================================\n";
            cout << "1. Add Download Request\n";
            cout << "2. Display All Requests\n";
            cout << "3. Process Next Request\n";
            cout << "4. Search Request by ID\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cout << "Invalid input. Exiting program.\n";
                return;
            }

            switch (choice) {
                case 1:
                    addRequest();
                    break;
                case 2:
                    displayRequests();
                    break;
                case 3:
                    processRequest();
                    break;
                case 4:
                    searchRequest();
                    break;
                case 5:
                    cout << "\nThank you for using the system!\n";
                    break;
                default:
                    cout << "\nInvalid choice! Try again.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    DownloadScheduler scheduler;
    scheduler.run();
    return 0;
}
