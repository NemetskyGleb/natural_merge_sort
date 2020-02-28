
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
void PrintFile(char *name){
	int x;
	FILE *f;
	f = fopen(name, "r");
	if (!f) {
		puts("error");
		exit(-2);
		getch();
	}
	fscanf(f, "%d", &x);
	while (!feof(f)){
		printf("%d ", x);
		fscanf(f, "%d", &x);
	}
	fclose(f);
	}

void Split(FILE *A){
	int x, y;
	FILE *F[2];
	F[0] = fopen("F1.txt", "w");
	F[1] = fopen("F2.txt", "w");
	if ((!F[0]) || (!F[1]) || (!A)){
		puts("error");
		exit(-3);
		getch();
	}
	
	int n = 0;
	fscanf(A, "%d", &x);
	while (!feof(A)){
		fprintf(F[n], "%d ", x);
		fscanf(A, "%d", &y);
			while (!feof(A) && x < y ){
				x = y;
				fprintf(F[n], "%d ", x);
				fscanf(A, "%d", &y);
				}
		x = y;
		n = 1 - n;
	}
	fcloseall();
}
void Merge(FILE *A, FILE* F[2]){
	
	A = fopen("A.txt", "w");
	F[0] = fopen("F1.txt", "r");
	F[1] = fopen("F2.txt", "r");
		if ((!F[0]) || (!F[1]) || (!A)){
		puts("error");
		exit(-4);
		getch();
	}
	int numx[2];
	int numy[2];
	fscanf(F[0], "%d", &numx[0]);
	fscanf(F[1], "%d", &numx[1]);
	bool file1, file2;
	while (!feof(F[0]) && !feof(F[1])){
	file1 = file2 = false;
		while ( !file1 && !file2 )
		if (numx[0] <= numx[1]){
			fprintf(A, "%d ", numx[0]);
			file1 = End_File(F[0]);
			fscanf(F[0],"%d",&numy[0]);
			if (!feof(F[0]) && (numx[0] < numy[0]) ){
				numx[0] = numy[0];
			}
			else{
				fprintf(A, "%d ", numx[1]);
				file2 = End_File(F[1]);
				fscanf(F[1], "%d", &numy[1]);
				while (!feof(F[1]) && (numx[1] < numy[1]))
					numx[1] = numy[1];
				numx[0] = numy[0];
				numx[1] = numy[1];
			}       
	}
	else {
		fprintf(A, "%d ", numx[1]);
		file2 = End_File(F[1]);
		fscanf(F[1], "%d", &numy[1]);
		if (!feof(F[1]) && (numx[1] < numy[1]))
			numx[1] = numy[1];
		else{
			fprintf(A, "%d ", numx[0]);
			file1 = End_File(F[0]);
			fscanf(F[0], "%d", &numy[0]);
			while (!feof(F[0]) && (numx[0] < numy[0])){
				numx[0] = numy[0];
				fprintf(A, "%d ", numx[0]);
				file1 = End_File(F[0]);
				fscanf(F[0], "%d", &numy[0]);
			}
			numx[0] = numy[0];
			numx[1] = numy[1];
		}
	}
	}
			while (!feof(F[1])){
				fprintf(A, "%d ", numx[1]);
				file2 = End_File(F[1]);
				fscanf(F[1], "%d", &numx[1]);
			}
			while (!feof(F[0])){
				fprintf(A, "%d ", numx[0]);
				file1 = End_File(F[0]);
				fscanf(F[0], "%d", &numx[0]);
			}
			fcloseall();
}

}

bool End_File(char name[]){
  int x;
  FILE *F;
  F=fopen(name, "r");
   fscanf(F,"%d", &x)
  if (feof(F))
	  return true;
  else
	  return false;
   fclose(F);
}
int main(int argc, char const *argv[])
{
	PrintFile("A.txt");
	FILE *A;	
	FILE *F[2];
	A = fopen("A.txt", "r");
	Split(A);
	Merge(A,F);
	getch();
	return 0;
}