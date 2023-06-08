#include <iostream>
#include <cmath>

#include <Core/NeuralNetwork.h>


int main()
{
	HavocLearn::NeuralNetwork nn({2, 2, 1}, 1.0f);
	nn.Init();

	Eigen::Matrix<float, 4, 3> t{
				{ 0, 0, 0 },
				{ 0, 1, 1 },
				{ 1, 0, 1 },
				{ 1, 1, 0 }
			};

	Eigen::MatrixXf in = t.leftCols(2);
	Eigen::MatrixXf op = t.rightCols(1);

	for (int j = 0; j < 50*1000; j++)
	{
		std::cout << "Cost: " << nn.Cost(in, op) << "\n";
		nn.Learn(in, op);
	}



	for (int i = 0; i < t.rows(); i++)
	{
		Eigen::RowVectorXf in = t.row(i).leftCols(2);
		Eigen::RowVectorXf op = t.row(i).rightCols(1);
		std::cout << in(0) << " ^ " << in(1) << " = " << nn.Forward(in)(0, 0) << " Cost: " << nn.Cost(in, op) << std::endl;
	}
	std::cout << "-------------------------------------\n" << std::endl;


	return 0;
}