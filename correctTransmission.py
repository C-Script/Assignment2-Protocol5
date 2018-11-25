from helpingFunctions import send


def correctTransmission(N, totalPacketsNumber):
    currentPacketIndex = 0
    currentPacketNumber = 1
    receiverAckFlag = False

    while(currentPacketNumber < totalPacketsNumber+N):

        if(receiverAckFlag):
            send("Sender", "ack"+str(currentPacketIndex), "accepted")

        if(currentPacketNumber < totalPacketsNumber):
            send("Receiver", currentPacketIndex, "accepted")

        currentPacketIndex = currentPacketIndex+1
        currentPacketNumber = currentPacketNumber+1

        if(currentPacketIndex == N):
            currentPacketIndex = 0
            if(not receiverAckFlag):
                receiverAckFlag = True
