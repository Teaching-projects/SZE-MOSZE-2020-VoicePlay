# SZE-MOSZE-2020-VoicePlay
**How it works (currently):**
The main function utilizes 2 vector containers to store the "dead" and "alive" unit type entities. The data for the entities is read from the "unit_1", "unit_2" and "unit_3" json files by a static function. At first both units are in the "alive" vector and the while loop iterates until the size of the vector is larger than 1. The while loop contains an attack "phase" for the characters and the necessary outputs. Once a unit is dead it's moved to the "dead" vector and the while loop exits, there is a quick clean-up of potential memory leaks and the program exits.
The project is tested when pushed to the GitHub repo, it gets all six combinations of the json files, and writes the outputs into "output.txt". This txt is then compared to another txt file containing the expected output to see if there's any difference that indicates incorrect running.
Units now have a cooldown time, this is read from the json files along with their name, hp and damage. The project has doxygen documentation, the link to this:
https://teaching-projects.github.io/SZE-MOSZE-2020-VoicePlay/
