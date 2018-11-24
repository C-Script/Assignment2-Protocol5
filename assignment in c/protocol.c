/* Protocol 5 (Go-back-n) allows multiple outstanding frames. The sender may transmit up
to MAX_SEQ frames without waiting for an ack. In addition, unlike in the previous
protocols, the network layer is not assumed to have a new packet all the time. Instead,
the network layer causes a network_layer_ready event when there is a packet to send. */
#define MAX_SEQ 7
#include "protocol.h"
#include "stdio.h"


static boolean between(seq_nr a, seq_nr b, seq_nr c)
{
	/* Return true if a <= b < c circularly; false otherwise. */
	if(((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a)))
		return(true);
	else
		return(false);
}
static void send_data(seq_nr frame_nr, seq_nr frame_expected, packet buffer[])
{
	/* Construct and send a data frame. */
	frame s;                                                                           /* scratch variable */
	s.info = buffer[frame_nr];                                                         /* insert packet into frame */
	s.seq = frame_nr;                                                                  /* insert sequence number into frame */
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);                                /* piggyback ack */
	to_physical_layer(&s);                                                             /* transmit the frame */
	start_timer(frame_nr);                                                             /* start the timer running */
}
void protocol5(void)
{
	seq_nr next_frame_to_send;                                                         /* MAX_SEQ > 1; used for outbound stream */
	seq_nr ack_expected;                                                               /* oldest frame as yet unacknowledged */
	seq_nr frame_expected;                                                             /* next frame_expected on inbound stream */
	frame r;                                                                           /* scratch variable */
	packet buffer[MAX_SEQ + 1];                                                        /* buffers for the outbound stream */
	seq_nr nbuffered;                                                                  /* number of output buffers currently in use */
	seq_nr i;                                                                          /* used to index into the buffer array */
	event_type event;
    printf("%d",event);
	enable_network_layer();                                                            /* allow network_layer_ready events */
	ack_expected = 0;                                                                  /* next ack_expected inbound */
	next_frame_to_send = 0;                                                            /* next frame going out */
	frame_expected = 0;                                                                /* number of frame_expected inbound */
	nbuffered = 0;                                                                     /* initially no packets are buffered */
	for(int i=0;i<5;i++)//while(true)
 {
		wait_for_event(&event);                                                        /* four possibilities: see event_type above */

		switch(event) {
			case network_layer_ready:                                                  /* the network layer has a packet to send */
			/* Accept, save, and transmit a new frame. */
				from_network_layer(&buffer[next_frame_to_send]);                       /* fetch new packet */
            	nbuffered=nbuffered-1;                                             
   				send_data(next_frame_to_send, frame_expected, buffer);                 /* transmit the frame */
				inc(next_frame_to_send);                                               /* advance sender’s upper window edge */
				break;
			case frame_arrival:                                                        /* a data or control frame has arrived */
				from_physical_layer(&r);                                               /* get incoming frame from_physical_layer */
				if(r.seq == frame_expected) {
				/* Frames are accepted only in order. */
					to_network_layer(&r.info);                                         /* pass packet to_network_layer */
					inc(frame_expected);                                               /* advance lower edge of receiver’s window */
				}
				/* Ack n implies n − 1, n − 2, etc. Check for this. */
				while(between(ack_expected, r.ack, next_frame_to_send)) {
				/* Handle piggybacked ack. */
					nbuffered=nbuffered-1;                                             
                    stop_timer(ack_expected);                                          /* frame_arrived intact; stop_timer */
					inc(ack_expected);                                                 /* contract sender’s window */
				}
				break;
			case cksum_err: break;                                                     /* just ignore bad frames */
			case timeout:                                                              /* trouble; retransmit all outstanding frames */
				next_frame_to_send = ack_expected;                                     /* start retransmitting here */
				for (i = 1; i <= nbuffered; i++) {
					send_data(next_frame_to_send, frame_expected, buffer);             /* resend frame */
					inc(next_frame_to_send);                                           /* prepare to send the next one */
				}
		}
		if(nbuffered < MAX_SEQ)
			enable_network_layer();
		else
			disable_network_layer();
	}
}

/* wait for an event to happen; return its type of event */
void wait_for_event(event_type *event){
    
    printf("I am an event\n");
    
}

/* fetch a packet from the network layer for transmission */
void from_network_layer(packet *p){
    
        printf("from network\n ");

    
}

/* deliver information from an inbound frame to the network layer */
void to_network_layer(packet *p){
            printf("to network\n ");

    
}

/* get an inbound frame from the physical layer */
void from_physical_layer(frame *r){
    
            printf("from physical\n ");

}

/* pass the frame to the physical layer */
void to_physical_layer(frame *s){
    
            printf("to physical\n ");

    
}

/* start the clock and enable the timeout event */
void start_timer(seq_nr k){
    
            printf("start timer\n");

}

/* stop the clock and disable the timeout event */
void stop_timer(seq_nr k){
    
            printf("stop timer\n");

    
}

/* start an auxiliary timer and enable the ack_timeout event */
void start_ack_timer(seq_nr k){
    
            printf("start ack\n ");

    
}

/* stop an auxiliary timer and disable the ack_timeout event */
void stop_ack_timer(seq_nr k){
    
            printf("stop ack\n");

    
}

/* allow the network to cause a network_layer_ready event */
void enable_network_layer(void){
    
            printf("enable network\n");

    
}

/* forbid the network to cause a network_layer_ready event */
void disable_network_layer(void){
    
            printf("disable network layer\n");

    
}
