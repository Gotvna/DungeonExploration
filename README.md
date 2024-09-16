# DungeonExploration

## Code Conventions

- All identifiers are in `camelCase`
- Class names start with a capital
- Attribute and method names start with a lower-case letter
- Virtual methods must be explicitly redeclared as virtual in child classes (`virtual` keyword must appear)

## Game Loop

Initialize :

- window
- inputs
- load a map
- spawn player
- draw grid layout

While player not dead and not won :

- draw player stats
- if enemy nearby :
	draw enemy name + stats

- determine cells we can move on
- draw these cells
- While player picking cell (key is not space or enter) :
	- if arrow :
		move destination
		draw destination
	- if enter OR space :
		pick destination
		break
- move player to destination
- if enter :
	player attack
- for each enemy e :
	execute behavior for e

## User Interface

Top 2 rows :

- Nearby enemy HP
- Nearby enemy stats
- (Number of remaining enemies)

Bottom 2 rows :

- Player HP
- Player stats
- Messages ("You've been hit" etc...)

Middle :

- Fixed grid

- Delimited by walls

## Level Creation

TODO : Complete.