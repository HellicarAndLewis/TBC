/*
 * prompt for name on start
 */

var clientName = prompt("Name", "Smith");

/*
 * websockets
 */

var port = 9090;
var WebSocket = window.WebSocket || window.MozWebSocket;
var websocket = new WebSocket("ws://127.0.0.1:" + port);
var locs = [];

websocket.onopen = function() {
  console.log("on open");
};

websocket.onerror = function() {
  console.log("on error");
};

websocket.onmessage = function(message) {
	context.clearRect(0, 0, canvas.width, canvas.height);
  //console.log("on message " + message.data);
  var messages = message.data.split(",");
  messages.pop();
  for(var i = 0; i < messages.length; i++)
  {
  	var vals = messages[i].split(" ");
  	var pos = {
  		x: vals[0],
  		y: vals[1]
  	};
  	pos.x *= canvas.width;
  	pos.y *= canvas.height;
  	drawCircle(pos, 14);
  }
};

/*
 * canvas
 */

var canvas = document.getElementById("main");
var context = canvas.getContext("2d");

// fullscreen canvas on window resize
var resizeCanvas = function() {
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
}

resizeCanvas();
window.addEventListener("resize", resizeCanvas);

// there should be draw loop with requestAnimationFrame, etc. but for simple drawing this should be ok
var drawCircle = function(pos, radius) {
  context.beginPath();
  context.arc(pos.x, pos.y, radius, 0, 2 * Math.PI, false);
  context.fillStyle = "black";
  context.fill();
};

// handle mouse movement
canvas.addEventListener("mousemove", function(e) {
  var pos = {
    x: e.clientX,
    y: e.clientY
  };

  var normalized = {
    x: pos.x / window.innerWidth,
    y: pos.y / window.innerHeight
  };

  // send normalized position (0-1), so we can scale it to oF window without problems
  websocket.send(clientName + "," + normalized.x + "," + normalized.y);
}, false);
