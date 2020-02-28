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
    f.close();
}
void Split(std::fstream& A, std::fstream* F) {
    F[0].open("F1.txt", std::fstream::out);
    F[1].open("F2.txt", std::fstream::out);
    if (!F[0] || !F[1]) {
        std::cerr << "Error in create F1 and F2! ";
        std::exit(EXIT_FAILURE);
    }
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
        F[n] << "-1 "; // метка конца упор отрезка
		x = y;
		n = 1 - n;
	}
    A.close();
    F[0].close();
    F[1].close();
}

void Sort(const char* name) {
    using namespace std;
    fstream A(name, ios::in);
	if (!A.is_open()) {
		cerr << "File A isn't open!" << endl;
		std::exit(EXIT_FAILURE);
	}
    fstream F[2];
    std::cout << "Here is A.txt" << endl;
    PrintFile("A.txt");
    Split(A, F);
    cout << "F1 and F2 after Split:" << endl;
    PrintFile("F1.txt");
    PrintFile("F2.txt");
    fstream G[2];
    /* Merging */
    if (!F[1].eof()) {
        F[0].open("F1.txt", fstream::in);
        F[1].open("F2.txt", fstream::in);
        if (!F[0] || !F[1]) {
            cerr << "Error in create F1 and F2 or A! ";
            exit(EXIT_FAILURE);
        }
        G[0].open("G1.txt", fstream::out);
        G[1].open("G2.txt", fstream::out);
            if (!G[0] || !G[1]) {
            cerr << "Error in create G1 and G2! ";
            exit(EXIT_FAILURE);
        }
        Merge(F, G);
    }
/*     if(!G[1].eof()) {
        F[0].open("F1.txt", fstream::out);
        F[1].open("F2.txt", fstream::out);
        if (!F[0] || !F[1] || !A) {
            cerr << "Error in create F1 and F2 or A! ";
            exit(EXIT_FAILURE);
        }
        G[0].open("G1.txt", fstream::in);
        G[1].open("G2.txt", fstream::in);
        if (!G[0] || !G[1]) {
            cerr << "Error in create G1 and G2! ";
            exit(EXIT_FAILURE);
        }
        Merge(G, F);
    } */
    std::remove("F1.txt");
    std::remove("F2.txt");
    A.close();
    F[0].close();
    F[1].close();
}

void Merge(std::fstream* F, std::fstream* G) {
    using namespace std;
	int x[2];
	int y[3];
	F[0] >> x[0];
	F[1] >> x[1];
	int n = 0;
	while (!F[0].eof() || !F[1].eof()) {
		int k;
		if(x[0] < x[1]) 
			k = 0;
		else k = 1;
		G[n] << x[k];
		F[k] >> y[k];
		if (x[k] <= y[k]){
			x[k] = y[k];
		}
		else { // Дописываем хвост из F[1-k]
			G[n] << x[1-k];
			F[1-k] >> y[1-k];
			while (F[1-k].eof() && x[1-k] <= y[1-k]) {
				x[1-k] = y[1-k];
				G[n] << x[1-k];
				F[1-k] >> y[1-k];
			}
			x[1-k] = y[1-k];
			x[k] = y[k];
			n = 1- n;
		}
		while (!F[0].eof()) {
			G[n] << x[0];
			F[0] >> y[2];
			while (!F[0].eof() && y[2] != -1 ){ // check -1
				y[0] = y[2];
                x[0] = y[0];
				G[n] << x[0];
				F[0] >> y[2];
			}
			x[0] = y[0];
			n = 1 - n;
		}
		while (!F[1].eof()) {
			G[n] << x[1];
			F[1] >> y[1];
			while (F[1].eof() && x[1] <= y[1]){
				G[n] << x[1];
				F[1] >> y[1];
			}
			x[1] = y[1];
			n = 1 - n;
	    }
    }
}
