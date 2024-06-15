#include <iostream>
#include "CompactDisc.h"
#include "CDDrive.h"

using namespace std;

int main() {

    CompactDisc cd1("cd1", 100), cd2("cd2", 225);
    CDDrive theCDDrive("theCDDrive", 2500);

    theCDDrive.InsertCD(&cd1);
    theCDDrive.Play();
    theCDDrive.EjectCD();
    theCDDrive.Play();
    theCDDrive.InsertCD(&cd2);
    theCDDrive.Play();
    theCDDrive.EjectCD();

}