from flask import Flask, render_template, request
from dbmodel import DBmanager
from db import sql_name,sql_host, sql_pass, sql_login
app = Flask(__name__)

@app.route("/")
def home():
    return render_template('mainpage.html')


@app.route("/senddata", methods=['GET'])
def senddata():
    table = request.args.get('table')
    status = request.args.get('status')
    mode = request.args.get('mode')
    wait = request.args.get('wait')
    count = request.args.get('count')
    base = DBmanager(sql_host, sql_login, sql_pass, sql_name)
    base.query(f"""CREATE TABLE IF NOT EXISTS table{table}(id INT AUTO_INCREMENT PRIMARY KEY, status text, mode text, wait text, count text)""")
    base.query(f"""INSERT INTO table{table}(status, mode, wait, count) VALUES(%s, %s, %s, %s)""",(status, mode, wait, count))

    return render_template('senddata.html')



if __name__=="__main__":
    app.run(debug=True, host='0.0.0.0')