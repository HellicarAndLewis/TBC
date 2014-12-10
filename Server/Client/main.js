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

websocket.onopen = function() {
  console.log("on open");
};

websocket.onerror = function() {
  console.log("on error");
};

websocket.onmessage = function(message) {
  console.log("on message", message.data);
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
  context.clearRect(0, 0, canvas.width, canvas.height);

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

  drawCircle(pos, 14);
}, false);
