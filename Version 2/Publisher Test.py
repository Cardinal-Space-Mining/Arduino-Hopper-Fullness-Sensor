import rclpy
from rclpy.node import Node

from std_msgs.msg import Float64
import serial,sys,glob

globals()["ser"] = "" 

#this is just code I took that find what port the arduino is connected 
def serial_ports():
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

#Just gets the data from serial with checking for erros and finding the port if it changes or arduino get unpluged
def DataOut():
    try: 
        data = globals()["ser"].readline().decode().strip()
        return data
    except:
        try: globals()["ser"] = serial.Serial(str(serial_ports()[0]),9600)
        except: pass

#takes the raw Arduino output and convert it to a single number
def DataAnalysis0():
    data = DataOut()
    if data: 
        data = data.split(" ")[-1]
        data = data.split(":")[-1]
        return int(data)/12

def CutOff(Data):
    out = 0
    for d in range(12):
        if int(Data[d]) >= cutoff: out +=1 
        return out

#takes the raw Arduino output and convert it to a single number but different
# I have not test this one so I don't know if it works
def DataAnalysis1():
    cutoff = 300
    total = 0
    data = DataOut()
    if data:
        DataList = data.split(" ")[0:12]
        for num in DataList:
            if int(num) > cutoff: total +=1 
        
        return total/12

# this is just a publish I stole the code from most of it I left the same but I added code to timer_callback
class MinimalPublisher(Node):
    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(Float64, 'Arduino', 10)
        timer_period = 0.5  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = Float64()

        D = DataAnalysis1() # D is a float

        if D or D==0: # only updates publisher if arduino in connected
            msg.data = D
            self.publisher_.publish(msg)
            self.get_logger().info('Publishing: "%s"' % msg.data)
            self.i += 1

def main(args=None):
    rclpy.init(args=args)
    minimal_publisher = MinimalPublisher()
    rclpy.spin(minimal_publisher)
    minimal_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()