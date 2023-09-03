from scapy.all import *

#function prototypes 


# sniff for each function call

def Closing_handshake():
    lis=sniff(count=10,lfilter=lambda x:x.haslayer(TCP) and x[TCP].flags==17)
    for obj in lis:
            packet=[]
            #add packet to list
            packet.append(obj)
            source=obj[TCP].sport
            destination=obj[TCP].dport
            for obj2 in a:
                if obj2[TCP].sport==destination and obj2[TCP].dport==source:
                    packet.append(obj2)
                    wrpcap("TCP_handshake_close_2101CS65.pcap",packet)
                    return
    Closing_handshake()

def tcp():
    lis=sniff(count=10,lfilter=lambda x:x.haslayer(TCP) and x[TCP].flags==16)
    for obj in lis:
            packet=[]
            #add packet to list
            packet.append(obj)
            source=obj[TCP].sport
            destination=obj[TCP].dport
            for obj2 in a:
                if obj2[TCP].sport==destination and obj2[TCP].dport==source:
                    packet.append(obj2)
                    wrpcap("TCP_Packets_2101CS65.pcap",packet)
                    return
    tcp()



def udp():
    lis=sniff(count=10,lfilter=lambda x:x.haslayer(UDP))
    for obj in a:
            packet=[]
            #add packet to list
            packet.append(obj)
            source=obj[UDP].sport
            destination=obj[UDP].dport
            for obj2 in lis:
                if obj2[UDP].sport==destination and obj2[UDP].dport==source:
                    packet.append(obj2)
                    wrpcap("UDP_Packets_2101CS65.pcap",packet)
                    return
    udp()
    

def Handshake_open():
    lis=sniff(count=250)
    for obj in lis:
        if obj.haslayer(TCP) and obj[TCP].flags==2:
            packet = []
            #add packet to list
            packet.append(obj)
            ip_src=obj[IP].src
            ip_dst=obj[IP].dst
            for obj2 in lis:
                if obj2.haslayer(TCP) and obj2[TCP].flags==18 and obj2[IP].src==ip_dst and obj2[IP].dst==ip_src:
                     packet.append(obj2)
                     for obj3 in lis:
                         if obj3.haslayer(TCP) and obj3[TCP].flags==16 and obj3[IP].src==ip_src and obj3[IP].dst==ip_dst:
                             packet.append(obj3)
                             wrpcap("TCP_3_way_handshake_start_2101CS65.pcap",packet)
                             return
    Handshake_open()


Handshake_open()
Closing_handshake()
tcp()
udp()