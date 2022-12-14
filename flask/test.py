from flask import Flask     
from flask import request

app = Flask(__name__)       

data = ''

@app.route('/')             

def hello():                
   return "Hello Flask!"    

@app.route("/post",methods=['POST'])

def post():
	value = request.form['input']
	msg = "%s 님 환영합니다." %value
	return msg



if __name__ == "__main__":  
   app.run(host="0.0.0.0", port = "8080")