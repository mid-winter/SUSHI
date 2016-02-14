#pragma once
#include<random>

class cRandom
{
	//メルセンヌ・ツイスタ
	std::mt19937 engin_;
	//0.0 ~ 1.0のランダムを取れるもん　1.0は出ない
	std::uniform_real_distribution<float> zero_one_;

public:
	//コンストラクタ
	cRandom() :
		engin_(std::mt19937::default_seed),
		zero_one_(0.0f, 1.0f){}

	//同じランダムを出す
	void setSeed(const unsigned int new_seed)
	{
		engin_.seed(new_seed);
	}

	//0, lastを返す
	int fromZeroLast(const int last)
	{
		return engin_() % last;
	}

	//first, last を返す
	int fromFirstLast(const int first, const int last)
	{
		return first + fromZeroLast(last - first + 1);
	}
	//first, last を返す
	float fromFirstLast(const float first, const float last)
	{
		return first + (last - first)* fromZeroOne();
	}

	//0.0f, 1.0fを返す
	float fromZeroOne()
	{
		return zero_one_(engin_);
	}
};