## SEND function ##
    #parameters: 
    ## destination (string): "Receiver" or "Sender" ##
    ## message (string): anything ##
    ## receivingState (string): "accepted" or "rejected" ##

def send(destination, message, receivingState):
    
    if(receivingState!="accepted"):
        if(receivingState!="rejected"):
            print("Incorrect sending format")
            return

    if(destination=="Receiver"):
        print("Sender         -----("+ message +")-----> " + receivingState +" Receiver")
    elif(destination=="Sender"):
        print("Sender "+ receivingState +" <-----("+ message +")-----        Receiver")
