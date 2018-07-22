







(function(MOT) {


  // machine states
  const OFF = "Power Off";
  const ON = "Power On";
  const PAUSED = "Waiting";
  const AWAKE = "Running";
  const ALERT = "Attentive";
  const ASLEEP = "Sleeping";
  const DREAM = "Dreaming";
  const IDLE = "Idle";

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

  // special stores
  var senses = [];
  // sensibilities

  // mot stores
  var motes = [];
  // utterances
  // exchanges
  // concepts
  // works

  // entity stores
  var entities= [];
  // individuals
  // collectives



  var tQueue = []; //temporal motes









////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////







  MOT.mot = function(sense, content) {
    this.start = performance.now();

    this.sense = sense;

    this.content = content;

    this.echo = 0;

    this.lead = []; // preceding motes
    this.trail = []; // following motes


    this.source = MOT.entity(); // origin (single entity, potentially a collective or individual
    this.target = []; // intended audience (zero to many entities)

    this.end = performance.now();
    return this;
  };



  MOT.sense = function(name, hook) {

    this.name = name;
    this.hook = hook;
    this.kStates = []; // known states

    this.potentialRevisions = [];



    return true;
  };

  MOT.entity = function() {

    this.motes = []; // motes of source == this

    this.name = "user";
    this.aliases = [];


    return true;
  };

  // a special entity
  MOT.self = function() {

    this.charge = 0;


    this.lead = 0;

// cadence (pace)

    this.content = 0;
    this.contentingFactors = [];

    return true;
  };


////////////////////////////////////////////////////////////////////





// TODO: send to percept() then intuit() then act()
  function procSense(e) {
    var mot = e.detail;
    var senseName = mot.sense;
    var content = mot.content;
    var sense = senses.find(function(sense){return sense.name == senseName});
    // var source = entity

    // add known state to sense
    var kState = sense.kStates.find(function(state){return state == content});
    if (!kState) sense.kStates.push(content);


    // build new mote (percept)
    // mot.source =
    mot = new MOT.mot(mot);
    console.log(mot);
    var prevMot;
    if (motes.length > 0) {
      prevMot = motes[motes.length - 1];
      mot.lead.push(prevMot);

      mot.lead = mot.start -  prevMot.start;
    } else {
      mot.lead = mot.start - start;
    }


    // find existing mote
    var exMot = motes.find(function(mote){if (mote.sense == mot.sense && mote.content == mot.content) return mote;});

    // commit new mote to motes
    if (exMot) {
      exMot.echo += 1;
      tQueue.push(exMot);
    } else {
      if (prevMot) prevMot.trail.push(mot);
      motes.push(mot);
      tQueue.push(mot);
    }

    report(content, false);
    return true;
    // console.log(motes);
  }; // end procSense





	function run() {
		tNow = performance.now();
		dt = tNow - runTick;
		runTick = tNow;
		accum += dt;
	 	while(accum > ts) {
      clock += dt;


      // smarts

      if (MOT.self.lead > 0) {
        MOT.self.lead -= dt;
      }
      if (MOT.self.lead <= 0) {
        MOT.self.lead = 0;
        MOT.self.charge = 1;
      }

      console.log(MOT.self.lead);

      if (MOT.self.charge == 1 && tQueue.length > 0) {

        console.log(tQueue);
        while(tQueue.length > 0) {

          tQueue.shift();

        }

        var utter = "arf";
var utterance = function() {
var utter = "aroo";
  return utter;
};

        report(utterance, true);
        MOT.self.charge = 0;
      }




      // check percept queue
      // intuit
      // act (from queue)




      if (reportClock) MOT.readClock();

			accum -= dt;
	  }
		raf = requestAnimationFrame(run);
	}; // end run





  ////////////////////////////////////////////////////////////////////


  MOT.init = function(){
    // Sense listener
    document.addEventListener('sense', function(e) {
      procSense(e);
    });

    initialized = true;

    return true;
  }; // end MOT.init



	MOT.start = function() {
    if (!initialized) MOT.init();

		runTick = performance.now();
		raf = requestAnimationFrame(run);
    setState(ON);
    setState(AWAKE);

    if (!start) start = performance.now();
    return true;
	};


  MOT.stop = function() {
    cancelAnimationFrame(raf);

    setState(PAUSED);

    return true;
  };



  MOT.setSense = function(name, hook) {
    var found = senses.findIndex(function(key){return key.name == name})
    // senses.filter(function(key) { return key.name === name; });

    if (found == -1) {
      var newSense = new MOT.sense(name, hook);
      senses.push(newSense);
    }

    return true;
  };



  MOT.triggerSense = function(mot) {
    // var start = performance.now();
    if (state == PAUSED || state == OFF) return false;
    // Create the event
    var event = new CustomEvent('sense', { "detail" : mot });
    // Fire the event
    document.dispatchEvent(event);
    // add source
    return true;
  }



  MOT.readState = function(id) {
    if (!id && !reportState) return state;
    if (!reportState) reportState = id;
    // output
    var t = document.getElementById(reportState);
    t.innerHTML = state;
    return state;
  };



  MOT.readClock = function(id) {
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
    if (reportState) MOT.readState();
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


}(window.MOT = window.MOT || {}));
