# app.py
from flask import Flask, jsonify,render_template
import sqlite3

app = Flask(__name__)
DB_NAME = 'sensor_data.db'

def get_db_connection():
    conn = sqlite3.connect(DB_NAME) 
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def index():
    return render_template('ind.html')

@app.route('/data')
def get_latest_data():
    conn = get_db_connection()
    row = conn.execute(
        'SELECT id, X, Y, Z, sound, temp, impulse, timestamp FROM sensor_readings ORDER BY timestamp DESC LIMIT 1'
    ).fetchone()
    conn.close()
    if row:
        data = {
            "id": row["id"],
            "X": row["X"],
            "Y": row["Y"],
            "Z": row["Z"],
            "sound": row["sound"],
            "temp": row["temp"],
            "impulse": row["impulse"],
            "timestamp": row["timestamp"]
        }
    else:
        data = {
            "id": None,
            "X": None,
            "Y": None,
            "Z": None,
            "sound": None,
            "temp": None,
            "impulse": None,
            "timestamp": None
        }
    return jsonify(data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
