#include<iomanip>
#include <iostream>
#include <time.h>

using namespace std;

const int MAX = 8;
int numbercount = 0;
// arr dùng để lưu vị trí của con ngựa đã đi
int arr[MAX][MAX];
int X[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int Y[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

// Set gia tri mang arr bang 0
void init() {

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			arr[i][j] = 0;
		}
	}
}

// Xuat vi tri cua quan ngua da di
void show() {
	//system("cls");
	cout << "\nVi tri cua con ngua da di!\n" << endl;

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			cout << setw(3);
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\n-------------------------------\n";
}

// Kiem tra mot vi tri co thuoc ban co khong
// Tra ve true neu hop le
bool isValid(int x, int y) {
	if (x < 0 || x > 7)
		return false;
	else if (y < 0 || y > 7)
		return false;
	else if (arr[x][y] != 0)
		return false;
	return true;
}

// Kiem tra tai vi tri x, y co con duong di
// return true neu van con duong
bool isRunXY(int x, int y) {
	
	for (int i = 0; i < MAX; i++) {
		int u = x + X[i];
		int v = y + Y[i];
		if (isValid(u, v))
			return true;
	}

	return false;
}

// Cho con ngua di chuyen theo cach ngau nhien
void randomRun(int x, int y) {
	
	arr[x][y] = 1;
	int count = 2;
	srand((int)time(0));
	int u = x;
	int v = y;

	do
	{
		
		int index = rand() % MAX;
		if (isValid(u + X[index], v + Y[index])) {
			u = u + X[index];
			v = v + Y[index];
			arr[u][v] = count;
			count++;
		}

	} while (isRunXY(u, v));
}

// Dem so luong cac o co the di duoc tai vi tri x, y
// Tra ve kieu int là so luong cac o co the di duoc
int numberRun(int x, int y) {
	int result = 0;
	
	for (int i = 0; i < MAX; i++) {
		if (isValid(x + X[i], y + Y[i])) {
			result++;
		}
	}
	
	return result;
}

// Cho con ngua di vao cac o co it kha nang di nhat
void minimumRun(int x, int y) {

	arr[x][y] = 1;
	int count = 2;
	int u = x;
	int v = y;

	do
	{
		int* numbers = new int[MAX];

		for (int i = 0; i < MAX; i++) {
			numbers[i] = numberRun(u + X[i], y + Y[i]);
		}

		int indexMin = 0;
		int min = MAX;
		for (int i = 0; i < MAX; i++) {
			if (numbers[i] < min && isValid(u + X[i], v + Y[i])) {
				min = numbers[i];
				indexMin = i;
			}
		}

		u = u + X[indexMin];
		v = v + Y[indexMin];
		arr[u][v] = count;
		count++;

	} while (isRunXY(u, v));
	
}

// Cho con ngua di bang thuat toan quay lui
void backTrackRun(int x, int y) {

	static int count = 1;
	static bool isEnd = false;

	arr[x][y] = count;

	if (count == MAX * MAX) {
		isEnd = true;
		return;
	}
	
	int* numbers = new int[MAX];

	for (int i = 0; i < MAX; i++) {
		numbers[i] = numberRun(x + X[i], y + Y[i]);
	}

	int indexMin = 0;
	int min = MAX;
	for (int i = 0; i < MAX; i++) {
		if (numbers[i] < min && isValid(x + X[i], y + Y[i])) {
			min = numbers[i];
			indexMin = i;
		}
	}

	int u = x + X[indexMin];
	int v = y + Y[indexMin];
	if (isValid(u, v)) {
		count++;
		backTrackRun(u, v);
	}

	if (isEnd) {
		return;
	}

	count--;
	arr[x][y] = 0;

}

// lam menu
void menu() {

	while (true)
	{
		int select = 0;
		do
		{
			system("cls");
			cout << "Menu\n";
			cout << "1. Cho con ngua di chuyen ngau nhien.\n";
			cout << "2. Cho con ngua di chuyen vao cac o co kha nang di tiep theo it nhat.\n";
			cout << "3. Su dung thuat toan quay lui\n";
			cout << "0. Thoat chuong trinh.\n";
			cout << "Moi ban lua chon: ";
			cin >> select;
		} while (select < 0 || select > 3);

		if (select == 0) {
			exit(0);
		}

		int x = 0;
		int y = 0;
		do
		{
			cout << "Nhap x: ";
			cin >> x;
			cout << "Nhap y: ";
			cin >> y;
		} while (x < 0 || x >= MAX || y < 0 || y >= MAX);


		if (select == 1) {
			init();
			randomRun(x, y);
			show();
		}
		else if (select == 2) {
			init();
			minimumRun(x, y);
			show();
		}
		else {
			init();
			backTrackRun(x, y);
			show();
		}

		system("pause");
	}

}
//----------------------------------------------------//
int main()
{
	menu();
}
//----------------------------------------------------//
