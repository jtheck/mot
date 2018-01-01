







(function(mot) {

  const ON = "Power On";
  const PAUSED = "Waiting";
  const AWAKE = "Running";
  const IDLE = "Idle";
  const ALERT = "Attentive";
  const SLEEP = "Sleeping";


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


  var state = ON;
  var reportState;

  var start;
  var clock = 0;
  var reportClock;



  var knowledge = [];

  var senses = [];


  mot.self = self();







///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////







  mot.mot = function() {

    this.start = performance.now();
    this.end = 0;



    return true;
  };



  mot.sense = function(name, hook, states) {

    this.name = name;
    this.hook = hook;
    this.kStates = [];


    return true;
  };


  mot.getSense = function(name, hook, states) {
    var found = senses.findIndex(function(key){return key.name == name})
    // senses.filter(function(key) { return key.name === name; });

    if (found == -1) {
      var newSense = new mot.sense(name, hook, states);
      senses.push(newSense);
    }

    return true;

  };


  mot.get = function(wat) {

    var hrm = new mot.mot();

    knowledge.push(hrm);

    // console.log(knowledge[knowledge.length-1].start);
    // console.log(senses);

    return true;
  };











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
    setState(AWAKE);
    if (!start) start = performance.now();
    return true;
	};

  mot.stop = function() {
    cancelAnimationFrame(raf);
    setState(PAUSED);
    return true;
  };



  mot.readState = function(id) {
    if (!id && !reportState) return state;
    if (!reportState) reportState = id;
    // output
    var t = document.getElementById(reportState);
    t.innerHTML = state;
    return state;
  };

  function setState(p) {
    state = p;
    if (reportState) mot.readState();
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




  function self() {
    return true;
  }







///////////////////////////////////////////////




  function dateObjFormatter(ms) {
    var date = new Date(ms);

    var hh = date.getUTCHours();
    var mm = date.getUTCMinutes();
    var ss = date.getSeconds();

    if (hh < 10) {hh = '0' + hh}
    if (mm < 10) {mm = '0' + mm}
    if (ss < 10) {ss = '0' + ss}

    return hh + ':' + mm + ':' + ss;
  };


}(window.mot = window.mot || {}));
