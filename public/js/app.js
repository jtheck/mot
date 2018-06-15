


var init = function() {

  mot.readState("state");
  mot.readClock("clock");


  mot.setSense("Binary Switch", "bs_ui");
  mot.setSense("Ternary Switch", "ts_ui");
  mot.setSense("Text Input", "text_out");



  // text input
  var textIn = document.querySelector("#text_in");
  textIn.addEventListener("submit", function(e) {
    var val = textIn.elements.notion.value;

    mot.trigger("Text Input", val);

    report("echo " + val);
    textIn.elements.notion.value = "";

    e.preventDefault();
  });


  // binary switch
  var binaryIn = document.querySelector("#binary_in");
  binaryIn.onclick  = function(){
    mot.trigger("Binary Switch", "onoff");
  };


  // trinary switch


} // end init



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
