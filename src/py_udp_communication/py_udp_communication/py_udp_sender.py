import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import socket




class UDP_SENDER(Node):
    def __init__(self):
        super().__init__('UDP_SENDER')

        # ESP32 IP and port
        self.ESP32_IP = "192.168.0.200"
        self.ESP32_PORT = 4210

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(("0.0.0.0", 4211)) # Host sends commands FROM this port
        
        self.subscriber = self.create_subscription( 
            String, 
            'car_cmd', 
            self.sender_callback, 
            10
            )
        
    def sender_callback(self, msg):
        self.get_logger().info(f'Received: {msg.data}')
        self.sock.sendto(msg.data.encode(), (self.ESP32_IP, self.ESP32_PORT))
        self.get_logger().info(f"Data Sent!")


def main(args=None):
    rclpy.init(args=args)

    udp_sender = UDP_SENDER()
    rclpy.spin(udp_sender)

    udp_sender.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()