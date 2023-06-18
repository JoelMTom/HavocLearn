#include "NeuralNetwork.h"

#include <ctime>
#include <cmath>	
#include <iostream>


#include "raylib.h"

namespace HavocLearn
{
	void NeuralNetwork::Init()
	{
		//srand(10);
		srand(unsigned int(time(0)));

		for (int i = 1; i < m_Arch.size(); i++)
		{
			m_Weights.push_back(Eigen::MatrixXf::Random(m_Arch[i], m_Arch[i - 1]));
			m_Biases.push_back(Eigen::RowVectorXf::Random(m_Arch[i]));
		}

		m_IntermediateResult.resize(m_Arch.size());

		const int screenWidth = 800;
		const int screenHeight = 450;

		InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

		while (!WindowShouldClose())
		{
			BeginDrawing();

			ClearBackground(RAYWHITE);

			DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

			EndDrawing();
		}
		CloseWindow();
		
	}

	void NeuralNetwork::PrintNeuralNetwork()
	{
		for (int i = 0; i < m_Arch.size() - 1; i++)
		{
			std::cout << "Layer " << i << ":" << std::endl;
			std::cout << "W" << i << ": " << std::endl << m_Weights[i] << std::endl;
			std::cout << "B" << i << ": " << std::endl << m_Biases[i] << std::endl;
			std::cout << "-------------------------------------\n" << std::endl;
		}
	}

	/*const Eigen::MatrixXf& NeuralNetwork::Forward(const Eigen::RowVectorXf& in)
	{
		m_IntermediateResult[0] = in * m_Weights[0] + m_Biases[0];
		ActivationFunction(m_IntermediateResult[0]);
		for (int i = 1; i < m_Arch.size() - 1; i++)
		{
			m_IntermediateResult[i] = m_IntermediateResult[i - 1] * m_Weights[i] + m_Biases[i];
			ActivationFunction(m_IntermediateResult[i]);
		}

		return m_IntermediateResult[m_Arch.size() - 2];

	}*/

	const Eigen::MatrixXf& NeuralNetwork::Forward(const Eigen::MatrixXf& in)
	{
		m_IntermediateResult[0] = in.transpose();
		for (int i = 1; i < m_Arch.size(); i++)
		{
			m_IntermediateResult[i] = (m_Weights[i - 1] * m_IntermediateResult[i - 1]).colwise() + m_Biases[i - 1];
			ActivationFunction(m_IntermediateResult[i]);
		}

		return m_IntermediateResult[m_Arch.size() - 1];
	}

	void NeuralNetwork::ActivationFunction(Eigen::MatrixXf& in)
	{
		//sigmoid activation function
		in = ((-in.array()).exp() + 1).inverse();


		//ReLU activation function
		/*in = in.array().max(0);*/
	}


	const float NeuralNetwork::Cost(const Eigen::MatrixXf& in, const Eigen::MatrixXf& d)
	{
		Eigen::MatrixXf res = Forward(in) - d.transpose();
		res = res.array().square();
		res /= 2;
		return res.rowwise().sum().mean();
	}

	void NeuralNetwork::Learn(const Eigen::MatrixXf& in, const Eigen::MatrixXf& d)
	{
		Forward(in);
		auto n = in.rows();
		std::vector<Eigen::MatrixXf> dbmatrix(m_Arch.size() - 1);
		std::vector<Eigen::MatrixXf> db(m_Arch.size() - 1);
		std::vector<Eigen::MatrixXf> dw(m_Arch.size() - 1);
		std::vector<Eigen::MatrixXf> da(m_Arch.size() - 2);
		for (auto i = m_Arch.size() - 1; i > 0; i--)
		{
			if (i == m_Arch.size() - 1)
			{
				dbmatrix[i - 1] = m_IntermediateResult[i] - d.transpose();
			}
			else
			{
				dbmatrix[i - 1] = da[i - 1];
			}

			dbmatrix[i - 1] = (dbmatrix[i - 1].array() * m_IntermediateResult[i].array() * (1 - m_IntermediateResult[i].array())).matrix();
			dw[i - 1] = dbmatrix[i - 1] * m_IntermediateResult[i - 1].transpose();
			if (i > 1)
			{
				da[i - 2] = m_Weights[i - 1].transpose() * dbmatrix[i - 1];
				da[i - 2] = da[i - 2] / n;
			}
			db[i - 1] = dbmatrix[i - 1].rowwise().mean();
			dw[i - 1] = dw[i - 1] / n;

		}

		for (int i = 0; i < m_Arch.size() - 1; i++)
		{
			m_Weights[i] -= m_LearnRate * dw[i];
			m_Biases[i] -= m_LearnRate * db[i];
		}
	}

	void NeuralNetwork::PrintForward(const Eigen::RowVectorXf& in)
	{
		std::cout << std::endl << Forward(in) << std::endl;
		std::cout << "-------------------------------------\n" << std::endl;
	}

	void NeuralNetwork::PrintCost()
	{
		return;
	}
}
