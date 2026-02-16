import serial
import re
import sqlite3

# Create/connect to SQLite DB
conn = sqlite3.connect('sensor_data.db')
c = conn.cursor()

# Create table if not exists
c.execute('''CREATE TABLE IF NOT EXISTS sensor_readings (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                X REAL,
                Y REAL,
                Z REAL,
                Sound REAL,
                Temp REAL,
                Impulse INTEGER,
                timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
            )''')
conn.commit()

# Setup Serial (COM23)
ser = serial.Serial('COM5', 115200, timeout=1)

# Regex pattern
pattern = re.compile(
    r'X:(?P<X>[\d.]+) Y:(?P<Y>[\d.]+) Z:(?P<Z>[\d.]+) \| Sound:(?P<Sound>[-\d.]+) dB \| Temp:(?P<Temp>[\d.]+) C \| Impulse:(?P<Impulse>\d+)'
)

# Receive and insert into DB
while True:
    line = ser.readline().decode().strip()
    print("Received:", line)

    match = pattern.search(line)
    if match:
        x = float(match.group('X'))
        y = float(match.group('Y'))
        z = float(match.group('Z'))
        sound = float(match.group('Sound'))
        temp = float(match.group('Temp'))
        impulse = int(match.group('Impulse'))

        c.execute('''INSERT INTO sensor_readings (X, Y, Z, Sound, Temp, Impulse)
                     VALUES (?, ?, ?, ?, ?, ?)''', (x, y, z, sound, temp, impulse))
        conn.commit()



# import socket
# import re
# import sqlite3

# # Create/connect to SQLite DB
# conn = sqlite3.connect('sensor_data.db')
# c = conn.cursor()

# # Create table if not exists
# c.execute('''CREATE TABLE IF NOT EXISTS sensor_readings (
#                 id INTEGER PRIMARY KEY AUTOINCREMENT,
#                 X REAL,
#                 Y REAL,
#                 Z REAL,
#                 Sound REAL,
#                 Temp REAL,
#                 Impulse INTEGER,
#                 timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
#             )''')
# conn.commit()

# # Setup UDP socket
# UDP_IP = "0.0.0.0"   # Listen on all interfaces
# UDP_PORT = 1234      # Match with transmitter port

# sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# sock.bind((UDP_IP, UDP_PORT))

# # Regex pattern
# pattern = re.compile(
#     r'RMS=>X:(?P<X>[\d.]+) Y:(?P<Y>[\d.]+) Z:(?P<Z>[\d.]+) \| Sound:(?P<Sound>-?[\d.]+) dB \| Temp:(?P<Temp>[\d.]+) C \| Impulse:(?P<Impulse>\d+)'
# )


# # Receive and insert into DB
# while True:
#     try:
#         data, addr = sock.recvfrom(1024)
#         line = data.decode(errors='ignore').strip()
#         print("Received:", line)

#         match = pattern.search(line)
#         if match:
#             x = float(match.group('X'))
#             y = float(match.group('Y'))
#             z = float(match.group('Z'))
#             sound = float(match.group('Sound'))
#             temp = float(match.group('Temp'))
#             impulse = int(match.group('Impulse'))

#             c.execute('''INSERT INTO sensor_readings (X, Y, Z, Sound, Temp, Impulse)
#                          VALUES (?, ?, ?, ?, ?, ?)''', (x, y, z, sound, temp, impulse))
#             conn.commit()
#     except Exception as e:
#         print("Skipped invalid packet.")
#         continue
