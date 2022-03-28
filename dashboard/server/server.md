# Dashboard Server 

1. Server configuration
2. Dashboard back-end
3. Server setup

# Giving access to new IP address
1. SSH into server
2. ```sudo ufw allow from __new_ip_address__```

## Reminder: Make sure to check ufw status after to ensure it is from correct ip address 

#### Extra commands for ufw
1. ```sudo ufw status numbered``` to check the available ip addresses with the corresponding number
2. ```sudo ufw delete __x__``` to delete rule number x

# Running server.py
1. SSH into server
2. cd into ```Team302-SAND-E/dashboard/server```
3. ```python3 server.py```
