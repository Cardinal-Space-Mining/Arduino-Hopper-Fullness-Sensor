import sys
import glob
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
    
if __name__ == "__main__":
    while True:
        try: 
            data = ser.readline().decode().strip()
            DataList = data.split(" ")[0:12]

            if data:
                text = str(DataList)[1:-1].replace("'","").replace(",","")
                text += " open:" + str(CutOff(DataList))
                print(text)

        except:
            try: ser = serial.Serial(str(serial_ports()[0]),9600)
            except: pass
