import sys
import glob, time
try:    import serial
except: print("pyserial not installed")

cutoff = 150

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

def CutOff(Data):
    out = 0
    for d in range(12):
        if int(Data[d]) >= cutoff: out +=1 
    return out

def DataOut2():
    out = []
    for port in serial_ports():
        port1 = serial.Serial(str(port),9600)
        data = port1.read()#line().decode().strip()
        out.append([data])

    print(out)

    for o in out:
        if "open:" in str(o[0]): 
            return o[0]
out = ""
data=""
port1 = serial.Serial(str(serial_ports()[0]),9600)

while False:
    for port in serial_ports():
        port1 = serial.Serial(str(port),9600)
        num = port1.read(port1.inWaiting())
        print(num)
        time.sleep(0.1)


if __name__ == "__main__":
    while True:
        data = DataOut2()

        print(data)
        time.sleep(0.1)

        if data and False:
            text = str(DataList)[1:-1].replace("'","").replace(",","")
            text += " open:" + str(CutOff(DataList))
            print(text)
