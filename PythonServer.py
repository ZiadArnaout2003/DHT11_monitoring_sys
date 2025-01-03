from http.server import SimpleHTTPRequestHandler, HTTPServer
import serial
import threading
import time
import json

# Initialize global variables
latest_data = {"humidity": None, "tempC": None, "tempF": None}

PORT = 9999  # Port to host the API
BAUD_RATE = 9600  # Bluetooth module baud rate

# Open the Bluetooth serial connection
ser = serial.Serial('COM5', BAUD_RATE)  # Replace 'COM3' with the correct port for your Bluetooth device

def read_bluetooth_data():
    global latest_data
    while True:
        try:
            # Read and process the Bluetooth data
            raw_data = ser.readline().decode('utf-8').strip()
            parts = raw_data.split(',')
            humidity = parts[0].split(':')[1]  # Extract '29' from 'humidity:29'
            tempC = parts[1].split(':')[1]  # Extract '30' from 'tempC:30'
            tempF = parts[2].split(':')[1]  # Extract '86' from 'tempF:86'

            # Update the latest data dictionary
            latest_data["humidity"] = humidity
            latest_data["tempC"] = tempC
            latest_data["tempF"] = tempF
            print(f"Latest Data: {latest_data}")
        except Exception as e:
            print(f"Error reading data: {e}")
        time.sleep(1)

# Start the Bluetooth data reading thread
threading.Thread(target=read_bluetooth_data, daemon=True).start()

class MyHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/bluetooth-data':
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.send_header('Access-Control-Allow-Origin', '*')
            self.end_headers()

            # Convert latest_data to JSON and send as a response
            self.wfile.write(json.dumps(latest_data).encode('utf-8'))
        else:
            super().do_GET()

# Start the HTTP server
httpd = HTTPServer(('127.0.0.1', PORT), MyHandler)  
print(f"Server running on port {PORT}...")
httpd.serve_forever()

