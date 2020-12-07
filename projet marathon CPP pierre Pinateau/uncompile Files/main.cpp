#include "fonctions.h"



int main()
{
    /* var GUI param*/
    const int WIDTH = 1800;
    const int HEIGHT = 999;

    
    float spacerHisto = 25;
    float spacerStat = 10;
    float posHeightRanking = 0;

    float heightHisto = 0;
    float spacerCatSize = 20;

    float maxWidthHisto = WIDTH*0.50;
    float posWidthStat = WIDTH * 0.82;
    float posWidthRanking = WIDTH * 0.51;

    int sizeTextStat = 20;
    const int maxDisplay = 9;

    srand(time(NULL));
    int random = (rand() % 5);

    ofstream resfich("Resultat.txt");


    ifstream ifsRunner("data/runners_list.json"); //open file with all runners
    IStreamWrapper iswRunner(ifsRunner);
    Document file_runners;
    file_runners.ParseStream(iswRunner);

    const Value& list_runners = file_runners["Runners"];


    ifstream ifsMap("data/maps/json/map-" + to_string(random) + ".json"); //open file with map
    IStreamWrapper iswMap(ifsMap);
    Document mapJson;
    mapJson.ParseStream(iswMap);
   
    const Value& mapTemp = mapJson["mapMarathon"];
    assert(mapTemp.IsArray());

    int map[42195];
    int y = 0;
    for (auto& v : mapTemp.GetArray()) {
        map[y] = v.GetInt();
        
        y++;

      
    }


    const int numberOfRunners = file_runners["numberOfRunners"].GetInt();
    Runner* runners = new Runner[numberOfRunners];

    heightHisto = ((HEIGHT - (spacerHisto * numberOfRunners)) / numberOfRunners);

    if (numberOfRunners > maxDisplay)//set GUI position
    {

    posHeightRanking = (spacerHisto + sizeTextStat) * maxDisplay + spacerCatSize;
    }
    else
    {
        posHeightRanking = (spacerHisto + sizeTextStat) * numberOfRunners + spacerCatSize;
    }

    int i = 0;
    for (auto& runner : list_runners.GetArray()) {//construct runners

            string name = runner["name"].GetString();
            int id = runner["id"].GetInt();
            float weight = stod(runner["weight"].GetString());
            float height = stod(runner["height"].GetString());
            float shoesWeight = stod(runner["shoesWeight"].GetString());
            float averageSpeed = stod(runner["averageSpeed"].GetString());
            int trainingWeeks = runner["trainingWeeks"].GetInt();
            int LastAverageSpeed = stod(runner["LastAverageSpeed"].GetString());

            runners[i].newRunner(name, id, weight, height, shoesWeight, averageSpeed, trainingWeeks, LastAverageSpeed);
            i++;
        }
        i = 0;
    

     Marathon *marathon = new Marathon("Marathonfinement", numberOfRunners);//sTarT the MaRathOn
  
     /* Some SFML var*/
     RenderWindow window(VideoMode(WIDTH, HEIGHT), "Marathon spicy montains");

     sf::Event event;
     sf::Font MyFont;
     MyFont.loadFromFile("data/anime-ace.regular.ttf");

     sf::Texture background;
     if (!background.loadFromFile("data/maps/images/map-" + to_string(random) + ".png"))
         return -1;

     sf::Sprite sprite(background);
     sprite.setScale(0.35, 0.4);
     sprite.setPosition(posWidthRanking, posHeightRanking);

     /* marathon param */
     bool marathonFisnish = marathon->ifFinish();
     const int pasTimer = 2;
     const float time = 1.0* pasTimer;

     const int displayGraph = (int)time * 1;
     bool ifDisplay = true;
     string ranking = "   -- Classement --\n\n";
     string mentalBoom = "";

     
     int runnerDisplay = 0;
     while (window.isOpen())
     {
         while (!marathonFisnish)//main while
         {
             runnerDisplay = 0;

             if (ifDisplay)
             {
                 window.clear();
             }

             for (int j = 0; j < numberOfRunners; j++)// iterate througt all runners
             {
                 if (!runners[j].getIfFinish())
                 {
            
                     if (!runners[j].run(time, marathon->getTime(), map, runners[i].ID)) { //if not still running

                         if (!runners[j].getMoral()) {// if mental boom
                             runners[j].setMentalBoom(marathon->addFF(), marathon->getTime());
                             

                                 int timeFinish = runners[j].getFinishTime();
                                 

                                 string timeFormat = to_string(int(timeFinish / 3600)) + "h "
                                     + to_string(int(timeFinish / 60 % 60)) + "mn et "
                                     + to_string(int(timeFinish % 60)) + "s";
                                 if (runners[j].getRanking() < 9)// SMFL add runner to ranking
                                 {

                                 mentalBoom += to_string(runners[j].getRanking()) + " - " +
                                     runners[j].name + " in " + timeFormat + "(Mental Boom)\n\n";

                             }
                                 if (resfich) {
                                     resfich << to_string(runners[j].getRanking()) + " - " +
                                         runners[j].name + " in " + timeFormat + "(Mental Boom) average speed =  " << runners[j].getDistance()/ timeFinish << " m/s" << endl;
                                 }

                         }
                         else if (runners[j].getIfFinish()) {// if runner finisished the race
                             runners[j].setRanking(marathon->addArrivedRunner(), marathon->getTime());



                             int timeFinish = runners[j].getFinishTime();

                             string timeFormat = to_string(int(timeFinish / 3600)) + "h "
                                 + to_string(int(timeFinish / 60 % 60)) + "mn et "
                                 + to_string(int(timeFinish % 60)) + "s";

                                if (resfich) {
                                    resfich << to_string(runners[j].getRanking()) + " - " +
                                        runners[j].name + " in " + timeFormat + " average speed =  " << runners[j].getDistance() / timeFinish << " m/s" << endl;
                                }
                             if (runners[j].getRanking()<9)// SMFL add runner to ranking
                             {

                                ranking += to_string(runners[j].getRanking()) + " - " +  
                                        runners[j].name + " in " + timeFormat + "\n\n";

                             }

                         }
                     }
                     else {
                         if (ifDisplay) {//display sfml histogram 
                             if (runnerDisplay < maxDisplay)
                             {

                             float posHeightStat = (sizeTextStat + spacerStat) * runnerDisplay + spacerStat +sizeTextStat;
                             sf::Text statRunner;
                             string statRunnerText = runners[j].name + " : " + to_string((int)runners[j].getDistance() - 1) + "m";

                             statRunner.setString(statRunnerText);
                             statRunner.setFont(MyFont);
                             statRunner.setCharacterSize(sizeTextStat);
                             statRunner.setPosition(posWidthStat, posHeightStat);
                             window.draw(statRunner);
                                 runnerDisplay++;
                         }
                         }
                     }
                        
                         
                     

                 }
                 
                 if (ifDisplay)
                 { /* only smfl here */
                    
                     window.draw(sprite);

                     sf::Text runnersWhoRun;
                     runnersWhoRun.setString("  -- Coureurs en lice  --");
                     runnersWhoRun.setFont(MyFont);
                     runnersWhoRun.setCharacterSize(sizeTextStat);
                     runnersWhoRun.setPosition(posWidthStat, 0);
                     window.draw(runnersWhoRun);

                         float posHeightRunner = (heightHisto + spacerHisto) * runners[j].ID;
                     
                         sf::Text nameRunner;
                         nameRunner.setString(runners[j].name);
                         nameRunner.setFont(MyFont);
                         nameRunner.setCharacterSize(heightHisto*0.7);
                         nameRunner.setPosition(0, posHeightRunner);
                         
                     

                     float widthHisto = runners[j].getDistance() * maxWidthHisto / 42195;

                     RectangleShape rectangle(Vector2f(widthHisto, heightHisto));
                     rectangle.setPosition(0, posHeightRunner);

                     if (runners[j].getIfFinish())
                     {
                         if (runners[j].getMoral())
                         {

                             rectangle.setFillColor(Color::Green);
                         }
                         else
                         {
                             rectangle.setFillColor(Color::Red);
                         }
                     }

                     else {

                        rectangle.setFillColor(Color::Blue);
                     }
                     window.draw(rectangle);
                     window.draw(nameRunner);
                     
                     

                    sf::Text rankingText;
                    rankingText.setString(ranking);
                    rankingText.setFont(MyFont);
                    rankingText.setCharacterSize(sizeTextStat);
                    rankingText.setPosition(posWidthRanking, 0);
                    window.draw(rankingText);
                     

                    
                 }

             }


             marathon->timeAdd(time);//l'horlorge tourne
             marathonFisnish = marathon->ifFinish();


             if (ifDisplay)
             {
                 window.display();
             }


             /* set fps of sfml*/
             if ((int)marathon->getTime() % displayGraph == 0)
             {
                 ifDisplay = true;
                 
             }
             else {
                 ifDisplay = false;
             }

             

             while (window.pollEvent(event))
             {
                 if (event.type == sf::Event::Closed)
                     window.close();
             }
         } // marathon fini

         while (window.pollEvent(event))
         {
             if (event.type == sf::Event::Closed)
                 window.close();
         }
     }

 }


 
    
 