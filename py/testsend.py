import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("localhost", 5801))
s.listen(5)

print("Accepting connections...")

(client, address) = s.accept()
print("Accepted address at: " + address[0])

print(client.recv(6))
