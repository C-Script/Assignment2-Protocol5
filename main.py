from correctTransmission import correctTransmission
from incorrectTransmission import incorrectTransmission
from helpingFunctions import send

print("Hello dear user")
print("This program implements Go-Back-N Protocol\n")
N=input("Please enter the window size / value of N:\n")

totalPacketsNumber=input("Please enter the number of packets to be sent:\n")

print("\n1- Transmission with no error")
print("2- Transmission with an error (retransmission needed)\n")

invalidChoice=True

while(invalidChoice):
    userChoice=input("Choose 1 or 2\n")

    if(userChoice=="1"):
        invalidChoice=False
        correctTransmission(N, totalPacketsNumber)

    elif(userChoice=="2"):
        invalidChoice=False
        retransmittedPacketNumber=input("\nPlease enter the number of the packet that is not transmitted\n(Number should be less than "+totalPacketsNumber+")\n")
        incorrectTransmission(N, totalPacketsNumber, retransmittedPacketNumber)

