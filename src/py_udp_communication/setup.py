from setuptools import find_packages, setup

package_name = 'py_udp_communication'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='umair',
    maintainer_email='muhammad.umair.javed.mct@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'sender = py_udp_communication.py_udp_sender:main',
            'receiver = py_udp_communication.py_udp_receiver:main'
        ],
    },
)
