# SZE-MOSZE-2020-VoicePlay
**How it works (currently):**
The game receives a json file containing the name of the map, the hero and the monsters. It reads the data from these files, if cannot find the files ot the data is not managable, throws an exception. If all files are right, the program sets up the map, puts the hero and the monsters on the map, and starts the game.
The game waits for the player to move the hero. The hero cannot see more on the map than its light_radius attribute, cannot step on walls and cannot go out of the map area. If it reaches an enemy, they start to fight until one of them is dead. During the fight the hero can gain experience, and if it reaches a certain amount of xp, it levels up. This means that the hero gets several boosts, such as damage (both magical and physical), health and light radius increase, and cooldown time decrease. If the hero dies, the game is over. If it wins, it can move further on the map, to the next monster. If all monsters die, the hero wins and the game ends with cleared map.
New map cannot be set while the old is used, and new hero cannot be placed on the map until the previous is dead.
The game has several unit tests, as well as memory leak check, which runs on push.
It also has doxygen documentation: https://teaching-projects.github.io/SZE-MOSZE-2020-VoicePlay/
