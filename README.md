# Simple websockets example

Requires [ofxLibwebsockets](https://github.com/labatrockwell/ofxLibwebsockets)
Requires [ofxJSON](https://github.com/jefftimesten/ofxJSON)


# Running

1. compile & run Server
2. cd into Client
3. `python -m SimpleHTTPServer 3000`
4. open [http://localhost:3000](http://localhost:3000)

# Functionality

Clicking changes each circle's color on the server and on the client'

# Notes

Ensure if you are using the project generator to add the addons, you must delete the jsoncpp file inside ofxJSON lib folder because there is another copy in ofxLibwebsockets and it won't compile if both of them are there.

