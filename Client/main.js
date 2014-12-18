/*
 * prompt for name on start
 */

var clientName = prompt("Name", "Smith");

var clientColor;

var clientId = new Date();

/*
 * websockets
 */

var port = 9090;
var WebSocket = window.WebSocket || window.MozWebSocket;
var websocket = new WebSocket("ws://127.0.0.1:" + port);
var clients = [];

websocket.onopen = function() {
  console.log("on open");
};

websocket.onerror = function() {
  console.log("on error");
};

websocket.onmessage = function(message) {

  clients = JSON.parse(message.data);

  clients.forEach(function(client) {
    if(client.name === clientName)
    {
        clientColor = client.color;
    }
  });
}

/*
 * canvas
 */

var canvas = document.getElementById("main");
var context = canvas.getContext("2d");

// fullscreen canvas on window resize
var resizeCanvas = function() {
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
};

resizeCanvas();
window.addEventListener("resize", resizeCanvas);

// there should be draw loop with requestAnimationFrame, etc. but for simple drawing this should be ok
var drawCircle = function(x, y, radius, color) {
  context.beginPath();
  context.arc(x, y, radius, 0, 2 * Math.PI, false);
  context.fillStyle = color;
  context.fill();
};

function draw() {
  context.clearRect(0, 0, canvas.width, canvas.height);
  var width = window.innerWidth;
  var height = window.innerHeight;

  clients.map(function(client) {
      return { x: client.x * width, y: client.y * height, color: client.color};
    })
    .forEach(function(client) {
      var hexString = "#" + client.color.toString(16);
      drawCircle(client.x, client.y, 14, hexString);      
    });
  requestAnimationFrame(draw);
}

draw();

// handle mouse movement
canvas.addEventListener("mousemove", function(e) {
  sendMessage(e, false);
}, false);

canvas.addEventListener("mousedown", function(e) {
  sendMessage(e, true);
}, false);

var sendMessage = function(e, clicked)
{
  var pos = {
    x: e.clientX,
    y: e.clientY
  };

  var message = {
    id: clientId,
    name: clientName,
    x: pos.x / window.innerWidth,
    y: pos.y / window.innerHeight,
    clicked: clicked,
    color: clientColor
  }

  var validMessage = JSON.stringify(message);
  websocket.send(validMessage);
}
