from playhouse.shortcuts import model_to_dict
from json import JSONEncoder
from flask import Flask
from main import Data

app = Flask(__name__)


def get_json(data):
    return JSONEncoder().encode([model_to_dict(d) for d in data])


@app.route('/get_last')
def get_last():
    return get_json(Data.select().where(Data.is_last == 1))


@app.route('/get_cell/<string:cell_id>')
def get_cell(cell_id):
    return get_json(Data.select().where(Data.cell_id == cell_id))


if __name__ == '__main__':
    app.run(debug=True)
