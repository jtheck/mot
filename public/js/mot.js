







(function(mot) {

  // machine states
  const ON = "Power On";
  const OFF = "Power Off";
  const SLEEP = "Sleeping";
  const PAUSED = "Waiting";
  const IDLE = "Idle";
  const AWAKE = "Running";
  const ALERT = "Attentive";

  var state = OFF;
  var reportState;


  // timing
  var fps = 30;
  var ts = 1000 / fps; // timestep
  var runTick = null;
  var tNow = null;
  var accum = 0; // accumulator
  var dt = 0; // delta time
  var raf;

  var requestAnimationFrame = window.requestAnimationFrame || window.mozRequestAnimationFrame ||
                        window.webkitRequestAnimationFrame || window.msRequestAnimationFrame;
  var cancelAnimationFrame = window.cancelAnimationFrame || window.mozCancelAnimationFrame;

  var start = false;
  var clock = 0;
  var reportClock;


  // stores
  var senses = [];
  var knowledge = [];



  mot.self = self();







///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////







  mot.mot = function(content, start) {

    this.content = content;

    this.beginning = start;
    this.end = performance.now();

    return true;
  };



  mot.sense = function(name, hook) {

    this.name = name;
    this.hook = hook;
    this.knownStates = [];

    this.listening = false;

    return true;
  };





  //////////////////////////////////////////////////////////





  mot.setSense = function(name, hook) {
    var found = senses.findIndex(function(key){return key.name == name})
    // senses.filter(function(key) { return key.name === name; });

    if (found == -1) {
      var newSense = new mot.sense(name, hook);
      senses.push(newSense);
    }

    return true;
  };



  mot.init = function(){

    // create event listeners
    for (var i=0;  i<senses.length;  i++) {
      tSense = senses[i];

      // Skip if already listening
      if (tSense.listening == true) continue;

      // Add an event listener
      document.addEventListener(tSense.name, function(e) {
        var mote = new mot.mot(e.detail.content, e.detail.start);

        knowledge.push(mote);

        console.log(knowledge);
      });

      tSense.listening = true;

    }

    console.log(senses);

    return true;
  }; // end mot.init




	function run() {
		tNow = performance.now();
		dt = tNow - runTick;
		runTick = tNow;
		accum += dt;
	 	while(accum > ts) {
      clock += dt;


      // smarts









      if (reportClock) mot.readClock();

			accum -= dt;
	  }
		raf = requestAnimationFrame(run);
	};










	mot.start = function() {
		runTick = performance.now();
		raf = requestAnimationFrame(run);
    setState(ON);

    mot.init();

    if (!start) start = performance.now();
    return true;
	};


  mot.stop = function() {
    cancelAnimationFrame(raf);

    setState(PAUSED);
    return true;
  };




  mot.trigger = function(sense, val) {
    var start = performance.now();
    if (state == PAUSED) return false;
    // Create the event
    var event = new CustomEvent(sense, { "detail" : {"content":val, "start":start} });
    // Dispatch/Trigger/Fire the event
    document.dispatchEvent(event);
    return true;
  }




  mot.readState = function(id) {
    if (!id && !reportState) return state;
    if (!reportState) reportState = id;
    // output
    var t = document.getElementById(reportState);
    t.innerHTML = state;
    return state;
  };



  mot.readClock = function(id) {
    if (!id && !reportClock) return clock;
    if (!reportClock) reportClock = id;
    // output
    var t = document.getElementById(reportClock);
    t.innerHTML = dateObjFormatter(clock);
    return clock;
  };





  ///////////////////////////////////////////////





  function setState(p) {
    state = p;
    if (reportState) mot.readState();
    return state;
  };


  function self() {
    return true;
  }



  function dateObjFormatter(ms) {
    var date = new Date(ms);

    var hh = date.getUTCHours();
    var mm = date.getUTCMinutes();
    var ss = date.getUTCSeconds();
    var ms = date.getUTCMilliseconds();

    // maintain constant width
    if (hh < 10) {hh = '0' + hh}
    if (mm < 10) {mm = '0' + mm}
    if (ss < 10) {ss = '0' + ss}
    if (ms < 10) {ms = '0' + ms}
    if (ms < 100) {ms = '0' + ms}

    return hh + ':' + mm + ':' + ss + ":" + ms;
  };


}(window.mot = window.mot || {}));
