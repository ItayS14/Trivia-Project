import requests
from urllib.parse import unquote
import sqlite3

categories = {'1':'21','2':'9','3':'23','4':'14','5':'22'}
def fill_database(category):
	"""
	This function will reach the api, parse the questions and the answers from the json and will enter them to the database
	:param category: category of questions
	:type category: int
	"""
	if category == '0':
		URL = "https://opentdb.com/api.php?amount=50&type=multiple&encode=url3986"
	else:
		URL = "https://opentdb.com/api.php?amount=50&category="+categories[category]+"&type=multiple&encode=url3986"
	print(URL)
	r = requests.get(URL)
	# extracting data in json format 
	results = r.json()['results'] 
	conn = sqlite3.connect('trivia.sqlite')
	c = conn.cursor()
	for result in results:
		question = unquote(result['question']).replace("\"","") #unquote decodes from url encoding
		correct_answer = unquote(result['correct_answer']).replace("\"","")
		incorrect = result["incorrect_answers"]
		command = "INSERT INTO questions (question,type,correct_ans,ans2,ans3,ans4) VALUES (\""+question+"\",\""+category+"\",\""+correct_answer+"\",\""
		for ans in result["incorrect_answers"]:
			command += unquote(ans).replace("\"","") + "\",\""
		command = command[:-2] + ")"
		c.execute(command)
	conn.commit()
	conn.close()

def main():
	for i in range(6):
		fill_database(str(i))

if __name__ == '__main__':
	main()