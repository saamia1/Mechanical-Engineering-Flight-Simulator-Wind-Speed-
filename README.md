
# Mechanical Engineering Flight Simulator Wind Speed


The software assumes a file exists with the simulation configuration. The file, named
“simulationConfiguration.txt”, should store the parameters for the wind simulation.
The first line stores the wind simulation configurations, namely the average speed, gust
value, duration, and step size). The second line stores the storm simulation parameters,
namely the storm probability, the minimum and maximum storm amplitude, and the
minimum and maximum storm duration values. The third line stores the microburst
parameters, namely thee microburst probability, the minimum and maximum burst
amplitude, and the minimum and maximum microburst duration values.

The program reads the average wind speed, the gust value, the duration and step size of
the wind speed simulation from the “simulationConfiguration.txt” file (first line). The
program should generate a data file named “WindSpeedData.txt” that contains the
simulated wind speeds. The time should always start with 0 seconds. Each line of the
“WindSpeedData.txt” file should contain the time in seconds and the corresponding
wind speed. The wind speed is a random number between the (average speed + gust
value) and the (average speed - gust value).

The wind speed simulation must include storm simulation. Assuming that the
possibility of encountering a storm at each time step is Pstorm, the program must add a
storm magnitude (a random number between the minimum and maximum storm
amplitude values) to the simulated wind speed for a duration T (a random number
between the minimum and maximum storm duration). The storm parameters are read
from the “simulationConfiguration.txt” configuration file (second line). The storm
simulation data must be stored in the file “StormData.txt”.

The storm simulation must also include a simulation of microbursts. Microburst are
simulated using three parameters: the possibility of encountering a microburst at each
time step in a storm (Pburs), the burst amplitude (a random number between the
minimum and maximum microburst amplitude values), and the duration of the burst (a
random number between the minimum and maximum storm duration values). The burst
parameters are read from the “simulationConfiguration.txt” configuration file (third
line). The microburst data must be stored in the file “BurstData.txt”.

Generate the final wind simulation by combining the wind speed, storm, and burst data
(three files created during steps 2 to 4). Save the result in a data file named
“WindSimulation.txt”. You may add a binary value to each line signifying whether a
storm is active at the same.
