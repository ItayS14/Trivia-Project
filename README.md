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
	"username" : ""
	"password" : ""
	"email" : ""
}	


101 - login
json:
{
	"username" : ""
	"password" : ""
}

