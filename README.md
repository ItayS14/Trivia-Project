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
	"time_per_question" : *unsigned int*
	"type" : *unsigned int*
}

104 - join room
json:
{
	"room_id" : *unsigned int*
}


