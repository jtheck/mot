


var init = function() {

  mot.readState("state");
  mot.readClock("clock");


  mot.setSense("Range Slider", "range_ui");
  mot.setSense("Ternary Switch", "switch_ui");
  mot.setSense("Text Input", "text_out");



  // text input
  var textIn = document.querySelector("#text_in");
  textIn.addEventListener("submit", function(e) {
    var val = textIn.elements.notion.value;

    mot.triggerSense("Text Input", val);

    textIn.elements.notion.value = "";

    e.preventDefault();
  });


  // range slider
  var sliderIn = document.querySelector("#slider_in");
  sliderIn.onchange  = function(){
    mot.triggerSense("Range Slider", this.value);
  };


  // trinary switch
  var ternaryIn = document.querySelector("#ternary_in");
  ternaryIn.onclick  = function(e){
    var val = e.path[0].getAttribute("data-val");
    if (!val) return;
    mot.triggerSense("Ternary Switch", val);
  };

  mot.init();

} // end init



var ignite = function(){
  var butt = document.getElementById("ignition");
  if (butt.getAttribute("data-state") == "OFF") {
    butt.setAttribute("data-state", "ON");
    butt.innerHTML = "<b>꡷</b>&nbsp;▶";
    butt.style.backgroundColor = "red";

    mot.start();
  } else {
    butt.setAttribute("data-state", "OFF");
    butt.innerHTML = "<b>꡷</b>&nbsp;▶";
    butt.style.backgroundColor = "#0d0";

    mot.stop();
  }
}
