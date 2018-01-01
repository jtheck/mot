


var init = function() {
  var form = document.querySelector("form");

  mot.readState("state");
  mot.readClock("clock");

  mot.getSense("Binary Switch", "bs_ui", ["ON", "OFF"]);
  mot.getSense("Ternary Switch", "ts_ui", ["ON", "OFF", "NEUTRAL"]);



  form.addEventListener("submit", function(e) {

    mot.get(form.elements.notion.value);


    report("echo " + form.elements.notion.value);

    form.elements.notion.value = "";
    e.preventDefault();
  });




  // Add an event listener
  document.addEventListener("name-of-event", function(e) {
    console.log(e.detail); // Prints "Example of an event"
  });

  // Create the event
  var event = new CustomEvent("name-of-event", { "detail": "Example of an event" });

  // Dispatch/Trigger/Fire the event
  document.dispatchEvent(event);




}

var report = function(msg){
  var vm = document.getElementById("vitals_log");
  vm.innerHTML = "<br>" + msg + vm.innerHTML;
}

var ignite = function(){
  var butt = document.getElementById("ignition");
  if (butt.getAttribute("data-state") == "OFF") {
    butt.setAttribute("data-state", "ON");
    butt.innerHTML = "STOP";
    butt.style.backgroundColor = "red";

    mot.start();
  } else {
    butt.setAttribute("data-state", "OFF");
    butt.innerHTML = "START";
    butt.style.backgroundColor = "#0d0";

    mot.stop();
  }
}
