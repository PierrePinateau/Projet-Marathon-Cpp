#pragma once

#include <vector>

#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <string> 
#include<random>

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include <rapidjson/istreamwrapper.h>

using namespace rapidjson;
using namespace sf;
using namespace std;



class Marathon {
	
public:
	string name;

	Marathon(string name, int numberRunners);
	~Marathon();

	// setters & getters
	int addFF();
	int addArrivedRunner();
	void timeAdd(int time);

	int getTime();
	bool ifFinish();


private:
	int numberRunners = 0;
	int arrivedRunner = 0; //number of runner who arrived
	int ffRunner = 0; //number of runners who dropped out
	int time = 0;
	bool marathonFinish = false;

};

class Runner  {
public:
	string name = "Bancho";
	int ID = 0;

	//Runner(string nameRunner, int id, float weightRunner, float heightRunner, float shoesWeightRunner, float averageSpeedRunner, int trainingWeeksRunner);
	//~Runner();

	// setters & getters
	void newRunner(string nameRunner, int id, float weightRunner, float heightRunner, float shoesWeightRunner, float averageSpeedRunner, int trainingWeeksRunner, float LastAverageSpeed);
	bool getIfFinish();
	float getFinishTime();
	bool getMoral();
	int getRanking();

	/*
	float getSpeed();
	float getShoesWeight();
	int getTrainning();
	float getWeight();
	float getHeight();
	float getHydration();
	*/
	float getDistance();

	bool run(float time, int timeMarathon, int* map, int orientationWind);
	void setRanking(int ranking, int time);
	void setMentalBoom(int ranking, int time);



private:
	float weight = 0.0;
	float height = 0.0;
	float shoesWeight = 0.0;
	float averageSpeed = 0.0;
	int trainingWeeks = 0;
	float LastAverageSpeed = 0;

	float distanceDecrease = 42195; //selon les semaines d'entrainement
	int hydration = 500;
	int moral = 100;
	float distanceBeforeFF = 2000.0;

	int RunnerFinish = false;
	int ranking = 0;
	int finishTime = 0;
	float distance = 0.0;

};