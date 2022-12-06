# Hashing-Inc


|| ================== Interface ================== ||

The interface to the program displays the car accident 
data based off of the longitude and latitude of the 
user's preference. The table displays the 10 most
frequent values for a condition in a sector. The two 
hashing buttons in the lower left corner change the 
hashing functions for the hashmaps used in data 
retreval and the timer represents how much time it 
took to retreive a set of data from the maps. 
The data set includes over 400,000 pieces of data 
for our program which the user can interact with.

The entire interface was made using SDL_Library.

|| =========================================== ||

|| ================== Hash Maps ================== ||

The HashMapD and HashMapS objects are two different
versions of the hash maps created for this project:
taking in doubles and strings as their keys respctively.

The two different hash maps under comparison are tied to
the different hashing functions we implmented. The 
constructor for each takes a boolean: true corresponds
with hashA() which is based on the Mid Square Method
and false corresponds with hashB() which uses the 
folding method.

|| =========================================== ||
