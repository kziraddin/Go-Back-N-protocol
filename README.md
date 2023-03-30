# Go-Back-N (GBN) protocol:

The Go-Back-N protocol is a type of automatic repeat request (ARQ) protocol used in communication networks, especially in point-to-point and broadcast networks. It is used to ensure reliable delivery of packets in the presence of transmission errors, lost packets, or out-of-order delivery.

In the Go-Back-N protocol, the sender transmits a sequence of packets to the receiver, and the receiver sends an acknowledgment (ACK) for each packet it receives correctly. The sender maintains a window of packets that it has sent but not yet received an ACK for. The window size represents the maximum number of packets that can be transmitted without receiving an ACK.

When the sender transmits a packet, it starts a timer for that packet. If an ACK for that packet is not received before the timer expires, the sender retransmits all the packets in the current window and resets the timer for the first packet in the window. This process is called "go-back-n" because the sender goes back to the first unacknowledged packet in the window and retransmits from there.
If a packet is lost or corrupted in transit, the receiver discards it and sends an ACK for the last correctly received packet. This ACK tells the sender to go back and retransmit all the packets in the window starting from the last acknowledged packet.

The Go-Back-N protocol is a simple and efficient method for ensuring reliable packet delivery in noisy communication channels. However, it can suffer from low efficiency if there are frequent packet losses or if the round-trip time (RTT) between the sender and receiver is long. In these cases, other ARQ protocols like Selective Repeat or Hybrid ARQ may be more suitable.
