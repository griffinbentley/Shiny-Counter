# Shiny-Counter
Keeps track of pokemon shiny hunts, storing the data in .txt files.

Files created are stored in the "Hunts" file and store the number of encounters, the generation, the method, whether or not the user has 
the shiny charm, as well as the date of the start of the hunt.
When the user finds a shiny, the user is given the option to delete the file or keep it. If kept, the file will also store the date
and time that the shiny pokemon was found.

Keeps track of the method used to hunt as well as the generation in order to use a binomial distribution to give a rough estimate of what 
the probability is that the next pokemon you encounter will be a shiny.

Runs in the console, and allows the user to create new hunts, or continue old ones.
Starting a new hunt will prompt the user for the name of the pokemon they're hunting, the generation their hunting in, the method their
using, and if applicable, whether or not they have the shiny charm. This creates a new file with the given information and starts a hunt.

Increments the count when the user presses enter, and displays the number of encounters they've had so far as well as the probability that
the next pokemon will be the shiny that they're looking for.
