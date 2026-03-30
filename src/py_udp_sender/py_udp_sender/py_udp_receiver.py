import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import socket
import struct
from custom_interfaces.msg import EncoderData


class UDP_RECEIVER(Node):
    def __init__(self):
        super().__init__('UDP_RECEIVER')  

        

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.setblocking(False)
        self.sock.bind(("0.0.0.0", 4212)) # Host RECEIVES encoder data on this port

        self.get_logger().info("Initialized Listening...")

        self.publish_enc_data = self.create_publisher(  
            EncoderData,                                 
            'enc_data',
            10
        )

        
        self.last_msg = EncoderData()

        timer_period = 0.2
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        try:
            data, _ = self.sock.recvfrom(1024)
            left, right, timestamp = struct.unpack('<iiI', data)

            # Only update when we actually receive new data
            self.last_msg.left_ticks = left
            self.last_msg.right_ticks = right
            self.last_msg.timestamp = timestamp

        except BlockingIOError:
            pass  # No new data — last_msg retains previous values

        self.publish_enc_data.publish(self.last_msg) 


def main(args=None):
    rclpy.init(args=args)
    udp_receiver = UDP_RECEIVER()
    rclpy.spin(udp_receiver)
    udp_receiver.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()