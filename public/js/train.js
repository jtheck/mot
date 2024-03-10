




var moe = window.MOT;
var joe = window.MOT;




var initTraining = function() {

  let header = $id('header');
  let p_home = $id('page_home');
  let p_repo = $id('page_repository');
  let p_train = $id('page_training');
  let p_help = $id('page_help');

  header.onclick = function(e){
      switch(e.target.id){
      case 'b_home':
          p_home.style.display = 'block';
          p_train.style.display = 'none';
          p_repo.style.display = 'none';
          p_help.style.display = 'none';
      break;
      case 'b_repo':
          p_repo.style.display = 'block';
          p_home.style.display = 'none';
          p_train.style.display = 'none';
          p_help.style.display = 'none';
      break;
      case 'b_train':
          p_train.style.display = 'block';
          p_home.style.display = 'none';
          p_repo.style.display = 'none';
          p_help.style.display = 'none';
      break;
      case 'b_help':
          p_help.style.display = 'block';
          p_home.style.display = 'none';
          p_train.style.display = 'none';
          p_repo.style.display = 'none';
      break;
      }
  }


  moe.readState("state");
  moe.readClock("clock");


  moe.setSense("Range Slider", "range_ui");
  moe.setSense("Binary Switch", "binary_ui");
  moe.setSense("Ternary Switch", "switch_ui");
  moe.setSense("Directional Pad", "directional_pad");
  moe.setSense("Symbol Set", "symbol_set");
  moe.setSense("Text Input", "text_out");


  // joe.setSense("Text Input", "text_out");


  // onKeydown(e) {
  //   const { toggleSidebar, next, previous } = this.props;

  //   const keyMapping = new Map([
  //     [ 83, toggleSidebar ],  // user presses the s button
  //     [ 37, next          ],  // user presses the right arrow
  //     [ 39, previous      ]   // user presses the left arrow
  //   ]);

  //   if (keyMapping.has(e.which)) {
  //     e.preventDefault();
  //     keyMapping.get(e.which)();
  //   }
  // }

    
  // Check compatibility for the browser we're running this in
  if ("serviceWorker" in navigator) {
    if (navigator.serviceWorker.controller) {
      console.log("sw active service worker found, no need to register");
    } else {
      // Register the service worker
      navigator.serviceWorker
        .register("sw-momo.js", {
          scope: "./"
        })
        .then(function (reg) {
          console.log("sw Service worker has been registered for scope: " + reg.scope);
        });
    }
  }
  


  var powerIcon = '<svg xmlns="http://www.w3.org/2000/svg" version="1.2" baseProfile="tiny" x="0" y="0" width="100%" height="100%" viewBox="-0.8 -0.5 177 202" xml:space="preserve">  <path fill="none" stroke-width="30" stroke-linecap="round" d="M33.7 64.3C22.1 77.2 15 94.3 15 113c0 40.1 32.5 72.7 72.7 72.7 40.1 0 72.7-32.5 72.7-72.7 0-18.7-7.1-35.8-18.7-48.7"/>  <line fill="none" stroke-width="30" stroke-linecap="round" x1="87.8" y1="15" x2="87.8" y2="113"/></svg>';
  var $ignition_switch = document.querySelector("#ignition");
  $ignition_switch.innerHTML = powerIcon;


  // text input
  var textIn = document.querySelector("#text_in");
  textIn.addEventListener("submit", function(e) {
    var val = textIn.elements.notion.value.replace(/\r?\n|\r/g,'');
    var percept = {sense: "Text Input", source: "bobby", content: val};
    moe.triggerSense(percept);
    // joe.triggerSense(percept);








    textIn.elements.notion.value = "";

    e.preventDefault();
  });
  textIn.addEventListener("keyup", function(e) {
    if (e.key === "Enter") {
      var submit = document.querySelector("#text_submit");
      submit.click();

    // textIn.submit();
    // e.preventDefault();
    // alert("barf");
    //   var val = textIn.elements.notion.value.replace(/\r?\n|\r/g,'');
    //   var percept = {sense: "Text Inpugt", source: "bobby", content: val};
    //   moe.triggerSense(percept);
    //
    //   textIn.elements.notion.value = "";
    }
  });




  // SENSES

  // range slider
  var sliderIn = document.querySelector("#slider_in");
  sliderIn.onchange  = function(){
    var percept = {sense: "Range Slider", source: "bobby", content: this.value};
    moe.triggerSense(percept);
  };


  // binary switch
  var binaryIn = document.querySelector("#binary_in");
  binaryIn.onclick  = function(e){
    var val = e.path[0].getAttribute("data-val");
    if (!val) return;
    var percept = {sense: "Binary Switch", source: "bobby", content: val};
    moe.triggerSense(percept);
  };


  // ternary switch
  var ternaryIn = document.querySelector("#ternary_in");
  ternaryIn.onclick  = function(e){
    var val = e.path[0].getAttribute("data-val");
    if (!val) return;
    var percept = {sense: "Ternary Switch", source: "bobby", content: val};
    moe.triggerSense(percept);
  };


  // directional pad
  var dPad = document.querySelector("#directional_pad");
  dPad.onclick  = function(e){
    var val = e.path[0].getAttribute("data-val");
    if (!val) return;
    var percept = {sense: "Directional Pad", source: "bobby", content: val};
    moe.triggerSense(percept);
  };


  // symbol set
  var symSet = document.querySelector("#symbol_set");
  symSet.onclick  = function(e)
  {
    // console.log(e)
    var val = e.path[0].getAttribute("data-val");
    if (!val) return;
    var percept = {sense: "Symbol Set", source: "bobby", content: val};
    moe.triggerSense(percept);
  };


  // space button
  var sb = document.querySelector("#space_b");
  sb.onclick  = function(e){
    window.location.href = "/3d.html";
  };



  moe.init();


} // end init




function $id(id) {
return document.querySelector("#"+id);
}


var pokeMot = function(){
var xhr = new XMLHttpRequest();
// xhr.open("GET", "http://192.168.2.3/boop");
xhr.open("POST", "http://192.168.2.3/boop");
let data = '{x:"yz", 1:23}';
xhr.send(data);
xhr.onload = function(e){
    const data = JSON.parse(xhr.responseText);
    // alert(xhr.status)
    console.log(data);
}
xhr.onerror = function(e){
    alert('its bad');
    console.log(e);
}
}

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
  