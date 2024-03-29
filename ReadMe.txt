
This application consists of a large number of mine objects that have a unique identifier, a position,
a team and can be marked as active or invulnerable.

Each loop, all active mines find what other non-invulnerable mines are within their blast radius
(i.e. what other mines would be damaged if it exploded).  Then, for each team, the mine with the most targets is exploded.

This continues until a round occurs in which no target mines were targeted/damaged by the explosion of mines from each team.

The team with the most remaining mines is declared the winner.

Tips:
-start by making sure the code compiles cleanly
-get the code to run (it does not run successfully right off the bat)
-verify that the code is accomplishing its main goal correctly
-look for ways to optimize the code for both performance and memory usage
  * there are significant gains that can be made in performance
-look to enforce defensive programming (const correctness, error checking and handling, etc.)
-invulnerable mines cannot take damage from other mines
-invulnerable mines are not targetable
-inactive mines cannot be triggered to explode. They can only explode from taking too much damage
-active mines, even if they are invulnerable, can be triggered to explode.
-even a mine with no targets can be triggered to explode
-chain reactions are possible (i.e. a fatally damaged mine will explode and damage its targets)



-friendly fire is on (an exploding mine will damage both enemy and friendly targets within its destructive radius)


- There is a 20% chance that when a mine explodes it will misfire and its destructive radius is cut by 50%. There
     is an additional 10% chance that it will do the opposite and its destructive radius is now 150% the original value.

- There is a 1% chance that a mine will provide stealth for allied mines within 200% of its destructive radius.
     Allied mines within the stealth radius will not be picked up in a targeting pass (similar to how invulnerable 
	 mines are ignored) but can still be damaged if within the destructive radius of an exploding mine.

- Mines now move. Add a velocity to each mine, with a random magnitude between zero and 15 units, in a random direction
     selected at time of mine creation. All mines move at the end of a turn.

- There is a 30% chance If at least two enemy mines are destroyed, that same team gets to explode another of its mines. The team
     can continue to explode mines until less than two enemy mines are destroyed when exploding one of their mines.


Do not modify the existing four command line input parameters used.  Feel free to add additional command line
inputs if needed, but make sure they are not required.

The four command line parameters are: <random seed> <number of worker threads> <number of teams> <number of mines per team>

Here are some sample results that show program output after bug fixes and initial cleanup. Again, don't obsess on 
these results. They are only provided as an initial goal for the cleanup portion. 

With the following input parameters: 987654 1 3 500
Object id 1071 position (-755.938, 93.133, -556.052) active Y invulnerable N
Object id 275 position (266.852, -32.735, 970.941) active Y invulnerable N
Object id 934 position (570.726, -275.077, -346.969) active N invulnerable N
Object id 1863 position (903.713, -300.514, 338.788) active Y invulnerable Y
Object id 3885 position (331.019, 376.530, 101.836) active Y invulnerable N
Object id 1470 position (-924.728, 20.487, -262.222) active Y invulnerable N
Object id 3201 position (379.957, 81.881, 458.886) active Y invulnerable N
Object id 2538 position (-119.712, -5.246, -345.135) active Y invulnerable N
Object id 455 position (-610.912, -547.901, -254.453) active Y invulnerable N
Object id 2465 position (429.587, -295.623, -74.395) active Y invulnerable N
Turn 1: Team 0 picks Mine with object id 2540 (with 2 targets) to explode
Turn 1: Team 1 picks Mine with object id 1104 (with 3 targets) to explode
Turn 1: Team 2 picks Mine with object id 553 (with 2 targets) to explode
Turn 2: Team 0 picks Mine with object id 2223 (with 2 targets) to explode
Turn 2: Team 1 picks Mine with object id 358 (with 3 targets) to explode
Turn 2: Team 2 picks Mine with object id 581 (with 2 targets) to explode
Turn 3: Team 0 picks Mine with object id 2466 (with 1 targets) to explode
Turn 3: Team 1 picks Mine with object id 4973 (with 2 targets) to explode
Turn 3: Team 2 picks Mine with object id 4548 (with 2 targets) to explode
Turn 4: Team 0 picks Mine with object id 53 (with 1 targets) to explode
Turn 4: Team 1 picks Mine with object id 4247 (with 2 targets) to explode
Turn 4: Team 2 picks Mine with object id 3923 (with 1 targets) to explode
Team 0 has 357 mines remaining
Team 1 has 385 mines remaining
Team 2 has 424 mines remaining
Team 2 WINS after 41 turns!!

With the following input parameters: 456 16 3 1000
Object id 5241 position (-502.488, 960.968, -673.866) active Y invulnerable N
Object id 8308 position (-429.672, 251.257, -690.690) active Y invulnerable N
Object id 9649 position (518.235, 635.312, -637.790) active Y invulnerable N
Object id 5054 position (-410.384, -226.540, -217.858) active Y invulnerable Y
Object id 2728 position (373.186, -937.465, -62.392) active Y invulnerable N
Object id 8632 position (-651.196, 446.681, 638.653) active Y invulnerable N
Object id 5008 position (893.620, 164.387, 108.439) active Y invulnerable N
Object id 7782 position (-93.770, -602.303, 213.354) active Y invulnerable Y
Object id 4858 position (-599.576, 697.088, -730.733) active Y invulnerable N
Object id 507 position (698.314, 716.660, 750.904) active Y invulnerable N
Turn 1: Team 0 picks Mine with object id 3398 (with 3 targets) to explode
Turn 1: Team 1 picks Mine with object id 2609 (with 4 targets) to explode
Turn 1: Team 2 picks Mine with object id 5427 (with 3 targets) to explode
Turn 2: Team 0 picks Mine with object id 6725 (with 3 targets) to explode
Turn 2: Team 1 picks Mine with object id 8415 (with 3 targets) to explode
Turn 2: Team 2 picks Mine with object id 9307 (with 3 targets) to explode
Turn 3: Team 0 picks Mine with object id 4314 (with 3 targets) to explode
Turn 3: Team 1 picks Mine with object id 4372 (with 3 targets) to explode
Turn 3: Team 2 picks Mine with object id 5106 (with 3 targets) to explode
Turn 4: Team 0 picks Mine with object id 4800 (with 3 targets) to explode
Turn 4: Team 1 picks Mine with object id 553 (with 3 targets) to explode
Turn 4: Team 2 picks Mine with object id 8917 (with 3 targets) to explode
Team 0 has 623 mines remaining
Team 1 has 722 mines remaining
Team 2 has 773 mines remaining
Team 2 WINS after 115 turns!!

With the following input parameters: 654321 12 5 1500
Object id 8591 position (-898.894, -290.149, 50.030) active Y invulnerable N
Object id 7110 position (-303.245, 718.965, -516.425) active Y invulnerable N
Object id 1466 position (637.269, -285.511, -88.674) active Y invulnerable N
Object id 10286 position (-312.755, -866.798, -53.850) active Y invulnerable N
Object id 10766 position (316.465, 415.601, 571.089) active Y invulnerable N
Object id 3469 position (956.990, -160.174, -141.135) active Y invulnerable N
Object id 44 position (447.428, -995.504, 571.503) active N invulnerable N
Object id 14905 position (-256.135, -394.987, -613.572) active Y invulnerable N
Object id 14267 position (-446.510, -544.947, 657.727) active Y invulnerable N
Object id 7000 position (-123.204, -670.820, 631.414) active Y invulnerable N
Turn 1: Team 0 picks Mine with object id 1920 (with 6 targets) to explode
Turn 1: Team 1 picks Mine with object id 1678 (with 6 targets) to explode
Turn 1: Team 2 picks Mine with object id 7753 (with 6 targets) to explode
Turn 1: Team 3 picks Mine with object id 7578 (with 5 targets) to explode
Turn 1: Team 4 picks Mine with object id 11024 (with 8 targets) to explode
Turn 2: Team 0 picks Mine with object id 947 (with 5 targets) to explode
Turn 2: Team 1 picks Mine with object id 801 (with 6 targets) to explode
Turn 2: Team 2 picks Mine with object id 7181 (with 6 targets) to explode
Turn 2: Team 3 picks Mine with object id 1515 (with 4 targets) to explode
Turn 2: Team 4 picks Mine with object id 3190 (with 6 targets) to explode
Turn 3: Team 0 picks Mine with object id 13719 (with 5 targets) to explode
Turn 3: Team 1 picks Mine with object id 5827 (with 6 targets) to explode
Turn 3: Team 2 picks Mine with object id 9530 (with 6 targets) to explode
Turn 3: Team 3 picks Mine with object id 8955 (with 4 targets) to explode
Turn 3: Team 4 picks Mine with object id 9682 (with 5 targets) to explode
Turn 4: Team 0 picks Mine with object id 14543 (with 5 targets) to explode
Turn 4: Team 1 picks Mine with object id 10092 (with 6 targets) to explode
Turn 4: Team 2 picks Mine with object id 1466 (with 4 targets) to explode
Turn 4: Team 3 picks Mine with object id 13093 (with 4 targets) to explode
Turn 4: Team 4 picks Mine with object id 10741 (with 5 targets) to explode
Team 0 has 565 mines remaining
Team 1 has 574 mines remaining
Team 2 has 738 mines remaining
Team 3 has 814 mines remaining
Team 4 has 949 mines remaining
Team 4 WINS after 278 turns!!

These results were obtained on a Windows 10 PC.


/////////////////////////////////////////////////////////////////////////////
