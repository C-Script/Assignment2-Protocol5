## SEND function ##
# parameters:
## destination (string): "Receiver" or "Sender" ##
## message: anything ##
## receivingState (string): "accepted" or "rejected" or 'lost' ##


def send(destination, message, receivingState):

    message = str(message)

    if(receivingState != "accepted"):
        if(receivingState != "rejected"):
            if(receivingState != "lost"):
                print("Incorrect sending format")
                return

    if(receivingState == "lost"):
        receivingState = "LOST"

    if(destination == "Receiver"):
        print("Sender         -----(" + message + ")-----> " +
              receivingState + " Receiver")
    elif(destination == "Sender"):
        print("Sender " + receivingState +
              " <-----(" + message + ")-----        Receiver")
