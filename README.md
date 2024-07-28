# ESP-DHS Client

**ESP**32-S3 **D**evice **H**ardening **S**ystem

## Setup

Project built using VS Code and ESP-IDF extensions v1.7.1 (did not work with newer versions of the extension)

1.  Make sure the necessary SDK configuration are set in menuconfig:  
- **DHS ATECC608 Configuration**  
Secure Element Connected: only check if the ATECC608 should be connected   
(if the secure element is not connected but this option is checked, the client will be significantly slowed down)  
- **DHS MQTT Configuration**  
Broker URL: `mqtts://<username>:<password>@<fqdn>`  
(fqdn: fully qualified domain name of the MQTT server)  
- **DHS WiFi Configuration**  
WiFi SSID: `<SSID>`  
WiFi Password: `<Password>`

2. copy the SSL certificate for the connection with the MQTT broker to the location `/components/dhs_mqtt/ca.crt` (make sure it is called `ca.crt`)