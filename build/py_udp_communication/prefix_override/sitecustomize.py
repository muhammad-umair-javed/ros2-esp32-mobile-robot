import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/umair/ros2-esp32-mobile-robot/install/py_udp_communication'
