# QuAD
Since the 2017 Tubbs Wildfire, our region's wildfires have been accompanied by unhealthy air quality. California and other heavily wildfire impacted states are burdened with unhealthy air. Community health safety measures as the world combats climate change. In Summer/Fall 2020 Northern California regions had multiple days and weeks where the AQI was over 200.

What our device, QuAD, offers is affordability and user friendly interface.  QuAD takes current AQI of your device’s location and alerts users based on unhealthy statistics.

## Getting Started
### Prerequisites
Visual Studios

### Installation

- For QuAD device:
  - Software:
    - Arduino IDE
  - Hardware:
    - [Seven Segment Display](https://www.walmart.com/ip/Common-Cathode-12Pin-4-Bit-1-98-x-0-75-x-0-31-Inch-0-55-Red-Display-5pcs/628095701?wmlspartner=wlpa&selectedSellerId=571&&adid=22222222227255957575&wl0=&wl1=g&wl2=c&wl3=301996525824&wl4=pla-541690746941&wl5=9032310&wl6=&wl7=&wl8=&wl9=pla&wl10=111838760&wl11=online&wl12=628095701&veh=sem&gclid=Cj0KCQjwxNT8BRD9ARIsAJ8S5xb0KKYwO4wriSn3N2pJXfxID8vKxb17n8UuiZGQAQ9Gmnj6f3sK6TUaAhqSEALw_wcB)
    - [Active Buzzer](https://www.aliexpress.com/item/32740652543.html?aff_platform=api-new-product-query&aff_trace_key=9f543db456ee49058fd3b7abda83123d-1603655362016-08448&terminal_id=48ed02993af2453cba81db68e7c72d18&tmLog=new_Detail)
    - [Joystick](https://vetco.net/products/joystick-module-for-arduino?gclid=Cj0KCQjwxNT8BRD9ARIsAJ8S5xYxa7cgINW2WT74oWsLeiyQJQKcfS0Ci6KK6I8ruq-eradA9Rn5DZAaAkhnEALw_wcB) 
    - Breadboard
    - [Nodemcu ESP8266](https://www.amazon.com/gp/product/B081CSJV2V/ref=ox_sc_saved_title_1?smid=A30QSGOJR8LMXA&psc=1)

- For QuADApi, install:
  - the following packages:
    - HtmlAgilityPack
    - Selenium.WebDriver
    - System.Xml.XmlSerializer
  - Firefox browser

### Configuration

- Hardware setup:
  - Pin layout
    ![Pin layout](https://github.com/BrandonMFong/QuAD/blob/main/img/DeviceDiagram.v4.png)
- Software config for api:
  - When Nodemcu launches the webserver, put its private IP address into WebServerIP
    ```
    <?xml version="1.0" encoding="utf-8" ?>
    <QuAD>
      <WebServerIP>192.168.1.36</WebServerIP>
    </QuAD>
    ```

## Usage

This device is only in its first iteration.  So there may be some bugs.  This project's purpose is solely to prove the concept of providing up to date AQI data to the user.

- Flow chart
  - ![QuAD Flowchart](https://github.com/BrandonMFong/QuAD/blob/main/img/QuAD.Flow.png)
- QuAD Finite State Machine
  - ![Finite State Machine](https://github.com/BrandonMFong/QuAD/blob/main/img/States.v5.png)

## Contributing
Project was submitted to 
[2020 Virtual IoT Hackathon](https://docs.google.com/document/d/e/2PACX-1vSoZdG2YSPsEtawXJnYKJOsn27L2ftez70Ca6tAhft8WLVZHQE_9DzEIeb2izOIFvzIDDjxzc-AuOFa/pub)
@ Sonoma State University 
Building Technology for Social Good!

## Credits
Mel Kadar (Business Manager)
Armando Santos-Landa (Engineer)
Thomas Swanson (Engineer)
Brandon Fong (Engineer)
