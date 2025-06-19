#include "FloydWarshall.h"
#include "JohnsonAlgorithm.h"

using namespace std;

void menu(JohnsonAlgorithm& johnson) {
	while (true) {
		system("cls");
		cout << " -------------------- Menu ------------------ " << endl;
		cout << "1. Enter data for Johnson algorithm" << endl;
		cout << "2. Enter data for Floyd–Warshall algorithm" << endl;
		cout << "3. Run Johnson algorithm" << endl;
		cout << "4. Run Floyd–Warshall algorithm" << endl;
		cout << "5. Exit" << endl;
		cout << " -------------------------------------------- " << endl;
		int choice;
		cout << "Enter your choice: "; cin >> choice;
		if (choice == 1) 
		{ 
			while(true)
			{
				system("cls");
				cout << " ----------- Menu ----------- " << endl;
				cout << "1. Input data from keyboard" << endl;
				cout << "2. Input data from file" << endl;
				cout << "3. Exit" << endl;
				cout << " ---------------------------- " << endl;
				int choice;
				cout << "Enter your choice: "; cin >> choice;
				if (choice == 1) {
					int V, E;
					cout << "+ Number of vertices: "; cin >> V;
					cout << "+ Number of edges: ";    cin >> E;
					johnson = JohnsonAlgorithm(V);
					for (int i = 0; i < E; ++i) {
						int u, v, w;
						cout << "-------- Edge_ " << (i + 1) << " --------" << endl;
						cout << "Start vertex: ";      cin >> u;
						cout << "End vertex: ";        cin >> v;
						cout << "Weight: ";            cin >> w;
						cout << "---------------------------" << endl;
						johnson.addEdge(u, v, w);
					}
					cout << "Johnson data entry complete\n";
					system("pause");
				}
				else if (choice == 2) {
					int V, E;
					ifstream inFile;
					inFile.open("Data_Johnson.txt");
					if (inFile.is_open()) {
						inFile >> V >> E;
						johnson = JohnsonAlgorithm(V);
						for (int i = 0; i < E; i++) {
							int u, v, w;
							inFile >> u >> v >> w;
							johnson.addEdge(u, v, w);
						}
						cout << "Data successfully loaded from file!" << endl;
						system("pause");
					}
					else {
						cout << "Failed to open file!" << endl;
					}
					inFile.close();
				}
				else {
					break;
				}
			}

		}
		else if (choice == 2) {

		}
		else if (choice == 3) {
			johnson.Johnson();
			system("pause");
		}
		else if (choice == 4) {

		}
		else {
			break;
		}
	}
}

int main() {
	JohnsonAlgorithm johnson(0);
	//FloydWarshall floyd(0);
	menu(johnson);
    
	return 0;
}