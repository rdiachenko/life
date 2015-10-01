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
		int getCell(int, int);
		void setCellOn(int, int);
		void setCellOff(int, int);
		void simulate();
		void clear();

	private:
		int n;
		int m;
		int* frontField;
		int* backField;
		void setCell(int, int, int);
		int countNeighbours(int, int);
		void swapFields();
};

#endif
