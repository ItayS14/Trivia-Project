Welcome to our Trivia Project!

This will be a multiplayer trivia game with multiple features.
Have fun!

Protocol:

[code + data_size + data (string for error messages / json)]

Client requests: 
code: 100 - 199

Server responses:
Error code: 400
Success code: 200 (with additional data if needed, otherwise sends 0 after '200')


Code List:

100 - signup 
json:
{
	"username" : *string*
	"password" : *string*
	"email" : *string*
}	

101 - login
json:
{
	"username" : *string*
	"password" : *string*
}

102 - logout
*no data needed*

103 - create room
json:
{
	"room_name" : *string*
	"max_players" : *unsigned int*
	"question_count" : *unsigned int*
	"time_per_question" : *unsigned int* (Seconds)
	"type" : *unsigned int* [Options: all = 0, sport = 1, general = 2, math = 3, tv = 4, geography = 5]
}
response json:
{
	"room_id" : *unsigned int*
}

104 - join room
json:
{
	"room_id" : *unsigned int*
}

105 - get rooms
response json:
*list of dict*
inner dict:
{
	"room_id" : *unsigned int*
	"room_name" : *string*
	"max_players" : *unsigned int*
	"logged_players" : *unsigned int*
	"question_count" : *unsigned int*
	"time_per_question" : *unsigned int* (Seconds)
	"state" : *unsigned int* [Options: Joinable = 0, In Game = 1, Finished = 2]
	"type" : *unsigned int* [Options: all = 0, sport = 1, general = 2, math = 3, tv = 4, geography = 5]
}

106 - get room state
json:
{
	"room_id" : *unsigned int*
}
response json:
{
	"room_id" : *unsigned int*
	"room_name" : *string*
	"max_players" : *unsigned int*
	"players" : *list of strings*
	"is_admin" : *bool* (is the current user admin)
	"state" : *unsigned int* [Options: Joinable = 0, In Game = 1, Finished = 2]
	"type" : *unsigned int* [Options: all = 0, sport = 1, general = 2, math = 3, tv = 4, geography = 5]
}

107 - leave room (if 0 users will be logged to the room - the room would be closed)
{
	"room_id" : *unsigned int*
}

108 - start game
json:
{
	"room_id" : *unsigned int*
}



