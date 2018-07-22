

var moe = window.MOT;
var init = function() {


  moe.readState("state");
  moe.readClock("clock");


  moe.setSense("Range Slider", "range_ui");
  moe.setSense("Binary Switch", "binary_ui");
  moe.setSense("Ternary Switch", "switch_ui");
  moe.setSense("Directional Pad", "directional_pad");
  moe.setSense("Text Input", "text_out");



  var chat = GETFIRE({topicName: "mot moe", startOpen: true, fullHeight: false, devMode: false});


  var powerIcon = '<svg xmlns="http://www.w3.org/2000/svg" version="1.2" baseProfile="tiny" x="0" y="0" width="100%" height="100%" viewBox="-0.8 -0.5 177 202" xml:space="preserve">  <path fill="none" stroke-width="30" stroke-linecap="round" d="M33.7 64.3C22.1 77.2 15 94.3 15 113c0 40.1 32.5 72.7 72.7 72.7 40.1 0 72.7-32.5 72.7-72.7 0-18.7-7.1-35.8-18.7-48.7"/>  <line fill="none" stroke-width="30" stroke-linecap="round" x1="87.8" y1="15" x2="87.8" y2="113"/></svg>';
  var $ignition_switch = document.querySelector("#ignition");
  $ignition_switch.innerHTML = powerIcon;


  // text input
  var textIn = document.querySelector("#text_in");
  textIn.addEventListener("submit", function(e) {
    var val = textIn.elements.notion.value.replace(/\r?\n|\r/g,'');
    var mot={sense: "Text Input", source: "bobby", content: val};
    moe.triggerSense(mot);

    textIn.elements.notion.value = "";

    e.preventDefault();
  });
  textIn.addEventListener("keyup", function(e) {
    if (e.key === "Enter") {
      var val = textIn.elements.notion.value.replace(/\r?\n|\r/g,'');
      var mot={sense: "Text Inpugt", source: "bobby", content: val};
      moe.triggerSense(mot);

      textIn.elements.notion.value = "";
    }
  });



  // range slider
  var sliderIn = document.querySelector("#slider_in");
  sliderIn.onchange  = function(){
    var mot={sense: "Range Slider", source: "bobby", content: this.value};
    moe.triggerSense(mot);
  };


    // binary switch
    var binaryIn = document.querySelector("#binary_in");
    binaryIn.onclick  = function(e){
      var val = e.path[0].getAttribute("data-val");
      if (!val) return;
      var mot={sense: "Binary Switch", source: "bobby", content: val};
      moe.triggerSense(mot);
    };


  // ternary switch
  var ternaryIn = document.querySelector("#ternary_in");
  ternaryIn.onclick  = function(e){
    var val = e.path[0].getAttribute("data-val");
    if (!val) return;
    var mot={sense: "Ternary Switch", source: "bobby", content: val};
    moe.triggerSense(mot);
  };


  // directional pad
  var dPad = document.querySelector("#directional_pad");
  dPad.onclick  = function(e){
    var val = e.path[0].getAttribute("data-val");
    if (!val) return;
    var mot={sense: "Directional Pad", source: "bobby", content: val};
    moe.triggerSense(mot);
  };


  // space button
  var sb = document.querySelector("#space_b");
  sb.onclick  = function(e){
    window.location.href = "/3d.html";
  };



  moe.init();


} // end init



var ignite = function(){
  var butt = document.getElementById("ignition");
  if (butt.getAttribute("data-state") == "OFF") {
    butt.setAttribute("data-state", "ON");
    butt.style.stroke = "#0f0";

    moe.start();
  } else {
    butt.setAttribute("data-state", "OFF");
    butt.style.stroke = "#f00";

    moe.stop();
  }
}
