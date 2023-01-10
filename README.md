# 2110SimCity

Description:
This collection of files includes all necessary files to compile our program, SimCity. Our program will ask the user to provide the name of the configuration file they would like to read from. Once the filename is provided, all of the data provided in the config file will be read and saved. Following this, the region file that was specified in the config file will be read and parsed into a
vector. To represent each cell in the city grid we have created a Cell class which has multiple children classes that
represent the different possible kinds of zones (Residential, Commerical, Industrial, Combo, Road, Power Plant, and Power Line). The vector holds pointers to all of these values. In order to display a map of our city, a DisplayCity()
function is called in main after each file is read and processed. The city class holds most of all methods used for actual updating of values within the children classes of Cell and the Cell class itself.

Bonus:
No bonus was added to this project

An example of what the proper initial state output of our program should look like:

Welcome to SimCity.
Please proved the configuration file name: <user_input>

Our City Display:
|   |   | T | # | T | T | T |   |
| I | I | I | - | C | C | T |   |
| I | I | I | - | C | C | T |   |
| I | I | I | - | C | C | T |   |
| - | - | - | - | - | - | # | - |
|   |   | - | R | R | R | T |   |
|   |   | - | R | R | R |   |   |
|   |   | - | R | R | R |   |   |

CONTRIBUTERS:
Libra Bates
Joseph Caldwell
Aishat Oyedeji
Emma McKenzie

ROLES:
Libra Bates - Power classes, display city functionality, bug testing, creation of the makefile, main functionality, worker/good assignment and management functionality, and implementation of Industrial/Residential/Commercial update functionality
Joseph Caldwell - Initial framework design, implementation, and header files, City class (i.e. reading config file, reading region file, initializing cell_list vector, file processing), Pollution calculation functions, and bug testing,
pollution functionality, and adjaceny list functionality
Aishat Oyedeji - Industrial and Commercial classes logic
Emma McKenzie - Residential and Cell classes logic

INSTRUCTIONS:
1.) Run the Makefile using the command 'make SimCity'.
2.) Use the SimCity excecutable to run the program (i.e. ./SimCity).
3.) Provide configuration file name
4.) Program provides output up until maxtimestep or population ceases to grow
5.) Provide zoomed in region coordinates
6.) Final output is provided
