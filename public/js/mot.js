







(function(mot) {

  // machine states
  const OFF = "Power Off";
  const ON = "Power On";
  const PAUSED = "Waiting";
  const AWAKE = "Running";
  const ASLEEP = "Sleeping";
  const IDLE = "Idle";
  const ALERT = "Attentive";

  var state = OFF;
  var reportState;

  var initialized = false;

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
  var knowledge = []; // all motes
  // experiences
  // memories

  var tQueue = []; //temporal motes









////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////







  mot.mot = function(sense, content) {

    this.sense = sense;

    this.content = content;

    this.echo = 0;

    this.lead = [];
    this.trail = [];

    this.start = performance.now();
    this.end = performance.now();

    return true;
  };



  mot.sense = function(name, hook) {

    this.name = name;
    this.hook = hook;
    this.kStates = []; // known states

    this.potentialRevisions = [];



    return true;
  };



  mot.self = function() {

    this.charge = 0;


    this.lead = 0;

// cadence (pace)

    this.content = 0;
    this.contentingFactors = [];

    return true;
  };


////////////////////////////////////////////////////////////////////






  function procSense(e) {
    var senseName = e.detail.sense;
    var content = e.detail.content;

    var sense = senses.find(function(sense){return sense.name == senseName});


    // add known state to sense
    var kState = sense.kStates.find(function(state){return state == content});
    if (!kState) sense.kStates.push(content);


    // build new mote
    var mote = new mot.mot(senseName, content);
    var prevMote;
    if (knowledge.length > 0) {
      prevMote = knowledge[knowledge.length - 1];
      mote.lead.push(prevMote);

      mot.self.lead = mote.start -  prevMote.start;
    } else {
      mot.self.lead = mote.start - start;
    }


    // find existing mote
    var exMote = knowledge.find(function(mot){if (mot.sense == mote.sense && mot.content == mote.content) return mot;});

    // commit new mote to knowledge
    if (exMote) {
      exMote.echo += 1;
      tQueue.push(exMote);
    } else {
      if (prevMote) prevMote.trail.push(mote);
      knowledge.push(mote);
      tQueue.push(mote);
    }

    report(content, false);
    // console.log(knowledge);
  };





	function run() {
		tNow = performance.now();
		dt = tNow - runTick;
		runTick = tNow;
		accum += dt;
	 	while(accum > ts) {
      clock += dt;


      // smarts

      if (mot.self.lead > 0) {
        mot.self.lead -= dt;
      }
      if (mot.self.lead <= 0) {
        mot.self.lead = 0;
        mot.self.charge = 1;
      }

      // console.log(mot.self.lead);

      if (mot.self.charge == 1 && tQueue.length > 0) {

        console.log(tQueue);
        while(tQueue.length > 0) {

          tQueue.shift();

        }

        var utter = "arf";
        report(utter, true);
        mot.self.charge = 0;
      }





      if (reportClock) mot.readClock();

			accum -= dt;
	  }
		raf = requestAnimationFrame(run);
	};





  ////////////////////////////////////////////////////////////////////


  mot.init = function(){
    // Sense listener
    document.addEventListener('sense', function(e) {
      procSense(e);
    });

    initialized = true;

    return true;
  }; // end mot.init



	mot.start = function() {
    if (!initialized) mot.init();

		runTick = performance.now();
		raf = requestAnimationFrame(run);
    setState(ON);
    setState(AWAKE);

    if (!start) start = performance.now();
    return true;
	};


  mot.stop = function() {
    cancelAnimationFrame(raf);

    setState(PAUSED);

    return true;
  };



  mot.setSense = function(name, hook) {
    var found = senses.findIndex(function(key){return key.name == name})
    // senses.filter(function(key) { return key.name === name; });

    if (found == -1) {
      var newSense = new mot.sense(name, hook);
      senses.push(newSense);
    }

    return true;
  };



  mot.triggerSense = function(sense, val) {
    // var start = performance.now();
    if (state == PAUSED || state == OFF) return false;
    // Create the event
    var event = new CustomEvent('sense', { "detail" : {"sense":sense, "content":val} });
    // Fire the event
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
    var $t = document.getElementById(reportClock);
    $t.innerHTML = dateObjFormatter(clock);
    return clock;
  };





  //////////////////////////////////////////////////////////////////


  function report(msg, self) {
    var $c = document.getElementById("mot_out");
    if (!$c) {
      console.log(msg);
      return false;
    } else {
      if (!msg) msg = "_";
      var $i = document.createElement("div");
      $i.setAttribute("class", "mo_item");
      if (!self) {
        $i.setAttribute("class", "mi_left");
        msg = "t/s> " + msg;
      }
      $i.append(msg);
      $c.prepend($i);
      $c.scrollTop = 0;
    }
    return true;
  };



  function setState(p) {
    state = p;
    if (reportState) mot.readState();
    return state;
  };



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
