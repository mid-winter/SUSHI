#pragma once
#include<random>

class cRandom
{
	//�����Z���k�E�c�C�X�^
	std::mt19937 engin;
	//0.0 ~ 1.0�̃����_�����������@1.0�͏o�Ȃ�
	std::uniform_real_distribution<float> zero_one;

public:
	//�R���X�g���N�^
	cRandom():
		engin(std::mt19937::default_seed),
		zero_one(0.0f, 1.0f){}

	//���������_�����o��
	void setSeed(const unsigned int new_seed)
	{
		engin.seed(new_seed);
	}

	//0, last��Ԃ�
	int fromZeroLast(const int last)
	{
		return engin() % last;
	}

	//first, last ��Ԃ�
	int fromFirstLast(const int first, const int last)
	{
		return first + fromZeroLast(last - first + 1);
	}
	//first, last ��Ԃ�
	float fromFirstLast(const float first, const float last)
	{
		return first + (last - first)* fromZeroOne();
	}

	//0.0f, 1.0f��Ԃ�
	float fromZeroOne()
	{
		return zero_one(engin);
	}
};