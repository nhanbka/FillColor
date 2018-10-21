#include <stdio.h>
#include <conio.h>

int main(int argc, char* argv[]) {
	//Khai báo
	int n, m, i, j, med1, med2;
	int deg[100][2];
	int side[100][2];
	//Nhập số đỉnh, số cạnh
	printf("Nhap vao so dinh: ");
	scanf_s("%d", &n);
	printf("Nhap vao so canh: ");
	scanf_s("%d", &m);
	//Khởi tạo mảng bậc
	for (i = 0; i < n; i++)
	{
		deg[i][0] = n;
		deg[i][1] = 0;
	}
	//Nhập cạnh, tính bậc cho các đỉnh vào
	for (i = 0; i < m; i++)
	{
		printf("Nhap canh %d:", i + 1);
		scanf_s("%d %d", &side[i][0], &side[i][1]);
		deg[side[i][0]][1]++;
		deg[side[i][1]][1]++;
	}
	//Sắp xếp mảng bậc theo thứ tự giảm dần của bậc
	for (i = 0; i < n - 1; i++)
	{
		for (j = i; j < n - 1 ; j++)
		{
			if (deg[j][1] < deg[j + 1][1]) {
				med1 = deg[j][0];
				med2 = deg[j][1];
				deg[j][0] = deg[j + 1][0];
				deg[j][1] = deg[j + 1][1];
				deg[j + 1][0] = med1;
				deg[j + 2][1] = med2;
			}
		}
	}
	for (i = 0; i < m; i++)
	{
		printf("%d -- %d\n", side[i][0], side[i][1]);
	}
	_getch();
	return 0;
}