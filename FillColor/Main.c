
#include <stdio.h>
#include <conio.h>

int main(int argc, char* argv[]) {

	//Khai báo
	FILE *f;
	errno_t a;
	int n, m, i, j, k, med1, med2, med, max;
	int deg[50][2], side[100][2], mamau[50], fillcolor[100][2], trgian[50];

	//Nhập số đỉnh, số cạnh từ tệp dothi.txt
	a = fopen_s(&f, "dothi.txt", "r");
	if (f == NULL) {
		printf("Chua co tep dothi.txt");
		_getch();
		return 0;
	}
	else {
		fscanf_s(f, "%d%d", &n, &m);
		//Nhập cạnh, tính bậc cho các đỉnh vào
		
		//Khởi tạo mảng bậc
		for (i = 0; i < n; i++)
		{
			deg[i][0] = i + 1;
			deg[i][1] = 0;
			fillcolor[i][0] = i + 1;
			fillcolor[i][1] = -1;
		}

		//Nhập cạnh
		for (i = 0; i < m; i++)
		{
			fscanf_s(f, "%d %d", &side[i][0], &side[i][1]);
			deg[side[i][0] - 1][1]++;
			deg[side[i][1] - 1][1]++;
		}
		fclose(f);
	}

	//Tạo bảng đối chiếu mã màu
	for (i = 0; i < n + 1; i++)
	{
		mamau[i] = 1048576 + i*5256;
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

	//Thuật toán tham lam
	fillcolor[deg[0][0] - 1][1] = mamau[0];
	for (i = 1; i < n; i++)
	{
		med = 0;
		j = 0;
		max = mamau[0];
		med1 = 0;
		do
		{
			if (side[j][0] == deg[i][0])
			{
				trgian[med] = side[j][1];
				med++;
			}
			if (side[j][1] == deg[i][0])
			{
				trgian[med] = side[j][0];
				med++;
			}
			j++;
		} while (med < deg[i][1]);
		for (k = 0; k < n+1; k++)
		{
			med1 = 0;
			for (j = 0; j < deg[i][1]; j++)
			{
				if (mamau[k] == fillcolor[trgian[j] - 1][1]) {
					med1++;
				}
			}
			if(med1 == 0)
			{
				fillcolor[deg[i][0] - 1][1] = mamau[k];
				break;
			}
		}
	}

	//In kết quả
	a = fopen_s(&f , "dothitomau.dot", "w");
	fprintf(f,"graph dothi\n{\n");

	for (i = 0; i < n; i++)
	{
		fprintf(f,"   %d [fillcolor=#%X, style=filled];\n", fillcolor[i][0], fillcolor[i][1]);
	}
	fprintf(f,"\n} \n");
	for (i = 0; i < m; i++)
	{
		fprintf(f,"   %d -- %d\n", side[i][0], side[i][1]);
	}
	fclose(f);
	_getch();
	return 0;
}