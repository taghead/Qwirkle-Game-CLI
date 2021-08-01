# Main Report

Qwirkle is a game, particularly one with varying rules and scoring. The
aim of this assignment was to implement the Qwirkle game with the given
specifications. However, the implementation was left open ended leaving
explanation for justifications of efficiency, design and structure.

The report begins with descriptions of design elements, following is
analyses of each features governing data structures, their
implementations and efficiency.

To overview the ADTs, the flow of the program demanded certain classes
were made, *GameEngine, Player, LinkedList, Node* and *Tile*. There were
also mandatory attributes to consider such as the tile bag and board.
These ADTs led to a well-designed program as it efficiently,
compartmentalizing the data structures and code, improving readability,
reduces reptation and increases code clarity. Further, enabling
simplification of testing and debugging and of the code.

*Qwirkle* is the running file, supplying a menu with options to start a
new game, load game, show credits or exit. Furthermore, it instantiates
the *GameEngine* and uses the objects functions to prepare the game
state.

The *Tile* class handles the definition of a *Tile* object. A tile
consists of two categories, color and shape, when together they form one
Tile. The primitive data types such as char and int can easily create
uncertainty when no context is given in the codebase. Therefore, the
typedefs Color (char) and Shape (int)exist. *Tile* class is not
dependent on other classes for its operation.

Tile bag is the bag in which all tiles are found. In our implementation
it is an instance of the *LinkedList* class which is situated in the
*GameEngine* class as the variable *tileBag*. These tiles are shuffled
by selecting a random (*uniform_int_distribution)* node in the *tileBag*
re-instantiate the tile as a new node and add it to the back of the
*tileBag* and finally removing the selected node, this is repeated 72
times to ensure all tiles are fair game. the tiles are then distributed
this ensures that the game is fair. If a tile is removed from the bag,
the number of tiles in the bag is reduced. The *tileBag* depends on the
*LinkedList* class for its instantiation.

The Board is the variable responsible for keeping the game board state.
In our implementation it is a two-dimensional tile vector array situated
in the *GameEngine* class as the variable *board*. The *GameEngine*
class handles updating tiles within the board state to their respective
positions. The *board* depends on the class *GameEngine* for its
operations.

The *Player* class contain player data, each player is an instance of a
*Player* with their own: *LinkedList* as the variable *hand* to store
the player\'s hand, integer variable *score* to store the player\'s
score and string variable *name* to store the player\'s name. *Player*
depends on the class *LinkedList* and is used by *GameEngine*.

*GameEngine* class handles creating a game instance where everything
comes together. *LinkedList, Player* and their dependencies *Nodes and
Tiles* are therefore defined as variables. *GameEngine* checks if: a
move is valid, whose turn it is, ensures the position is unoccupied, a
tile from the *tilebag* can be taken, distribution of tiles to players
from the *tilebag,* calculating the score and updating the player\'s
*score* and ensuring rules are enforced.

When a game is started, one of the first steps is to call the
*QwikleEngine* method, after which the game will start. Upon user
interaction the *GameEngine* will refer to various checks to confirm
whether a command is allowed; this means whether the correct tile is
placed next to, below or above and whether no move is made on a spot
where there is already a tile. Moreover, *GameEngine* updates the score,
whether there is a winner, and who this winner may be. *GameEngine*
depends on the classes: *Player*, *Tile* and *LinkedList*.

*LinkedList* class handles the storage of nodes. Our group decided to
use a double LinkedList to store a collection of tiles for the player
hand and tile bag. Using double LinkedList lead to a well-designed
program by allowing for better implementation of Qwirkle as per the
rulebook with enhanced performance. Our reason for using a double
LinkedList is to improve the programs performance and efficiency.

A double LinkedList uses pointers to two specific nodes as reference,
the *head* and *tail*. The primary benefit of using a double LinkedList
is to supply an access point to the start and final node in the
LinkedList. The use of *next* and *prev* pointers in our nodes,
mitigates a full iteration of the LinkedList and allows for iterations
to start from either the *head* or *tail*.

For the implementation of Qwirkle, using a LinkedList is more suitable
than an array, because tiles can be added to or taken from either *tail*
or *head*. In comparison to an array, *LinkedList* does not have fixed
amount of memory or size, and releases memory when an item is removed.

We instantiate *LinkedList* and populate the *tileBag* with 72 tiles.
Afterwords migrating 6 tiles to each players' *hand*. Moreover, it
possible to increase the number of tiles in a *LinkedList*, to the
ruleset of 108 tiles.

Instances of *LinkedList* are used by the *hand* and *tileBag.* Using
functions inside the *LinkedList* object, *tiles* in a *node* becomes
accessible. Two distinct techniques are used when functions access
nodes: *addFront(), addBack(), deleteFront()* and *deleteBack()* all
reference the *head* and *tail* nodes. *getTile(), getNode(),
getNodeAt()* and *deleteAt()*, all use iteration to access certain
nodes.

These operations are used when a tile is drawn from the bag or placed in
the hand, it will be taken from the *head* of the *LinkedList*. The
double LinkedList was also used for the tile replacement function so
when a tile from the player's hand is put back into the tile bag then
they will be added to the *tail* of the *LinkedList*. The *LinkedList*
class is used by the classes: *Player* and *GameEngine*.

The tile replacement feature is when a tile from the player's hand is
put back into the tile bag, adding the *Tile* to the *tail* of the
*LinkedList*.

When a player draws a tile the first index of the *tileBag* is passed
into the *drawHand()* function. That *Tile* is then added to the
player\'s *hand*. The *GameEngine* then continues to delete the front of
the *tileBag* removing the migrated tile node from the tile bag.

Since the LinkedList used is a Double LinkedList, performance impact
when the *drawHand()* is overloaded with the *tileBag* the tile
immediately migrates into a player\'s *hand.* Furthermore, the *head*
tile of the *tileBag* will be placed in the *tail* of the player hand.
Finally, to ensure there are no duplicate tiles the *Node* of the
migrated *Tile* is then removed from the *head* of the *tileBag*.

The place tile feature is when a tile from the player's hand is put onto
the board.

Before a tile is placed onto the board, validations are made by
*GameEngine* to ensure placement is correct: tiles must be placed on the
side of another tile except for the first tile, tiles must match either
by color or shape with the surrounding tile/s and no identical tiles on
the same line/set.

The *GameEngine* will look for any tiles that will be connected to the
placed tile on the x and y axis to ensure the tile placement is valid.
The *GameEngine* will also confirm that the selected tile is within the
player\'s hand.

Since the user input denies input beyond 25 for columns and A-Z to rows
the Qwirkle board is constrained to 26x26. Furthermore, all indexes of
the *board* vector are initially populated with null pointers this
allows for indexes to correlate to the rows and columns of the board,
for example A25 will be \[0\]\[25\].

If the tile placement passes the validations, the tile will go into the
board vector, and it will be deleted from the player's hand. The tile
will also appear on the board print out in the terminal. When the tile
is placed, the scores will also be calculated and added to the player's
score counter. The score will be calculated according to the Qwirkle
rule. The *GameEngine* will look for any tiles connected to the placed
tile on the x axis and y axis and calculate the score according to the
rules of Qwirkle.

Performance is somewhat impacted when Tile object uses typedefs for
Color and Shape, due to comparisons needing conversions from string to
char and string to integer, reducing efficiency. However, this is
necessary to enforce rulesets. In contrast, the *board* being a vector
of *Tiles* enables the players *hand* to be directly compared with the
same typedefs, so no efficiency is lost.

The save game feature is when the current games state is saved as a
file.

The *saveGame()* function is called from *GameEngine* when a user inputs
the command save \<filename> while in game. This will save the game into
a file, each line in the save file contains a distinct set of data. In
order, player 1 name, player 1 score, player 1 hand, player 2 name,
player 2 score, player 2 hand, board dimension, tiles board placement,
tile bag content and current player.

To create a file, we used ofstring, which allows us to create and save
text to a file.

To save the player details access to each Players object is obtained
from *GameEngine*'s array of pointers *playerArrs\[\]*. With this
referencing index 0 and 1 of the *playerArr\[\]* supplies pointers to
player 1 and 2.

Save uses various techniques to reach the save state details. in the
*Player* and *LinkedList* class to obtain players names and scores,
methods from *LinkedList* class are employed on the *tileBag* and *hand*
outputted to a string and *GameEngine currentPlayer* variable is read
for the current player. The *board* vector is iterated over and
reformatted to TILE\@POS. Strangely, our implementation of save game
stores the board dimensions even though it is unused.

The performance impact is minimized through getters to players data,
with no conversions needed except for the board state out of necessity.

The load game feature enables a save file to be read and load each set
of data to their respective variables. Every line is sent into a fstream
and then pushed back into a vector; this was done for compatibility.
Since when directly interacting with the fstream a crash would occur.

Each line in a save file is assumed to contain a distinct set of data.
In order, player 1 name, player 1 score, player 1 hand, player 2 name,
player 2 score, player 2 hand, board dimension, tiles board placement,
tile bag content and current player.

Having been programmed for only two players it takes line 1,2 and 3 as
the first player\'s name, score and hand. Following suite lines 4,5 and
6 are taken as the second player\'s name, score and hand. When it gets
the players name, it is overloaded *Player*'s default constructor
creating a new instance. Points are added by using an incrementor method
*addPointer(int points)*. The players are then added to the
*playersArr\[*\].

When loading a set of tiles, it is added to the back of their respective
*LinkedList*, this would be either a player hand or tile bag. However,
for the board state coordinates get iterated over and translated to
their numerical counterpart. Hence, the obtaining integers for rows and
columns. With this direct index of the *board* is available. Following
this, a tile is then instantiated and added to the *board*.

The current player is obtained by comparing the instances of the Players
in the playersArr\[\] using their names and then updates the
*currentPlayer* variable with a pointer to their respective *Player*
object.

There is a performance impact on load game due to reliance on ifstream
and vector, the use of a vector is an added step is needed as a
workaround. Without the vector load game would not work, reason was not
discovered. In addition, rather than directly referencing each index of
the vector the wrong decision was made to reiterate over the vector.
This is completely redundant since each index is a line and can be
referenced.

Prior to implementing features, our group had a meeting to decide what
tests will be needed to successfully evaluate all part of Qwirkle. Every
test we used was to breakdown the features of Qwirkle into simpler parts
and makes sure each part is working before implementing the next part.
These tests considered feature tests and edge cases to make sure that
Qwirkle would run correctly. The list of tests is mentioned here:

-   Gameplay edge of board vertical

-   Test gameplay cannot add tile after Qwirkle

-   Test gameplay edge of board

-   Test gameplay invalid locations

-   Test gameplay invalid tile colour

-   Test gameplay invalid tile shape

-   Test gameplay no duplicate

-   Test gameplay obtaining a Qwirkle horizontal.

-   Test gameplay out of bound tile

-   Test gameplay place tile away from set

-   Test gameplay place tile not in hand

-   Test gameplays replace tile.

-   Test gameplay scoring place tile joining corner.

-   Test gameplay scoring qwirkle

-   Test gameplay typo location

-   Test gameplay typo tile

-   Test gameplay winner check (broken)

-   Test gameplay winner draw

-   Test gameplay winner quit.

-   Test menu credits

-   Test menu playername is not capital.

-   Test gameplay Qwirkle vertical

-   Test save game.

Over the span of our development, we utilized VSCode Collaborative, MS
Team and GitHub. MS Team allows for greater communication between group
members, it is easy to set meeting and allows communication between
group members. Furthermore, team members can upload their files to a
shared one drive improving the collaboration between teammates. Using
GitHub for development enabled to follow a git workflow in which all
members create their own feature branches, preventing conflicting work.

Qwirkle is a game, with varying rules and scoring. The longer we spent
working on this program, the more we realized it could go on endlessly.
With every review a new inadequacy is revealed. With our current
implementation majority of the performance is good enough to not be
called unoptimized, worst performance was the use a subpar method for
load game to work around a bug. The design of the ADT's supplies a
logical suite for developers to understand clearly given time to
understand the codebase. Though many of the good and bad design choices
are validated given their context, however we still have a lot to learn.


# Additional Enhancements

Qwirkles enhancements proved to be a challenge, provided that the group
codebase was stable and fully implemented with non-critical errors. This
milestone consisted of three individual enhancements under a separate
repository: help, expandable board and three to four player modes.

The minor enhancement help used the existing *userInput()* function in
*GameEngine* which already had a series of checks for inputs such as
place, replace and save. This implementation affixed a help statement to
the series of statements. When true hardcoded details on tile codes,
coordinates, and commands printed to the terminal. Performance is
affected by the added checks with every inputted command. However, this
is out of necessity, being hardcoded it has the benefit of not relying
on other data structure increasing the performance. Though at the cost
of scalability, hence if purple became replaced by silver the help code
block will need an update.

The minor enhancement expandable board used the existing *printBoard()*
function*.* Mandatory to prevent conflicts with older test cases the use
of setter functions enabled changing the value of the variable
*expandableBoard*. Through supposing the boolean *expandableBoard* is
false then the *BOARD_DIM* global declaration will be iterated printing
the entire board, otherwise on the condition it is false the position of
the most distant X and Y axis tile will be used as reference, printing
up to that position with the addition of one extra space. Additionally,
appended to the menu was a choice to toggle the feature, when selecting
*5* *Qwirkle.cpp* employs the following methods in *GameEngine*:
*enableExpandableBoard()* and *disableExpandableBoard()*. Performance is
better since it will reiterate less when printing a small size board.

The major enhancement three to four players had modifications to
*loadGame()* in *GameEngine* and *Qwirkle.cpp.* Consequently, ADTs
already accounted for scalability players since *Player* pointers go
into the *playerArr\[\]* which the size of increases the game player
size. To begin, the addition of option *six* in *Qwirkle.cpp* prompts
for the number of players either three or four then goes ahead to run
*addPlayer()* from the *GameEngine* for every name inputted,
automatically scaling players, turns, change turns and hands. Exception
to scalability is *loadGame()* the saves state prefixes three lines of
player data per player, this was hard coded with the assumption each
line had a data. To resolve this *loadGame()* iterates over the number
of lines minus four for non-player data and decides the number of
players by checking if line 0, 3, 6 or 9 is exists. Performance was
affected marginally, the if statements costed efficiency however out of
necessity. In contrast, the non-player data is assumed as the last four
lines reducing some iterations.

Testing occurred often and automatically when compiling using make. New
test files consist of:

-   New Game, Load, Save, Gameplay and Win condition for three to four
    players.

-   Centre, Lower Left, Lower Right, Upper Left and Upper Right
    positions for expandable board

-   Running the help command in game