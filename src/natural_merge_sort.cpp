#include"../lib/natural_merge_sort.h"
void PrintFile(const char* name) {
    using namespace std;
    fstream f(name, ios::in);
	if (!f.is_open()) {
		cerr << "File isn't open!" << endl;
		std::exit(EXIT_FAILURE);
	}
    if(!f) {
        std::cerr << "Error in reading file" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    int x;
    while(f >> x) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}
void Split(std::fstream& A, std::fstream* F) {
    int n = 0, x, y;
	A >> x;
    while (!A.eof()) {
        F[n] << x << " ";
		A >> y;
			while (!A.eof() && x <= y ){
				x = y;
                F[n] << x << " ";
                A >> y;
			}
		x = y;
		n = 1 - n;
	}
}

void Sort(const char* name) {
    using namespace std;
    fstream A(name);
	if (!A.is_open()) {
		cerr << "File A isn't open!" << endl;
		std::exit(EXIT_FAILURE);
	}
    fstream F[2];
    F[0].open("F1.txt", fstream::out);
    F[1].open("F2.txt", fstream::out);
    if (!F[0] || !F[1]) {
        cerr << "Error in create F1 and F2! ";
        exit(EXIT_FAILURE);
    }
    std::cout << "Here is A.txt" << endl;
    PrintFile("A.txt");
    Split(A, F);
    cout << "F1 and F2 after Split:" << endl;
    F[0].close();
    F[1].close();
    PrintFile("F1.txt");
    PrintFile("F2.txt");
    fstream G[2];
    std::remove("F1.txt");
    std::remove("F2.txt");
    A.close();
    F[0].close();
    F[1].close();
}
