#ifndef LIFE_MODEL_H
#define LIFE_MODEL_H

class LifeModel
{
	public:
		LifeModel(int width, int height)
		{
			n = width;
			m = height;
			frontField = new int[n * m];
			backField = new int[n * m];
		}
		~LifeModel()
		{
			delete[] frontField;
			delete[] backField;
		}
		void setCell(int row, int col, int val)
		{
			frontField[row * n + col] = val;
		}
		void simulate();

	private:
		int n;
		int m;
		int* frontField;
		int* backField;
};

#endif
