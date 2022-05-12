#include <fstream>
#include <iostream>

// TASK 1
//
// .

int** task4_read(char* NAME)
{
	std::ifstream file(NAME, std::ifstream::in);

	int size;
	file >> size;

	int** matrix = new int* [size];

	for (int i = 0; i < size; i++)
	{
		//fill matrix with zeroes
		matrix[i] = new int[size];
		memset(matrix[i], 0, size * sizeof(int));
	}

	int a, b;
	while (file >> a >> b)
	{
		matrix[b - 1][a - 1] = 1;
	}

	file.close();

	return matrix;
}

void task4_del(int** mtrx, int size)
{
	for (int i = 0; i < size; i++) {
		delete[] mtrx[i];
	}
	delete[] mtrx;
}

int** task4_multiply(int** mtrx1, int** mtrx2, int size)
{
	int** result = new int* [size];

	for (int i = 0; i < size; i++)
	{
		result[i] = new int[size];
		memset(result[i], 0, (size) * sizeof(int));
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < size; k++)
			{
				int a1 = mtrx1[i][k];
				int a2 = mtrx2[k][j];
				result[i][j] += a1 * a2;
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			std::cout << result[i][j] << " ";

		std::cout << "\n";
	}
	std::cout << "\n\n";

	return result;
}

void task4_equate(int** mtrx1, int** mtrx2, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			mtrx1[i][j] = mtrx2[i][j];
	}
}

bool task4_cycle_check(int** mtrx, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (mtrx[i][i] == 0) return false;
	}
	return true;
}

int main()
{

	// TASK 4
	//
	// .
	char name[] = "matrix.txt";
	std::ifstream file(name, std::ifstream::in);
	int size;
	file >> size;
	file.close();
	int** mtrx = task4_read(name);
	int** temp1 = task4_read(name);

	if (task4_cycle_check(temp1, size))
	{
		std::cout << "Cycle exists.\n\n";
		return 0;
	}

	for (int i = 0; i < size; i++)
	{
		int** temp2 = task4_multiply(temp1, mtrx, size);

		task4_equate(temp1, temp2, size);

		if (task4_cycle_check(temp1, size))
		{
			std::cout << "Cycle exists\n\n";
			break;
		}
	}

	// TASK 4
	// 
	// 
	// .

}