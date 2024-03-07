from flask import Flask, render_template, request, jsonify
app = Flask(__name__)

@app.route("/")
def home():
    return render_template('index.html')

@app.route("/hardinfo", methods=['GET'])
def hardinfo():
    data = request.args.get('station')
    print(data)
    obj = {
        "Value": data,
        "Subject": "Data Structures and Algorithms",
    }
    return render_template('index.html', data=data),obj

if __name__=="__main__":
    app.run(debug=True, host='0.0.0.0')