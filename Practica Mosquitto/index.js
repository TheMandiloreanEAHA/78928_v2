// Create a client instance
client = new Paho.MQTT.Client("ip172-19-0-8-ch1akn2e69v000b1c070-9001.direct.labs.play-with-docker.com", 9001, "Changuito 2");

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// connect the client
client.connect({onSuccess:onConnect});

let name = "Erick"

// called when the client connects
function onConnect() {
  // Once a connection has been made, make a subscription and send a message.
  console.log("onConnect");
  client.subscribe("World");
  message = new Paho.MQTT.Message("Hello");
  message.destinationName = "World";
  //client.send(message);
}

function sendMessage() {
  let mensaje = document.getElementById("mensaje").value
  console.log(mensaje)
  client.subscribe("World");
  message = new Paho.MQTT.Message(name +": "+mensaje);
  message.destinationName = "World";
  client.send(message);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:"+responseObject.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {
  console.log("onMessageArrived:"+message.payloadString);
  let texto = document.getElementById("valueInput").value;
  document.getElementById("valueInput").innerHTML += "<br>"+message.payloadString;
}