SERVER :
import socket

# Configuration
UDP_IP = "127.0.0.1"
UDP_PORT = 5005
TOTAL_STUDENTS = 10  # Change this to your total batch size
HALF_MARK = TOTAL_STUDENTS // 2

# Create UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print(f"UDP Server listening on {UDP_IP}:{UDP_PORT}...")
print(f"Expecting {TOTAL_STUDENTS} students total.")

student_count = 0

while student_count < TOTAL_STUDENTS:
    # Receive data from client
    data, addr = sock.recvfrom(1024)
    incoming_string = data.decode('utf-8')
    student_count += 1
    
    print(f"\n[Student {student_count}] Received from {addr}: '{incoming_string}'")
    
    # Process string based on student count
    if student_count <= HALF_MARK:
        # Operation A: Convert to lower case
        result = incoming_string.lower()
        print(f"Processing: First 50% (Lower Case) -> {result}")
    else:
        # Operation B: Reverse the string
        result = incoming_string[::-1]
        print(f"Processing: Remaining 50% (Reverse) -> {result}")
        
    # Send the result back to the student client
    sock.sendto(result.encode('utf-8'), addr)

print("\nAll students processed. Server shutting down.")
sock.close()
 CLIENT SERVER:
import socket

# Configuration
UDP_IP = "127.0.0.1"
UDP_PORT = 5005

# Create UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Take input from student
message = input("Enter the string to process: ")

try:
    # Send data
    print(f"Sending data to server: {message}")
    sock.sendto(message.encode('utf-8'), (UDP_IP, UDP_PORT))
    
    # Receive response (Timeout set to 5 seconds so it doesn't block forever)
    sock.settimeout(5.0)
    data, server = sock.recvfrom(1024)
    print(f"Received from server: {data.decode('utf-8')}")

except socket.timeout:
    print("Error: Server response timed out.")
finally:
    sock.close()
