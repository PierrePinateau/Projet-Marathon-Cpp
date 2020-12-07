#include "fonctions.h"

int get_random(int x, int y) {
	int random = (rand() % (y-x)) + x;
	return random;

}

/* Class Runner */
void Runner::newRunner(string nameRunner, int id, float weightRunner, float heightRunner, float shoesWeightRunner, float averageSpeedRunner, int trainingWeeksRunner, float lastAverageSpeed) {
	this->name = nameRunner;
	this->ID = id;
	this->weight = weightRunner;
	this->height = heightRunner;
	this->shoesWeight = shoesWeightRunner;
	this->averageSpeed = averageSpeedRunner;
	this->trainingWeeks = trainingWeeksRunner;
	this->LastAverageSpeed = lastAverageSpeed;
	this->distanceDecrease = (42195 / 2 * (1 + (trainingWeeksRunner - 8.0) / 8));
}

/* getters */

float::Runner::getDistance() {
	return this->distance;
}



bool::Runner::getIfFinish() {
	return this->RunnerFinish;
}
bool::Runner::getMoral() {
	if (this->moral != 0) {
		return true;
	}
	else {
		return false;
	}
}
float::Runner::getFinishTime() {
	return this->finishTime;
}

int::Runner::getRanking() {
	return this->ranking;
}


/* Setters */

// Set Ranking
void::Runner::setRanking(int ranking, int time) {
	this->ranking = ranking;
	this->finishTime = time;
	
	/* cout result in console*/
	/* if (time>0)
	{
	string timeFormat = to_string(int(time / 3600)) + "h " 
		+ to_string(int(time / 60 % 60)) + "mn et " 
		+ to_string(int(time % 60)) + "s";
	
	cout << this->name<< " just arrived in position : " << ranking << " (" << timeFormat << ")" << endl;

	}
	else
	{
	cout << this->name << " is a cheater" << endl;

	}*/ 

}

void::Runner::setMentalBoom(int ranking, int time) {
	this->ranking = ranking;
	this->finishTime = time;

	/* cout result in console*/
	/*if (time > 0)
	{
		string timeFormat = to_string(int(time / 3600)) + "h "
			+ to_string(int(time / 60 % 60)) + "mn et "
			+ to_string(int(time % 60)) + "s";
		cout << this->name << " just mental boom in position : " << ranking
			<< "  ||  At " << this->distance << "m from the start  (in " << timeFormat << ")" << endl;
	}
	else {
		cout << "" << " à mental boom en 0s" << endl;
	}*/
}


/* MAIN FUNCTION */
// Run Forest, run away
bool::Runner::run(float time, int timeMarathon, int* map, int orientationWind) {


	if(!this->RunnerFinish){
		float speed = this->averageSpeed / 3.6;
		float random = get_random(-20, 20) / 3.6;//vent aléatoire entre -20 et 20km/h



		/* EVENT (vent etc) */
		float  windSpeed = random;

		float pr = speed * this->weight * 0.98;
		float paL = 0.5 * 0.137 * this->height * (this->LastAverageSpeed / 3.6 + 0) * (this->LastAverageSpeed / 3.6 + 0) * this->LastAverageSpeed / 3.6;
		float ptmax = pr + paL;

		
		float pa = 0.5 * 0.137 * this->height * (speed + windSpeed*orientationWind) * (speed + windSpeed* orientationWind) * speed;
		speed = (ptmax - pa) / (this->weight * 0.98);

			
		
		/* ShoesWeight */
		float speedShoesDecrease = this->shoesWeight * 2.2 / 200;
		speed -= (speed * (speedShoesDecrease / 100));

		

		/* TrainingWeek */
		if (this->distance > this->distanceDecrease) {
			speed = speed * 0.8;

		}
		

		/* Hydration */
		float hydrationLevel = 1 - ((this->hydration/10000.0) / (0.5 * timeMarathon / 3600.0));

		if (hydrationLevel <= 0.8 && hydrationLevel >= 0.2)
		{
			speed -= (speed * (hydrationLevel * 5 / 100 / 0.8));
		}
		
		
		
		

		/* Altitude */

		float distanceRunned = 0;
		float pasDistance = 0.5;
		float baseSpeed = speed;

		/* Simulation, on fait le fait  courir sur pasDisatnce mètre en fonction de la pente 
		et on regarde le temps qu'il met jusqu'a ce qu'il dépasse le temps attendu
		*/

		while (time>0)
		{
			speed = baseSpeed;

			bool stillRunning = true;
			int locationMap = this->distance + distanceRunned;

			if (locationMap>42195)
			{
				time = 0;
				stillRunning = false;
			}
			if (stillRunning) {

				if (map[locationMap] == 666) { //checkpoint
					
					this->hydration = get_random(125, 500);
					this->moral = get_random(25, 50);
					locationMap++;
				}
					float percPenteVitesse = 0.0;
					int percPente = map[locationMap];

					if (percPente<0)//côte
					{
						percPenteVitesse = 1 + percPente / 1.5;
					}
					else if (percPente>0) {//pente
						percPenteVitesse = percPente * 0.35 / 1.5;
					}
					
					speed -= speed * (percPenteVitesse/100);
					
					time -= pasDistance / speed;//simulation 
					distanceRunned += pasDistance;

					

				
			}
		}


		


		this->distance += distanceRunned;

		
		/* If no more water in my body */
		if (hydrationLevel < 0)
		{

			if (this->distanceBeforeFF <= 0)
			{	
				this->moral = 0;
				this->RunnerFinish = true;
			}
			else {
				this->distanceBeforeFF -= distanceRunned;
			}
		}

		if (this->distance > 42195)// if runner finished 
		{
			this->RunnerFinish = true;
			return false;
		}
		else if (this->RunnerFinish) {//if runner stillnt running
			return false;
		}
		else {// if runner still running
			return true;
		}
	}
}





// Class Marathon
Marathon::Marathon(string name, int numberRunners) {
	this->name = name;
	this->numberRunners = numberRunners;
}
//getters :
int Marathon::getTime() {
	return time;
}



int Marathon::addFF() {
	this->ffRunner++;
	return (this->numberRunners - this->ffRunner+1);
}

int Marathon::addArrivedRunner() {
	this->arrivedRunner++;
	return this->arrivedRunner;
}

void Marathon::timeAdd(int time) {
	this->time+=time;
}


bool Marathon::ifFinish() {
	/* when all runners are arrived or forfeit */
	if (this->arrivedRunner+this->ffRunner >= this->numberRunners)
	{
		this->marathonFinish = true;
		cout << "Marathon fini !" << endl;
		return true;
	}
	else {
		return false;
	}
}


