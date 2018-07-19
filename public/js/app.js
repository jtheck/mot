


var init = function() {


  mot.readState("state");
  mot.readClock("clock");


  mot.setSense("Range Slider", "range_ui");
  mot.setSense("Binary Switch", "binary_ui");
  mot.setSense("Ternary Switch", "switch_ui");
  mot.setSense("Directional Pad", "directional_pad");
  mot.setSense("Text Input", "text_out");



  var chat = GETFIRE({topic: "mot moe", startOpen: true});


  var powerIcon = '<svg xmlns="http://www.w3.org/2000/svg" version="1.2" baseProfile="tiny" x="0" y="0" width="100%" height="100%" viewBox="-0.8 -0.5 177 202" xml:space="preserve">  <path fill="none" stroke-width="30" stroke-linecap="round" d="M33.7 64.3C22.1 77.2 15 94.3 15 113c0 40.1 32.5 72.7 72.7 72.7 40.1 0 72.7-32.5 72.7-72.7 0-18.7-7.1-35.8-18.7-48.7"/>  <line fill="none" stroke-width="30" stroke-linecap="round" x1="87.8" y1="15" x2="87.8" y2="113"/></svg>';
  var $ignition_switch = document.querySelector("#ignition");
  $ignition_switch.innerHTML = powerIcon;


  // text input
  var textIn = document.querySelector("#text_in");
  textIn.addEventListener("submit", function(e) {
    var val = textIn.elements.notion.value.replace(/\r?\n|\r/g,'');
    mot.triggerSense("Text Input", val);

    textIn.elements.notion.value = "";

    e.preventDefault();
  });
  textIn.addEventListener("keyup", function(e) {
    if (e.key === "Enter") {
      var val = textIn.elements.notion.value.replace(/\r?\n|\r/g,'');
      mot.triggerSense("Text Input", val);

      textIn.elements.notion.value = "";
    }
  });



  // range slider
  var sliderIn = document.querySelector("#slider_in");
  sliderIn.onchange  = function(){
    mot.triggerSense("Range Slider", this.value);
  };


    // binary switch
    var binaryIn = document.querySelector("#binary_in");
    binaryIn.onclick  = function(e){
      var val = e.path[0].getAttribute("data-val");
      if (!val) return;
      mot.triggerSense("Binary Switch", val);
    };


  // ternary switch
  var ternaryIn = document.querySelector("#ternary_in");
  ternaryIn.onclick  = function(e){
    var val = e.path[0].getAttribute("data-val");
    if (!val) return;
    mot.triggerSense("Ternary Switch", val);
  };


  // directional pad
  var dPad = document.querySelector("#directional_pad");
  dPad.onclick  = function(e){
    var val = e.path[0].getAttribute("data-val");
    if (!val) return;
    mot.triggerSense("Directional Pad", val);
  };


  // space button
  var sb = document.querySelector("#space_b");
  sb.onclick  = function(e){
    window.location.href = "/3d.html";
  };



  mot.init();


} // end init



var ignite = function(){
  var butt = document.getElementById("ignition");
  if (butt.getAttribute("data-state") == "OFF") {
    butt.setAttribute("data-state", "ON");
    butt.style.stroke = "#0f0";

    mot.start();
  } else {
    butt.setAttribute("data-state", "OFF");
    butt.style.stroke = "#f00";

    mot.stop();
  }
}
