#!/usr/bin/python

import pg

class Wdb:
    def __init__(self, database = 'wdb'):
        self.database = pg.connect(database)
        self.database.query("SELECT wci.begin('vegardb')")
        
    def __del__(self):
        self.database.close()
        
    def read(self, latitude, longitude):
        query = "SELECT value, astext(placegeometry) FROM wci.read(NULL,'surround POINT(%f %f)',NULL,NULL,NULL,NULL,NULL,NULL::wci.returnfloat)"
        result = self.database.query(query % (longitude, latitude)).dictresult()
        ret = []
        for row in result:
            ret.append(row['value'])
        return ret
        
def format(s, spaces):
    
    return s + (spaces-len(s))*' '

class ValidatedData:
    def __init__(self, inputLine):
        input = inputLine.split()
        self.name = input[0]
        self.latitude = float(input[1])
        self.longitude = float(input[2])
        self.altitude = int(input[3])
        
    def __str__(self):
        return format(self.name, 18) + format(str(self.altitude), 12)
    
    def validate(self, fetchedData):
        fetchedData.sort()
        print str(self) + str(fetchedData)

def processFile(fileToProcess, database):

    print 'STED              YR.NO       WDB'
    
    f = file(fileToProcess)
    for line in f:
        line = line.strip()
        if ( len(line) > 0 and line[0] != '#' ):
            line = line.replace(',', '.')
            valid = ValidatedData(line)
            valid.validate(database.read(valid.latitude, valid.longitude))

if __name__ == '__main__':
    import sys

    db = Wdb('wdb')

    filesToParse = sys.argv[1:]
    if len(filesToParse) == 0:
        filesToParse = ['samples.txt']

    for f in filesToParse:
        processFile(f, db)