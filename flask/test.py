from flask import Flask, render_template
from flask import request
import os
import sys
sys.path.append(os.path.dirname(os.path.abspath(os.path.dirname(__file__))))
from servo_driver import pwm
app = Flask(__name__)       

data = ''

@app.route('/')             

def hello():                
   return render_template('input.html')

@app.route("/post",methods=['POST'])

def post():
	try:
		value = int(request.form['input'])
		pwm.pwm(value)
	except Exception as e:
		print(e)
	return render_template('input.html', value = value)



if __name__ == "__main__":  
   app.run(host="0.0.0.0", port = "8080")