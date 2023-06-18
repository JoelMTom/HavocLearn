#pragma once

#include <vector>


#include "Eigen/Dense"

namespace HavocLearn
{
	class NeuralNetwork
	{
	public:
		NeuralNetwork()							//By default constructor, the class will create a Perceptron
		{	
			m_Arch.push_back(2);
			m_Arch.push_back(1);
			m_Weights.reserve(1);
			m_Biases.reserve(1);
			m_IntermediateResult.reserve(1);
			m_LearnRate = 1.0f;
		}

		NeuralNetwork(std::vector<uint32_t> arch, float learnrate)
			:m_Arch(arch), m_LearnRate(learnrate) {}


		void Init();

		//const Eigen::MatrixXf& Forward(const Eigen::RowVectorXf& in);
		const Eigen::MatrixXf& Forward(const Eigen::MatrixXf& in);
		void Learn(const Eigen::MatrixXf& in, const Eigen::MatrixXf& d);

		const float Cost(const Eigen::MatrixXf& in, const Eigen::MatrixXf& d);


		void PrintNeuralNetwork();
		void PrintForward(const Eigen::RowVectorXf& in);
		void PrintCost();

	private:
		void ActivationFunction(Eigen::MatrixXf& in);

	private:
		float m_LearnRate;
		std::vector<uint32_t> m_Arch;
		std::vector<Eigen::MatrixXf> m_Weights;
		std::vector<Eigen::VectorXf> m_Biases;
		std::vector<Eigen::MatrixXf> m_IntermediateResult;

	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	};
}
