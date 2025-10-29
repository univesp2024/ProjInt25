from flask import Flask, render_template
from flask_sock import Sock

app = Flask(__name__)
sock = Sock(app)

clients = []

@app.route('/')
def index():
    return render_template('index.html')

@sock.route('/ws')
def ws(sock):
    clients.append(sock)
    print("✅ ESP32 conectado via WebSocket")

    while True:
        try:
            data = sock.receive()
            if data:
                print("📡 Dados recebidos:", data)
                for client in clients:
                    if client != sock:
                        client.send(data)
        except Exception:
            print("⚠️ ESP32 desconectado.")
            clients.remove(sock)
            break

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
