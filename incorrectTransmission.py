from helpingFunctions import send


def incorrectTransmission(N, totalPacketsNumber, retransmittedPacketNumber):
    currentPacketIndex = 0
    currentPacketNumber = 1
    receiverAckFlag = False
    rejectedTransmission = False
    NAKsent = False

    while(currentPacketNumber < totalPacketsNumber+N):

        if(receiverAckFlag and not rejectedTransmission):
            send("Sender", "ack"+str(currentPacketIndex), "accepted")

        if(receiverAckFlag and rejectedTransmission and not NAKsent and currentPacketNumber-retransmittedPacketNumber < N):
            send("Sender", "ack"+str(currentPacketIndex), "accepted")

        if(rejectedTransmission and currentPacketNumber == retransmittedPacketNumber+(N-1)):
            send("Sender", "Nack"+str(retransmittedPacketNumber % N - 1), "accepted")
            currentPacketNumber = retransmittedPacketNumber
            currentPacketIndex = currentPacketNumber % N - 1
            NAKsent = True
            rejectedTransmission = False
            retransmittedPacketNumber = 'none'

        if(currentPacketNumber <= totalPacketsNumber):
            if(currentPacketNumber == retransmittedPacketNumber and not rejectedTransmission):
                send("Receiver", currentPacketIndex, "lost")
                rejectedTransmission = True

            elif(rejectedTransmission):
                send("Receiver", currentPacketIndex, "rejected")
            else:
                send("Receiver", currentPacketIndex, "accepted")

        currentPacketIndex = currentPacketIndex+1
        currentPacketNumber = currentPacketNumber+1

        if(currentPacketIndex == N):
            currentPacketIndex = 0
            if(not receiverAckFlag):
                receiverAckFlag = True
