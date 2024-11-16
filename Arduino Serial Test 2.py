import sys
import glob
import serial

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

#ser = serial.Serial(str(serial_ports()[0]),9600)

while True:
    try: 
        data = ser.readline().decode().strip()
        if data:
            print(data)
    except:
        try: ser = serial.Serial(str(serial_ports()[0]),9600)
        except: pass








