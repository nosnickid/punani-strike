# map dimensions
x 40
y 40

# tile id's
#water	
t 0 data/tiles/water 
#land
t 1 data/tiles/grass 
#trees
t 20 data/tiles/trees
#road - north south
t 2 data/tiles/road00 
#road - east west
t 3 data/tiles/road01
#crossroads
t 19 data/tiles/road02
#t-junction (exit: w)
t 20 data/tiles/road03
#t-junction (exit: s)
t 21 data/tiles/road04	
#t-junction (exit: n)
t 22 data/tiles/road05	
#t-junction (exit: e)
t 23 data/tiles/road06
#corner sw
t 24 data/tiles/road07
#corner nw
t 25 data/tiles/road08
#corner ne
t 26 data/tiles/road09
#corner se
t 27 data/tiles/road10

	
#grass
t 4 data/tiles/null 
#university
t 5 data/tiles/null 


t 6 data/tiles/city01 
#highrise 1
t 7 data/tiles/city02 
#highrise 2
t 8 data/tiles/city03 
#highrise 3
t 9 data/tiles/city04 
#highrise 4
t 10 data/tiles/city05 
#highrise 5
t 11 data/tiles/city06 
#highrise 6
t 12 data/tiles/city07 
#highrise 7
t 13 data/tiles/city08 
#highrise 8
t 14 data/tiles/city09 
#highrise 9
t 15 data/tiles/city10 
#highrise 10
#highrise 11 - really tall!
t 16 data/tiles/city11
	
#stadium c1
t 30 data/tiles/stadium_0
#stadium c2
t 31 data/tiles/stadium_1
#stadium c3
t 32 data/tiles/stadium_2
#stadium c4
t 33 data/tiles/stadium_3
#stadium s1
t 34 data/tiles/stadium_4
#stadium s2
t 35 data/tiles/stadium_5
#stadium s3
t 36 data/tiles/stadium_6
#stadium s4
t 37 data/tiles/stadium_7
t 99 data/tiles/grass

begin
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 27 3 3 3 21 3 3 3 3 3 3 3 3 3 3 3 21 3 3 3 3 3 3 3
0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 2 6 7 9 2 5 5 5 5 5 5 5 5 5 5 5 2 7 9 8 6 9 13 15
0 0 0 0 0 0 0 0 0 0 0 0 1 27 3 3 25 7 8 9 2 5 5 5 5 5 5 5 5 5 5 5 2 13 10 15 6 10 11 12
0 0 0 0 0 0 0 0 0 0 0 1 1 2 7 7 12 11 15 10 2 5 5 5 5 5 5 5 5 5 5 5 2 3 3 3 2 10 7 6
0 0 0 0 0 0 1 1 1 1 1 1 1 2 6 10 15 9 12 6 2 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 2 9 13 15
0 0 0 0 0 0 1 2 3 3 3 3 3 2 15 9 13 11 10 9 2 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 2 8 7 10
0 0 0 0 0 0 1 2 6 7 8 8 6 10 11 8 15 13 12 9 2 5 5 5 5 5 5 5 5 5 5 5 5 5 5 2 3 3 3 3
0 0 0 0 0 0 1 2 3 3 3 3 3 3 3 3 3 3 3 3 22 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 4 4 4 4
0 0 0 0 0 0 1 2 6 7 8 9 10 11 12 13 12 15 11 12 6 9 8 10 2 12 13 6 7 8 10 11 9 2 12 2 4 4 4 4
0 0 0 0 0 0 1 2 9 2 3 3 3 3 3 12 9 6 8 15 9 11 10 8 2 9 6 15 11 12 9 7 13 2 15 2 3 2 3 3
0 0 0 1 1 1 1 2 7 2 15 12 9 15 9 16 6 2 3 3 3 3 2 3 2 6 9 15 10 11 6 9 7 2 13 15 6 7 11 12
0 0 0 1 1 1 1 2 8 2 6 10 11 12 9 7 9 2 10 6 15 15 9 13 8 10 15 10 15 9 10 2 3 2 6 15 9 7 7 9
0 0 0 1 1 1 1 2 3 19 3 3 3 3 3 3 3 3 3 3 3 15 9 9 7 10 13 8 10 7 8 2 11 15 13 8 16 11 9 11
0 0 0 1 1 1 1 2 9 15 13 10 8 8 8 2 11 15 9 6 2 13 9 11 6 8 8 15 8 11 15 2 13 6 7 8 11 12 9 2
0 0 0 0 0 0 1 2 8 13 6 9 8 10 10 2 6 15 9 9 2 3 3 3 3 3 3 3 3 3 3 2 9 8 12 15 7 7 10 2
0 0 0 0 1 1 1 2 3 3 3 3 3 3 3 3 3 3 3 3 2 12 8 15 12 13 9 13 12 13 15 2 8 8 12 6 15 7 12 2
0 0 0 1 1 1 1 2 7 6 11 12 7 7 7 6 11 9 8 11 9 7 11 12 6 13 7 6 10 13 15 2 3 3 3 3 3 3 3 2
0 0 1 1 1 1 1 2 7 8 7 15 12 11 7 9 9 10 12 8 9 9 15 10 9 10 15 15 15 13 15 2 11 12 11 6 6 9 9 2
0 0 0 1 1 1 1 2 12 9 8 10 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 3 3 2
0 0 0 1 1 1 1 2 15 10 11 10 2 9 6 8 15 10 15 15 10 12 10 6 8 13 9 11 8 10 9 2 15 10 6 7 8 7 13 2
0 1 1 1 1 2 3 2 12 2 3 3 2 9 7 6 2 3 3 3 3 3 3 3 2 13 7 11 8 10 7 2 8 11 9 8 10 15 7 2
0 0 1 1 1 2 8 15 15 2 10 9 6 10 10 15 2 5 5 5 5 5 5 5 2 9 12 10 9 12 15 2 8 10 13 15 2 3 3 2
0 0 0 0 1 2 3 3 3 2 8 7 15 10 10 9 2 5 5 5 5 5 5 5 2 3 3 3 3 3 6 2 13 6 15 15 2 9 13 2
0 0 0 0 1 1 1 1 1 2 8 7 10 13 7 11 2 5 5 5 5 5 5 5 11 16 14 15 9 2 10 2 13 10 15 10 2 11 15 2
0 0 0 0 0 0 0 0 1 2 10 11 13 9 8 8 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 10 15 2
0 0 0 0 0 0 0 0 1 2 7 11 8 9 10 13 2 8 15 6 6 7 10 14 10 8 15 11 9 11 10 7 6 2 9 7 11 9 11 2
0 0 0 0 0 0 0 0 1 2 13 12 15 10 9 9 2 9 11 10 9 9 10 12 10 9 8 10 7 11 10 8 9 2 9 15 8 15 9 2
0 0 0 0 0 0 0 0 1 2 3 2 12 8 6 8 2 6 13 15 13 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2
0 0 0 0 0 0 0 0 1 1 1 2 9 13 6 16 2 3 3 3 3 2 13 12 11 13 6 11 6 8 7 2 4 4 4 4 4 4 2 8
0 0 0 0 0 0 33 36 36 32 1 2 5 5 5 5 13 11 13 9 7 6 13 10 10 6 11 10 6 15 10 2 4 4 4 4 4 4 2 14
0 0 0 0 0 1 37 1 1 35 1 2 5 5 5 5 2 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 4 4 4 4 4 4 2 10
0 0 0 1 1 1 37 1 1 35 1 2 5 5 5 5 2 9 10 11 13 6 13 2 7 15 15 12 10 11 12 2 4 4 4 4 4 4 2 11
0 0 0 1 1 1 37 1 1 35 1 2 5 5 5 5 2 13 11 13 15 8 11 2 10 10 12 7 7 6 6 2 4 4 4 4 4 4 2 15
0 0 0 1 1 1 37 1 1 35 1 2 3 3 3 3 2 15 11 9 10 6 15 2 11 10 13 13 11 8 8 2 4 4 4 4 4 4 2 7
0 0 0 1 1 1 30 34 34 31 1 1 1 1 2 10 13 12 12 6 8 9 16 2 11 12 10 7 2 12 8 2 4 4 4 4 4 4 2 8
0 0 0 0 0 0 0 0 0 0 1 1 1 1 2 13 11 7 15 11 12 8 7 2 11 12 6 6 2 3 3 3 3 3 3 3 3 3 2 7
0 0 0 0 0 0 0 0 0 0 1 1 1 1 2 15 10 9 10 7 8 9 13 2 10 13 6 8 2 8 11 12 7 13 15 7 11 11 12 13
