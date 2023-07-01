#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace std;

void load_configuration(ifstream& infile);//delaration of functons by function prototype
int generate_Wind_Speed(ifstream& infile, ofstream& outfile); //for wind speed data file
void generateStormData(ifstream& infile, ofstream& outfile, int duration); //for storm data file
void generateBurstData(ifstream& infile, ofstream& outfile, int duration); //for burst data file
void generate_WindSimulation(ofstream& windsimulationFile); //for combining all three data files

int main()

{
    ifstream infile;//declaring inout file stream
    ofstream windfile, stormfile, burstfile, windsimulationFile;//declaring output file streams
    load_configuration(infile);//calling functions
    int wind_duration = generate_Wind_Speed(infile, windfile);
    cout << "Wind Speed Data file made successfully!" << endl;
    generateStormData(infile, stormfile, wind_duration);
    cout << "Storm Data file made successfully!" << endl;
    generateBurstData(infile, burstfile, wind_duration);
    cout << "MicroBurst Data file made successfully!" << endl;
    generate_WindSimulation(windsimulationFile);
    cout << "Wind Simulation File generated successfully!" << endl;

    return 0;
}
void load_configuration(ifstream& infile) //function for opening data file for taking inputs
{
    infile.open("simulationConfiguration.txt");
    if (infile.fail())
    {
        cerr << "Error opening the data file!" << endl;
        exit(1);
    }
}

int generate_Wind_Speed(ifstream& infile, ofstream& outfile) //function for wind speed data file formation
{
    srand(time(NULL));
    outfile.open("WindSpeedData.txt"); //opening file for output
    if (outfile.fail())
    {
        cerr << "Error creating the data file!" << endl;
        exit(1);
    }

    int avg_wind; //input variable
    int gust;
    int duration;
    int step_size;

    int random_wind;//output variable


     //reading variables from the file

    infile >> avg_wind;
    infile >> gust;
    infile >> duration;
    infile >> step_size;

    for (int i = 0; i < (duration * 3600); i = i + step_size) //loop until wind duration not ended
    {
        random_wind = rand() % ((avg_wind + gust) - (avg_wind - gust) + 1) + (avg_wind - gust);
        outfile << i << "\t" << random_wind << "\n";
    }
    return duration * 3600; //to be used in storm and burst functions' loops
}

void generateStormData(ifstream& infile, ofstream& outfile, int wind_duration)// function for creating storm data file
{
    srand(time(NULL));

    outfile.open("StormData.txt", ios::out); //opening file for output
    if (outfile.fail())
    {
        cerr << "Error creating the data file!" << endl;
        exit(1);
    }

    double storm_prob; //declaring variable to be read from the input data file
    int storm_magnitude, storm_duration, min_amp, max_amp, min_dur, max_dur, number;

    infile >> storm_prob; //reading from the input file stream
    infile >> min_amp;
    infile >> max_amp;
    infile >> min_dur;
    infile >> max_dur;


    for (int i = 0; i <= wind_duration; i = i + 10) //loop until wind duration for storm
    {
        number = rand() % 100 + 1; //taking storm probability into consideration 
        if (number <= (storm_prob * 100))
        {
            storm_duration = rand() % ((max_dur)-(min_dur)+1) + (min_dur);
            storm_magnitude = rand() % ((max_amp)-(min_amp)+1) + (min_amp);
            outfile << i << "\t" << storm_magnitude << "\t" << storm_duration << "\n";
        }
        else //if probability less than storm probability then no storm
        {
            outfile << i << "\t" << "0" << "\t" << "0" << "\n";
        }

    }
}

void generateBurstData(ifstream& infile, ofstream& outfile, int wind_duration) //function for formation of burst data file
{
    srand(time(NULL));

    outfile.open("BurstData.txt", ios::out); //open burst data file for output
    if (outfile.fail())
    {
        cerr << "Error creating the data file!" << endl;
        exit(1);
    }

    double burst_prob; //declaring variables to be read from the input data file
    int burst_magnitude, burst_duration, min_amp, max_amp, min_dur, max_dur, number;

    infile >> burst_prob; //reading from the input data file
    infile >> min_amp;
    infile >> max_amp;
    infile >> min_dur;
    infile >> max_dur;


    for (int i = 0; i <= wind_duration; i = i + 10) {//loop for until the wind is blowing
        number = rand() % 100 + 1;
        if (number <= (burst_prob * 100)) {

            burst_duration = rand() % ((max_dur)-(min_dur)+1) + (min_dur);
            burst_magnitude = rand() % ((max_amp)-(min_amp)+1) + (min_amp);
            outfile << i << "\t" << burst_magnitude << "\t" << burst_duration << "\n";
        }

        else //if probability greater than burst probability then no microburst
        {
            burst_duration = rand() % ((max_dur)-(min_dur)+1) + (min_dur);
            outfile << i << "\t" << "0" << "\t" << "0" << "\n";
        }
    }
}

void generate_WindSimulation(ofstream& windsimulationFile)// function for combining all the three data files created
{
    ifstream windfile, stormfile, burstfile; //declaring files
    windsimulationFile.open("WindSimulation.txt"); //opening file for taking input

    int wind_time, storm_time, burst_time; //declaring variables for reading from the input files
    int storm_duration, burst_duration;
    int wind_magnitude, storm_magnitude, burst_magnitude, final_wind_magnitude;

    while (!windfile.eof() || !stormfile.eof() || !burstfile.eof())//read data till end of file reached in either files
    {
        windfile >> wind_time;
        windfile >> wind_magnitude;
        stormfile >> storm_time;
        stormfile >> storm_magnitude;
        stormfile >> storm_duration;

        burstfile >> burst_time;
        burstfile >> burst_magnitude;
        burstfile >> burst_duration;

        final_wind_magnitude = wind_magnitude;

        if (wind_time == storm_time) //wind has storm only
        {
            if (storm_time == burst_time) //wind has both storm and bursts 
            {
                for (int j = 0; j < burst_duration; j++)
                {
                    wind_time++;
                    final_wind_magnitude = wind_magnitude + storm_magnitude + burst_magnitude;//assinging total magnitude to a final value
                    windsimulationFile << wind_time << "\t" << final_wind_magnitude << "\n";
                }
            }

            else //wind and storm
            {
                for (int i = 0; i < storm_duration; i++)
                {
                    wind_time++;
                    final_wind_magnitude = wind_magnitude + storm_magnitude;
                    windsimulationFile << wind_time << "\t" << final_wind_magnitude << "\n";
                }
            }
        }
        else //just wind 
        {
            windsimulationFile << wind_time << "\t" << final_wind_magnitude << "\n";
        }
    }
}

